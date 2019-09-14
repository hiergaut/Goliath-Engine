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
//#include <opengl/geometry/boneGeometry.h>
//#include <gui/editor/3dview/MainWindow3dView.h>
//#include <opengl/BoundingBox.h>
//#include <opengl/rayTracer/Ray.h>

//#include <gui/editor/MainWindowEditor.h>
//#include <gui/editor/3dview/MainWindow3dView.h>

//#include <engine/scene/Object.h>

class Model {
public:
//    mutable bool m_selected = false;
//    mutable BoundingBox m_box;
    Meshes m_meshes;
//    mutable glm::mat4 m_transform = glm::mat4(1.0f);

//    float m_radius;

//    enum Type {
//        OBJECT,
//        CAMERA,
//        LIGHT
//    } m_type;

public:
    Model(const std::string& path);
    Model(std::ifstream & file);
    //    Model(const Model& model) = delete;
    //    Model(Model& model) = delete;
    //    Model(const Model&& model) = delete;

//        Model(const Model & model) = default;
//    Model & operator=(const Model &) = default;
    Model(Model&& model) noexcept;

    //    Model(const Model&& model);
    //    Model(Model&& model) noexcept;
    //    Model(Model&& model) = default;
    //    Model(Model & model);
    ~Model();

    void prepareHierarchy(ulong frameTime) const;

    void draw(const Shader &shader, bool dotCloud, const glm::mat4 &modelMatrix = glm::mat4(1.0f), const glm::mat4 & worldTransform = glm::mat4(1.0f)) const override;
    void draw(const Shader & shader, const glm::mat4 &modelMatrix = glm::mat4(1.0f), const glm::mat4 &worldTransform = glm::mat4(1.0f)) const override;
//    void draw(const glm::mat4 &modelMatrix, const Shader & shader, const MainWindow3dView & view, const glm::mat4 &worldTransform = glm::mat4(1.0f)) const override;

    void updateBoundingBox() const override;
    void drawBoundingBox(const Shader & shader) const override;
//    void selectObject(const Ray & ray, float &depthMin, bool &find, uint &iModelMin, uint &iMeshMin, uint &iBoneMin, uint &iTriangleMin, bool unselect = false) const;
//    void unselectRay(const Ray & ray) const;
//    void objectFinderRay(const Ray & ray) const;
//    void


    void DrawHierarchy(const glm::mat4 &modelMatrix, const MainWindow3dView & view, const glm::mat4 &worldTransform = glm::mat4(1.0f)) const;
    void buildItemModel(QStandardItem* parent) const;

//    void load(std::ifstream & file) const;
    void save(std::ofstream & file) const;
//    glm::mat4 scaleCenter(float scale) const;

private:
//    void modelRecurseNode(const Node& node, QStandardItem* parent) const;
//    void modelRecurseMesh(const Mesh& mesh, QStandardItem* parent) const;
//    void modelRecurseMaterial(const Material& material, QStandardItem* parent) const;
//    void modelMat4(const glm::mat4 matrix, QStandardItem* parent) const;

    void assimpLoadModel(std::string const& path);
//    void updateBoundingBoxing();
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
    mutable int m_currentAnimation = -1;


//    glm::vec3 m_boxMin;
//    glm::vec3 m_boxMax;


    //    const Node * m_rootNode = nullptr;
    //    std::vector<Node> m_nodes;

    //    bool gammaCorrection;
    std::string m_filename;
    std::string directory;

//    BoneGeometry m_boneGeometry;
    std::unique_ptr<Node> m_rootNode;

//    mutable std::vector<glm::vec3> m_triangles;

public:
    std::string filename() const;
};

//    Assimp::Importer Model::m_importer;
//}

#endif
