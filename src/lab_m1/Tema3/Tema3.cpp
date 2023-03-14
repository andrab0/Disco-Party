#include "lab_m1/Tema3/Tema3.h"

#include <iostream>

using namespace std;
using namespace m1;

Tema3::Tema3()
{ 
}

Tema3::~Tema3()
{
}

void Tema3::Init()
{
    /*
    *     //  TE-AI INTREBAT VREODATA CUM E SA IEI SI ACID SI SPEED?
    // VARIANTA TURBO:
    {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                ringDans[i][j] = glm::vec3(0, 0, 0);
            }
        }

    }

    */

    {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                randR = (float)rand() / RAND_MAX;
                randG = (float)rand() / RAND_MAX;
                randB = (float)rand() / RAND_MAX;
                
                ringDans[i][j] = glm::vec3(randR, randG, randB);
                matriceCulori[i][j] = glm::vec3(i, 0.1, j);
            }
        }
    }

    // primul dansator
    {
        translateX1 = rand() % 8;
        translateZ1 = rand() % 8;
        posD1 = glm::vec3(translateX1, 0.1, translateZ1);
        translateZ1 = rand() % 8;
        pos1end = glm::vec3(translateX1, 0.1, translateZ1);

    // al doilea dansator
        translateX2 = rand() % 8;
        translateZ2 = rand() % 8;
        posD2 = glm::vec3(translateX2, 0.1, translateZ2);
        translateZ2 = rand() % 8;
        pos2end = glm::vec3(translateX2, 0.1, translateZ2);

    // al treilea dansator
        translateX3 = rand() % 8;
        translateZ3 = rand() % 8;
        posD3 = glm::vec3(translateX3, 0.1, translateZ3);
        translateZ3 = rand() % 8;
        pos3end = glm::vec3(translateX3, 0.1, translateZ3);

    // al 4lea dansator
        translateX4 = rand() % 8;
        translateZ4 = rand() % 8;
        posD4 = glm::vec3(translateX4, 0.1, translateZ4);
        translateZ4 = rand() % 8;
        pos4end = glm::vec3(translateX4, 0.1, translateZ4);

    // al 5lea dansator
        translateX5 = rand() % 8;
        translateZ5 = rand() % 8;
        posD5 = glm::vec3(translateX5, 0.1, translateZ5);
        translateZ5 = rand() % 8;
        pos5end = glm::vec3(translateX5, 0.1, translateZ5);
    }

    // spot-uri:
    {
        pozitieSpot[0] = glm::vec3(1, 5, 2);
        randR = (float)rand() / RAND_MAX;
        randG = (float)rand() / RAND_MAX;
        randB = (float)rand() / RAND_MAX;
        culoareSpot[0] = glm::vec3(randR, randG, randB);
        directieSpot[0] = glm::vec3(0, -1, 0);

        pozitieSpot[1] = glm::vec3(6, 5, 2);
        randR = (float)rand() / RAND_MAX;
        randG = (float)rand() / RAND_MAX;
        randB = (float)rand() / RAND_MAX;
        culoareSpot[1] = glm::vec3(randR, randG, randB);
        directieSpot[1] = glm::vec3(0, -1, 0);
  

        pozitieSpot[2] = glm::vec3(1, 5, 6);
        randR = (float)rand() / RAND_MAX;
        randG = (float)rand() / RAND_MAX;
        randB = (float)rand() / RAND_MAX;
        culoareSpot[2] = glm::vec3(randR, randG, randB);
        directieSpot[2] = glm::vec3(0, -1, 0);


        pozitieSpot[3] = glm::vec3(6, 5, 5);
        randR = (float)rand() / RAND_MAX;
        randG = (float)rand() / RAND_MAX;
        randB = (float)rand() / RAND_MAX;
        culoareSpot[3] = glm::vec3(randR, randG, randB);
        directieSpot[3] = glm::vec3(0, -1, 0);
    }

    // conuri:
    {
        vector<VertexFormat> vertices;
        vertices.push_back(VertexFormat(glm::vec3(0, 0, 0)));
        vertices.push_back(VertexFormat(glm::vec3(1, -1, 0)));
        for (int i = 1; i <= n - 2; i++) {
            vertices.push_back(VertexFormat(glm::vec3(cos(nr_grade_intre * i), -1, sin(nr_grade_intre * i))));
        }



        vector<unsigned int> indices;
        indices.push_back(0);
        for (int i = n - 1; i >= 1; i--) {
            indices.push_back(i);
        }
        indices.push_back(n - 1);



        meshes["con"] = new Mesh("generated cerc");
        meshes["con"]->SetDrawMode(GL_TRIANGLE_FAN);
        meshes["con"]->InitFromData(vertices, indices);
    }

    // randuri:
    {
        for (int i = 0; i < 4; i++) {
            dirAct[i] = rand() % 2;
            unghiStDr[i] = 0.0f;
            unghiSusJos[i] = 0.0f;
            directii[i] = 1.f;
        }
    }

    {
        luminaPodea = 1;
        luminaSpotlight = 1;
        luminaGlob = 1;
    }
    
    {
        mapTextures["random"] = CreateRandomTexture(16, 16);
    }

    {
		Mesh* mesh = new Mesh("plane");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // glob:
    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // textura glob:

    // Create a shader program for drawing face polygon with the color of the normal
    {
        Shader* shader = new Shader("Tema3Shader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "FragmentShaderRingDans.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    {
        Shader* shader1 = new Shader("Tema3ShaderPereti");
        shader1->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader1->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "FragmentShaderPereti.glsl"), GL_FRAGMENT_SHADER);
        shader1->CreateAndLink();
        shaders[shader1->GetName()] = shader1;
    }

    {
        Shader* shader2 = new Shader("Tema3ShaderDansatori");
        shader2->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader2->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "FragmentShaderDansatori.glsl"), GL_FRAGMENT_SHADER);
        shader2->CreateAndLink();
        shaders[shader2->GetName()] = shader2;
    }

    {
        Shader* shader3 = new Shader("Tema3ShaderConuri");
        shader3->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader3->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "FragmentShaderSpot.glsl"), GL_FRAGMENT_SHADER);
        shader3->CreateAndLink();
        shaders[shader3->GetName()] = shader3;
    }

    {
        Shader* shader4 = new Shader("Tema3ShaderGlob");
        shader4->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader4->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "FragmentShaderGlob.glsl"), GL_FRAGMENT_SHADER);
        shader4->CreateAndLink();
        shaders[shader4->GetName()] = shader4;
    }

    // Light & material properties
    {
        lightPosition = glm::vec3(0, 1, 1);
        lightDirection = glm::vec3(0, -1, 0);
        materialShininess = 30;
        materialKd = 0.5;
        materialKs = 0.5;
    }
}

