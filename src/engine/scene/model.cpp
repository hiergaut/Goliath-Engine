#include "model.h"
#include <QFileInfo>
//#include <QPainter>

//#include "Assimp.h"
#include <assimp/Assimp.h>

//#include <iostream>
//#include <vector>
#include <memory>
//#include <cstdio>
//#include <fstream>
//#include <cassert>
#include <functional>
#include <glm/gtc/matrix_transform.hpp>

Model::Model(const std::string& path)
//        : gammaCorrection(gamma),
//        : m_file(path)
{
    //    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();

    m_meshes.reserve(50);
    m_materials.reserve(50);
    m_textures.reserve(100);

    //        initializeOpenGLFunctions();
    //    fun = QOpenGLContext::globalShareContext()->versionFunctions<QOpenGLFunctionsCore>();
    //        fun = ctx->versionFunctions<QOpenGLFunctionsCore>();
    //        m_fun = fun;
    //        if (!fake) {
    //    qDebug() << QThread::currentThreadId() << "[MODEL]" << this << "[CONTEXT]" << fun;

    assimpLoadModel(g_resourcesPath + path);
    //    std::cout << "[MODEL] load : " << path << std::endl;
    //        }
    //    std::cout << "[Model] create " << this << std::endl;
    //    std::cout << "\033[32m";
    //    std::cout << "[Model] " << m_filename << " created " << this << std::endl;
    //    std::cout << "\033[0m";
}

Model::~Model()
{
    //    qDebug() << "[Model] destruct " << this;
    std::cout << "\033[31m";
    std::cout << "[Model] '" << m_filename << "' destruct " << this << std::endl;
    std::cout << "\033[0m";

    //    delete m_rootNode;

    //    if (m_rootNode != nullptr)
    //        delete m_rootNode;
}

//    static Assimp::Importer m_importer;
/*  Functions   */
// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
void Model::assimpLoadModel(std::string const& path)
{

    //        qDebug() << QThread::currentThreadId() << "[MODEL][LOAD]" << this << "[CONTEXT]" << m_fun;
    //        qDebug() << QThread::currentThreadId() << "[MODEL][LOAD]" << this << "[CONTEXT]" << QOpenGLContext::currentContext()->functions();
    // read file via ASSIMP
    Assimp::Importer m_importer;
    //        qDebug() << "[MODEL] m_importer : " << &m_importer;
    //    const aiScene* scene = m_importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);
    //    const aiScene* scene = m_importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_SplitByBoneCount);
    const aiScene* scene = m_importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    //    const aiScene* scene = m_importer.ReadFile(path, aiProcess_FlipUVs);
    //    m_scene = m_importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    //        const aiScene* scene = m_importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_FlipWindingOrder);
    //            const aiScene* scene = m_importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_MakeLeftHanded);
    //    qDebug() << "[MODEL]" << directory.c_str() << "aiScene : " << scene << "importer" << &m_importer << "numMeshes" << scene->mNumMeshes;
    //        const aiScene* scene = m_importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_GenNormals);
    // check for errors
    if (!scene || !scene->mRootNode) // if is Not Zero
    {
        std::cout << "ERROR::ASSIMP:: '" << m_importer.GetErrorString() << "'" << std::endl;
        //        return;
        exit(1);
    }
    if (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
        std::cout << "ERROR::ASSIMP::SCENE_FLAGS_INCOMPLETE '" << m_importer.GetErrorString() << "'" << std::endl;
        //        return;
        //        exit(1);
    }
    //    Q_ASSERT(scene && scene->mRootNode);
    // retrieve the directory path of the filepath
    directory = path.substr(0, path.find_last_of('/'));

    QFileInfo fileInfo(path.c_str());
    m_filename = fileInfo.baseName().toStdString();

    for (uint i = 0; i < scene->mNumAnimations; ++i) {
        const aiAnimation* ai_animation = scene->mAnimations[i];
        m_animations.emplace_back(ai_animation);
    }

    //    m_materials.reserve(100);
    for (uint i = 0; i < scene->mNumMaterials; ++i) {
        //        const aiMaterial * scene->mMaterials[i];
        const aiMaterial* ai_material = scene->mMaterials[i];
        //        std::cout << "load material " << i << std::endl;
        //        Material material(ai_material);
        //        Material material(ai_material, m_textures, directory);
        //        m_materials.push_back(material);
        //        m_materials.push_back(std::move(Material(ai_material, m_textures, directory)));
        m_materials.emplace_back(ai_material, m_textures, directory);
        //        m_materials.push_back({ai_material, m_textures, directory});

        //        m_materials.push_back(std::move(material));
    }
    Q_ASSERT(scene->mNumMaterials == m_materials.size());

    m_meshes.clear();
    for (uint i = 0; i < scene->mNumMeshes; ++i) {
        const aiMesh* ai_mesh = scene->mMeshes[i];
        //        m_meshes.push_back(assimpProcessMesh(ai_mesh, scene, 0));
        //        m_meshes.push_back(std::move(Mesh(ai_mesh)));
        m_meshes.emplace_back(ai_mesh, m_materials, m_textures);
    }
    Q_ASSERT(scene->mNumMeshes == m_meshes.size());

    //    m_rootNode = new Node(scene->mRootNode);
    //    m_rootNode = std::make_unique<
    m_rootNode = std::make_unique<Node>(scene->mRootNode, m_meshes, m_animations);

    //    std::make_unique<Node>();

    //    m_nodes.push_back(Node(scene->mRootNode));

    //    m_rootNode = new Node(scene->mRootNode);
    //    Q_ASSERT(m_rootNode);
    //    std::cout << "root node : " << m_rootNode << std::endl;
    //    std::cout << "assimpProcessNode root node " << m_rootNode <<  " " <<m_rootNode->m_children.size() << std::endl;
}

