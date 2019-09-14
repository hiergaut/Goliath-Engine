#include "Scene.h"

//#include <engine/Environment.h>
#include <gui/editor/outliner/QTreeView_outliner.h>
//#include <opengl/model.h>
#include <opengl/version.h>
//#include <opengl/shader.h>

#include "camera/CameraWorld.h"
#include <gui/editor/timeline/FormTimeline.h>
#include <opengl/geometry/AxisGeometry.h>
#include <opengl/geometry/DotGeometry.h>
#include <opengl/geometry/LineGeometry.h>
#include <opengl/geometry/TriangleGeometry.h>

Scene* Scene::m_scene = nullptr;
//QStandardItemModel Scene::m_sceneModel;
//Model* Scene::m_cameraModel = nullptr;
//Model* Scene::m_lightDirModel = nullptr;
//std::list<Camera*> Scene::m_cameras;
//std::list<const Object *> Scene::m_objects;
std::vector<Camera*> Scene::m_cameras; // legacy

Scene::Scene()
{
    Q_ASSERT(m_scene == nullptr);
    m_scene = this;

    m_models.reserve(10);
    m_dirLights.reserve(10);
    //    m_objects.reserve(50);
    //    m_dirLights.reserve(10);

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
    //    m_cameras.push_back(new CameraWorld(50.0f, glm::vec3(200, -200, 200), glm::vec3(0, 0, 0)));

    //    m_itemModel.appendColumn();
    //    model->appendColumn(item0);
}

void Scene::initializeGL()
{
    //    m_cameraModel = new Model(g_resourcesPath + "models/camera/camera.obj");
    //    m_lightDirModel = new Model(g_resourcesPath + "models/sun/sun.obj");

    //    m_shaderCamera = new Shader("camera.vsh", "camera.fsh");
    //    m_shader = new Shader("model_loading.vsh", "model_loading.fsh");

    //    m_cameras.push_back(new CameraWorld(50.0f, glm::vec3(200, -200, 200), glm::vec3(0, 0, 0)));

    m_grid = new Grid;
    normalShader = new Shader("normalVector.vsh", "normalVector.fsh", "normalVector.gsh");
    //    normalShader = new Shader("shading/normal.vsh", "shading/normal.fsh");
    //    m_bone = new BoneGeometry;

    initialized = true;
    //    MainWindow3dView::glInitialize();

    glm::vec3 ambient = 0.5f * glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 diffuse = 1.0f * glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 specular = 1.0f * glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 direction = 1.0f * glm::vec3(0.0f, 0.0f, -1.0f);
    //    glm::vec3 ambient = 1.0f * glm::vec3(0.05f, 0.05f, 0.05f);
    //    glm::vec3 diffuse = 1.0f * glm::vec3(0.4f, 0.4f, 0.4f);
    //    glm::vec3 specular = 1.0f * glm::vec3(0.5f, 0.5f, 0.5f);
    m_dirLights.emplace_back(glm::vec3(0.0f, 0.0f, 1000.0f), ambient, diffuse, specular, direction);
    //    //        m_dirLights.push_back(5);
    //            shader.setVec3("dirLight[" + QString::number(0).toStdString() + "].direction", -0.2f, -1.0f, -0.3f);
    //            shader.setVec3("dirLight[" + QString::number(0).toStdString() + "].ambient", 0.05f, 0.05f, 0.05f);
    //            shader.setVec3("dirLight[" + QString::number(0).toStdString() + "].diffuse", 0.4f, 0.4f, 0.4f);
    //            shader.setVec3("dirLight[" + QString::number(0).toStdString() + "].specular", 0.5f, 0.5f, 0.5f);

    //    m_axis = new Axis();
}

void Scene::prepareHierarchy(ulong frameTime)
{
    for (const Object& object : m_models) {
        //	    glm::mat4 model(1.0);
        //        glm::mat4 modelMatrix(1.0);
        //        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.01));
        //        modelMatrix = glm::rotate(modelMatrix, 1.57f, glm::vec3(1, 0, 0));
        //        m_shader->setMat4("model", modelMatrix);

        //        model.Draw(modelMatrix, shader, frameTime);
        object.m_model.prepareHierarchy(frameTime);
        //        model.prepareHierarchy(frameTime);
    }

    if (m_autoUpdateBoundingBox) {
        if (FormTimeline::play()) {
            updateBoundingBox();
        } else {

            if (FormTimeline::m_animationTimeChanged) {
                FormTimeline::m_animationTimeChanged = false;

                updateBoundingBox();
            }
        }
    }
}

