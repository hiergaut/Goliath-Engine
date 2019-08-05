#ifndef MESH_H
#define MESH_H

//#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "version.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
//using namespace std;
//#include <QOpenGLExtraFunctions>
#include <QDebug>
#include <QOpenGLFunctions>
//#include <ostream>
#include <sstream>

//struct Vertex {
//    // position
//    glm::vec3 Position;
//    // normal
//    glm::vec3 Normal;
//    // texCoords
//    glm::vec2 TexCoords;
//    // tangent
//    glm::vec3 Tangent;
//    // bitangent
//    glm::vec3 Bitangent;
//};
using Vertex = glm::vec3;
//struct Vertex {
//    glm::vec3 ;
//};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

struct Face {
    std::vector<uint> m_indices;
};

//struct Face {

//};

class Mesh {
public:
    /*  Mesh Data  */
    QOpenGLFunctionsCore* m_fun;

    std::string m_name;
    std::vector<Face> m_faces;
    std::vector<Vertex> m_vertices;

//    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    unsigned int VAO;

    /*  Functions  */
    // constructor
//    Mesh(std::string name, std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) : m_name(name)
    Mesh(std::string name);
//    operator QString() const;
    void Draw(const Shader& shader);

    void setupMesh();
private:
    /*  Render data  */
    unsigned int VBO, EBO;

    /*  Functions    */
    // initializes all the buffer objects/arrays
};
#endif
