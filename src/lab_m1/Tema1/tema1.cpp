#include "lab_m1/Tema1/tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/utile.h"
#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/lab3_vis2D.h"



using namespace std;
using namespace m1;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    // spatiu logic:
    logicSpace.x = 0;       // logic x
    logicSpace.y = 0;       // logic y
    logicSpace.width = 10;   // logic width
    logicSpace.height = 10;  // logic height

    // harta:
    glm::vec3 mapCorner = glm::vec3(0, 0, 0);
    mapSide = 8;

    // jucator:
    glm::vec3 playerCorner = glm::vec3(0, 0, 0);
    playerRadius = 1;
    cx = playerRadius/2 + playerCorner.x;
    cy = playerRadius/2 + playerCorner.y;

    nasCorner = glm::vec3(0, 0, 0);
    nasSide = 0.2f;

    // Initialize tx and ty (the translation steps)
    translateX = mapSide/2;
    translateY = mapSide/2;


    Mesh* map = utile::CreateSquare("harta", mapCorner, mapSide, glm::vec3(0.173, 0.216, 0.230), true);
    AddMeshToList(map);

    enemyCorner = glm::vec3(0, 0, 0);
    enemySide = 3.0f ;
    cxEnm = enemySide / 2;
    cyEnm = enemySide / 2;

    proiectilCorner = glm::vec3(0, 0, 0);
    proiectilSide = 1.0f;
    cxPro = proiectilSide / 2;
    cyPro = proiectilSide / 2;

    translateXEnemyMic = 8;
    translateYEnemyMic = 0;

    translateXProiectil = mapSide/2;
    translateYProiectil = mapSide/2;

    translateXEnemy1 = rand() % 8 + 1;
    translateYEnemy1 = rand() % 8 + 1;

    translateXEnemy2 = rand() % 8 + 1;
    translateYEnemy2 = rand() % 8 + 1;

    translateXEnemy3 = rand() % 8 + 1;
    translateYEnemy3 = rand() % 8 + 1;

    translateXEnemy4 = rand() % 8 + 1;
    translateYEnemy4 = rand() % 8 + 1;


    scaleX1 = 1;
    scaleY1 = 1;

    scaleX2 = 1;
    scaleY2 = 1;
    
    scaleX3 = 1;
    scaleY3 = 1;
    
    scaleX4 = 1;
    scaleY4 = 1;

    count = 0;

    atac1 = true;
    atac2 = true;
    atac3 = true;
    atac4 = true;

    CrearePlayer();
    CreareObst();
    CreareInamic();
}

void Tema1::CrearePlayer()
{
    Mesh* player = utile::CreateCircle("jucator", glm::vec3(0, 0, 0), glm::vec3(1, 1, 0), 100, true);
    AddMeshToList(player);

    Mesh* playerBorder = utile::CreateCircle("jucatorBordura", glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 100, true);
    AddMeshToList(playerBorder);

    Mesh* eye = utile::CreateCircle("ochi", glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), 100, true);
    AddMeshToList(eye);

    Mesh* eyeBordura = utile::CreateCircle("ochiBordura", glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 100, true);
    AddMeshToList(eyeBordura);

    Mesh* nas = utile::CreateSquare("nasuc", nasCorner, nasSide, glm::vec3(0, 0, 0), true);
    AddMeshToList(nas);
}

void Tema1::CreareObst()
{
    Mesh* obst1 = utile::CreateSquare("obs1", glm::vec3(0, 0, 0), 1, glm::vec3(0.2, 0, 1), true);
    AddMeshToList(obst1);
}

