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
#include <gui/editor/timeline/FormTimeline.h>

Model::Model(const std::string& path)
//        : gammaCorrection(gamma),
//        : m_file(path)
{
    //    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();

    m_meshes.reserve(50);
    m_materials.reserve(50);
    m_textures.reserve(100);
    m_animations.reserve(10);

    //        initializeOpenGLFunctions();
    //    fun = QOpenGLContext::globalShareContext()->versionFunctions<QOpenGLFunctionsCore>();
    //        fun = ctx->versionFunctions<QOpenGLFunctionsCore>();
    //        m_fun = fun;
    //        if (!fake) {
    //    qDebug() << QThread::currentThreadId() << "[MODEL]" << this << "[CONTEXT]" << fun;

    //    assimpLoadModel(g_resourcesPath + path);
    assimpLoadModel(path);
    //    std::cout << "[MODEL] load : " << path << std::endl;
    //        }
    //    std::cout << "[Model] create " << this << std::endl;
    //        std::cout << "\033[32m";
    //        std::cout << "[Model] " << m_filename << " created " << this << std::endl;
    //        std::cout << "\033[0m";
    updateBoundingBoxing();
}

Model::Model(std::ifstream& file)
{
    m_meshes.reserve(50);
    m_materials.reserve(50);
    m_textures.reserve(100);
    m_animations.reserve(10);

    //    load(file);
    uint size;

    //    std::cout << "load materials" << std::endl;
    //    file.read(reinterpret_cast<char *>(&size), sizeof(size));
    Session::load(size, file);
    for (uint i = 0; i < size; ++i) {
        m_materials.emplace_back(file, &m_textures);
    }

    //    std::cout << "load textures" << std::endl;
    Session::load(size, file);
    //    file.read(reinterpret_cast<char *>(&size), sizeof(size));
    for (uint i = 0; i < size; ++i) {
        m_textures.emplace_back(file);
    }

    //    std::cout << "load animations" << std::endl;
    Session::load(size, file);
    //    file.read(reinterpret_cast<char *>(&size), sizeof(size));
    for (uint i = 0; i < size; ++i) {
        m_animations.emplace_back(file);
    }

    //    std::cout << "load meshes" << std::endl;
    Session::load(size, file);
    //    file.read(reinterpret_cast<char *>(&size), sizeof(size));
    for (uint i = 0; i < size; ++i) {
        m_meshes.emplace_back(file, &m_materials, &m_textures);
    }

    //    std::cout << "load node" << std::endl;
    ////    m_rootNode = std::make_unique<Node>(scene->mRootNode, m_meshes, m_animations);
    m_rootNode = std::make_unique<Node>(file, &m_meshes, &m_animations);

    //    std::cout << "load filename" << std::endl;
    Session::load(m_filename, file);
    //    std::cout << "load directory" << std::endl;
    Session::load(directory, file);

    //        std::cout << "\033[32m";
    //        std::cout << "[Model] " << m_filename << " created " << this << std::endl;
    //        std::cout << "\033[0m";
    updateBoundingBoxing();
}

Model::Model(Model&& model) noexcept
    : m_box(std::move(model.m_box))
    , m_materials(std::move(model.m_materials))
    , m_textures(std::move(model.m_textures))
    , m_animations(std::move(model.m_animations))
    , m_meshes(std::move(model.m_meshes))
    , m_rootNode(std::move(model.m_rootNode))
    , m_filename(std::move(model.m_filename))
    , directory(std::move(model.directory))
{
    for (Material& material : m_materials) {
        material.m_textures = &m_textures;
    }

    //    for (Material& material : model.m_materials) {
    //        m_materials.emplace_back(material);
    //    }

    for (Mesh& mesh : m_meshes) {
        //        const_cast<Materials&>(mesh.m_materials) = m_materials;
        //        const_cast<Textures&>(mesh.m_textures) = m_textures;
        mesh.m_materials = &m_materials;
        mesh.m_textures = &m_textures;
    }

    m_rootNode->updateReferences(&m_meshes, &m_animations);
}

//Model::Model(const Model &model)
//{
//    std::cout << "\033[31m";
//    std::cout << "[Model] '" << m_filename << "' copy constructor " << this << std::endl;
//    std::cout << "\033[0m";

//}

