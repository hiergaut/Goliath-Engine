#include "Scene.h"

//#include <engine/Environment.h>
#include <opengl/model.h>
#include <opengl/version.h>

Scene::Scene()
{

    //    m_itemModel = new QStandardItemModel;

    //    QStandardItem* item0 = new QStandardItem("Scene");
    //        QStandardItem * item1 = new QStandardItem("World");
    //    //    item0->appendRow(item1);
    //    m_itemModel.appendRow(item0);
    //    m_itemModel.appendRow(item1);

    //    QStandardItemModel model;
    //    QStandardItem *parentItem = m_itemModel.invisibleRootItem();
    //    for (int i = 0; i < 4; ++i) {
    //        QStandardItem *item = new QStandardItem(QString("item %0").arg(i));
    //        item->setData(QVariant("fuck"));
    //        parentItem->appendRow(item);
    //        parentItem = item;
    //    }

    //    g_cameras = &m_cameras;

    //    m_itemModel.appendColumn();
    //    model->appendColumn(item0);
}

void Scene::initialize()
{
    m_cameraModel = new Model("models/camera/camera.obj");

    m_shaderCamera = new Shader("camera.vsh", "camera.fsh");
    m_shader = new Shader("model_loading.vsh", "model_loading.fsh");

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
    for (auto & model : m_models) {
        model.Draw(*m_shader);
    }


    m_shaderCamera->use();
    //    m_shaderCamera->setMat4("model", model);
    m_shaderCamera->setMat4("view", viewMatrix);
    m_shaderCamera->setMat4("projection", projectionMatrix);

    for (const QOpenGLWidget_3dView* view : *m_views) {
        const CameraWorld* camera = view->camera();

        //        for (const CameraWorld * camera : m_cameras) {
        glm::mat4 model;
        //        //        model = glm::translate(model, glm::vec3(10, 0, 0));
        //        model = glm::inverse(view->viewMatrix());
        model = glm::inverse(camera->getViewMatrix());
        m_shaderCamera->setMat4("model", model);

        m_cameraModel->Draw(*m_shaderCamera);
    }
}

void Scene::addModel(std::string file)
{
//    qDebug() << "[SCENE] add model : " << file.c_str();
    Model newModel(file);
    //    m_itemModel.appendRow(item);
    //    m_itemModel.appendColumn(item);
//    m_models.push_back(std::move(newModel));
//    m_models.push_back(std::make_pair(file, std::move(newModel)));
//    Q_ASSERT(m_models.find(file) == m_models.end());
//    m_models[file] = std::move(newModel);
//    m_models.insert(std::make_pair(file, std::move(newModel)));
    m_models.push_back(std::move(newModel));
}

void Scene::delModel(string file)
{

    qDebug() << "[SCENE] delete model : " << file.c_str();
//    const auto & it = m_models.find(file);
//    Q_ASSERT(it != m_models.end());
//    m_models.erase(it);

//    m_models.remove(file);
//    std::pair<std::string, Model> & pair =
}

//void Scene::load(ifstream &file)
//{
//    clear();

//}

//void Scene::clear()
//{
//    m_models.clear();
//}

//QStandardItemModel  *Scene::fileOpennedModel()
//{
//    return &m_fileOpennedModel;
//}

//const QStandardItemModel & Scene::itemModel() const
//{
//    return m_itemModel;
//}

void Scene::setViews(std::list<const QOpenGLWidget_3dView*>* views)
{
    m_views = views;
}

//std::vector<const CameraWorld &> & Scene::cameras() const
//{
//    return m_cameras;
//}

//std::vector<QOpenGLWidget_3dView *> Scene::views() const
//{
//    return m_views;
//}

//void Scene::save(ofstream &file)
//{
//    //    qDebug() << "[SCENE] " << m_itemModel.rowCount();
//}

//QStandardItemModel* Scene::itemModel()
//{
//    return &m_itemModel;
//}