void m1::Tema1::CreareInamic()
{
    Mesh* inamicMic = utile::CreateSquare("ceva", glm::vec3(0, 0, 0), enemySide, glm::vec3(0.537, 0.419, 0.38), true);
    AddMeshToList(inamicMic);

    Mesh* inamicMicBordura = utile::CreateSquare("cevaBordura", glm::vec3(0, 0, 0), enemySide, glm::vec3(0, 0, 0), true);
    AddMeshToList(inamicMicBordura);

    Mesh* ochiCeva = utile::CreateCircle("ochiCeva", glm::vec3(0, 0, 0), glm::vec3(0.011, 0.729, 0.133), 100, true);
    AddMeshToList(ochiCeva);

    Mesh* inamic = utile::CreateCircle("printesa", glm::vec3(0, 0, 0), glm::vec3(0.8, 0, 1), 100, true);
    AddMeshToList(inamic);

    Mesh* inamicBordura = utile::CreateCircle("printesaBordura", glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 100, true);
    AddMeshToList(inamicBordura);
}

void m1::Tema1::CreareProiectil()
{
    Mesh* proiectil = utile::CreateSquare("proiectilul", glm::vec3(0, 0, 0), proiectilSide, glm::vec3(1, 1, 1), true);
    AddMeshToList(proiectil);
} 

// 2D visualization matrix
glm::mat3 Tema1::VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    tx = viewSpace.x - sx * logicSpace.x;
    ty = viewSpace.y - sy * logicSpace.y;

    return glm::transpose(glm::mat3(
        sx, 0.0f, tx,
        0.0f, sy, ty,
        0.0f, 0.0f, 1.0f));
}


// Uniform 2D visualization matrix (same scale factor on x and y axes)
glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
        smin, 0.0f, tx,
        0.0f, smin, ty,
        0.0f, 0.0f, 1.0f));
}


void Tema1::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();
    // The viewport is now the right half of the window

    viewSpace = ViewportSpace(0, 0, resolution.x , resolution.y);
    SetViewportArea(viewSpace, glm::vec3(0.5f), true);

    // Compute uniform 2D visualization matrix
    visMatrix = glm::mat3(1);
    logicSpace.x = (translateX - (logicSpace.width / 2));//deltaTimeSeconds * 0.001;
    logicSpace.y = (translateY - (logicSpace.height / 2));//deltaTimeSeconds * 0.001;

    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
    DrawScene(visMatrix, deltaTimeSeconds);
}

void Tema1::FollowPlayer1(float deltaTime)
{
    // inamic mare:
    if (translateXEnemy1 <= translateX) {
        translateXEnemy1 += deltaTime*0.5;
    }

    if (translateYEnemy1 <= translateY) {
        translateYEnemy1 += deltaTime*0.5;
    }

    if (translateXEnemy1 >= translateX) {
        translateXEnemy1 -= deltaTime*0.5;
    }

    if (translateYEnemy1 >= translateY) {
        translateYEnemy1 -= deltaTime*0.5;
    }
}

void Tema1::FollowPlayer2(float deltaTime)
{
    // inamic mare:
    if (translateXEnemy2 <= translateX) {
        translateXEnemy2 += deltaTime*0.75;
    }

    if (translateYEnemy2 <= translateY) {
        translateYEnemy2 += deltaTime*0.75;
    }

    if (translateXEnemy2 >= translateX) {
        translateXEnemy2 -= deltaTime*0.75;
    }

    if (translateYEnemy2 >= translateY) {
        translateYEnemy2 -= deltaTime*0.75;
    }

 }

void Tema1::FollowPlayer3(float deltaTime)
{
    // inamic mare:
    if (translateXEnemy3 <= translateX) {
        translateXEnemy3 += deltaTime*0.75;
    }

    if (translateYEnemy3 <= translateY) {
        translateYEnemy3 += deltaTime*0.75;
    }

    if (translateXEnemy3 >= translateX) {
        translateXEnemy3 -= deltaTime*0.75;
    }

    if (translateYEnemy3 >= translateY) {
        translateYEnemy3 -= deltaTime*0.75;
    }

}

