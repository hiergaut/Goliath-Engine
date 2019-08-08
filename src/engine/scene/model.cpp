#include "model.h"
#include <QFileInfo>
#include <QPainter>

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
    m_meshes.reserve(50);
    m_materials.reserve(50);
    m_textures.reserve(100);

    //        initializeOpenGLFunctions();
    //    fun = QOpenGLContext::globalShareContext()->versionFunctions<QOpenGLFunctionsCore>();
    //        fun = ctx->versionFunctions<QOpenGLFunctionsCore>();
    //        m_fun = fun;
    //        if (!fake) {
    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    //    qDebug() << QThread::currentThreadId() << "[MODEL]" << this << "[CONTEXT]" << fun;

    assimpLoadModel(g_resourcesPath + path);
    //    std::cout << "[MODEL] load : " << path << std::endl;
    //        }
    //    std::cout << "[Model] create " << this << std::endl;
    //    std::cout << "\033[32m";
    //    std::cout << "[Model] " << m_filename << " created " << this << std::endl;
    //    std::cout << "\033[0m";
}

//Model::Model(const Model &model)
////    : m_meshes(model.m_meshes)
////    : m_rootNode = std::make_uni
//    : m_rootNode(std::make_unique<Node>(*model.m_rootNode))
////    : m_rootNode(std::move(model.m_rootNode))
////    : m_rootNode(std::move(model.m_rootNode))
//{
//    std::cout << "\033[35m";
//    std::cout << "[Model] " << m_filename << " " << &model << " left moving to " << this << std::endl;
//    std::cout << "m_fun : " << model.m_fun << ", m_meshes : " << &model.m_meshes << " " << model.m_meshes.size() << ", m_rootNode : " << &model.m_rootNode << " " << model.m_rootNode.get() << " " << model.m_rootNode.get()->m_name <<  ", m_filename : " << model.m_filename <<  std::endl;
//    m_fun = model.m_fun;

////    m_rootNode = std::move(model.m_rootNode);
////    m_rootNode = std::move(model.m_rootNode);
////    m_rootNode = std::make_unique<Node>();
////    m_rootNode = std::make_unique<Node>(model.m_rootNode.get());

//    m_filename = model.m_filename;
//    directory = model.directory;
//    std::cout << "m_fun : " << m_fun << ", m_meshes : " << &m_meshes << " " << m_meshes.size() << ", m_rootNode : " << &m_rootNode << " " << m_rootNode.get() << " " << m_rootNode.get()->m_name <<  ", m_filename : " << m_filename <<  std::endl;
//    std::cout << "\033[0m";
////    m_rootNode = model.m_rootNode;
////    m_rootNode = model.m_rootNode;
////    model.m_rootNode = nullptr;

//}

//Model::Model(Model &model)
//{
//    std::cout << "fuck" << std::endl;

//}

//Model::Model(Model &&model) noexcept
////    : m_meshes(std::move(model.m_meshes))
////    , m_rootNode(std::move(model.m_rootNode))
//    : m_fun(model.m_fun)
//{
////    m_meshes.reserve(100);
////    std::cout << "\033[33m";
////    std::cout << "[Model] " << m_filename << " moving " << this << std::endl;
////    std::cout << "\033[0m";
//    std::cout << "\033[34m";
//    std::cout << "[Model] " << model.m_filename << " " << &model << " right moving to " << this << std::endl;
//    std::cout << "m_fun : " << model.m_fun << ", m_meshes : " << &model.m_meshes << " " << model.m_meshes.size() << ", m_rootNode : " << &model.m_rootNode << " " << model.m_rootNode.get() << " " << model.m_rootNode.get()->m_name <<  ", m_filename : " << model.m_filename <<  std::endl;
////    m_fun = model.m_fun;

//    m_rootNode = std::move(model.m_rootNode);
//    m_meshes = std::move(model.m_meshes);
//    m_materials = std::move(model.m_materials);
////    m_rootNode = std::move(model.m_rootNode);
////    m_rootNode = std::make_unique<Node>();
////    m_rootNode = std::make_unique<Node>(model.m_rootNode.get());

//    m_filename = model.m_filename;
//    directory = model.directory;
//    std::cout << "m_fun : " << m_fun << ", m_meshes : " << &m_meshes << " " << m_meshes.size() << ", m_rootNode : " << &m_rootNode << " " << m_rootNode.get() << " " << m_rootNode.get()->m_name <<  ", m_filename : " << m_filename <<  std::endl;
//    std::cout << "\033[0m";
////    m_rootNode = model.m_rootNode;
////    m_rootNode = model.m_rootNode;
////    m_rootNode = model.m_rootNode;

//}

//Model::Model(const Model &&model)
//{
//    std::cout << "bitch" << std::endl;

//}

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
        m_meshes.emplace_back(ai_mesh);
    }
    Q_ASSERT(scene->mNumMeshes == m_meshes.size());

    //    m_rootNode = new Node(scene->mRootNode);
    //    m_rootNode = std::make_unique<
    m_rootNode = std::make_unique<Node>(scene->mRootNode);

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
        m_fun->glBindVertexArray(mesh.VAO);
        m_fun->glDrawElements(GL_TRIANGLES, mesh.m_indices.size(), GL_UNSIGNED_INT, 0);
        m_fun->glBindVertexArray(0);

        // always good practice to set everything back to defaults once configured.
        m_fun->glActiveTexture(GL_TEXTURE0);
    }
}