// draws the model, and thus all its meshes
void Model::Draw(glm::mat4 modelMatrix, const Shader& shader) const
{

    //    shader.use();

    //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    ////    m_fun->glBindVertexArray()
    ///
    /////
    /// i
    if (m_animations.size() > 0) {
        m_rootNode->draw(shader, modelMatrix);
        shader.setMat4("model", glm::mat4(1));
        shader.setBool("isSkeleton", true);
    }
    else {
        shader.setBool("isSkeleton", false);
    }

    //    model = glm::mat4(1.0f);
    //    model = glm::scale(model, glm::vec3(0.01));
    //    model = glm::rotate(model, 1.57f, glm::vec3(1, 0, 0));
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //    m_boneGeometry.draw(shader, glm::vec3(0, 0, 0), glm::vec3(10, 10, 10));
    //    shader.setBool("isSkeleton", true);
    for (const Mesh& mesh : m_meshes) {
//        shader.setMat4("model", modelMatrix);
        //        const Mesh& mesh = m_meshes[i];
        mesh.draw(shader);
    }

    //    shader.use();
}

// -------------------------------------------------------------------
void Model::buildItemModel(QStandardItem* parent) const
{
    //    modelRecurseNode(*m_rootNode, parent);
    m_rootNode->buildItemModel(parent);

    //    QStandardItem* item = new QStandardItem(QIcon(":/icons/animations.png"), "animations  " + QString::number(m_animations.size()));
    //    parent->appendRow(item);
    //    for (const Animation& animation : m_animations) {
    //        animation.buildItemModel(item);
    //    }

    //    item = new QStandardItem("materials  " + QString::number(m_materials.size()));
    //    parent->appendRow(item);
    //    for (const Material& material : m_materials) {
    //        //        modelRecurseMaterial(material, item);
    //        material.buildItemModel(item);
    //    }
}

//void Model::modelRecurseMaterial(const Material& material, QStandardItem* parent) const
//{
//}

//void Model::modelMat4(const glm::mat4 matrix, QStandardItem* parent) const
//{
//    QStandardItem* item = new QStandardItem("transformation");

//    QString str;
//    for (int i = 0; i < 4; ++i) {
//        for (int j = 0; j < 4; ++j) {
//            str += QString::number(matrix[i][j]) + " ";
//        }
//        if (i != 3) {
//            str += "\n";
//        }
//    }
//    QStandardItem* item2 = new QStandardItem(str);
//    item->appendRow(item2);

//    parent->appendRow(item);
//}

std::string Model::filename() const
{
    return m_filename;
}
