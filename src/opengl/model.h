#ifndef MODEL_H
#define MODEL_H

//#include <glad/glad.h>
#include "version.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "stb_image.h"
//#include <QOpenGLContext>

#include "mesh.h"
#include "shader.h"

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
//using namespace std;
#include <QDebug>
//#include <QThread>
//#include <QOpenGLExtraFunctions>
#include "Node.h"
#include <QStandardItem>
#include "Material.h"

//namespace  {
//#include "mesh.h"

class Model {
public:
    std::vector<Material> m_materials;
    std::vector<Texture> m_textures;

private:
    QOpenGLFunctionsCore* m_fun;

    //    std::vector<Texture> textures_loaded; // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    //    std::vector<Material> m_materials;
    //    const aiScene * m_scene = nullptr;
    std::vector<Mesh> m_meshes;
    Node* m_rootNode;

    //    Node m_rootNode;

    bool gammaCorrection;
    std::string m_filename;
    std::string directory;
    //    std::string m_file;
public:
    /*  Model Data */

    //    Model() {}

    /*  Functions   */
    // constructor, expects a filepath to a 3D model.
    //    Model(string const& path, bool gamma = false)
    Model(const std::string& path);
    // draws the model, and thus all its meshes
    void Draw(const Shader& shader);

    void modelBuild(QStandardItem* parent) const;

private:
    void modelRecurseNode(const Node* node, QStandardItem* parent) const;
    void modelRecurseMesh(const Mesh* mesh, QStandardItem* parent) const;
//    void modelRecurseFace(const Face* face, QStandardItem* parent) const;
    void modelMat4(const glm::mat4 matrix, QStandardItem* parent) const;
//    void modelVertex(const Vertex * vertex, QStandardItem * parent) const;

    //    static Assimp::Importer m_importer;
    void assimpLoadModel(std::string const& path);
    Node* assimpProcessNode(aiNode* node, const aiScene* scene, int depth);
    Mesh assimpProcessMesh(const aiMesh* mesh, const aiScene* scene, int depth);
    std::vector<uint> assimpLoadMaterialTextures(aiMaterial* mat, aiTextureType ai_type, Texture::e_type type);

    unsigned int TextureFromFile(const char* path, const std::string& directory);

public:
    std::string filename() const;
};

//    Assimp::Importer Model::m_importer;
//}

#endif
