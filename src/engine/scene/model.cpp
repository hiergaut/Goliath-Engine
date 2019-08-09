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

Model::Model(const std::string& path)
//        : gammaCorrection(gamma),
//        : m_file(path)
{
    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();

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
    const aiScene* scene = m_importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_SplitByBoneCount);
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
        m_meshes.emplace_back(ai_mesh, m_materials);
    }
    Q_ASSERT(scene->mNumMeshes == m_meshes.size());

    //    m_rootNode = new Node(scene->mRootNode);
    //    m_rootNode = std::make_unique<
    m_rootNode = std::make_unique<Node>(scene->mRootNode, m_meshes);

    //    std::make_unique<Node>();

    //    m_nodes.push_back(Node(scene->mRootNode));

    //    m_rootNode = new Node(scene->mRootNode);
    //    Q_ASSERT(m_rootNode);
    //    std::cout << "root node : " << m_rootNode << std::endl;
    //    std::cout << "assimpProcessNode root node " << m_rootNode <<  " " <<m_rootNode->m_children.size() << std::endl;
}

// draws the model, and thus all its meshes
void Model::Draw(const Shader& shader) const
{

    for (const Mesh& mesh : m_meshes) {
        //        const Mesh& mesh = m_meshes[i];

        const Material& material = m_materials[mesh.m_iMaterial];
        //        const Material& material = mesh.m_material;
        //        const Material& material = mesh.m_material;

        uint cpt = 0;
        //    for (uint diffuse : material.m_diffuseMaps) {
        //    for (uint i = 0; i < material.m_diffuseMaps.size();++i) {
        //        for (uint i =0; i <material.m_iTextures->size(); ++i) {
        //                const Texture& texture = m_textures[material.m_iTextures[i]];

        //        }
        for (uint i = 0; i < Texture::size; ++i) {
            for (uint j = 0; j < material.m_iTextures[i].size(); ++j) {
                const Texture& texture = m_textures[material.m_iTextures[i][j]];

                m_fun->glActiveTexture(GL_TEXTURE0 + cpt);
                std::string number = std::to_string(j);
                std::string name = std::string(texture);
                m_fun->glUniform1i(m_fun->glGetUniformLocation(shader.ID, (name + number).c_str()), cpt);
                m_fun->glBindTexture(GL_TEXTURE_2D, texture.m_id);

                ++cpt;
                //            }
            }
        }

        // draw mesh
        m_fun->glBindVertexArray(mesh.m_vao);
        m_fun->glDrawElements(GL_TRIANGLES, mesh.m_indices.size(), GL_UNSIGNED_INT, 0);
        m_fun->glBindVertexArray(0);

        // always good practice to set everything back to defaults once configured.
        m_fun->glActiveTexture(GL_TEXTURE0);
    }
}

// -------------------------------------------------------------------
void Model::buildItemModel(QStandardItem* parent) const
{
    //    modelRecurseNode(*m_rootNode, parent);
    m_rootNode->buildItemModel(parent);

    QStandardItem* item = new QStandardItem(QIcon(":/icons/animations.png"), "animations  " + QString::number(m_animations.size()));
    parent->appendRow(item);
    for (const Animation& animation : m_animations) {
        animation.buildItemModel(item);
    }

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
