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
//#include "Vertex.h"
#include <engine/scene/model/Vertex.h>
#include "bone/Bone.h"
#include <QStandardItem>
#include <assimp/scene.h>

#include "../material/Material.h"

#include <opengl/BoundingBox.h>
//#include <gui/editor/3dview/MainWindow3dView.h>

class Mesh;
using Meshes = std::vector<Mesh>;

class Mesh {
public:
    Materials * m_materials;
    Textures * m_textures;

    std::vector<Bone> m_bones;
    mutable glm::mat4 m_transform;

    std::vector<Vertex> m_vertices;
    std::vector<std::set<uint>> m_triangles; // triangles per vertex

    mutable BoundingBox m_box;

    std::string m_name;

    std::vector<uint> m_indices; // triangles

public:
    //    Mesh(std::string name, std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) : m_name(name)
    Mesh(const aiMesh* ai_mesh, Materials * materials, Textures * textures);
    Mesh(std::ifstream& file, Materials * materials, Textures * textures);
//        Mesh(const Mesh & mesh) = delete ;
        Mesh(const Mesh & mesh) = delete;
    Mesh(Mesh&& mesh) noexcept = default;
//    Mesh & operator =(const Mesh& mesh);

    ~Mesh();
    //    Mesh(const & mesh)
    //    operator QString() const;
    void buildItemModel(QStandardItem* parent) const;
    void setupMesh();
    void draw(const Shader& shader) const;
    void draw(const Shader& shader, bool dotCloud) const;
    void drawBoundingBox(const Shader & shader) const;

    void save(std::ofstream& file) const;

//    void initBonesBoundingBox() const;
    void updateBoundingBox(const glm::mat4 &modelTransform) const;

private:
//    std::vector<BoundingBox> m_box;
    /*  Render data  */
    uint m_iMaterial;
    QOpenGLFunctionsCore* m_fun;

    /*  Mesh Data  */
    //    uint m_numAnimMesh;

    //    std::vector<Face> m_faces;
    //    std::vector<uint> m_boneOfVertice;
    std::vector<VertexBoneData> m_bonesData;

    uint m_sumBoneWeights;

    //    std::vector<Vertex> vertices;
    //    std::vector<unsigned int> indices;
    uint m_numFaces;
    //    std::vector<uint> m_lenFaces;

    //    std::vector<Texture> textures;

    unsigned int m_vao;

    uint m_bbo;
    unsigned int VBO, EBO;

    /*  Functions    */
    // initializes all the buffer objects/arrays
};
#endif
