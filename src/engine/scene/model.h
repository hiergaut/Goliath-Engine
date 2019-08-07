#ifndef MODEL_H
#define MODEL_H

//#include <glad/glad.h>
//#include "version.h"
#include <opengl/version.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//#include "stb_image.h"
#include <image/stb_image.h>
//#include <QOpenGLContext>

//#include "mesh.h"
#include "mesh/mesh.h"
//#include "shader.h"
#include <opengl/shader.h>

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
//#include "Material.h"
#include "material/Material.h"

#include "animation/Animation.h"


class Model {
public:
    Materials m_materials;
//    std::vector<Texture> m_textures;
    Textures m_textures;

private:
    QOpenGLFunctionsCore* m_fun;

    std::vector<Animation> m_animations;
    std::vector<Mesh> m_meshes;
    Node * m_rootNode = nullptr;


//    bool gammaCorrection;
    std::string m_filename;
    std::string directory;
public:
    Model(const std::string& path);
    ~Model();
    void Draw(const Shader& shader);

    void modelBuild(QStandardItem* parent) const;

private:
    void modelRecurseNode(const Node* node, QStandardItem* parent) const;
    void modelRecurseMesh(const Mesh* mesh, QStandardItem* parent) const;
    void modelMat4(const glm::mat4 matrix, QStandardItem* parent) const;

    void assimpLoadModel(std::string const& path);
    Node* assimpProcessNode(aiNode* node, const aiScene* scene, int depth);
//    Mesh assimpProcessMesh(const aiMesh* mesh, const aiScene* scene, int depth);
//    std::vector<uint> assimpLoadMaterialTextures(aiMaterial* mat, aiTextureType ai_type, Texture::Type type);

//    unsigned int TextureFromFile(const char* path, const std::string& directory);

public:
    std::string filename() const;
};

//    Assimp::Importer Model::m_importer;
//}

#endif