void Tema3::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// Sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema3::Update(float deltaTimeSeconds)
{
	/*// TO COMPLETE  VARIANTA TURBO NEBUNA:
    {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, glm::vec3(i, 0.1, j));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.02f));
                float randR = (float)rand() / RAND_MAX;
                float randG = (float)rand() / RAND_MAX;
                float randB = (float)rand() / RAND_MAX;
                ringDans[i][j] = glm::vec3(randR, randG, randB);

                RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, ringDans[i][j]);
            }
        }
    }*/

    // tavan:
    {
        
    }

    // podea:
    {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, glm::vec3(i, 0.1, j));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.02f));

                RenderSimpleMesh(meshes["plane"], shaders["Tema3Shader"], modelMatrix, ringDans[i][j], luminaGlob, mapTextures["random"]);

                modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, glm::vec3(i, 5, j));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.02f));

                RenderSimpleMesh(meshes["plane"], shaders["Tema3Shader"], modelMatrix, glm::vec3(0,0,0), luminaGlob, mapTextures["random"]);
            }
        }
    }

    // pereti:
    {
        for (int i = 0; i < 8; i++) {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-1, 1, i));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 8, 1));
            RenderSimpleMeshPerete(meshes["box"], shaders["Tema3ShaderPereti"], modelMatrix, glm::vec3(0, 0, 0), 0, i, luminaPodea, luminaSpotlight, luminaGlob, mapTextures["random"]);

            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(i, 1, 8));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 8, 1));
            RenderSimpleMeshPerete(meshes["box"], shaders["Tema3ShaderPereti"], modelMatrix, glm::vec3(0, 0, 0), i, 7, luminaPodea, luminaSpotlight, luminaGlob, mapTextures["random"]);

            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(8, 1, i));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 8, 1));
            RenderSimpleMeshPerete(meshes["box"], shaders["Tema3ShaderPereti"], modelMatrix, glm::vec3(0, 0, 0), 7, i, luminaPodea, luminaSpotlight, luminaGlob, mapTextures["random"]);

            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(i, 1, -1));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 8, 1));
            RenderSimpleMeshPerete(meshes["box"], shaders["Tema3ShaderPereti"], modelMatrix, glm::vec3(0, 0, 0), i, 0, luminaPodea, luminaSpotlight, luminaGlob, mapTextures["random"]);
        }
    }

    // dansatori:
    {
        // dansator 1:
        delta1 = pos1end - posD1;

        // miscare orizontala pe Z:
        zPas = (float)delta1.z / 10;

        if (abs(zPas) >= 0.1f) {
            glm::vec3 pos1nou = MiscareDansatorOrizontal(deltaTimeSeconds, posD1, zPas);
            posD1 = pos1nou;
                
        }
        else {
            pos1end.z = rand() % 8;
            delta1 = pos1end - posD1;
        }

        // miscare verticala pe X:
        xPas = (float)delta1.x / 10;

        if (abs(xPas) >= 0.1f) {
            glm::vec3 pos1nou = MiscareDansatorVertical(deltaTimeSeconds, posD1, xPas);
            posD1 = pos1nou;
        }
        else {
            pos1end.x = rand() % 8;
        }

        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, posD1);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 3, 0.5f));

        RenderSimpleMeshDansator(meshes["box"], shaders["Tema3ShaderDansatori"], modelMatrix, glm::vec3(0, 0, 0), posD1, luminaPodea, luminaSpotlight, luminaGlob, mapTextures["random"]);
       // RenderSimpleMesh(meshes["box"], shaders["Tema3Shader"], modelMatrix, glm::vec3(0, 0, 0));

        // dansator 2:
        delta2 = pos2end - posD2;

        // miscare orizontala pe Z:
        zPas = (float)delta2.z / 10;

        if (abs(zPas) >= 0.1f) {
            glm::vec3 pos2nou = MiscareDansatorOrizontal(deltaTimeSeconds, posD2, zPas);
            posD2 = pos2nou;

        }
        else {
            pos2end.z = rand() % 8;
            delta2 = pos2end - posD2;
        }

        // miscare verticala pe X:
        xPas = (float)delta2.x / 10;

        if (abs(xPas) >= 0.1f) {
            glm::vec3 pos2nou = MiscareDansatorVertical(deltaTimeSeconds, posD2, xPas);
            posD2 = pos2nou;
        }
        else {
            pos2end.x = rand() % 8;
        }

        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, posD2);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 3, 0.5f));

        RenderSimpleMeshDansator(meshes["box"], shaders["Tema3ShaderDansatori"], modelMatrix, glm::vec3(0, 0, 0), posD2, luminaPodea, luminaSpotlight, luminaGlob, mapTextures["random"]);
       // RenderSimpleMesh(meshes["box"], shaders["Tema3Shader"], modelMatrix, glm::vec3(0, 0, 0));

        // dansator 3:
        delta3 = pos3end - posD3;

