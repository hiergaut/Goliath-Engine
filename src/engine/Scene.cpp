#include "Scene.h"

#include <engine/Environment.h>
#include <gui/editor/3dview/QOpenGLWidget_3dView.h>
#include <opengl/model.h>
#include <opengl/version.h>

Scene::Scene()
{

    //    m_itemModel = new QStandardItemModel;

    QStandardItem* item0 = new QStandardItem("Scene");
    //    QStandardItem * item1 = new QStandardItem("World");
    //    item0->appendRow(item1);
    m_itemModel.appendRow(item0);
    //    model->appendColumn(item0);
}

void Scene::initialize()
{
    m_camera = new Model(g_resourcesPath + "models/camera/camera.obj");

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
    for (const QOpenGLWidget_3dView* view : g_env.m_views) {
        glm::mat4 model(1.0);
        //        model = glm::translate(model, glm::vec3(10, 0, 0));
        model = glm::inverse(view->viewMatrix());
        m_shaderCamera->setMat4("model", model);

        m_camera->Draw(*m_shaderCamera);
    }
}

QStandardItemModel* Scene::itemModel()
{
    return &m_itemModel;
}
