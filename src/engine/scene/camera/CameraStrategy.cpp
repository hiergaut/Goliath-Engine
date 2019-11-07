#include "CameraStrategy.h"
#include <engine/scene/Scene.h>

//#include <session/Session.h>

//CameraStrategy::CameraStrategy()
//{

//}

//Camera::Camera(Camera *camera)
//    : m_fov(camera->m_fov)
//    , m_position(camera->m_position)
//{
//}

//void CameraStrategy::save(std::ofstream &file)
//{

//}

CameraStrategy::CameraStrategy(glm::mat4& modelTransform, uint& id, Model& model)
    : m_modelTransform(modelTransform)
    , m_model(model)
    , m_id(id)
{
    //    updateAttachFrustumViews();

    updateNearestPointLights();
    //    glm::mat4 modelTransformCopy = modelTransform;
    //    updateModelTransform(std::move(modelTransformCopy));
}

//CameraStrategy::CameraStrategy(Model& model, uint& id)
//    : m_model(model)
//    //    , m_camera(camera)
//    , m_id(id)
//{
//    updateAttachFrustumViews();
//}

void CameraStrategy::keyPressEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_Shift:
        m_shiftPressed = true;
        break;
    }
}

void CameraStrategy::keyReleaseEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_Shift:
        m_shiftPressed = false;
        //        qDebug() << "shift pressed";
        break;
        //    case Qt::Key_Up:
        //    case Qt::Key_Comma:
        //    case Qt::Key_Down:
        //    case Qt::Key_O:
        //        frontDir = 0;
        //        break;

        //    case Qt::Key_Left:
        //    case Qt::Key_A:
        //    case Qt::Key_Right:
        //    case Qt::Key_E:
        //        sideDir = 0;
        //        break;
    }
}

void CameraStrategy::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::MiddleButton) {
        m_middleClicked = true;
        //    } else if (event->button() == Qt::LeftButton) {
        //        qDebug() << this << "left clicked";
    }
}

void CameraStrategy::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::MiddleButton) {
        m_middleClicked = false;
    }
    //    event->ignore();
}

void CameraStrategy::mouseMoveEvent(QMouseEvent* event)
{
}

void CameraStrategy::wheelEvent(QWheelEvent* event)
{
}

void CameraStrategy::focusInEvent(QFocusEvent* event)
{
    m_shiftPressed = false;
}

void CameraStrategy::resizeEvent(QResizeEvent* event)
{
}

void CameraStrategy::updateModelTransform(glm::mat4&& modelTransform)
{
    if (m_cptMovingStep > 10) {
        m_cptMovingStep = 0;
        m_model.setTransform(std::move(modelTransform));
//        qDebug() << "updateModelTransform";
        updateNearestPointLights();
        return;
    }
    //    m_model.setTransform(std::move(modelTransform));
    m_modelTransform = std::move(modelTransform);
    //    Scene::m_scene->m_oneModelTransformChanged = true;
    //    Scene::m_scene->m_cptShadowMapDetail = 0;

    updateAttachFrustumViews();
}

void CameraStrategy::updateAttachFrustumViews()
{
    for (const MainWindow3dView* view : *Scene::m_scene->m_views) {
        if (view->m_iCamera == m_id) {
            view->updateFrustum();
        }
        //        iCameras.push_back(view->m_iCamera);
    }
}

void CameraStrategy::updateNearestPointLights()
{
    std::vector<float> distances;
    std::list<uint> nearest;
    //        uint cpt =0;

    const auto& pointLights = Scene::m_scene->m_pointLights;

//    Q_ASSERT(pointLights.size() > 0);
    for (uint i = 0; i < pointLights.size(); ++i) {
        const PointLight& pointLight = pointLights[i];
        //        m_shadowComputedPointLights[i] = false;
        //        m_positionPointLights[i] = pointLight.position(m_localTransform, m_worldTransform);
        //            if (!pointLight.selected()) {
        const glm::vec3& position = pointLight.position();
        const float dist = glm::length(position - m_model.position());
        distances.emplace_back(dist);

        auto it = nearest.begin();
        while (it != nearest.end() && dist >= distances[*it])
            ++it;
        nearest.insert(it, i);

        //                if (pointLight.selected()) {
        //                    Shader& shader = (pointLight.selected()) ? (pointLight.depthShader(m_localTransform, m_worldTransform)) : (pointLight.depthShader());
        //                    renderScene(shader);
        //            pointLight.m_shadowComputed = true;
        //            m_shadowComputedPointLights[i] = true;
        //                }
        //                ++cpt;
        //            }
    }

    m_nearestPointLights = std::move(nearest);
}
