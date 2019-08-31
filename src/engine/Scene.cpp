#include "Scene.h"

//#include <engine/Environment.h>
#include <gui/editor/outliner/QTreeView_outliner.h>
//#include <opengl/model.h>
#include <opengl/version.h>
//#include <opengl/shader.h>

QStandardItemModel Scene::m_sceneModel;
#include <gui/editor/timeline/FormTimeline.h>

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
    m_cameraModel = new Model(g_resourcesPath + "models/camera/camera.obj");

    //    m_shaderCamera = new Shader("camera.vsh", "camera.fsh");
    //    m_shader = new Shader("model_loading.vsh", "model_loading.fsh");

    m_grid = new Grid;
    normalShader = new Shader("normalVector.vsh", "normalVector.fsh", "normalVector.gsh");
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
    GLint polygonMode;
    glGetIntegerv(GL_POLYGON_MODE, &polygonMode);
//    glClear(GL_DEPTH_BUFFER_BIT);

    //    glClear(GL_STENCIL_BUFFER_BIT);
    //    glEnable(GL_DEPTH_TEST);
    if (view.boundingBox()) {
        for (const Model& model : m_models) {
//            model.m_box.draw(modelMatrix, shader);
            model.DrawBoundingBox(modelMatrix, shader);
        }
    }

//    glLineWidth(1);
//    glPolygonMode(GL_FRONT, GL_LINE);
    for (const Model& model : m_models) {
        model.Draw(modelMatrix, shader, view.dotCloud());
    }
    glClear(GL_DEPTH_BUFFER_BIT);


    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

    glPolygonMode(GL_FRONT, GL_FILL);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0xFF);
    for (const Model& model : m_models) {
        model.Draw(modelMatrix, shader);
    }
//    glClear(GL_COLOR_BUFFER_BIT);

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilMask(0x00);
//        glDisable(GL_DEPTH_TEST);
    glLineWidth(3);
    glPolygonMode(GL_FRONT, GL_LINE);
    //    modelMatrix = glm::scale(modelMatrix, glm::vec3(1.1f, 1.1f, 1.1f));
    shader.setBool("userColor", true);
    shader.setVec3("color", glm::vec3(1.0f, 0.5f, 0.0f));
    for (const Model& model : m_models) {

        model.Draw(modelMatrix, shader);
    }
    //    shader.setMat4("projection", projectionMatrix);
//    shader.setMat4("view", viewMatrix);
    shader.setBool("userColor", false);
    glStencilMask(0xFF);
    glDisable(GL_STENCIL_TEST);
    glLineWidth(1);
//        glEnable(GL_DEPTH_TEST);


    glPolygonMode(GL_FRONT, polygonMode);
    for (const MainWindow3dView* otherViews : *m_views) {
        const Camera* camera = otherViews->camera();
        glm::mat4 modelMatrix = glm::inverse(camera->viewMatrix());
        Q_ASSERT(m_cameraModel != nullptr);
        m_cameraModel->Draw(modelMatrix, shader);
    }

    switch (view.m_mode) {
    case MainWindow3dView::Mode::OBJECT:
        break;
    case MainWindow3dView::Mode::EDIT:
        break;
    case MainWindow3dView::Mode::POSE:
        break;
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

void Scene::load(std::ifstream& file)
{
    //    clear();
    uint size;
    //    file.read(reinterpret_cast<char *>(&size), sizeof(size));
    Session::load(size, file);

    m_models.clear();
    //    m_models.resize(size);

    //    for (const Model & model : m_models) {
    for (uint i = 0; i < size; ++i) {
        //        model.load(file);
        m_models.emplace_back(file);
    }


    updateSceneModel();

    FormTimeline::load(file);
}

void Scene::save(std::ofstream& file)
{
    uint size = m_models.size();
    //    file.write(reinterpret_cast<const char *>(&size), sizeof(size));
    Session::save(size, file);

    for (const Model& model : m_models) {
        model.save(file);
    }

    FormTimeline::save(file);

    //    qDebug() << "[SCENE] " << m_itemModel.rowCount();
}

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

//QStandardItemModel* Scene::itemModel()
//{
//    return &m_itemModel;
//}