// -------------------------------------------------------------------
void Model::modelBuild(QStandardItem* parent) const
{
    modelRecurseNode(*m_rootNode, parent);

    QStandardItem* item = new QStandardItem("materials");
    parent->appendRow(item);
    for (const Material& material : m_materials) {
        modelRecurseMaterial(material, item);
    }
}

void Model::modelRecurseNode(const Node& node, QStandardItem* parent) const
{
    QStandardItem* item = new QStandardItem(QIcon(":/icons/node.png"), QString(node.m_name.c_str()));
    parent->appendRow(item);

    //    QStandardItem* item2 = new QStandardItem("fuck");
    //    parent->appendColumn({item2});

    const glm::mat4& m = node.m_transformation;
    modelMat4(node.m_transformation, item);

    for (ulong i = 0; i < node.m_iMeshes.size(); ++i) {
        //        QStandardItem * item2 = new QStandardItem("mesh:" + QString::number(node->m_meshes[i]) + ", " + m_meshes[node->m_meshes[i]]);
        //        QStandardItem * item2 = new QStandardItem(QString::number(node->m_meshes[i]) + "  " + m_meshes[node->m_meshes[i]]);

        Q_ASSERT(node.m_iMeshes[i] < m_meshes.size());
        //        Q_ASSERT(node->m_numMeshes == node->m_iMeshes.size());
        const Mesh& mesh = m_meshes[node.m_iMeshes[i]];
        modelRecurseMesh(mesh, item);
        //        QStandardItem * item2 = new QStandardItem("mesh : " + QString::number(node->m_meshes[i]));
        //        item->appendRow(item2);
    }

    //    std::cout << "node nbchildren : " << node->m_numChildren << std::endl;
    for (int i = 0; i < node.m_children.size(); ++i) {
        modelRecurseNode(node.m_children[i], item);
    }

    //    parent->appendRow(new QStandardItem(str));
}

void Model::modelRecurseMesh(const Mesh& mesh, QStandardItem* parent) const
{
    //    QStandardItem * item = new QStandardItem(mesh->m_name.c_str());
    QStandardItem* item = new QStandardItem(QIcon(":/icons/mesh.png"), QString(mesh.m_name.c_str()) + "  f:" + QString::number(mesh.m_numFaces) + "  v:" + QString::number(mesh.m_vertices.size()));
    parent->appendRow(item);

    const Material& material = m_materials[mesh.m_iMaterial];
    //    modelRecurseMaterial(material, item);

//    QStandardItem* item2 = new QStandardItem(material.m_name.c_str());
    QStandardItem* item2 = new QStandardItem(QIcon(":/icons/material.png"), material.m_name.c_str());
    item->appendRow(item2);

    //    QStandardItem * item2 = new QStandardItem(QIcon)
    //    for (const Bone& bone : mesh->m_bones) {
    //        QStandardItem* item2 = new QStandardItem(QIcon(":/icons/bone.png"), bone.m_name.c_str());
    //        item->appendRow(item2);
    //    }
}

void Model::modelRecurseMaterial(const Material& material, QStandardItem* parent) const
{
    QStandardItem* item2 = new QStandardItem(QIcon(":/icons/material.png"), material.m_name.c_str());

    QStandardItem* itemAmbient = new QStandardItem("ambient");
    item2->appendRow(itemAmbient);

    //    material.
    //    QPainter * paint = new QPainter(&pixmap);
    QPixmap pixmap(":/icons/disk.png");
    QPainter painter(&pixmap);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    //    painter.fillRect(pixmap.rect(), Qt::red);
    for (int i = 0; i < Color::Etype::size; ++i) {
        const Color& color(material.m_colors[i]);
        //    for ()
        painter.fillRect(pixmap.rect(), color);
        //        painter.end();
        //    paint->setBrush(QBrush(Qt::black));
        //    paint->drawPie(pixmap.rect(), 0, 1);
        //    pixmap.fill(QColor(material.m_colorDiffuse.x * 255.0f, material.m_colorDiffuse.y * 255.0f, material.m_colorDiffuse.z * 255.0f));

        QIcon icon(pixmap);

        if (i == 0) {
            QStandardItem* item3 = new QStandardItem(icon, "");
            itemAmbient->appendRow(item3);
        } else {
            QStandardItem* item3 = new QStandardItem(icon, color.to_string());
            item2->appendRow(item3);
        }
    }
    painter.end();

    for (int i = 0; i < Texture::size; ++i) {
        for (int j = 0; j < material.m_iTextures[i].size(); ++j) {
            const Texture& texture = m_textures[material.m_iTextures[i][j]];

            if (i == 0) {
                QStandardItem* item3 = new QStandardItem(QIcon(texture.m_pixmap), texture.m_filename.c_str());
                itemAmbient->appendRow(item3);
            } else {
                QStandardItem* item3 = new QStandardItem(QIcon(texture.m_pixmap), QString(texture) + texture.m_filename.c_str());
                item2->appendRow(item3);
            }
        }
    }
    parent->appendRow(item2);
}

void Model::modelMat4(const glm::mat4 matrix, QStandardItem* parent) const
{
    QStandardItem* item = new QStandardItem("transformation");

    QString str;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            str += QString::number(matrix[i][j]) + " ";
        }
        if (i != 3) {
            str += "\n";
        }
    }
    QStandardItem* item2 = new QStandardItem(str);
    item->appendRow(item2);

    parent->appendRow(item);
}

//void Model::modelVertex(const Vertex *vertex, QStandardItem *parent) const
//{

//}

// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).

// checks all material textures of a given type and loads the textures if they're not loaded yet.
// the required info is returned as a Texture struct.
std::string Model::filename() const
{
    return m_filename;
}
