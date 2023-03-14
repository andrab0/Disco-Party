#version 330

// Input
in vec2 texcoord;

// Uniform properties
uniform sampler2D texture_1;

// TODO(student): Declare various other uniforms
uniform float rotation;

// Output
layout(location = 0) out vec4 out_color;


void main()
{
    vec2 rotatedTexture = vec2(texcoord.x + rotation, texcoord.y);

    vec4 color1 = texture2D(texture_1, rotatedTexture);

    vec4 color;
    color = color1;


    out_color = color;
}