// miscare orizontala pe Z:
zPas = (float)delta3.z / 10;

if (abs(zPas) >= 0.1f) {
    glm::vec3 pos3nou = MiscareDansatorOrizontal(deltaTimeSeconds, posD3, zPas);
    posD3 = pos3nou;

}
else {
    pos3end.z = rand() % 8;
    delta3 = pos3end - posD3;
}

// miscare verticala pe X:
xPas = (float)delta3.x / 10;

if (abs(xPas) >= 0.1f) {
    glm::vec3 pos3nou = MiscareDansatorVertical(deltaTimeSeconds, posD3, xPas);
    posD3 = pos3nou;
}
else {
    pos3end.x = rand() % 8;
}

modelMatrix = glm::mat4(1);
modelMatrix = glm::translate(modelMatrix, posD3);
modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 3, 0.5f));
RenderSimpleMeshDansator(meshes["box"], shaders["Tema3ShaderDansatori"], modelMatrix, glm::vec3(0, 0, 0), posD3, luminaPodea, luminaSpotlight, luminaGlob, mapTextures["random"]);
//  RenderSimpleMesh(meshes["box"], shaders["Tema3Shader"], modelMatrix, glm::vec3(0, 0, 0));

  // dansator 4:
delta4 = pos4end - posD4;

// miscare orizontala pe Z:
zPas = (float)delta4.z / 10;

if (abs(zPas) >= 0.1f) {
    glm::vec3 pos4nou = MiscareDansatorOrizontal(deltaTimeSeconds, posD4, zPas);
    posD4 = pos4nou;

}
else {
    pos4end.z = rand() % 8;
    delta4 = pos4end - posD4;
}

// miscare verticala pe X:
xPas = (float)delta4.x / 10;

if (abs(xPas) >= 0.1f) {
    glm::vec3 pos4nou = MiscareDansatorVertical(deltaTimeSeconds, posD4, xPas);
    posD4 = pos4nou;
}
else {
    pos4end.x = rand() % 8;
}

modelMatrix = glm::mat4(1);
modelMatrix = glm::translate(modelMatrix, posD4);
modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 3, 0.5f));
RenderSimpleMeshDansator(meshes["box"], shaders["Tema3ShaderDansatori"], modelMatrix, glm::vec3(0, 0, 0), posD4, luminaPodea, luminaSpotlight, luminaGlob, mapTextures["random"]);

// RenderSimpleMesh(meshes["box"], shaders["Tema3Shader"], modelMatrix, glm::vec3(0, 0, 0));

 // dansator 5:
delta5 = pos5end - posD5;

// miscare orizontala pe Z:
zPas = (float)delta5.z / 10;

if (abs(zPas) >= 0.1f) {
    glm::vec3 pos5nou = MiscareDansatorOrizontal(deltaTimeSeconds, posD5, zPas);
    posD5 = pos5nou;

}
else {
    pos5end.z = rand() % 8;
    delta5 = pos5end - posD5;
}

// miscare verticala pe X:
xPas = (float)delta5.x / 10;

if (abs(xPas) >= 0.1f) {
    glm::vec3 pos5nou = MiscareDansatorVertical(deltaTimeSeconds, posD5, xPas);
    posD5 = pos5nou;
}
else {
    pos5end.x = rand() % 8;
}

modelMatrix = glm::mat4(1);
modelMatrix = glm::translate(modelMatrix, posD5);
modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 3, 0.5f));
RenderSimpleMeshDansator(meshes["box"], shaders["Tema3ShaderDansatori"], modelMatrix, glm::vec3(0, 0, 0), posD5, luminaPodea, luminaSpotlight, luminaGlob, mapTextures["random"]);