Model::~Model()
{
    //    qDebug() << "[Model] destruct " << this;
    std::cout << "\033[35m";
    std::cout << "[Model] '" << m_filename << "' deleted " << this << std::endl;
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

    //    std::cout << "animations" << std::endl;
    for (uint i = 0; i < scene->mNumAnimations; ++i) {
        const aiAnimation* ai_animation = scene->mAnimations[i];
        m_animations.emplace_back(ai_animation);
    }

    //    m_materials.reserve(100);
    //    std::cout << "materials" << std::endl;
    for (uint i = 0; i < scene->mNumMaterials; ++i) {
        //        const aiMaterial * scene->mMaterials[i];
        const aiMaterial* ai_material = scene->mMaterials[i];
        //        std::cout << "load material " << i << std::endl;
        //        Material material(ai_material);
        //        Material material(ai_material, m_textures, directory);
        //        m_materials.push_back(material);
        //        m_materials.push_back(std::move(Material(ai_material, m_textures, directory)));
        m_materials.emplace_back(ai_material, &m_textures, directory);
        //        m_materials.push_back({ai_material, m_textures, directory});

        //        m_materials.push_back(std::move(material));
    }
    Q_ASSERT(scene->mNumMaterials == m_materials.size());

    m_meshes.clear();
    //    std::cout << "meshes" << std::endl;
    for (uint i = 0; i < scene->mNumMeshes; ++i) {
        const aiMesh* ai_mesh = scene->mMeshes[i];
        //        m_meshes.push_back(assimpProcessMesh(ai_mesh, scene, 0));
        //        m_meshes.push_back(std::move(Mesh(ai_mesh)));
        m_meshes.emplace_back(ai_mesh, &m_materials, &m_textures);
    }
    Q_ASSERT(scene->mNumMeshes == m_meshes.size());

    //    m_rootNode = new Node(scene->mRootNode);
    //    m_rootNode = std::make_unique<
    //    std::cout << "node" << std::endl;
    m_rootNode = std::make_unique<Node>(scene->mRootNode, &m_meshes, &m_animations);

    //    m_rootNode->m_transformation = glm::inverse(m_rootNode->m_transformation);

    //    std::make_unique<Node>();

    //    m_nodes.push_back(Node(scene->mRootNode));

    //    m_rootNode = new Node(scene->mRootNode);
    //    Q_ASSERT(m_rootNode);
    //        std::cout << "root node : " << m_rootNode << std::endl;
    //    std::cout << "assimpProcessNode root node " << m_rootNode <<  " " <<m_rootNode->m_children.size() << std::endl;
    //    std::cout << "assimp load model finished" << path << std::endl;
}

void Model::updateBoundingBoxing() const
{
    m_box.clear();
    for (const Mesh & mesh : m_meshes) {
        for (const Vertex & vertex : mesh.m_vertices) {
            m_box << vertex.Position;
        }
    }

}

void Model::prepareHierarchy(ulong frameTime) const
{
    if (m_rootNode == nullptr)
        return;
    //    shader.use();

    //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    ////    m_fun->glBindVertexArray()
    ///
    /////
    ///
    //    bool isAnimated = false;
    const Animation* animation = nullptr;
    const Animation* currentAnimation = FormTimeline::animation();
    if (currentAnimation != nullptr) {
        for (const Animation& anim : m_animations) {
            if (currentAnimation == &anim) {
                //            isAnimated = true;
                animation = &anim;
                break;
            }
        }
    }

    if (animation != nullptr) {
        //        const Animation* animation = &m_animations[0];

        if (FormTimeline::play()) {
            double ticksPerSecond = animation->m_ticksPerSecond;
            double timeInTicks = (double)frameTime / 1000.0 * ticksPerSecond;
            double animationTime = fmod(timeInTicks, animation->m_duration);

            //            FormTimeline::animationTime = animationTime;
            FormTimeline::setAnimationTime(animationTime);
        }
        //        else {

        ////            std::cout << "animationTime " << animationTime << std::endl;
        //        }

        double animationTime = FormTimeline::animationTime();

        //        m_rootNode->draw(shader, modelMatrix, animation, animationTime);
        m_rootNode->prepareHierarchy(glm::mat4(1.0f), animation, animationTime);

        //        shader.setMat4("model", glm::mat4(1));
        //        shader.setBool("isSkeleton", true);
    } else {
        m_rootNode->prepareHierarchy(glm::mat4(1.0f));
        //        m_rootNode->draw(shader, modelMatrix);

        //        shader.setBool("isSkeleton", false);
    }

//    updateBoundingBoxing();
}

