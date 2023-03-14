#include "utile.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* utile::CreateSquare(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* utile::CreateCircle(const std::string& name, glm::vec3 center, glm::vec3 color, int verticesNr, bool fill)
{
    std::vector<VertexFormat> vertices;
    vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), color, glm::vec3(0.2, 0.8, 0.6)));
    vertices.push_back(VertexFormat(glm::vec3(1, 0, 0), color, glm::vec3(0.2, 0.8, 0.6)));

    float angle = RADIANS(M_PI*2);
    for (int i = 2; i <= verticesNr; i++) {
        glm::vec3 tmp(cos(i * angle) , sin(i * angle) , 0);
        vertices.push_back(VertexFormat(tmp, color));
    }

    std::vector<unsigned int> indices;
    for (int i = 0; i <= verticesNr; i++) {
        indices.push_back(i);
    }
    indices.push_back(1);
 
    Mesh* cerc = new Mesh(name);
    cerc->SetDrawMode(GL_TRIANGLE_FAN);
    cerc->InitFromData(vertices, indices);

    return cerc;
}

//Mesh* utile::CreateTriangle(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
//{
//    glm::vec3 corner = leftBottomCorner;
//
//    std::vector<VertexFormat> vertices =
//    {
//        VertexFormat(corner, color),
//        VertexFormat(corner + glm::vec3(length, 0, 0), color),
//    };
//
//    Mesh* triangle = new Mesh(name);
//    std::vector<unsigned int> indices = { 0, 1, 2 };
//
//    if (!fill) {
//        triangle->SetDrawMode(GL_LINE_LOOP);
//    }
//    else {
//        // Draw 2 triangles. Add the remaining 2 indices
//        indices.push_back(0);
//        indices.push_back(2);
//    }
//
//    triangle->InitFromData(vertices, indices);
//    return triangle;
//}