void Tema1::FollowPlayer4(float deltaTime)
{
    // inamic mare:
    if (translateXEnemy4 <= translateX) {
        translateXEnemy4 += deltaTime*0.75;
    }

    if (translateYEnemy4 <= translateY) {
        translateYEnemy4 += deltaTime*0.75;
    }

    if (translateXEnemy4 >= translateX) {
        translateXEnemy4 -= deltaTime*0.75;
    }

    if (translateYEnemy4 >= translateY) {
        translateYEnemy4 -= deltaTime*0.75;
    }

}

void m1::Tema1::ColiziuneHartaInamicA(float deltaTime)
{
    // coliziune perete stanga:
    if (translateXEnemyMic <= 0 + cxEnm/2) {
        translateXEnemyMic = 0;
    }

    // coliziune perete dreapta:
    if (translateXEnemyMic >= 8 - cxEnm/2) {
        translateXEnemyMic = 8;
    }

    // coliziune perete sus:
    if (translateYEnemyMic >= 8 - cyEnm/2) {
        translateYEnemyMic = 8;
    }

    // coliziune perete jos:
    if (translateYEnemyMic <= 0 + cyEnm/2) {
        translateYEnemyMic = 0;
    }
}

//void m1::Tema1::ColiziuneHartaInamicB(float deltaTime)
//{
//    // coliziune perete stanga:
//    if (translateXEnemy <= 0 + cx/2) {
//        translateXEnemy = 0 + cx/2;
//    }
//
//    // coliziune perete dreapta:
//    if (translateXEnemy >= 8 - cx/2) {
//        translateXEnemy = 8;
//    }
//
//    // coliziune perete sus:
//    if (translateYEnemy >= 8- cy/2) {
//        translateYEnemy = 8;
//    }
//
//    // coliziune perete jos:
//    if (translateYEnemy <= 0 + cy/2) {
//        translateYEnemy = 0;
//    }
//}

void m1::Tema1::ColiziuneHartaJucator(float deltaTime)
{
    // coliziune perete stanga:
    if (translateX  <= 0 + cx/2) {
        translateX = 0+cx/2;
    }

    // coliziune perete dreapta:
    if (translateX >= 8 - cx/2) {
        translateX = 8 - cx/2;
    }

    // coliziune perete sus:
    if (translateY >= 8 - cy/2) {
        translateY = 8 - cy/2;
    }

    // coliziune perete jos:
    if (translateY <= 0 + cy/2) {
        translateY = 0 + cy/2;
    }
}

void Tema1::DrawScene(glm::mat3 visMatrix, float deltaTime)
{
    // obstacole:
    DrawObstacles(visMatrix, deltaTime);

    // coliziuni harta:
    ColiziuneHartaJucator(deltaTime);
    //ColiziuneHartaInamicB(deltaTime);

    // jucator:
    DrawPlayer(visMatrix, deltaTime);


    // proiectil:
    DrawProiectil(visMatrix, deltaTime);


    // inamic:
    FollowPlayer1(deltaTime);
    FollowPlayer2(deltaTime);
    FollowPlayer3(deltaTime);
    FollowPlayer4(deltaTime);


    GenerareEnemy(visMatrix, deltaTime);
    //ColiziuneHartaInamicB(deltaTime);

    // harta:
    modelMatrix = visMatrix * transform2D::Translate(0, 0);
    RenderMesh2D(meshes["harta"], shaders["VertexColor"], modelMatrix);     
}

