#version 330

// Input
in vec3 world_position;
in vec3 world_normal;
in vec2 texcoord;


// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

vec3 V;
vec3 N;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform vec3 object_color;
uniform vec3 pozitiiSpot_location[4];
uniform vec3 culoriSpot_location[4];
uniform vec3 directiiSpot_location[4];

uniform vec3 disco_ball_position;
uniform sampler2D texture_1;
uniform float rotation;
uniform int luminaGlob_location;



// Output
layout(location = 0) out vec4 out_color;


vec3 GlobLightContribution(vec3 lightPos, vec3 lightColor)
{
    vec3 color = vec3(0, 0, 0);
    vec3 diffuse_light = vec3(0, 0, 0);
    vec3 specular_light = vec3(0, 0, 0);

    vec3 L = normalize(lightPos - world_position);
    vec3 R = normalize(reflect(-L, N));

    diffuse_light = lightColor * max(dot(N, L), 0);

    if (dot(N, L) > 0)
    {
        specular_light = lightColor * pow(max(dot(V, R), 0), material_shininess);
    }

    float att1 = 0.0f;
    float att2 = 0.0f;

    float dist = distance(world_position, lightPos);
    if (dist < 5) {
        att1 = pow(5 - dist, 2);
    }

    if (dist < 3.5) {
        att2 = pow(3.5 - dist, 2);
    }

    color = att1 * specular_light + att2 * diffuse_light;

    return color;
}

vec3 SpotlightContribution(vec3 lightPos, vec3 lightColor, vec3 lightDirection)
{
    vec3 light = vec3(0, 0, 0);
    vec3 diffuse_light = vec3(0, 0, 0);
    vec3 specular_light = vec3(0, 0, 0);

    vec3 L = normalize(lightPos - world_position);
    vec3 R = normalize(reflect(-L, N));

    diffuse_light = lightColor * max(dot(N, L), 0);

    if (dot(N, L) > 0)
    {
        specular_light = lightColor * pow(max(dot(V, R), 0), material_shininess);
    }

    float att1 = 0.0f;
    float att2 = 0.0f;

    float dist = distance(world_position, lightPos);
    if (dist < 0.5) {
        att1 = pow(0.5 - dist, 2);
    }

    if (dist < 1.5) {
        att2 = pow(1.5 - dist, 2);
    }

    float cut_off = radians(15);
    float spot_light = dot(-L, lightDirection);
    float spot_light_limit = cos(cut_off);

    float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
    float light_att_factor = pow(linear_att, 2);

    if (spot_light > spot_light_limit)
    {
        light = (light_att_factor + att2) * diffuse_light + (light_att_factor + att1) * specular_light;
    }

    return light;
}

void main()
{

    V = normalize(eye_position - world_position);
    N = normalize(world_normal);

    vec3 auxiliarSpotColorat = vec3(0, 0, 0);

    for (int i = 0; i < 4; i++) {
        auxiliarSpotColorat += SpotlightContribution(pozitiiSpot_location[i], culoriSpot_location[i], directiiSpot_location[i]);
    }

    // light_dir  este directia de iluminare
    vec3 light_dir = world_position - disco_ball_position;
 
    // texcoord este coordonata de textura utilizata pentru esantionare
    vec2 texcoord1;// = texcoord;
    texcoord1.x = (1.0 / (2 * 3.14159)) * atan (light_dir.x, light_dir.z);
    texcoord1.y = (1.0 / 3.14159) * acos (light_dir.y / length (light_dir));
 
    texcoord1.x += rotation;
    // color este culoarea corespunzatoare pozitiei world_position
    vec3 color_actuala = texture(texture_1, texcoord1).xyz;
    
    vec3 auxiliarCuloareGlob = vec3(0, 0, 0);
    if (luminaGlob_location > 0)
        auxiliarCuloareGlob = GlobLightContribution(disco_ball_position, color_actuala);

    out_color = vec4(object_color + auxiliarSpotColorat + auxiliarCuloareGlob, 1);
}
