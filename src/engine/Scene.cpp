#include "Scene.h"

//#include <engine/Environment.h>
#include <gui/editor/outliner/QTreeView_outliner.h>
//#include <opengl/model.h>
#include <opengl/version.h>
//#include <opengl/shader.h>

QStandardItemModel Scene::m_sceneModel;

Scene::Scene()
{
    m_models.reserve(10);

    QTreeView_outliner::setModelScene(&m_sceneModel);
    m_sceneModel.setHorizontalHeaderItem(0, new QStandardItem("Scene"));
    //    m_sceneModel.setHorizontalHeaderItem(1, new QStandardItem("Bonus"));

    //    m_itemModel = new QStandardItemModel;
    //    m_models.resize(10);

    //    m_models.reserve(10);

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
    //    std::cout << "fuck" << std::endl;
    m_cameraModel = new Model("models/camera/camera.obj");
    //    std::cout << "bitch" << std::endl;

    //    m_shaderCamera = new Shader("camera.vsh", "camera.fsh");
    //    m_shader = new Shader("model_loading.vsh", "model_loading.fsh");

    m_grid = new Grid;
    normalShader = new Shader("shading/normalVector.vsh", "shading/normalVector.fsh", "shading/normalVector.gsh");
//    normalShader = new Shader("shading/normal.vsh", "shading/normal.fsh");


    initialized = true;
    MainWindow3dView::glInitialize();

    //    m_axis = new Axis();
}

void Scene::prepareHierarchy(ulong frameTime)
{
    for (const Model& model : m_models) {
        //	    glm::mat4 model(1.0);
        //        glm::mat4 modelMatrix(1.0);
        //        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.01));
        //        modelMatrix = glm::rotate(modelMatrix, 1.57f, glm::vec3(1, 0, 0));
        //        m_shader->setMat4("model", modelMatrix);

        //        model.Draw(modelMatrix, shader, frameTime);
        model.prepareHierarchy(frameTime);
    }
}

void Scene::draw(const MainWindow3dView& view)
{
    Q_ASSERT(initialized);
    glm::mat4 viewMatrix = view.viewMatrix();
    glm::mat4 projectionMatrix = view.projectionMatrix();

    glm::mat4 modelMatrix(1.0);
    m_grid->draw(modelMatrix, viewMatrix, projectionMatrix);


    const Shader& shader = view.shader();
    //        shader.use();

    //    modelMatrix = glm::translate(modelMatrix, glm::vec3(10.0f, 0.0f, 0.0f));
    //    shader.use();
    //    m_shader->setMat4("model", modelMatrix);
    //    shader.setMat4("view", viewMatrix);
    //    shader.setMat4("projection", projectionMatrix);
    //        qDebug() << "[3dView] " << this << "nb model = " << g_env.m_scene.size();

    for (const Model& model : m_models) {
        //	    glm::mat4 model(1.0);
        //        glm::mat4 modelMatrix(1.0);
        //        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.01));
        //        modelMatrix = glm::rotate(modelMatrix, 1.57f, glm::vec3(1, 0, 0));
        //        m_shader->setMat4("model", modelMatrix);

        model.Draw(modelMatrix, shader);
    }

    //    m_shaderCamera->use();
    //    m_shaderCamera->setMat4("model", model);
    //    m_shaderCamera->setMat4("view", viewMatrix);
    //    m_shaderCamera->setMat4("projection", projectionMatrix);

    for (const MainWindow3dView* otherViews : *m_views) {
        const Camera* camera = otherViews->camera();

        //        for (const CameraWorld * camera : m_cameras) {
        //        glm::mat4 modelMatrix;
        //        //        model = glm::translate(model, glm::vec3(10, 0, 0));
        //        model = glm::inverse(view->viewMatrix());
        modelMatrix = glm::inverse(camera->viewMatrix());

        //        m_shader->setMat4("otherViews", viewMatrix * modelMatrix);
        //        m_shader->setMat4("model", modelMatrix);

        //        m_shader->setBool("isSkeleton", false);
        m_cameraModel->Draw(modelMatrix, shader);
    }

    modelMatrix = glm::mat4(1.0f);
//    glEnable(GL_DEPTH_TEST);
    if (view.normal()) {
        normalShader->use();
//        glm::mat4 viewMatrix = view.viewMatrix();
//        glm::mat4 projectionMatrix = view.projectionMatrix();
        normalShader->setMat4("view", viewMatrix);
        normalShader->setMat4("projection", projectionMatrix);
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//        glEnable(GL_CULL_FACE);
//        glEnable(GL_LIGHTING);
//        glDisable(GL_BLEND);
//        glCullFace(GL_BACK);
//        normalShader->setMat4("model", modelMatrix);
        for (const Model& model : m_models) {
            //	    glm::mat4 model(1.0);
            //        glm::mat4 modelMatrix(1.0);
            //        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.01));
            //        modelMatrix = glm::rotate(modelMatrix, 1.57f, glm::vec3(1, 0, 0));
            //        m_shader->setMat4("model", modelMatrix);

            model.Draw(modelMatrix, *normalShader);
        }
    }

    if (view.skeleton()) {
        //        modelMatrix = glm::mat4(1.0f);
        for (const Model& model : m_models) {
            //	    glm::mat4 model(1.0);
            //        glm::mat4 modelMatrix(1.0);
            //        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.01));
            //        modelMatrix = glm::rotate(modelMatrix, 1.57f, glm::vec3(1, 0, 0));
            //        m_shader->setMat4("model", modelMatrix);

            model.DrawHierarchy(modelMatrix, view);
        }
    }

    //    glViewport(5, 5, 55, 55);
    //    m_axis->draw(viewMatrix);
}

