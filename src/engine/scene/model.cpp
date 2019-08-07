#include "model.h"
#include <QFileInfo>
#include <QPainter>

//#include "Assimp.h"
#include <assimp/Assimp.h>

Model::Model(const std::string& path)
//        : gammaCorrection(gamma),
//        : m_file(path)
{

    //        initializeOpenGLFunctions();
    //    fun = QOpenGLContext::globalShareContext()->versionFunctions<QOpenGLFunctionsCore>();
    //        fun = ctx->versionFunctions<QOpenGLFunctionsCore>();
    //        m_fun = fun;
    //        if (!fake) {
    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    //    qDebug() << QThread::currentThreadId() << "[MODEL]" << this << "[CONTEXT]" << fun;

    assimpLoadModel(g_resourcesPath + path);
    std::cout << "[MODEL] load : " << path << std::endl;
    //        }
}
Model::~Model()
{
    delete m_rootNode;
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
    qDebug() << "[MODEL]" << path.c_str() << "aiScene : " << scene << "importer" << &m_importer << "numMeshes" << scene->mNumMeshes;
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

    //            std::cout << "scene:";
    //            std::cout << ", numLights: " << scene->mNumLights;
    //            std::cout << ", numMeshes: " << scene->mNumMeshes;
    //            std::cout << ", numCameras: " << scene->mNumCameras;
    //            std::cout << ", numTextures: " << scene->mNumTextures;
    //            std::cout << ", numMaterials: " << scene->mNumMaterials;
    //                std::cout << ", numAnimations: " << scene->mNumAnimations << std::endl;
    //    for (uint i =0; i <scene->mNumTextures; ++i) {

    //    }
    //    for (uint i =0; i <scene->mNumAnimations; ++i) {
    //        const aiAnimation * ai_animation = scene->mAnimations[i];

    //        m_animations.push_back(Animation(ai_animation));

    //    }
    for (uint i = 0; i < scene->mNumMaterials; ++i) {
        //        const aiMaterial * scene->mMaterials[i];
        const aiMaterial* ai_material = scene->mMaterials[i];
        //        Material material(ai_material);
        //        Material material(ai_material, m_textures, directory);
        //        m_materials.push_back(material);
        m_materials.push_back(Material(ai_material, m_textures, directory));
        //        m_materials.push_back({ai_material, m_textures, directory});

        //        m_materials.push_back(std::move(material));
    }

    for (uint i = 0; i < scene->mNumMeshes; ++i) {
        const aiMesh* ai_mesh = scene->mMeshes[i];
        //        m_meshes.push_back(assimpProcessMesh(ai_mesh, scene, 0));
        m_meshes.push_back(std::move(Mesh(ai_mesh)));
    }

    //    for (int i =0; i <scene->mNumTextures; ++i) {

    //    }

    // process ASSIMP's root node recursively
    //    m_rootNode = scene->mRootNode;

    //    processNode(scene->mRootNode, scene, 0);
    //    Q_ASSERT(scene->mRootNode);
    //    Q_ASSERT(scene->HasMeshes());
        m_rootNode = assimpProcessNode(scene->mRootNode, scene, 0);
//    m_rootNode = new Node(scene->mRootNode);
        Q_ASSERT(m_rootNode);
    //    std::cout << "root node : " << m_rootNode << std::endl;
}


Node* Model::assimpProcessNode(aiNode* node, const aiScene* scene, int depth)
{
    Node* newNode = new Node(node);

    //            for (int i = 0; i < depth; ++i) {
    //                std::cout << "\t";
    //            }
    //            std::cout << "node: " << node->mName.C_Str();
    //            std::cout << ", numMeshes: " << node->mNumMeshes;
    //            std::cout << ", numChildren: " << node->mNumChildren;
    //            std::cout << std::endl;

    newNode->m_numMeshes = node->mNumMeshes;
    newNode->m_iMeshes.resize(newNode->m_numMeshes);
    // process each mesh located at the current node
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        // the node object only contains indices to index the actual objects in the scene.
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        //        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        //        newNode->m_meshes.push_back(1);
        //        m_meshes.push_back(assimpProcessMesh(mesh, scene, depth + 1));

        //        newNode->m_meshes[i] = m_meshes.size() - 1;
        newNode->m_iMeshes[i] = node->mMeshes[i];
        //        newNode->m_meshes.push_back(&m_meshes.back());
        //        newNode->m_transformation = node->mTransformation
    }
    // after we've processed all of the m_meshes (if any) we then recursively process each of the children nodes
    newNode->m_numChildren = node->mNumChildren;
    newNode->m_children.resize(newNode->m_numChildren);
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        newNode->m_children[i] = assimpProcessNode(node->mChildren[i], scene, depth + 1);
    }

    newNode->m_transformation = aiMatrix4x4ToGlm(node->mTransformation);

    return newNode;
}


//Node::~Node()
//{

//}

//    bool operator==(const Model& model)
//    {
//        return m_file == model.m_file;
//    }