// RenderSimpleMesh(meshes["box"], shaders["Tema3Shader"], modelMatrix, glm::vec3(0, 0, 0));
    }

    // glob:
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(4, 4, 4));
       // modelMatrix = glm::rotate(modelMatrix, RADIANS(60.f), glm::vec3(1, 0, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1.5f));
        RenderGlob(meshes["sphere"], shaders["Tema3ShaderGlob"], modelMatrix, mapTextures["random"]);
    }

    // conuri:

    // se vor desena doar fatetele fata
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // aceasta directiva este folosita pentru nu se scrie in depth buffer
    glDepthMask(GL_FALSE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // desenare conuri
    for (int i = 0; i < 4; i++) {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, pozitieSpot[i]);
        glm::mat4 rotatieX = glm::rotate(glm::mat4(1.f), unghiStDr[i], glm::vec3(1, 0, 0));
        glm::mat4 rotatieZ = glm::rotate(glm::mat4(1.f), unghiSusJos[i], glm::vec3(0, 0, 1));
        modelMatrix *= rotatieX;
        modelMatrix *= rotatieZ;
        modelMatrix = glm::scale(modelMatrix, glm::vec3(10 * tan(RADIANS(15)), 10, 10 * tan(RADIANS(15))));
        
        RenderCon(meshes["con"], shaders["Tema3ShaderConuri"], modelMatrix, culoareSpot[i]);

        directieSpot[i] = rotatieX * glm::vec4(0, -1, 0, 0);
        directieSpot[i] = rotatieZ * glm::vec4(directieSpot[i], 0);

        // if rand[i] = 0 rotesc st-dr else rotesc sus-jos:
        if (dirAct[i] == 0) {
            //cout << i << ":: " << directieSpot[i] << endl;
            unghiStDr[i] += directii[i] * 0.2 * deltaTimeSeconds;
            
            if (unghiStDr[i] > M_PI / 4 || unghiStDr[i] < -M_PI / 4) {
                directii[i] = -directii[i];
            }
        }
        else
        {
            unghiSusJos[i] += directii[i] * 0.2 * deltaTimeSeconds;

            if (unghiSusJos[i] > M_PI / 4 || unghiSusJos[i] < -M_PI / 4) {
                directii[i] = -directii[i];
            }
        }

        
    }

    // se dezactiveaza actiunile tuturor directivelor apelate anterior
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
 }

void Tema3::FrameEnd()
{
}

// render RingDans:
void Tema3::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3 color, int luminaGlob, Texture2D* texture1)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    int disco_location = glGetUniformLocation(shader->program, "disco_ball_position");
    glUniform3f(disco_location, 4, 4, 4);

    if (texture1)
    {
        // TODO(student): Do these:
        // - activate texture location 0
        // - bind the texture1 ID
        // - send theuniform value
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);

    }

    int rotation_location = glGetUniformLocation(shader->program, "rotation");
    glUniform1f(rotation_location, Engine::GetElapsedTime() / 10);

    int glob_location = glGetUniformLocation(shader->program, "luminaGlob_location");
    glUniform1i(glob_location, luminaGlob);

    int pozitiiSpot_location = glGetUniformLocation(shader->program, "pozitiiSpot_location");
    glUniform3fv(pozitiiSpot_location, 4, glm::value_ptr(pozitieSpot[0]));

    int culoriSpot_location = glGetUniformLocation(shader->program, "culoriSpot_location");
    glUniform3fv(culoriSpot_location, 4, glm::value_ptr(culoareSpot[0]));

    int directiiSpot_location = glGetUniformLocation(shader->program, "directiiSpot_location");
    glUniform3fv(directiiSpot_location, 4, glm::value_ptr(directieSpot[0]));

    // setez culoarea obiectului:
    int object_color = glGetUniformLocation(shader->program, "object_color");
    glUniform3fv(object_color, 1, glm::value_ptr(color));

    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

