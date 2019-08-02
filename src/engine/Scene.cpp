#include "Scene.h"

//#include <engine/Environment.h>
#include <opengl/model.h>
#include <opengl/version.h>

Scene::Scene()
{

    //    m_itemModel = new QStandardItemModel;

//    QStandardItem* item0 = new QStandardItem("Scene");
    //    QStandardItem * item1 = new QStandardItem("World");
    //    item0->appendRow(item1);
//    m_itemModel.appendRow(item0);

//    g_cameras = &m_cameras;

//    m_itemModel.appendColumn();
    //    model->appendColumn(item0);
}

void Scene::initialize()
{
    m_cameraModel = new Model(g_resourcesPath + "models/camera/camera.obj");

    m_shaderCamera = new Shader(g_shaderPath + "camera.vsh", g_shaderPath + "camera.fsh");
    m_shader = new Shader(g_shaderPath + "model_loading.vsh", g_shaderPath + "model_loading.fsh");

    m_grid = new Grid;
}

void Scene::draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
    glm::mat4 model(1.0);
    m_grid->draw(model, viewMatrix, projectionMatrix);

    m_shader->use();
    m_shader->setMat4("model", model);
    m_shader->setMat4("view", viewMatrix);
    m_shader->setMat4("projection", projectionMatrix);
    //        qDebug() << "[3dView] " << this << "nb model = " << g_env.m_scene.size();
    for (Model& model : m_models) {
        model.Draw(*m_shader);
    }

    m_shaderCamera->use();
//    m_shaderCamera->setMat4("model", model);
    m_shaderCamera->setMat4("view", viewMatrix);
    m_shaderCamera->setMat4("projection", projectionMatrix);
//    for (const QOpenGLWidget_3dView* view : m_views) {
        for (const CameraWorld * camera : m_cameras) {
        glm::mat4 model(1.0);
        //        model = glm::translate(model, glm::vec3(10, 0, 0));
//        model = glm::inverse(view->viewMatrix());
        model = glm::inverse(camera->getViewMatrix());
        m_shaderCamera->setMat4("model", model);

        m_cameraModel->Draw(*m_shaderCamera);
    }
}

void Scene::addModel(std::string file)
{
    Model newModel(g_resourcesPath + file);
    QStandardItem * item = new QStandardItem(file.c_str());
    m_itemModel.appendRow(item);
//    m_itemModel.appendColumn(item);
    m_models.push_back(std::move(newModel));

}

void Scene::load(ifstream &file)
{
    clear();

   size_t size;
//   size = m_itemModel.rowCount();
   file.read(reinterpret_cast<char *>(&size), sizeof(size));


   for (int i =0; i <size; ++i) {
//       std::string path = m_itemModel.data(m_itemModel.index(i, 0)).toString().toStdString();
//       qDebug() << "[SCENE]" <<  path.c_str();

       size_t sizePath;
       file.read(reinterpret_cast<char*>(&sizePath), sizeof(sizePath));

       char path[sizePath +1];
       path[sizePath] = 0;
//       std::string path();
       file.read(reinterpret_cast<char*>(path), sizePath * sizeof(char));

       std::string file(path);
       addModel(file);
   }



}

void Scene::clear()
{
    m_itemModel.clear();
    m_models.clear();

}

//std::vector<const CameraWorld &> & Scene::cameras() const
//{
//    return m_cameras;
//}

//std::vector<QOpenGLWidget_3dView *> Scene::views() const
//{
//    return m_views;
//}

void Scene::save(ofstream &file)
{
    //    qDebug() << "[SCENE] " << m_itemModel.rowCount();
   size_t size;
   size = m_itemModel.rowCount();
   file.write(reinterpret_cast<const char *>(&size), sizeof(size));


   for (int i =0; i <size; ++i) {
       std::string path = m_itemModel.data(m_itemModel.index(i, 0)).toString().toStdString();
       qDebug() << "[SCENE]" <<  path.c_str();

       size = path.size();
       file.write(reinterpret_cast<const char*>(&size), sizeof(size));

       file.write(reinterpret_cast<const char*>(path.data()), size * sizeof(char));
   }

}

QStandardItemModel* Scene::itemModel()
{
    return &m_itemModel;
}