// draws the model, and thus all its meshes
void Model::Draw(const Shader& shader)
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
                m_fun->glBindTexture(GL_TEXTURE_2D, texture.id);

                ++cpt;
                //            }
            }
        }

        //        shader.setVec3("material.ambient", material.m_colors[Color::Etype::AMBIENT]);
        //        qDebug() << material.m_colorAmbient.x << material.m_colorAmbient.y << material.m_colorAmbient.z;
        //        shader.setVec3("material.diffuse", material.m_colors[Color::Etype::DIFFUSE]);
        //        shader.setVec3("material.specular", material.m_colors[Color::Etype::SPECULAR]);
        //        shader.setFloat("material.shininess", material.m_shininess);

        //        qDebug() << material.m_colorAmbient.x << material.m_colorAmbient.y << material.m_colorAmbient.z;

        //        shader.setVec3()
        //    for (uint i =0; i <m_material)

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
    //    Q_ASSERT(scene != nullptr);
    //            std::cout << std::flush;

    //    for (int i =0; i <m_materials.size(); ++i) {
    //    const Material& material = m_materials[i];
    //    QStandardItem* item = new QStandardItem(QIcon(":/icons/material.png"), material.m_name.c_str());
    //    parent->appendRow(item);
    //    }
    //    for (int i =0; i <m_animations.size(); ++i) {
    for (const Animation& animation : m_animations) {
        QStandardItem* item = new QStandardItem(animation.m_name.c_str());
        parent->appendRow(item);
    }

    Q_ASSERT(m_rootNode != nullptr);
    std::cout << "node nbchildren : " << m_rootNode->m_numChildren << std::endl;
//    modelRecurseNode(m_rootNode, parent);

    //    QStandardItem* item2 = new QStandardItem("fuck");
    //    parent->appendColumn({item2});
}

void Model::modelRecurseNode(const Node* node, QStandardItem* parent) const
{
    //    Q_ASSERT(scene != nullptr);
    Q_ASSERT(node != nullptr);

    //    std::cout << "opennode : " << node << std::endl;

    //    qDebug() << "node : '" << node->m_name.c_str() << "'";
    //    Q_ASSERT(!node->m_name.empty());
    //    Q_ASSERT(node->m_name.c_str());
    QStandardItem* item = new QStandardItem(QIcon(":/icons/node.png"), QString(node->m_name.c_str()));
    parent->appendRow(item);

    //    QStandardItem* item2 = new QStandardItem("fuck");
    //    parent->appendColumn({item2});

    const glm::mat4& m = node->m_transformation;
    modelMat4(node->m_transformation, item);

    for (int i = 0; i < node->m_numMeshes; ++i) {
        //        QStandardItem * item2 = new QStandardItem("mesh:" + QString::number(node->m_meshes[i]) + ", " + m_meshes[node->m_meshes[i]]);
        //        QStandardItem * item2 = new QStandardItem(QString::number(node->m_meshes[i]) + "  " + m_meshes[node->m_meshes[i]]);

        Q_ASSERT(node->m_iMeshes[i] < node->m_numMeshes);
        Q_ASSERT(node->m_numMeshes == node->m_iMeshes.size());
        modelRecurseMesh(&m_meshes[node->m_iMeshes[i]], item);
        //        QStandardItem * item2 = new QStandardItem("mesh : " + QString::number(node->m_meshes[i]));
        //        item->appendRow(item2);
    }

    std::cout << "node nbchildren : " << node->m_numChildren << std::endl;
    for (int i = 0; i < node->m_numChildren; ++i) {
        modelRecurseNode(node->m_children[i], item);
    }

    //    parent->appendRow(new QStandardItem(str));
}

void Model::modelRecurseMesh(const Mesh* mesh, QStandardItem* parent) const
{
    //    QStandardItem * item = new QStandardItem(mesh->m_name.c_str());
    QStandardItem* item = new QStandardItem(QIcon(":/icons/mesh.png"), QString(mesh->m_name.c_str()) + "  f:" + QString::number(mesh->m_numFaces) + "  v:" + QString::number(mesh->m_vertices.size()));
    parent->appendRow(item);

    //    QStandardItem * item2 = new QStandardItem(QIcon)
    for (const Bone& bone : mesh->m_bones) {
        QStandardItem* item2 = new QStandardItem(QIcon(":/icons/bone.png"), bone.m_name.c_str());
        item->appendRow(item2);
    }

    const Material& material = m_materials[mesh->m_iMaterial];
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

            //            QString path = QString(texture.path.c_str());
            //            QPixmap pixmap(texture.path.c_str());
            //            bool success;
            //            QImage image = loadTga(texture.path.c_str(), success);
            //            Q_ASSERT(success);
            ////            Q_ASSERT(! image.isNull());
            ////            QPixmap pixmap(image);
            //            QPixmap pixmap(QPixmap::fromImage(image));

            //            qDebug() << "path = " << path;
            //            item2->appendRow(item3);
            if (i == 0) {
                QStandardItem* item3 = new QStandardItem(QIcon(texture.pixmap), texture.filename.c_str());
                itemAmbient->appendRow(item3);
            } else {
                QStandardItem* item3 = new QStandardItem(QIcon(texture.pixmap), QString(texture) + texture.filename.c_str());
                item2->appendRow(item3);
            }
        }
    }
    item->appendRow(item2);
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