void m1::Tema3::RenderSimpleMeshPerete(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3 color, int i, int j, int luminaPodea, int luminaSpot, int luminaGlob, Texture2D* texture1)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    glm::vec3 culoriZona[9];
    glm::vec3 pozitiiCuloriZona[9];
    int dimFin = 0;

    if ((i == 0) && (j == 0)) {
        culoriZona[dimFin] = ringDans[0][0];
        pozitiiCuloriZona[dimFin] = glm::vec3(0, 0.1f, 0);
        dimFin++;
    }

    if ((i == 0) && (j == 7)) {
        culoriZona[dimFin] = ringDans[0][7];
        pozitiiCuloriZona[dimFin] = glm::vec3(0, 0.1f, 7);
        dimFin++;
    }

    if ((i == 7) && (j == 0)) {
        culoriZona[dimFin] = ringDans[7][0];
        pozitiiCuloriZona[dimFin] = glm::vec3(7, 0.1f, 0);
        dimFin++;
    }

    if ((i == 7) && (j == 7)) {
        culoriZona[dimFin] = ringDans[7][7];
        pozitiiCuloriZona[dimFin] = glm::vec3(7, 0.1f, 7);
        dimFin++;
    }

    if (((j == 0) || (j == 7)) && (i > 0) && (i < 7)) {
        for (int k = -1; k < 2; k++) {
            culoriZona[dimFin] = ringDans[i][j + k];
            pozitiiCuloriZona[dimFin] = glm::vec3(i, 0.1f, j + k);
            dimFin++;
        }
    }

    if (((i == 0) || (i == 7)) && (j > 0) && (j < 7)) {
        for (int k = -1; k < 2; k++) {
            culoriZona[dimFin] = ringDans[i + k][j];
            pozitiiCuloriZona[dimFin] = glm::vec3(i + k, 0.1f, j);
            dimFin++;
        }
    }

    int disco_location = glGetUniformLocation(shader->program, "disco_ball_position");
    glUniform3fv(disco_location, 1, glm::value_ptr(glm::vec3(4, 4, 4)));

    if (texture1)
    {
        // TODO(student): Do these:
        // - activate texture location 0
        // - bind the texture1 ID
        // - send theuniform value
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);

    }

    int rotation_location = glGetUniformLocation(shader->program, "rotation");
    glUniform1f(rotation_location, Engine::GetElapsedTime() / 10);

    int podea_location = glGetUniformLocation(shader->program, "luminaPodea_location");
    glUniform1i(podea_location, luminaPodea);

    int spot_location = glGetUniformLocation(shader->program, "luminaSpot_location");
    glUniform1i(spot_location, luminaSpot);

    int glob_location = glGetUniformLocation(shader->program, "luminaGlob_location");
    glUniform1i(glob_location, luminaGlob);

    int pozitiiSpot_location = glGetUniformLocation(shader->program, "pozitiiSpot_location");
    glUniform3fv(pozitiiSpot_location, 4, glm::value_ptr(pozitieSpot[0]));

    int culoriSpot_location = glGetUniformLocation(shader->program, "culoriSpot_location");
    glUniform3fv(culoriSpot_location, 4, glm::value_ptr(culoareSpot[0]));

    int directiiSpot_location = glGetUniformLocation(shader->program, "directiiSpot_location");
    glUniform3fv(directiiSpot_location, 4, glm::value_ptr(directieSpot[0]));

    // setez dimensiunea vectorilor:
    int dimFin_location = glGetUniformLocation(shader->program, "dimFin_location");
    glUniform1i(dimFin_location, dimFin);

    int culoriZona_location = glGetUniformLocation(shader->program, "culoriZona_location");
    glUniform3fv(culoriZona_location, 9, glm::value_ptr(culoriZona[0]));

    int pozitiiCuloriZona_location = glGetUniformLocation(shader->program, "pozitiiCuloriZona_location");
    glUniform3fv(pozitiiCuloriZona_location, 9, glm::value_ptr(pozitiiCuloriZona[0]));

    // setez culoarea obiectului:
    int object_color = glGetUniformLocation(shader->program, "object_color");
    glUniform3fv(object_color, 1, glm::value_ptr(color));
  
    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

