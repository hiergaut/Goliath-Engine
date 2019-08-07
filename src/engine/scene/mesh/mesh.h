#ifndef MESH_H
#define MESH_H

//#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//#include "shader.h"
#include <opengl/shader.h>
//#include "version.h"
#include <opengl/version.h>

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
//#include "model.h"
//#include "Bone.h"
#include "bone/Bone.h"
#include <assimp/scene.h>
#include "Vertex.h"


class Mesh {
public:
    /*  Mesh Data  */
    QOpenGLFunctionsCore* m_fun;

    std::string m_name;
//    std::vector<Face> m_faces;
    std::vector<uint> m_indices;
    std::vector<Vertex> m_vertices;
    uint m_iMaterial;

    std::vector<Bone> m_bones;

//    std::vector<Vertex> vertices;
//    std::vector<unsigned int> indices;
    uint m_numFaces;
//    std::vector<uint> m_lenFaces;


//    std::vector<Texture> textures;
    unsigned int VAO;

    /*  Functions  */
    // constructor
//    Mesh(std::string name, std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) : m_name(name)
    Mesh(const aiMesh * ai_mesh);
//    operator QString() const;
//    void Draw(const Shader& shader, const Model & model);

    void setupMesh();
private:
    /*  Render data  */
    unsigned int VBO, EBO;

    /*  Functions    */
    // initializes all the buffer objects/arrays
};
#endif