//void Model::Draw(const glm::mat4& modelMatrix, const MainWindow3dView& view) const
void Model::Draw(const glm::mat4& modelMatrix, const Shader& shader) const
{
    //    model = glm::mat4(1.0f);
    //    model = glm::scale(model, glm::vec3(0.01));
    //    //    model = glm::rotate(model, 1.57f, glm::vec3(1, 0, 0));
    //    //    m_boneGeometry.draw(shader, glm::vec3(0, 0, 0), glm::vec3(10, 10, 10));
    //    //    shader.setBool("isSkeleton", true);

    //    const Shader& shader = view.shader();
    //    shader.use();
    for (const Mesh& mesh : m_meshes) {
        //        shader.setMat4("model", modelMatrix);
        //        const Mesh& mesh = m_meshes[i];
        shader.setMat4("model", modelMatrix * mesh.m_transform);
        mesh.draw(shader);

//        mesh.m_box->draw(modelMatrix * mesh.m_transform, shader);
    }

//    m_box.draw(modelMatrix, )

    //    shader.use();
}

void Model::DrawBoundingBox(const glm::mat4 &modelMatrix, const Shader &shader) const
{
    for (const Mesh& mesh : m_meshes) {
        //        shader.setMat4("model", modelMatrix);
        //        const Mesh& mesh = m_meshes[i];
        shader.setMat4("model", modelMatrix * mesh.m_transform);
//        mesh.draw(shader);

        mesh.m_box->draw(modelMatrix * mesh.m_transform, shader);
    }


}

void Model::DrawHierarchy(const glm::mat4& modelMatrix, const MainWindow3dView& view) const
{
    const Shader& shader = view.shader();
    shader.use();
    //    m_rootNode.draw(m_boneGeometry);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //        glDepthFunc(GL_ALWAYS);
    //    glClear()
    glClear(GL_DEPTH_BUFFER_BIT);

    //    m_boneGeometry.setVP(viewMatrix, projectionMatrix);
    m_boneGeometry.updateShader(view);
    m_rootNode->drawHierarchy(m_boneGeometry, modelMatrix);
    //        glDepthFunc(GL_LESS);
}

// -------------------------------------------------------------------
void Model::buildItemModel(QStandardItem* parent) const
{
    //    modelRecurseNode(*m_rootNode, parent);
    if (m_rootNode == nullptr)
        return;

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

//void Model::load(std::ifstream &file) const
//{

//}

void Model::save(std::ofstream& file) const
{
    uint size;

    //    std::cout << "m_materials" << std::endl;
    size = m_materials.size();
    //    file.write(reinterpret_cast<const char *>(&size), sizeof(size));
    Session::save(size, file);
    for (const Material& material : m_materials) {
        material.save(file);
    }

    //    std::cout << "save textures" << std::endl;
    size = m_textures.size();
    Session::save(size, file);
    //    file.write(reinterpret_cast<const char *>(&size), sizeof(size));
    for (const Texture& texture : m_textures) {
        texture.save(file);
    }

    //    std::cout << "save animations" << std::endl;
    size = m_animations.size();
    Session::save(size, file);
    //    file.write(reinterpret_cast<const char *>(&size), sizeof(size));
    for (const Animation& animation : m_animations) {
        animation.save(file);
    }

    //    std::cout << "save meshes" << std::endl;
    size = m_meshes.size();
    Session::save(size, file);
    //    file.write(reinterpret_cast<const char *>(&size), sizeof(size));
    for (const Mesh& mesh : m_meshes) {
        mesh.save(file);
    }

    //    std::cout << "save nodes" << std::endl;
    //    m_rootNode = std::make_unique<Node>(scene->mRootNode, m_meshes, m_animations);
    //    m_rootNode = std::make_unique<Node>(file);

    m_rootNode->save(file);

    //    std::cout << "save filename" << std::endl;
    Session::save(m_filename, file);
    //    std::cout << "save directory" << std::endl;
    Session::save(directory, file);
}

glm::mat4 Model::scaleCenter(float scale) const
{
    glm::mat4 mat(1.0f);
    glm::vec3 center = m_box.center();
//    qDebug() << center.x << center.y << center.z;
    mat = glm::translate(mat, center);
    mat = glm::scale(mat, glm::vec3(scale));
    mat = glm::translate(mat, -center);

    return mat;
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