void m1::Tema3::RenderSimpleMeshDansator(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3 color, glm::vec3 pozitie, int luminaPodea, int luminaSpot, int luminaGlob, Texture2D* texture1)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    glm::vec3 culoriZona[9];
    glm::vec3 pozitiiCuloriZona[9];
    int dimFin = 0;
    int i = (int) pozitie.x;
    int j = (int) pozitie.z;

    // daca e dansatorul in coltul idn stanga sus:
    if ((i == 0) && (j == 0)) {
        culoriZona[dimFin] = ringDans[0][0];
        pozitiiCuloriZona[dimFin] = glm::vec3(0, 0.1f, 0);
        dimFin++;

        culoriZona[dimFin] = ringDans[1][0];
        pozitiiCuloriZona[dimFin] = glm::vec3(1, 0.1f, 0);
        dimFin++;

        culoriZona[dimFin] = ringDans[1][1];
        pozitiiCuloriZona[dimFin] = glm::vec3(1, 0.1f, 1);
        dimFin++;

        culoriZona[dimFin] = ringDans[0][1];
        pozitiiCuloriZona[dimFin] = glm::vec3(0, 0.1f, 1);
        dimFin++;
    }

    // daca e dansatorul in coltul din dreapta sus:
    if ((i == 0) && (j == 7)) {
        culoriZona[dimFin] = ringDans[0][7];
        pozitiiCuloriZona[dimFin] = glm::vec3(0, 0.1f, 7);
        dimFin++;

        culoriZona[dimFin] = ringDans[1][7];
        pozitiiCuloriZona[dimFin] = glm::vec3(1, 0.1f, 7);
        dimFin++;

        culoriZona[dimFin] = ringDans[1][6];
        pozitiiCuloriZona[dimFin] = glm::vec3(1, 0.1f, 6);
        dimFin++;

        culoriZona[dimFin] = ringDans[0][6];
        pozitiiCuloriZona[dimFin] = glm::vec3(0, 0.1f, 6);
        dimFin++;
    }

    // daca e dansatorul in coltul din stanga jos:
    if ((i == 7) && (j == 0)) {
        culoriZona[dimFin] = ringDans[7][0];
        pozitiiCuloriZona[dimFin] = glm::vec3(7, 0.1f, 0);
        dimFin++;

        culoriZona[dimFin] = ringDans[6][0];
        pozitiiCuloriZona[dimFin] = glm::vec3(6, 0.1f, 0);
        dimFin++;

        culoriZona[dimFin] = ringDans[6][1];
        pozitiiCuloriZona[dimFin] = glm::vec3(6, 0.1f, 1);
        dimFin++;

        culoriZona[dimFin] = ringDans[7][1];
        pozitiiCuloriZona[dimFin] = glm::vec3(7, 0.1f, 1);
        dimFin++;
    }

    // daca e dansatorul in coltul de dreapta jos:
    if ((i == 7) && (j == 7)) {
        culoriZona[dimFin] = ringDans[7][7];
        pozitiiCuloriZona[dimFin] = glm::vec3(7, 0.1f, 7);
        dimFin++;

        culoriZona[dimFin] = ringDans[7][6];
        pozitiiCuloriZona[dimFin] = glm::vec3(7, 0.1f, 6);
        dimFin++;

        culoriZona[dimFin] = ringDans[6][6];
        pozitiiCuloriZona[dimFin] = glm::vec3(6, 0.1f, 6);
        dimFin++;

        culoriZona[dimFin] = ringDans[6][7];
        pozitiiCuloriZona[dimFin] = glm::vec3(6, 0.1f, 7);
        dimFin++;
    }

    // daca e dansatorul pe marginea stanga:
    if ((j == 0) && (i > 0) && (i < 7)) {
        culoriZona[dimFin] = ringDans[i][j];
        pozitiiCuloriZona[dimFin] = glm::vec3(i, 0.1f, j);
        dimFin++;

        culoriZona[dimFin] = ringDans[i][j-1];
        pozitiiCuloriZona[dimFin] = glm::vec3(i, 0.1f, j-1);
        dimFin++;

        culoriZona[dimFin] = ringDans[i][j+1];
        pozitiiCuloriZona[dimFin] = glm::vec3(i, 0.1f, j+1);
        dimFin++;

        culoriZona[dimFin] = ringDans[i+1][j];
        pozitiiCuloriZona[dimFin] = glm::vec3(i+1, 0.1f, j);
        dimFin++;

        culoriZona[dimFin] = ringDans[i+1][j-1];
        pozitiiCuloriZona[dimFin] = glm::vec3(i+1, 0.1f, j-1);
        dimFin++;

        culoriZona[dimFin] = ringDans[i+1][j+1];
        pozitiiCuloriZona[dimFin] = glm::vec3(i+1, 0.1f, j+1);
        dimFin++;
    }

    // daca e dansatorul pe marginea dreapta:
    if ((j == 7) && (i > 0) && (i < 7)) {
        culoriZona[dimFin] = ringDans[i][j];
        pozitiiCuloriZona[dimFin] = glm::vec3(i, 0.1f, j);
        dimFin++;

        culoriZona[dimFin] = ringDans[i][j-1];
        pozitiiCuloriZona[dimFin] = glm::vec3(i, 0.1f, j - 1);
        dimFin++;

        culoriZona[dimFin] = ringDans[i][j + 1];
        pozitiiCuloriZona[dimFin] = glm::vec3(i, 0.1f, j + 1);
        dimFin++;

        culoriZona[dimFin] = ringDans[i - 1][j];
        pozitiiCuloriZona[dimFin] = glm::vec3(i - 1, 0.1f, j);
        dimFin++;

        culoriZona[dimFin] = ringDans[i - 1 ][j - 1];
        pozitiiCuloriZona[dimFin] = glm::vec3(i - 1, 0.1f, j - 1);
        dimFin++;

        culoriZona[dimFin] = ringDans[i - 1][j + 1];
        pozitiiCuloriZona[dimFin] = glm::vec3(i - 1, 0.1f, j + 1);
        dimFin++;
    }

    // daca e dansatorul pe marginea de sus:
    if ((i == 0) && (j > 0) && (j < 7)) {
        culoriZona[dimFin] = ringDans[i][j];
        pozitiiCuloriZona[dimFin] = glm::vec3(i, 0.1f, j);
        dimFin++;

        culoriZona[dimFin] = ringDans[i - 1][j];
        pozitiiCuloriZona[dimFin] = glm::vec3(i - 1, 0.1f, j);
        dimFin++;

        culoriZona[dimFin] = ringDans[i + 1][j];
        pozitiiCuloriZona[dimFin] = glm::vec3(i + 1, 0.1f, j);
        dimFin++;

        culoriZona[dimFin] = ringDans[i][j + 1];
        pozitiiCuloriZona[dimFin] = glm::vec3(i, 0.1f, j + 1);
        dimFin++;

        culoriZona[dimFin] = ringDans[i - 1][j + 1];
        pozitiiCuloriZona[dimFin] = glm::vec3(i - 1, 0.1f, j + 1);
        dimFin++;

        culoriZona[dimFin] = ringDans[i + 1][j + 1];
        pozitiiCuloriZona[dimFin] = glm::vec3(i + 1, 0.1f, j + 1);
        dimFin++;
    }

    // daca e dansatorul pe marginea de jos:
    if ((i == 7) && (j > 0) && (j < 7)) {
        culoriZona[dimFin] = ringDans[i][j];
        pozitiiCuloriZona[dimFin] = glm::vec3(i, 0.1f, j);
        dimFin++;

        culoriZona[dimFin] = ringDans[i - 1][j];
        pozitiiCuloriZona[dimFin] = glm::vec3(i - 1, 0.1f, j);
        dimFin++;

        culoriZona[dimFin] = ringDans[i + 1][j];
        pozitiiCuloriZona[dimFin] = glm::vec3(i + 1, 0.1f, j);
        dimFin++;

        culoriZona[dimFin] = ringDans[i][j - 1];
        pozitiiCuloriZona[dimFin] = glm::vec3(i, 0.1f, j - 1);
        dimFin++;

        culoriZona[dimFin] = ringDans[i - 1][j - 1];
        pozitiiCuloriZona[dimFin] = glm::vec3(i - 1, 0.1f, j - 1);
        dimFin++;

        culoriZona[dimFin] = ringDans[i + 1][j - 1];
        pozitiiCuloriZona[dimFin] = glm::vec3(i + 1, 0.1f, j - 1);
        dimFin++;
    }

    // daca e dansatorul pe mijloc:
    if ((i > 0) && (i < 7) && (j > 0) && (j < 7)) {
        culoriZona[dimFin] = ringDans[i][j];
        pozitiiCuloriZona[dimFin] = glm::vec3(i, 0.1f, j);
        dimFin++;

        culoriZona[dimFin] = ringDans[i - 1][j];
        pozitiiCuloriZona[dimFin] = glm::vec3(i - 1, 0.1f, j);
        dimFin++;

        culoriZona[dimFin] = ringDans[i + 1][j];
        pozitiiCuloriZona[dimFin] = glm::vec3(i + 1, 0.1f, j);
        dimFin++;

        culoriZona[dimFin] = ringDans[i][j - 1];
        pozitiiCuloriZona[dimFin] = glm::vec3(i, 0.1f, j - 1);
        dimFin++;

        culoriZona[dimFin] = ringDans[i - 1][j - 1];
        pozitiiCuloriZona[dimFin] = glm::vec3(i - 1, 0.1f, j - 1);
        dimFin++;

        culoriZona[dimFin] = ringDans[i + 1][j - 1];
        pozitiiCuloriZona[dimFin] = glm::vec3(i + 1, 0.1f, j - 1);
        dimFin++;

        culoriZona[dimFin] = ringDans[i][j + 1];
        pozitiiCuloriZona[dimFin] = glm::vec3(i, 0.1f, j + 1);
        dimFin++;

        culoriZona[dimFin] = ringDans[i - 1][j + 1];
        pozitiiCuloriZona[dimFin] = glm::vec3(i - 1, 0.1f, j + 1);
        dimFin++;

        culoriZona[dimFin] = ringDans[i + 1][j + 1];
        pozitiiCuloriZona[dimFin] = glm::vec3(i + 1, 0.1f, j + 1);
        dimFin++;
    }

    int disco_location = glGetUniformLocation(shader->program, "disco_ball_position");
    glUniform3fv(disco_location, 1, glm::value_ptr(glm::vec3(4, 4, 4)));

    if (texture1)
    {
        // TODO(student): Do these:
        // - activate texture location 0
        // - bind the texture1 ID
        // - send theuniform value
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);

    }

    int rotation_location = glGetUniformLocation(shader->program, "rotation");
    glUniform1f(rotation_location, Engine::GetElapsedTime() / 10);

    int podea_location = glGetUniformLocation(shader->program, "luminaPodea_location");
    glUniform1i(podea_location, luminaPodea);

    int spot_location = glGetUniformLocation(shader->program, "luminaSpot_location");
    glUniform1i(spot_location, luminaSpot);

    int glob_location = glGetUniformLocation(shader->program, "luminaGlob_location");
    glUniform1i(glob_location, luminaGlob);

    int pozitiiSpot_location = glGetUniformLocation(shader->program, "pozitiiSpot_location");
    glUniform3fv(pozitiiSpot_location, 4, glm::value_ptr(pozitieSpot[0]));

    int culoriSpot_location = glGetUniformLocation(shader->program, "culoriSpot_location");
    glUniform3fv(culoriSpot_location, 4, glm::value_ptr(culoareSpot[0]));

    int directiiSpot_location = glGetUniformLocation(shader->program, "directiiSpot_location");
    glUniform3fv(directiiSpot_location, 4, glm::value_ptr(directieSpot[0]));

    // setez dimensiunea vectorilor:
    int dimFin_location = glGetUniformLocation(shader->program, "dimFin_location");
    glUniform1i(dimFin_location, dimFin);

    int culoriZona_location = glGetUniformLocation(shader->program, "culoriZona_location");
    glUniform3fv(culoriZona_location, 9, glm::value_ptr(culoriZona[0]));

    int pozitiiCuloriZona_location = glGetUniformLocation(shader->program, "pozitiiCuloriZona_location");
    glUniform3fv(pozitiiCuloriZona_location, 9, glm::value_ptr(pozitiiCuloriZona[0]));

    // setez culoarea obiectului:
    int object_color = glGetUniformLocation(shader->program, "object_color");
    glUniform3fv(object_color, 1, glm::value_ptr(color));

    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

