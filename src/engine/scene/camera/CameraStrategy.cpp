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

CameraStrategy::CameraStrategy(glm::mat4 & modelTransform, uint & id)
    : m_modelTransform(modelTransform)
    , m_id(id)
{
//    updateAttachFrustumViews();

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
//    m_model.setTransform(std::move(modelTransform));
    m_modelTransform = std::move(modelTransform);

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