void m1::Tema1::DrawPlayer(glm::mat3 visMatrix, float deltaTime)
{
   // nas:
    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(-cx, -cy);
    modelMatrix *= transform2D::Translate(0.35 * cx + 0.4, 0.3 * cy + 0.3);
    modelMatrix *= transform2D::Scale(0.2, 0.4);

    RenderMesh2D(meshes["nasuc"], shaders["VertexColor"], modelMatrix);

    //ochi:
    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(cx, cy);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Translate(-cx, -cy);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(0.35 * cx + 0.05, 0.3 * cy - 0.25);
    modelMatrix *= transform2D::Scale(0.055, 0.055);

    RenderMesh2D(meshes["ochi"], shaders["VertexColor"], modelMatrix);


    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(cx, cy);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Translate(-cx, -cy);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(0.35 * cx + 0.04, 0.3 * cy - 0.05);
    modelMatrix *= transform2D::Scale(0.055, 0.055);

    RenderMesh2D(meshes["ochi"], shaders["VertexColor"], modelMatrix);


    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(cx, cy);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Translate(-cx, -cy);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(0.36 * cx + 0.05, 0.31 *cy - 0.25);
    modelMatrix *= transform2D::Scale(0.07, 0.07);

    RenderMesh2D(meshes["ochiBordura"], shaders["VertexColor"], modelMatrix);


    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(cx, cy);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Translate(-cx, -cy);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(0.36 * cx + 0.04, 0.31 * cy - 0.05);
    modelMatrix *= transform2D::Scale(0.07, 0.07);
    
    RenderMesh2D(meshes["ochiBordura"], shaders["VertexColor"], modelMatrix);

    // corp:
    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(cx, cy);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Translate(-cx, -cy);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Scale(0.35, 0.3);

    RenderMesh2D(meshes["jucator"], shaders["VertexColor"], modelMatrix);


    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(cx, cy);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Translate(-cx, -cy);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Scale(0.36, 0.31);

    RenderMesh2D(meshes["jucatorBordura"], shaders["VertexColor"], modelMatrix);
}