void m1::Tema3::RenderCon(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3 color)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // setez culoarea obiectului:
    int object_color = glGetUniformLocation(shader->program, "object_color");
    glUniform3fv(object_color, 1, glm::value_ptr(color));

    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

void m1::Tema3::RenderGlob(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    int rotation_location = glGetUniformLocation(shader->program, "rotation");
    glUniform1f(rotation_location, Engine::GetElapsedTime() / 10);


    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // TODO(student): Set any other shader uniforms that you need

    if (texture1)
    {
        // TODO(student): Do these:
        // - activate texture location 0
        // - bind the texture1 ID
        // - send theuniform value
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);

    }

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

glm::vec3 m1::Tema3::MiscareDansator(float deltaTime, float translateX, float translateZ)
{
    if (translateX >= 7.f) {
        translateX -= (rand() % 2 + 1) * deltaTime;

    } else if (translateX <= 0.f)
    {
        translateX += (rand() % 2 + 1) * deltaTime;


    }
    else {
        cout << "pula x " << translateX << endl;

        translateX +=  (rand() % 2 - 1) * deltaTime;
        cout << "pula x " << translateX << endl;
    }


    if (translateZ >= 7.f)
    {
        translateZ -= (rand() % 2 + 1) * deltaTime;


    } else if (translateZ <= 0.f) {
        translateZ += (rand() % 2 + 1) * deltaTime;
    }
    else {
        cout << "pula z " << translateZ << endl;

        translateZ += (rand() % 2 - 1) * deltaTime;
        cout << "pula z " << translateZ << endl;

    }

    return glm::vec3((float)translateX, 0.1, (float)translateZ);
}