void Scene::addModel(std::string file)
{
    Q_ASSERT(initialized);
    //    qDebug() << "[SCENE] add model : " << file.c_str();
    //    Model newModel(file);
    //    m_itemModel.appendRow(item);
    //    m_itemModel.appendColumn(item);
    //    m_models.push_back(std::move(newModel));
    //    m_models.push_back(std::make_pair(file, std::move(newModel)));
    //    Q_ASSERT(m_models.find(file) == m_models.end());
    //    m_models[file] = std::move(newModel);
    //    m_models.insert(std::make_pair(file, std::move(newModel)));
    //    m_models.push_back(std::move(newModel));
    //    m_models.push_back(std::move(Model(file)));
    m_models.emplace_back(file);

    //    std::cout << &m_models[0] << std::endl;
    updateSceneModel();
}

void Scene::delModel(std::string file)
{

    qDebug() << "[SCENE] delete model : " << file.c_str();
    //    const auto & it = m_models.find(file);
    //    Q_ASSERT(it != m_models.end());
    //    m_models.erase(it);

    //    m_models.remove(file);
    //    std::pair<std::string, Model> & pair =
}

void Scene::updateSceneModel()
{
    m_sceneModel.clear();

    //    QStandardItemModel model;
    QStandardItem* parentItem = m_sceneModel.invisibleRootItem();
    for (const Model& model : m_models) {
        QStandardItem* item = new QStandardItem(model.filename().c_str());
        parentItem->appendRow(item);

        model.buildItemModel(item);
    }

    emit m_sceneModel.dataChanged(m_sceneModel.index(0, 0), m_sceneModel.index(0, 0));
    //    for (int i = 0; i < 4; ++i) {
    //        QStandardItem* item = new QStandardItem(QString("item %0").arg(i));
    //        item->setData(QVariant("fuck"));
    //        parentItem->appendRow(item);
    //        parentItem = item;
    //    }
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

void Scene::setViews(std::list<const MainWindow3dView*>* views)
{
    m_views = views;
}

//std::vector<const CameraWorld &> & Scene::cameras() const
//{
//    return m_cameras;
//}

//std::vector<MainWindow3dView *> Scene::views() const
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
