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
#include <memory>
#include <opengl/geometry/boneGeometry.h>

class Model {
public:

public:
    Model(const std::string& path);
    //    Model(const Model& model) = delete;
    //    Model(Model& model) = delete;
    //    Model(const Model&& model) = delete;
    //    Model(const Model & model) = default;
    Model(Model&& model) noexcept = default;
    //    Model(const Model&& model);
    //    Model(Model&& model) noexcept;
    //    Model(Model&& model) = default;
    //    Model(Model & model);
    ~Model();
    void Draw(glm::mat4 modelMatrix, const Shader& shader) const;
    void buildItemModel(QStandardItem* parent) const;

private:
//    void modelRecurseNode(const Node& node, QStandardItem* parent) const;
//    void modelRecurseMesh(const Mesh& mesh, QStandardItem* parent) const;
//    void modelRecurseMaterial(const Material& material, QStandardItem* parent) const;
//    void modelMat4(const glm::mat4 matrix, QStandardItem* parent) const;

    void assimpLoadModel(std::string const& path);
    //    const Node* assimpProcessNode(const aiNode * node, const aiScene* scene, int depth);
    //    Mesh assimpProcessMesh(const aiMesh* mesh, const aiScene* scene, int depth);
    //    std::vector<uint> assimpLoadMaterialTextures(aiMaterial* mat, aiTextureType ai_type, Texture::Type type);

    //    unsigned int TextureFromFile(const char* path, const std::string& directory);
private:
//    QOpenGLFunctionsCore* m_fun;

    Materials m_materials;
    //    std::vector<Texture> m_textures;
    Textures m_textures;


//    std::vector<Animation> m_animations;
    Animations m_animations;
    Meshes m_meshes;

//    BoneGeometry m_boneGeometry;

    //    const Node * m_rootNode = nullptr;
    std::unique_ptr<Node> m_rootNode;
    //    std::vector<Node> m_nodes;

    //    bool gammaCorrection;
    std::string m_filename;
    std::string directory;

public:
    std::string filename() const;
};

//    Assimp::Importer Model::m_importer;
//}

#endif