glm::vec3 m1::Tema3::MiscareDansatorOrizontal(float deltaTime, glm::vec3 posAct, float pas) // pe Z
{  
    float tX, tY, tZ;
    tX = (float)posAct.x;
    tY = (float)posAct.y;
    tZ = (float)posAct.z;

    if (pas < 0) {
        tZ -= 0.5 * deltaTime;

    }
    else {
        tZ += 0.5 * deltaTime;
    }

    return glm::vec3(tX, tY, (float)tZ);
}

glm::vec3 m1::Tema3::MiscareDansatorVertical(float deltaTime, glm::vec3 posAct, float pas) // pe X
{
    float tX, tY, tZ;
    tX = (float)posAct.x;
    tY = (float)posAct.y;
    tZ = (float)posAct.z;

    if (pas < 0) {
        tX -= 0.5 * deltaTime;

    }
    else {
        tX += 0.5 * deltaTime;
    }
    return glm::vec3((float)tX, tY, tZ);
}


Texture2D* Tema3::CreateRandomTexture(unsigned int width, unsigned int height)
{
    GLuint textureID = 1;
    unsigned int channels = 3;
    unsigned int size = width * height * channels;
    unsigned char* data = new unsigned char[size];

    // TODO(student): Generate random texture data 
    for (int i = 0; i < size; i++) {
        data[i] = (char)rand() % 256;
    }

    // TODO(student): Generate and bind the new texture ID
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    if (GLEW_EXT_texture_filter_anisotropic) {
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);
    }
    // TODO(student): Set the texture parameters (MIN_FILTER, MAG_FILTER and WRAPPING MODE) using glTexParameteri
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    CheckOpenGLError();

    // Use glTexImage2D to set the texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    // TODO(student): Generate texture mip-maps
    glGenerateMipmap(GL_TEXTURE_2D);

    CheckOpenGLError();

    // Save the texture into a wrapper Texture2D class for using easier later during rendering phase
    Texture2D* texture = new Texture2D();
    texture->Init(textureID, width, height, channels);

    SAFE_FREE_ARRAY(data);
    return texture;
}


void Tema3::OnInputUpdate(float deltaTime, int mods)
{
    float speed = 2;

    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        glm::vec3 up = glm::vec3(0, 1, 0);
        glm::vec3 right = GetSceneCamera()->m_transform->GetLocalOXVector();
        glm::vec3 forward = GetSceneCamera()->m_transform->GetLocalOZVector();
        forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));

        // Control light position using on W, A, S, D, E, Q
        if (window->KeyHold(GLFW_KEY_W)) lightPosition -= forward * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_A)) lightPosition -= right * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_S)) lightPosition += forward * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_D)) lightPosition += right * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_E)) lightPosition += up * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_Q)) lightPosition -= up * deltaTime * speed;
    }




}


void Tema3::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_P) {
        luminaPodea *= -1;
    }

    if (key == GLFW_KEY_O) {
        luminaSpotlight *= -1;
    }

    if (key == GLFW_KEY_I) {
        luminaGlob *= -1;
    }
}


void Tema3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema3::OnWindowResize(int width, int height)
{
}