/*void m1::Tema1::DrawEnemyA(glm::mat3 visMatrix, float deltaTime)
{
    angularStepInamic = -atan2(translateYEnemy - translateY, translateXEnemy - translateX);

    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(-cxEnm, -cyEnm);
    modelMatrix *= transform2D::Translate(translateXEnemyMic, translateYEnemyMic);
    modelMatrix *= transform2D::Translate(-cxEnm, -cyEnm);
    modelMatrix *= transform2D::Translate(0.15 * cxEnm, 0.15 * cyEnm);
    modelMatrix *= transform2D::Rotate(angularStepInamic + M_PI);
    modelMatrix *= transform2D::Scale(0.05, 0.05);

    RenderMesh2D(meshes["ochiCeva"], shaders["VertexColor"], modelMatrix);


    //modelMatrix = visMatrix;
    //modelMatrix *= transform2D::Translate(cxEnm, cyEnm);
    //modelMatrix *= transform2D::Translate(translateXEnemyMic, translateYEnemyMic);
    //modelMatrix *= transform2D::Translate(-cxEnm, -cyEnm);
    //modelMatrix *= transform2D::Rotate(angularStepInamic + M_PI);
    //modelMatrix *= transform2D::Translate(0.15 * cxEnm + 0.13, 0.15 * cyEnm);
    //modelMatrix *= transform2D::Scale(0.05, 0.05);

    //RenderMesh2D(meshes["ochiCeva"], shaders["VertexColor"], modelMatrix);


    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(cxEnm, cyEnm);
    modelMatrix *= transform2D::Translate(translateXEnemyMic, translateYEnemyMic);
    modelMatrix *= transform2D::Translate(-cxEnm, -cyEnm);
    modelMatrix *= transform2D::Rotate(angularStepInamic + M_PI);
    modelMatrix *= transform2D::Scale(0.15, 0.15);
    modelMatrix *= transform2D::Translate(-cxEnm, -cyEnm);

    RenderMesh2D(meshes["ceva"], shaders["VertexColor"], modelMatrix);


    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(cxEnm, cyEnm);
    modelMatrix *= transform2D::Translate(translateXEnemyMic, translateYEnemyMic);
    modelMatrix *= transform2D::Translate(-cxEnm, -cyEnm);
    modelMatrix *= transform2D::Rotate(angularStepInamic + M_PI);
    modelMatrix *= transform2D::Scale(0.16, 0.16);
    modelMatrix *= transform2D::Translate(-cxEnm, -cyEnm);
    
    RenderMesh2D(meshes["cevaBordura"], shaders["VertexColor"], modelMatrix);
}
*/
void m1::Tema1::DrawEnemyB(glm::mat3 visMatrix, float deltaTime, float translateXEnemy, float translateYEnemy)
{
            angularStepInamic = atan2(translateXEnemy - translateY, translateYEnemy - translateX);

            // inamic:
            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(cx, cy);
            modelMatrix *= transform2D::Translate(translateXEnemy, translateYEnemy);
            modelMatrix *= transform2D::Translate(-cx, -cy);
            modelMatrix *= transform2D::Rotate(angularStepInamic + M_PI);
            modelMatrix *= transform2D::Translate(0.351 * cx + 0.13, 0.249 * cy - 0.12);
            modelMatrix *= transform2D::Scale(0.03, 0.03);
            RenderMesh2D(meshes["jucator"], shaders["VertexColor"], modelMatrix);

            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(cx, cy);
            modelMatrix *= transform2D::Translate(translateXEnemy, translateYEnemy);
            modelMatrix *= transform2D::Translate(-cx, -cy);
            modelMatrix *= transform2D::Rotate(angularStepInamic + M_PI);
            modelMatrix *= transform2D::Translate(0.351 * cx, 0.249 * cy - 0.23);
            modelMatrix *= transform2D::Scale(0.04, 0.04);
            RenderMesh2D(meshes["ochiBordura"], shaders["VertexColor"], modelMatrix);

            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(cx, cy);
            modelMatrix *= transform2D::Translate(translateXEnemy, translateYEnemy);
            modelMatrix *= transform2D::Translate(-cx, -cy);
            modelMatrix *= transform2D::Rotate(angularStepInamic + M_PI);
            modelMatrix *= transform2D::Translate(0.351 * cx, 0.249 * cy);
            modelMatrix *= transform2D::Scale(0.04, 0.04);
            RenderMesh2D(meshes["ochiBordura"], shaders["VertexColor"], modelMatrix);


            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(cx, cy);
            modelMatrix *= transform2D::Translate(translateXEnemy, translateYEnemy);
            modelMatrix *= transform2D::Translate(-cx, -cy);
            modelMatrix *= transform2D::Rotate(angularStepInamic + M_PI);
            modelMatrix *= transform2D::Scale(0.351, 0.249);

            RenderMesh2D(meshes["printesa"], shaders["VertexColor"], modelMatrix);


            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(cx, cy);
            modelMatrix *= transform2D::Translate(translateXEnemy, translateYEnemy);
            modelMatrix *= transform2D::Translate(-cx, -cy);
            modelMatrix *= transform2D::Rotate(angularStepInamic + M_PI);
            modelMatrix *= transform2D::Translate(0.351 * cx - 0.119, 0.249 * cy - 0.135);
            modelMatrix *= transform2D::Scale(0.24, 0.28);

            RenderMesh2D(meshes["printesa"], shaders["VertexColor"], modelMatrix);


            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(cx, cy);
            modelMatrix *= transform2D::Translate(-cx, -cy);
            modelMatrix *= transform2D::Translate(translateXEnemy, translateYEnemy);
            modelMatrix *= transform2D::Rotate(angularStepInamic + M_PI);
            modelMatrix *= transform2D::Translate(0.351 * cx - 0.25, 0.249 * cy - 0.155);
            modelMatrix *= transform2D::Scale(0.15, 0.31);

            RenderMesh2D(meshes["printesa"], shaders["VertexColor"], modelMatrix);

            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(cx, cy);
            modelMatrix *= transform2D::Translate(translateXEnemy, translateYEnemy);
            modelMatrix *= transform2D::Translate(-cx, -cy);
            modelMatrix *= transform2D::Rotate(angularStepInamic + M_PI);
            modelMatrix *= transform2D::Translate(0.351 * cx - 0.475, 0.249 * cy - 0.27);
            modelMatrix *= transform2D::Scale(0.093, 0.093);

            RenderMesh2D(meshes["printesa"], shaders["VertexColor"], modelMatrix);


            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(cx, cy);
            modelMatrix *= transform2D::Translate(translateXEnemy, translateYEnemy);
            modelMatrix *= transform2D::Translate(-cx, -cy);
            modelMatrix *= transform2D::Rotate(angularStepInamic + M_PI);
            modelMatrix *= transform2D::Translate(0.351 * cx - 0.495, 0.249 * cy - 0.125);
            modelMatrix *= transform2D::Scale(0.093, 0.093);

            RenderMesh2D(meshes["printesa"], shaders["VertexColor"], modelMatrix);


            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(cx, cy);
            modelMatrix *= transform2D::Translate(-cx, -cy);
            modelMatrix *= transform2D::Translate(translateXEnemy, translateYEnemy);
            modelMatrix *= transform2D::Rotate(angularStepInamic + M_PI);
            modelMatrix *= transform2D::Translate(0.351 * cx - 0.44, 0.249 * cy);
            modelMatrix *= transform2D::Scale(0.093, 0.093);

            RenderMesh2D(meshes["printesa"], shaders["VertexColor"], modelMatrix);

            // inamic bordura:
            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(cx, cy);
            modelMatrix *= transform2D::Translate(translateXEnemy, translateYEnemy);
            modelMatrix *= transform2D::Translate(-cx, -cy);
            modelMatrix *= transform2D::Rotate(angularStepInamic + M_PI);
            modelMatrix *= transform2D::Scale(0.36, 0.26);

            RenderMesh2D(meshes["printesaBordura"], shaders["VertexColor"], modelMatrix);


            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(cx, cy);
            modelMatrix *= transform2D::Translate(translateXEnemy, translateYEnemy);
            modelMatrix *= transform2D::Translate(-cx, -cy);
            modelMatrix *= transform2D::Rotate(angularStepInamic + M_PI);
            modelMatrix *= transform2D::Translate(0.36 * cx - 0.119, 0.26 * cy - 0.14);
            modelMatrix *= transform2D::Scale(0.25, 0.29);

            RenderMesh2D(meshes["printesaBordura"], shaders["VertexColor"], modelMatrix);


            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(cx, cy);
            modelMatrix *= transform2D::Translate(translateXEnemy, translateYEnemy);
            modelMatrix *= transform2D::Translate(-cx, -cy);
            modelMatrix *= transform2D::Rotate(angularStepInamic + M_PI);
            modelMatrix *= transform2D::Translate(0.36 * cx - 0.25, 0.26 * cy - 0.16);
            modelMatrix *= transform2D::Scale(0.16, 0.32);

            RenderMesh2D(meshes["printesaBordura"], shaders["VertexColor"], modelMatrix);


            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(cx, cy);
            modelMatrix *= transform2D::Translate(translateXEnemy, translateYEnemy);
            modelMatrix *= transform2D::Translate(-cx, -cy);
            modelMatrix *= transform2D::Rotate(angularStepInamic + M_PI);
            modelMatrix *= transform2D::Translate(0.36 * cx - 0.48, 0.26 * cy - 0.28);
            modelMatrix *= transform2D::Scale(0.1, 0.1);

            RenderMesh2D(meshes["printesaBordura"], shaders["VertexColor"], modelMatrix);


            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(cx, cy);
            modelMatrix *= transform2D::Translate(translateXEnemy, translateYEnemy);
            modelMatrix *= transform2D::Translate(-cx, -cy);
            modelMatrix *= transform2D::Rotate(angularStepInamic + M_PI);
            modelMatrix *= transform2D::Translate(0.36 * cx - 0.5, 0.26 * cy - 0.13);
            modelMatrix *= transform2D::Scale(0.1, 0.1);

            RenderMesh2D(meshes["printesaBordura"], shaders["VertexColor"], modelMatrix);

            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(cx, cy);
            modelMatrix *= transform2D::Translate(translateXEnemy, translateYEnemy);
            modelMatrix *= transform2D::Translate(-cx, -cy);
            modelMatrix *= transform2D::Rotate(angularStepInamic + M_PI);
            modelMatrix *= transform2D::Translate(0.36 * cx - 0.44, 0.26 * cy);
            modelMatrix *= transform2D::Scale(0.1, 0.1);

            RenderMesh2D(meshes["printesaBordura"], shaders["VertexColor"], modelMatrix);
}