void Scene::draw(const MainWindow3dView& view)
{
    //    qDebug() << m_cameras.size();
    //    qDebug() << m_objects.size();
    //    if (view.m_iCamera >= m_cameras.size()) {
    //        return;
    //    }
    Object* viewCameraObject = m_cameras[view.m_iCamera];

    Q_ASSERT(initialized);
    glm::mat4 viewMatrix = view.viewMatrix();
    glm::mat4 projectionMatrix = view.projectionMatrix();

    //    Object* viewCameraObject = view.m_camera;

    //    glm::vec3 cameraPos = view.m_camera->position();
    glm::vec3 cameraPos = m_cameras[view.m_iCamera]->position();

    //    glm::mat4 modelMatrix(1.0);
    const glm::mat4 onesMatrix(1.0);
    if (view.m_shade != Shader::Type::RENDERED) {
        m_grid->draw(onesMatrix, viewMatrix, projectionMatrix);
        //        m_grid->draw(glm::scale(onesMatrix, glm::vec3(1.0f) * glm::length(glm::vec3(viewMatrix[3]))), viewMatrix, projectionMatrix);
    }

    const Shader& shader = view.shader();

    //    const glm::mat4& viewTransform = view.m_transformMatrix;
    //    const glm::mat4& viewWorldTransform = view.m_worldTransform;
    const glm::mat4& viewLocalTransform = m_localTransform;
    const glm::mat4& viewWorldTransform = m_worldTransform;

    GLint polygonMode;
    glGetIntegerv(GL_POLYGON_MODE, &polygonMode);

    //     -------------------------------- DRAW RAYS
    //    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_FRONT, GL_LINE);
    //    shader.use();
    if (view.intersectRay()) {
        shader.setMat4("model", onesMatrix);
        shader.setBool("userColor", true);
        shader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        for (const Ray& ray : m_rays) {
            if (!ray.m_hit) {
                LineGeometry::draw(ray.m_source, ray.m_source + ray.m_direction * ray.m_length);
            }
        }
        shader.setVec4("color", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
        //        std::vector<glm::vec3>
        std::vector<glm::vec3> triangles;
        for (const Ray& ray : m_rays) {
            if (ray.m_hit) {
                LineGeometry::draw(ray.m_source, ray.m_source + ray.m_direction * ray.m_length);
                //                TriangleGeometry::draw(ray.m_vertices[0], ray.m_vertices[1], ray.m_vertices[2]);
                //                for (const glm::vec3[3] & triangle : ray.m_triangles) {
                //                TriangleGeometry::draw(ray.m_triangles);
                triangles.insert(triangles.end(), ray.m_triangles.begin(), ray.m_triangles.end());
                //                for (uint i = 0; i < ray.m_triangles.size() / 3; ++i) {
                //                    const uint i3 = i * 3;
                //                    const glm::vec3& v0 = ray.m_triangles[i3];
                //                    const glm::vec3& v1 = ray.m_triangles[i3 + 1];
                //                    const glm::vec3& v2 = ray.m_triangles[i3 + 2];

                //                    TriangleGeometry::draw(v0, v1, v2);
                //                }
            }
        }
        Q_ASSERT(triangles.size() % 3 == 0);
        TriangleGeometry::draw(triangles);
        shader.setBool("userColor", false);
    }
    glPolygonMode(GL_FRONT, polygonMode);

    //    glClear(GL_DEPTH_BUFFER_BIT);
    //    glClear(GL_STENCIL_BUFFER_BIT);
    //    glEnable(GL_DEPTH_TEST);
    // -------------------------------- DRAW BOUNDING BOXES
    //    shader.setMat4("model", onesMatrix);
    if (view.boundingBox()) {
        //        for (const Model& model : m_models) {
        for (const Object* object : m_objects) {
            //            model.m_box.draw(modelMatrix, shader);
            object->drawBoundingBox(shader);
            //            if (object->m_selected) {

            ////                object->drawBoundingBox(viewWorldTransform, shader);
            //            } else {
            //                object->drawBoundingBox(onesMatrix, shader);
            //            }
        }
    }

    //    shader.setBool("userColor", false);
    //    for (uint i = 0; i < m_dirLights.size(); ++i) {
    //        const DirLight& dirLight = m_dirLights[i];

    //        dirLight.draw(shader);
    //        //        qDebug() << "draw light";
    //    }

    if (view.m_shade == Shader::Type::RENDERED) {

        //                for (const DirLight & dirLight : m_dirLights) {
        shader.setInt("nbDirLight", m_dirLights.size());
        for (uint i = 0; i < m_dirLights.size(); ++i) {
            const DirLight& dirLight = m_dirLights[i];

            //                        dirLight.draw(shader);

            shader.setVec3("dirLight[" + QString::number(i).toStdString() + "].direction", dirLight.m_direction);
            shader.setVec3("dirLight[" + QString::number(i).toStdString() + "].ambient", dirLight.m_ambient);
            shader.setVec3("dirLight[" + QString::number(i).toStdString() + "].diffuse", dirLight.m_diffuse);
            shader.setVec3("dirLight[" + QString::number(i).toStdString() + "].specular", dirLight.m_specular);

            //            shader.setVec3("dirLight[" + QString::number(0).toStdString() + "].direction", -0.2f, -1.0f, -0.3f);
            //            shader.setVec3("dirLight[" + QString::number(0).toStdString() + "].ambient", 0.05f, 0.05f, 0.05f);
            //            shader.setVec3("dirLight[" + QString::number(0).toStdString() + "].diffuse", 0.4f, 0.4f, 0.4f);
            //            shader.setVec3("dirLight[" + QString::number(0).toStdString() + "].specular", 0.5f, 0.5f, 0.5f);

            //                    shader.setVec3("dirLight.ambient", dirLight.m_ambient);
            //                    shader.setVec3("dirLight.diffuse", dirLight.m_diffuse);
            //                    shader.setVec3("dirLight.specular", dirLight.m_specular);
        }

        //            shader.setVec3("dirLight[" + QString::number(0).toStdString() + "].direction", -0.2f, -1.0f, -0.3f);
        //            shader.setVec3("dirLight[" + QString::number(0).toStdString() + "].ambient", 0.05f, 0.05f, 0.05f);
        //            shader.setVec3("dirLight[" + QString::number(0).toStdString() + "].diffuse", 0.4f, 0.4f, 0.4f);
        //            shader.setVec3("dirLight[" + QString::number(0).toStdString() + "].specular", 0.5f, 0.5f, 0.5f);
    }
    //    glLineWidth(1);
    //    glPolygonMode(GL_FRONT, GL_LINE);
    // -------------------------------- DRAW MODELS
    //    for (const Model& model : m_models) {
    //            qDebug() << m_objects;
    for (const Object* object : m_objects) {
        if (object != viewCameraObject) {
            if (object->m_selected) {
                object->draw(shader, view.dotCloud(), viewLocalTransform, viewWorldTransform);

            } else {

                object->draw(shader, view.dotCloud(), onesMatrix, onesMatrix);
            }
        }
    }
    glClear(GL_DEPTH_BUFFER_BIT);

    // -------------------------------- DRAW CONTOURS
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

    glPolygonMode(GL_FRONT, GL_FILL);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0xFF);
    //    for (const Model& model : m_models) {
    for (const Object* object : m_objects) {
        if (object->m_selected) {
            //            model.Draw(modelMatrix, shader);
            object->draw(shader, viewLocalTransform, viewWorldTransform);
        }
    }
    //    glClear(GL_COLOR_BUFFER_BIT);

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilMask(0x00);
    //        glDisable(GL_DEPTH_TEST);
    glLineWidth(4);
    glPolygonMode(GL_FRONT, GL_LINE);
    //    modelMatrix = glm::scale(modelMatrix, glm::vec3(1.1f, 1.1f, 1.1f));
    shader.setBool("userColor", true);
    shader.setVec4("color", glm::vec4(1.0f, 0.5f, 0.0f, 1.0f));
    //    for (const Model& model : m_models) {
    for (const Object* object : m_objects) {
        if (object->m_selected) {
            //            model.Draw(modelMatrix, shader);
            object->draw(shader, viewLocalTransform, viewWorldTransform);
            //            DotGeometry::draw(modelMatrix, shader, model.m_rootNode->m_transformation[3]);
        }
    }
    //    shader.setMat4("projection", projectionMatrix);
    //    shader.setMat4("view", viewMatrix);
    shader.setBool("userColor", false);
    glStencilMask(0xFF);
    glDisable(GL_STENCIL_TEST);
    glLineWidth(1);
    //        glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT, polygonMode);

    // -------------------------------- DRAW CAMERA VIEWS
    //    for (const MainWindow3dView* otherViews : *m_views) {
    //        const Camera* camera = otherViews->camera();
    //        glm::mat4 modelMatrix = glm::inverse(camera->viewMatrix());
    //        Q_ASSERT(m_cameraModel != nullptr);
    //        m_cameraModel->draw(shader, view.dotCloud(), modelMatrix);
    //    }

    switch (view.m_mode) {
    case MainWindow3dView::Mode::OBJECT:
        break;
    case MainWindow3dView::Mode::EDIT:
        break;
    case MainWindow3dView::Mode::POSE:
        break;
    }

    //    modelMatrix = glm::mat4(1.0f);
    //    glEnable(GL_DEPTH_TEST);
    // -------------------------------- NORMAL VECTORS
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
        //        for (const Model& model : m_models) {
        for (const Object* object : m_objects) {
            //	    glm::mat4 model(1.0);
            //        glm::mat4 modelMatrix(1.0);
            //        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.01));
            //        modelMatrix = glm::rotate(modelMatrix, 1.57f, glm::vec3(1, 0, 0));
            //        m_shader->setMat4("model", modelMatrix);

            normalShader->m_shade = view.m_shade;
            if (object->m_selected) {

                object->draw(*normalShader, view.dotCloud(), viewLocalTransform, viewWorldTransform);
            } else {
                object->draw(*normalShader, view.dotCloud(), onesMatrix, onesMatrix);
            }
        }
    }

    // -------------------------------- SKELETON
    if (view.skeleton()) {
        //        modelMatrix = glm::mat4(1.0f);
        //        for (const Model& model : m_models) {
        for (const Object& model : m_models) {
            //	    glm::mat4 model(1.0);
            //        glm::mat4 modelMatrix(1.0);
            //        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.01));
            //        modelMatrix = glm::rotate(modelMatrix, 1.57f, glm::vec3(1, 0, 0));
            //        m_shader->setMat4("model", modelMatrix);

            if (model.m_selected) {
                model.m_model.DrawHierarchy(viewLocalTransform, viewMatrix, projectionMatrix, cameraPos, viewWorldTransform);

                //                model.m_model.DrawHierarchy(viewLocalTransform, view, viewWorldTransform);
            } else {
                //                model.DrawHierarchy(onesMatrix, view);
                model.m_model.DrawHierarchy(onesMatrix, viewMatrix, projectionMatrix, cameraPos);
            }
        }
    }

    //    glViewport(5, 5, 55, 55);
    //    m_axis->draw(viewMatrix);
    // -------------------------------- DRAW ORIGINS MODELS
    //    glClear(GL_DEPTH_BUFFER_BIT);
    shader.use(); // skeleton use owner
    shader.setBool("isSkeleton", false);
    //    shader.setMat4("view", viewMatrix);
    //    shader.setMat4("projection", projectionMatrix);
    //    shader.setMat4("model", onesMatrix);
    glDepthFunc(GL_ALWAYS);
    glLineWidth(2);
    //    glPolygonMode(GL_FRONT, GL_LINE);
    //    for (const Model& model : m_models) {
    for (const Object* object : m_objects) {
        if (object->m_selected) {
            //            model.Draw(modelMatrix, shader);
            //            model.Draw(modelMatrix, shader, view.m_shade, view.dotCloud());

            // TODO
            AxisGeometry::draw(viewWorldTransform * object->m_model.m_transform * viewLocalTransform, shader);
            DotGeometry::draw(viewWorldTransform * object->m_model.m_transform * viewLocalTransform, shader);
            //            object->drawOrigin(viewWorldTransform, viewTransform, shader);
        }
    }
    glDepthFunc(GL_LESS);
    glLineWidth(1);

    // -------------------------------- DRAW AXIS TRANSFORM
    if (view.m_axisTransform) {
        shader.setBool("userColor", true);
        switch (view.m_axisFollow) {
        case 0:
            shader.setVec4("color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
            break;

        case 1:
            shader.setVec4("color", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
            break;

        case 2:
            shader.setVec4("color", glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
            break;
        }

        float lineSize = 1000.0f;

        //        shader.setMat4("model", onesMatrix);
        if (view.m_axisLocal) {
            //            for (const Model& model : m_models) {
            for (const Object* object : m_objects) {
                if (object->m_selected) {
                    shader.setMat4("model", object->m_model.m_transform);

                    switch (view.m_axisFollow) {
                    case 0:
                        LineGeometry::draw(glm::vec3(-lineSize, 0.0f, 0.0f), glm::vec3(lineSize, 0.0f, 0.0f));
                        break;
                    case 1:
                        LineGeometry::draw(glm::vec3(0.0f, -lineSize, 0.0f), glm::vec3(0.0f, lineSize, 0.0f));
                        break;
                    case 2:
                        LineGeometry::draw(glm::vec3(0.0f, 0.0f, -lineSize), glm::vec3(0.0f, 0.0f, lineSize));
                        break;
                    }
                }
            }

        } else {
            // ------------------------ GLOBAL AXIS

            shader.setMat4("model", onesMatrix);
            //            for (const Model& model : m_models) {
            for (const Object* object : m_objects) {
                if (object->m_selected) {

                    //                } else {
                    // ---------------- GLOBAL AXIS
                    glm::vec3 translate = object->m_model.m_transform[3];
                    switch (view.m_transform) {
                    case MainWindow3dView::Transform::TRANSLATE:
                    case MainWindow3dView::Transform::SCALE:
                        switch (view.m_axisFollow) {
                        case 0:
                            LineGeometry::draw(glm::vec3(-lineSize, 0.0f, 0.0f) + translate, glm::vec3(lineSize, 0.0f, 0.0f) + translate);
                            break;
                        case 1:
                            //                        LineGeometry::draw(viewWorldTransform, shader, glm::vec3(0.0f, -lineSize, 0.0f), glm::vec3(0.0f, lineSize, 0.0f));
                            LineGeometry::draw(glm::vec3(0.0f, -lineSize, 0.0f) + translate, glm::vec3(0.0f, lineSize, 0.0f) + translate);
                            break;
                        case 2:
                            //                        LineGeometry::draw(viewWorldTransform, shader, glm::vec3(0.0f, 0.0f, -lineSize), glm::vec3(0.0f, 0.0f, lineSize));
                            LineGeometry::draw(glm::vec3(0.0f, 0.0f, -lineSize) + translate, glm::vec3(0.0f, 0.0f, lineSize) + translate);
                            break;
                        }
                        break;

                    case MainWindow3dView::Transform::ROTATE:
                        switch (view.m_axisFollow) {
                        case 0:
                            LineGeometry::draw(glm::vec3(-lineSize, 0.0f, 0.0f), glm::vec3(lineSize, 0.0f, 0.0f));
                            break;
                        case 1:
                            //                        LineGeometry::draw(viewWorldTransform, shader, glm::vec3(0.0f, -lineSize, 0.0f), glm::vec3(0.0f, lineSize, 0.0f));
                            LineGeometry::draw(glm::vec3(0.0f, -lineSize, 0.0f), glm::vec3(0.0f, lineSize, 0.0f));
                            break;
                        case 2:
                            //                        LineGeometry::draw(viewWorldTransform, shader, glm::vec3(0.0f, 0.0f, -lineSize), glm::vec3(0.0f, 0.0f, lineSize));
                            LineGeometry::draw(glm::vec3(0.0f, 0.0f, -lineSize), glm::vec3(0.0f, 0.0f, lineSize));
                            break;
                        }
                        break;
                    }
                }
            }
        }
        shader.setBool("userColor", false);
    }
    //    glPolygonMode(GL_FRONT, polygonMode);
    //    shader.setMat4("projection", projectionMatrix);
}

void Scene::selectRay(const Ray& ray, bool additional)
{
    updateBoundingBox();

    //    std::vector<const Model *> models;
    //    models.insert(models.end(), m_models.begin(), m_models.end());

    //    uint iModelMin = 0;
    uint iObjectMin = 0;
    uint iMeshMin = 0;
    uint iBoneMin = 0;
    uint iTriangleMin = 0;

    //    float depth;

    float depthMin = Ray::MAX_RAY_LENGTH;
    //    bool first = t;
    //    bool find = false;
    std::vector<glm::vec3> triangles;

    std::vector<float> distances(m_objects.size());
    std::list<uint> nearestModel;
    uint iObject = 0;
    //    for (uint iObject = 0; iObject < m_objects.size(); ++iObject) {
    for (const Object* object : m_objects) {
        //    for (uint iModel = 0; iModel < m_models.size(); ++iModel) {
        //        distances[iModel] = glm::length(m_models ray.m_source)
        //        const Model& model = m_models[iModel];
        //        const Object& object = m_objects
        if (!additional) {

            object->m_selected = false;
        }

        distances[iObject] = std::abs(glm::length(object->m_model.m_box.center() - ray.m_source) - object->m_model.m_box.radius());
        //        nearestModel[iModel] = iModel;
        //        uint iNear =0;
        //        while (iNear < nearestModel.size() && distances[iModel] < nearestModel[iNear]) {
        //        uint cpt =0;
        auto it = nearestModel.begin();
        while (it != nearestModel.end() && distances[iObject] >= distances[*it])
            ++it;
        //        for (uint iNear : nearestModel) {
        //            if (distances[iModel] < distances[*it]) {
        //                nearestModel.insert(it, iModel);
        //                break;
        //            }
        //            ++cpt;
        //            ++it;
        //        }
        //        if (it == nearestModel.end()) {
        nearestModel.insert(it, iObject);
        //        }

        //        }
        ++iObject;
    }
    Q_ASSERT(nearestModel.size() == distances.size());

    //    for (uint iObject : nearestModel) {
    iObject = 0;
    for (const Object* object : m_objects) {
        //        const Object& object = m_models[iObject];
        float dist = distances[iObject];

        if (depthMin < dist) {
            break;
        }
        //        qDebug() << "model " << model.filename().c_str() << iModel << " dist " << dist;

        //    }
        //    return;

        //    for (uint iModel = 0; iModel < m_models.size(); ++iModel) {
        //    for (const Model& model : m_models) {
        //        const Model& model = m_models[iModel];
        //        model.objectFinderRay(ray);
        //        model.selectRay(ray);
        //        model.selectObject(ray, depthMin, find, iModelMin, iMeshMin, iBoneMin, iTriangleMin);
        float depth;

        if (object->m_model.m_box.intersect(ray)) {

            for (uint iMesh = 0; iMesh < object->m_model.m_meshes.size(); ++iMesh) {
                //        for (const Mesh& mesh : m_meshes) {
                const Mesh& mesh = object->m_model.m_meshes[iMesh];

                if (mesh.m_box.intersect(ray)) {
                    //                qDebug() << "select mesh " << mesh.m_name.c_str();
                    if (mesh.m_bones.size() == 0) {
                        for (uint iTriangle = 0; iTriangle < mesh.m_indices.size() / 3; ++iTriangle) {
                            uint i3 = iTriangle * 3;

                            glm::mat4 transform = object->m_model.m_transform * mesh.m_transform;
                            const glm::vec3& v0 = transform * glm::vec4(mesh.m_vertices[mesh.m_indices[i3]].Position, 1.0f);
                            const glm::vec3& v1 = transform * glm::vec4(mesh.m_vertices[mesh.m_indices[i3 + 1]].Position, 1.0f);
                            const glm::vec3& v2 = transform * glm::vec4(mesh.m_vertices[mesh.m_indices[i3 + 2]].Position, 1.0f);
                            //                            const glm::vec3& v1 = transform * glm::vec4(mesh.m_vertices[i3 + 1].Position, 1.0f);
                            //                            const glm::vec3& v2 = transform * glm::vec4(mesh.m_vertices[i3 + 2].Position, 1.0f);

                            //                            const glm::vec3& v0 = model.m_transform * mesh.m_transform * glm::vec4(mesh.m_vertices[i3].Position, 1.0f);
                            //                            const glm::vec3& v1 = model.m_transform * mesh.m_transform * glm::vec4(mesh.m_vertices[i3 + 1].Position, 1.0f);
                            //                            const glm::vec3& v2 = model.m_transform * mesh.m_transform * glm::vec4(mesh.m_vertices[i3 + 2].Position, 1.0f);
                            if (ray.intersect(v0, v1, v2, depth)) {
                                //                                qDebug() << "intersect model " << model.filename().c_str() << depth;
                                triangles.emplace_back(v0);
                                triangles.emplace_back(v1);
                                triangles.emplace_back(v2);
                                //                                if (!find) {
                                //                                    find = true;
                                //                                    iModelMin = iModel;
                                //                                    depthMin = depth;
                                //                                    iMeshMin = iMesh;
                                //                                    iTriangleMin = iTriangle;
                                //                                } else {
                                if (depth < depthMin) {
                                    //                                    qDebug() << "intersect model " << model.filename().c_str() << depth;
                                    iObjectMin = iObject;
                                    depthMin = depth;
                                    iMeshMin = iMesh;
                                    iTriangleMin = iTriangle;
                                }
                                //                                }
                            }
                        }

                    } else {

                        for (uint iBone = 0; iBone < mesh.m_bones.size(); ++iBone) {
                            //                for (const Bone& bone : mesh.m_bones) {
                            const Bone& bone = mesh.m_bones[iBone];

                            if (bone.m_box.intersect(ray)) {
                                //                        qDebug() << "intersect bone " << bone.m_name.c_str() << bone.m_iTriangles.size();

                                //                        for (uint iTriangle =0; iTriangle < bone.m_iTriangles.size(); ++iTriangle) {
                                //                        for (const uint& iTriangle : bone.m_iTriangles) {
                                for (const auto& pair : bone.m_weights) {
                                    const uint& iVertex = pair.first;

                                    for (const uint& iTriangle : mesh.m_triangles[iVertex]) {

                                        uint i3 = iTriangle * 3;
                                        //                            const Vertex & v0 = mesh.m_vertices[i3];
                                        //                            const Vertex & v1 = mesh.m_vertices[i3 + 1];
                                        //                            const Vertex & v2 = mesh.m_vertices[i3 + 2];
                                        Q_ASSERT(mesh.m_vertices.size() > i3 + 2);
                                        glm::mat4 transform = object->m_model.m_transform * bone.m_recurseModel * bone.m_offsetMatrix;
                                        const glm::vec3& v0 = transform * glm::vec4(mesh.m_vertices[i3].Position, 1.0f);
                                        const glm::vec3& v1 = transform * glm::vec4(mesh.m_vertices[i3 + 1].Position, 1.0f);
                                        const glm::vec3& v2 = transform * glm::vec4(mesh.m_vertices[i3 + 2].Position, 1.0f);

                                        //                                        const glm::vec3& v0 = model.m_transform * bone.m_recurseModel * bone.m_offsetMatrix * glm::vec4(mesh.m_vertices[i3].Position, 1.0f);
                                        //                                        const glm::vec3& v1 = model.m_transform * bone.m_recurseModel * bone.m_offsetMatrix * glm::vec4(mesh.m_vertices[i3 + 1].Position, 1.0f);
                                        //                                        const glm::vec3& v2 = model.m_transform * bone.m_recurseModel * bone.m_offsetMatrix * glm::vec4(mesh.m_vertices[i3 + 2].Position, 1.0f);
                                        //                                        //                            v0 = bone.m_recurseModel * bone.m_offsetMatrix * glm::vec4(v0, 1.0f);

                                        //                            std::cout << "v0 : " << v0.x << "  " << v0.y << "  " << v0.z << std::endl;
                                        //                            TriangleGeometry::draw(v0, v1, v2);

                                        if (ray.intersect(v0, v1, v2, depth)) {
                                            //                                            qDebug() << "intersect model " << model.filename().c_str() << depth;
                                            triangles.emplace_back(v0);
                                            triangles.emplace_back(v1);
                                            triangles.emplace_back(v2);
                                            //                                m_triangles.emplace_back(v0);
                                            //                                m_triangles.emplace_back(v1);
                                            //                                m_triangles.emplace_back(v2);

                                            //                                                                            qDebug() << "intersect triangle " << iTriangle;
                                            //                                            qDebug() << "intersect model " << model.filename().c_str();

                                            //                                            if (!find) {
                                            //                                                find = true;
                                            //                                                depthMin = depth;

                                            //                                                iModelMin = iModel;
                                            //                                                iMeshMin = iMesh;
                                            //                                                iBoneMin = iBone;
                                            //                                                iTriangleMin = iTriangle;
                                            //                                            } else {
                                            if (depth < depthMin) {
                                                //                                                qDebug() << "intersect model " << model.filename().c_str() << depth;
                                                //                                    depthMin = std::min(depthMin, depth);
                                                iObjectMin = iObject;
                                                depthMin = depth;
                                                iMeshMin = iMesh;
                                                iBoneMin = iBone;
                                                iTriangleMin = iTriangle;
                                            }
                                            //                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            // end for iMesh
        } // if insersect

        ++iObject;
    } // end loop m_objects

    //    qDebug() << "-----------------------------------------------------------";
    if (depthMin < Ray::MAX_RAY_LENGTH) {
        //        const Model& model = m_models[iModelMin];
        //        const Mesh& mesh = model.m_meshes[iMeshMin];
        //        const Bone& bone = mesh.m_bones[iBoneMin];
        //        uint i3 = iTriangleMin * 3;
        //        glm::mat4 transform = model.m_transform * bone.m_recurseModel * bone.m_offsetMatrix;
        //        const glm::vec3& v0 = transform * glm::vec4(mesh.m_vertices[i3].Position, 1.0f);
        //        const glm::vec3& v1 = transform * glm::vec4(mesh.m_vertices[i3 + 1].Position, 1.0f);
        //        const glm::vec3& v2 = transform * glm::vec4(mesh.m_vertices[i3 + 2].Position, 1.0f);

        if (additional) {
            m_models[iObjectMin].m_selected = !m_models[iObjectMin].m_selected;
        } else {

            m_models[iObjectMin].m_selected = true;
        }

        //        ray.m_length = depthMin;
        //        ray.m_hit = true;
        //        Ray hitRay (ray.m_source, ray.m_direction, depthMin);
        m_rays.emplace_back(ray.m_source, ray.m_direction, depthMin, std::move(triangles));
    } else {
        m_rays.emplace_back(ray.m_source, ray.m_direction);
    }
    //    for (Model & model : m_models) {

    //    }
    //    m_rays.emplace_back(std::move(ray));
    //    m_rays.push_back(ray);
}

//void Scene::unselectRay(const Ray &ray)
//{
//    updateBoundingBox();

//    uint iModelMin = 0;
//    uint iMeshMin = 0;
//    uint iBoneMin = 0;
//    uint iTriangleMin = 0;
//    float depthMin = 0.0f;
//    bool find = false;

//    for (const Model & model : m_models) {
////        model.objectFinderRay(ray);
////        model.unselectRay(ray);
//        model.selectObject(ray, depthMin, find, iModelMin, iMeshMin, iBoneMin, iTriangleMin, true);
//    }

////    m_rays.emplace_back(ray);
//}

//void Scene::objectFinderRay(const Ray &ray)
//{
//    for (const Model & model : m_models) {
//        model.objectFinderRay(ray);
//    }

//    m_rays.emplace_back(ray);
//}

void Scene::addModel(std::string file, const glm::vec3& origin)
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
    //    m_models.emplace_back(file);
    m_models.emplace_back(file);

    //    m_models[m_models.size() - 1].m_transform = glm::translate(glm::mat4(1.0f), origin);
    m_models.back().m_model.m_transform = glm::translate(glm::mat4(1.0f), origin);

    m_objects.push_back(&m_models.back());

    //    std::cout << &m_models[0] << std::endl;
    updateSceneItemModel();
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

void Scene::updateSceneItemModel()
{
    m_sceneModel.clear();

    //    QStandardItemModel model;
    QStandardItem* parentItem = m_sceneModel.invisibleRootItem();
    for (const Object& object : m_models) {
        QStandardItem* item = new QStandardItem(object.m_model.filename().c_str());
        parentItem->appendRow(item);

        object.m_model.buildItemModel(item);
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
    m_objects.clear();
    //    m_models.resize(size);

    //    for (const Model & model : m_models) {
    for (uint i = 0; i < size; ++i) {
        //        model.load(file);
        //        m_models.emplace_back(file);
        m_models.emplace_back(file);

        m_objects.push_back(&m_models.back());
    }

    //    m_cameras.clear();

    //    for (const MainWindow3dView* view : *m_views) {
    //        m_objects.push_back(view->m_camera);
    //    }
    m_cameras.clear();
    Session::load(size, file);
    for (uint i = 0; i < size; ++i) {
        Camera::Type type;
        type = static_cast<Camera::Type>(Session::loadEnum(file));

        //        Camera * camera = new Camera();
        Camera* camera;

        switch (type) {
        case Camera::WORLD:
            camera = new CameraWorld(file);
            //            m_objects.push_back(camera);
            break;

        case Camera::FPS:
            camera = new CameraFps(file);
            //            m_objects.push_back(camera);
            break;
        }
        m_cameras.push_back(camera);
        m_objects.push_back(camera);
    }

    updateSceneItemModel();

    FormTimeline::load(file);

    //    for (const MainWindow3dView * view : *m_views) {
    //        view->updateCameraId();
    //    }
}

void Scene::save(std::ofstream& file)
{
    //    file.write(reinterpret_cast<const char *>(&size), sizeof(size));
    uint size = m_models.size();
    Session::save(size, file);
    for (const Object& object : m_models) {
        object.m_model.save(file);
    }

    size = m_cameras.size();
    Session::save(size, file);
    for (Camera* camera : m_cameras) {
        Session::saveEnum(camera->m_type, file);
        camera->save(file);
    }

    FormTimeline::save(file);

    //    qDebug() << "[SCENE] " << m_itemModel.rowCount();
}

void Scene::updateBoundingBox()
{
    //    qDebug() << "dirLights";
    //    m_dirLights.emplace_back(glm::vec3(0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
    //        glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    //    //        m_dirLights.push_back(5);
    //    for (Model& model : m_models) {
    //        model.updateBoundingBox();
    //    }
    for (const Object* object : m_objects) {
        object->updateBoundingBox();
    }
}

void Scene::setSelectRootTransform(const glm::mat4& transformMatrix, const glm::mat4& worldTransform)
{
    for (Object& object : m_models) {
        if (object.m_selected) {
            //            model.m_rootNode->m_transformation *= transformMatrix;
            object.m_model.m_transform = worldTransform * object.m_model.m_transform * transformMatrix;
            //            model.m_rootNode->m_transformation = model.m_rootNode->m_transformation * transformMatrix;
        }
    }
    updateBoundingBox();
}

void Scene::setSelectToOriginTransform()
{
    for (Object& object : m_models) {
        if (object.m_selected) {
            //            camera.m_target = model.m_rootNode->m_transformation[3];
            //            camera.m_target = model.m_transform[3];
            object.m_model.m_transform = glm::mat4(1.0f);
        }
    }
}

void Scene::setSelectFocus(CameraWorld& camera)
{
    for (const Object& object : m_models) {
        if (object.m_selected) {
            //            camera.m_target = model.m_rootNode->m_transformation[3];
            camera.m_target = object.m_model.m_transform[3];
        }
    }
}

void Scene::deleteSelected()
{
    //    for (const Model & model : m_models) {
    //    auto it = m_models.begin();
    //    while (it != m_models.end()) {
    ////    for (auto &

    //        if (it->m_selected) {
    //            it = m_models.erase(it);
    ////            m_models.remove(model);
    //        }
    //        else {
    //            ++it;
    //        }
    //    }

    //    int cpt = -1;
    //    std::list<const Object *> allObjects;

    //    for (const Object * object : m_objects) {
    //        if (object->m_selected) {

    ////            Q_ASSERT(std::find(m_objects.begin(), m_objects.end(), object) != m_objects.end());
    ////            m_objects.remove(object);
    //            delete object;
    //        }
    //    }
    //    std::vector<const Object *> newObjects;
    //    for ()
    m_objects.clear();

    std::vector<Object> newModels;
    newModels.reserve(10);
    for (Object& object : m_models) {
        //        if (model.m_selected) {
        //            m_objects.remove(&model);
        //        }
        if (!object.m_selected) {
            //        else {
            newModels.emplace_back(std::move(object));
            m_objects.push_back(&newModels.back());
            //            newModels[++cpt] = std::move(model);
        }
    }

    //    for (DirLight & dirLight : m_dirLights) {
    //        if (! dirLight.m_s)
    //    }
    //    for (Camera & camera : m_cameras) {

    //    }

    m_models = std::move(newModels);
    //    m_objects = std::move(newObjects);
}

void Scene::addLight(Light::Type lightType, const glm::vec3 position)
{
    //        m_dirLights.push_back(5);

    switch (lightType) {
    case Light::Type::SUN:

        //        m_dirLights.emplace_back(glm::vec3(0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
        //            glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
        //        //        m_dirLights.push_back(Light(position));

        break;

    case Light::Type::AREA:
        break;

    case Light::Type::SPOT:
        break;

    case Light::Type::POINT:
        break;
    }
}

//void Scene::removeCamera(uint iCamera)
//{
//    std::vector<Camera*> newCameras;
//    uint i =0;
//    for (Camera * camera : m_cameras) {
//        if (i == iCamera) {
//            m_objects.remove(camera);
//            delete camera;
//        }
//        else {
//            newCameras.emplace_back(camera);
//        }

//        ++i;
//    }
////    newCameras.insert(m_cameras.begin(), m_cameras.begin() + iCamera - 1, newCameras.end());
////    newCameras.insert(m_cameras.begin() + iCamera, m_cameras.end(), newCameras.end());

//    m_cameras = std::move(newCameras);
//    //    m_cameras.remove()
//}

void Scene::removeHideCamera()
{
    std::vector<Camera*> newCameras;
    //    uint i =0;
    //    for (Camera * camera : m_cameras) {
    //        if (i == iCamera) {
    //            m_objects.remove(camera);
    //            delete camera;
    //        }
    //        else {
    //            newCameras.emplace_back(camera);
    //        }

    //        ++i;
    //    }
    ////    newCameras.insert(m_cameras.begin(), m_cameras.begin() + iCamera - 1, newCameras.end());
    //    newCameras.insert(m_cameras.begin() + iCamera, m_cameras.end(), newCameras.end());

    //    m_cameras = std::move(newCameras);
    uint iNewIndices[m_cameras.size()];
    //    for (uint i =0; i <m_cameras.size(); ++i) {
    //        iNewIndices
    //    }

    std::list<uint> iCameras;
    for (const MainWindow3dView* view : *m_views) {
        iCameras.push_back(view->m_iCamera);
    }

    //    for (Camera * camera : m_cameras) {
    uint i = 0;
    for (uint iCamera : iCameras) {
        Camera* camera = m_cameras[iCamera];

        newCameras.push_back(camera);
        iNewIndices[iCamera] = i;
        ++i;
    }

    for (const MainWindow3dView* view : *m_views) {
        view->m_iCamera = iNewIndices[view->m_iCamera];
        view->updateCameraId();
    }
    //    m_cameras.remove()

    m_cameras = std::move(newCameras);
}

//void Scene::addCamera(float fov, const glm::vec3 &position, const glm::vec3 &target)
//{
//    // question : camera is actually && references
////    m_cameras.push_back(fov);
//    m_cameras.emplace_back(new CameraWorld(fov, position, target));
//    m_objects.push_back(m_cameras.back());
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

//QStandardItemModel* Scene::itemModel()
//{
//    return &m_itemModel;
//}