void m1::Tema1::DrawObstacles(glm::mat3 visMatrix, float deltaTime)
{
    // obstacole:
    modelMatrix = visMatrix * transform2D::Translate(1, 5);
    modelMatrix *= transform2D::Scale(2, 1);
    RenderMesh2D(meshes["obs1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(1, 2);
    modelMatrix *= transform2D::Scale(0.5, 4);
    RenderMesh2D(meshes["obs1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(7, 1);
    modelMatrix *= transform2D::Scale(0.6, 2);
    RenderMesh2D(meshes["obs1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(7, 6);
    modelMatrix *= transform2D::Scale(1, 2);
    RenderMesh2D(meshes["obs1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(0, 3);
    modelMatrix *= transform2D::Scale(2, 0.6);
    RenderMesh2D(meshes["obs1"], shaders["VertexColor"], modelMatrix);
}

void m1::Tema1::DrawProiectil(glm::mat3 visMatrix, float deltaTime)
{
    for (auto i = proiectile.begin(); i != proiectile.end();) {
        if ((abs(i->transXDist - i->transX) <= 2) || (abs(i->transYDist - i->transY) <= 2)) {
            i->transX += deltaTime * cos(angularStepProiectil);
            i->transY += deltaTime * sin(angularStepProiectil);

            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(cxPro, cxPro);
            modelMatrix *= transform2D::Translate(i->transX, i->transY);
            modelMatrix *= transform2D::Translate(-cxPro, -cyPro);
            modelMatrix *= transform2D::Rotate(angularStepProiectil);
            modelMatrix *= transform2D::Scale(0.5, 0.5);
            modelMatrix *= transform2D::Translate(-cxPro, -cyPro);

            RenderMesh2D(meshes["proiectilul"], shaders["VertexColor"], modelMatrix);

            ++i;
        }
        else
        {
            i = proiectile.erase(i);
        }
    }
}

void m1::Tema1::GenerareEnemy(glm::mat3 visMatrix, float deltaTime)
{
    DrawEnemyB(visMatrix, deltaTime, translateXEnemy1, translateYEnemy1);
    DrawEnemyB(visMatrix, deltaTime, translateXEnemy2, translateYEnemy2);
    DrawEnemyB(visMatrix, deltaTime, translateXEnemy3, translateYEnemy3);
    DrawEnemyB(visMatrix, deltaTime, translateXEnemy4, translateYEnemy4);
}

void Tema1::FrameEnd()
{
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    if (window->KeyHold(GLFW_KEY_W)) {
        translateY += deltaTime * 0.9;
    }

    if (window->KeyHold(GLFW_KEY_A)) {
        translateX -= deltaTime * 0.9;
    }

    if (window->KeyHold(GLFW_KEY_S)) {
        translateY -= deltaTime * 0.9;
    }

    if (window->KeyHold(GLFW_KEY_D)) {
        translateX += deltaTime * 0.9;
    }
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event

    angularStep = -atan2(mouseY - playerRadius - resolution.y / 2, mouseX - playerRadius - resolution.x / 2);
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (button == 1) {
        angularStepProiectil = atan2(translateY - mouseX, translateY - mouseY) + M_PI;
        time_t momentan;

        time(&momentan);

        Glont glont(translateX, translateY, momentan, translateX, translateY);
        proiectile.push_back(glont);
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}