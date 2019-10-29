#include "Scene.h"

//#include <engine/Environment.h>
#include <gui/editor/outliner/QTreeView_outliner.h>
//#include <opengl/model.h>
#include <opengl/version.h>
//#include <opengl/shader.h>

#include "camera/CameraWorld.h"
#include "model/meshModel/MeshModel.h"
#include "model/paramModel/ParamModel.h"
#include "model/paramModel/surface/BSplineSurface.h"
#include <gui/editor/properties/context/curve/FormContextCurve.h>
#include <gui/editor/properties/context/surface/FormContextSurface.h>
#include <gui/editor/timeline/FormTimeline.h>
#include <opengl/geometry/AxisGeometry.h>
#include <opengl/geometry/DotGeometry.h>
#include <opengl/geometry/LineGeometry.h>
#include <opengl/geometry/TriangleGeometry.h>
#include <session/Session.h>

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
    m_pointLights.reserve(20);
    m_spotLights.reserve(10);
    m_cameras.reserve(10);
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
    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();

    //    m_fun->glGetIntegerv(GL_FRAMEBUFFER, &m_fbo);
    //    m_fun->glGetIntegerv(GL_FRAMEBUFFER, &m_fbo);
    //    qDebug() << "fbo : " << m_fbo;
    //    m_fun->glGetFramebufferAttachmentParameteriv(
    //    m_fbo = glGet
    //    glGetIntegerv(GL_POLYGON_MODE, &polygonMode);
    //    m_cameras.push_back(new CameraWorld(50.0f, glm::vec3(200, -200, 200), glm::vec3(0, 0, 0)));

    m_grid = new Grid;
    normalShader = new Shader("normalVector.vsh", "normalVector.fsh", "normalVector.gsh");
    //    normalShader = new Shader("shading/normal.vsh", "shading/normal.fsh");
    //    m_bone = new BoneGeometry;

    m_skyBox = new SkyBox("hw", "morning");
    //    m_skyBox = new SkyBox("ame", "iceflats");
    //    m_skyBox = new SkyBox("hw", "alps");
    //    m_skyBox = new SkyBox("mp", "sorbin");
    //    m_skyBox = new SkyBox("sb", "frozen");
    //    m_skyBox = new SkyBox("hw", "arctic");
    //    m_skyBox = new SkyBox("ame", "siege");

    //    m_skyBox = new SkyBox("ely", "peaks");
    //    m_skyBox = new SkyBox("mp", "morningdew");
    //    m_skyBox = new SkyBox("sb", "iceflow");
    //    m_skyBox = new SkyBox("mp", "hexagon");
    //    m_skyBox = new SkyBox("hw", "sandstorm");
    //    m_skyBox = new SkyBox("ely", "hills2");
    //    m_skyBox = new SkyBox("hw", "sahara");

    //    m_skyBox = new SkyBox("ame", "shadow");
    //    m_skyBox = new SkyBox("sor", "alien");
    //    m_skyBox = new SkyBox("hw", "craterlake");
    //    m_skyBox = new SkyBox("mp", "whirlpool");

    initialized = true;
    //    MainWindow3dView::glInitialize();

    //    glm::vec3 ambient = 0.5f * glm::vec3(1.0f, 1.0f, 1.0f);
    //    glm::vec3 diffuse = 1.0f * glm::vec3(1.0f, 1.0f, 1.0f);
    //    glm::vec3 specular = 1.0f * glm::vec3(1.0f, 1.0f, 1.0f);
    //    glm::vec3 direction = 1.0f * glm::vec3(0.0f, 0.0f, -1.0f);

    //    glm::vec3 ambient = 1.0f * glm::vec3(0.05f, 0.05f, 0.05f);
    //    glm::vec3 diffuse = 1.0f * glm::vec3(0.4f, 0.4f, 0.4f);
    //    glm::vec3 specular = 1.0f * glm::vec3(0.5f, 0.5f, 0.5f);

    //    m_dirLights.emplace_back(glm::vec3(0.0f, 0.0f, 1000.0f), ambient, diffuse, specular, direction);

    //    //        m_dirLights.push_back(5);
    //            shader.setVec3("dirLight[" + QString::number(0).toStdString() + "].direction", -0.2f, -1.0f, -0.3f);
    //            shader.setVec3("dirLight[" + QString::number(0).toStdString() + "].ambient", 0.05f, 0.05f, 0.05f);
    //            shader.setVec3("dirLight[" + QString::number(0).toStdString() + "].diffuse", 0.4f, 0.4f, 0.4f);
    //            shader.setVec3("dirLight[" + QString::number(0).toStdString() + "].specular", 0.5f, 0.5f, 0.5f);

    //    m_axis = new Axis();
    //    updateSceneBox();
    //    updateBoundingBox();
}

void Scene::renderScene(Shader& shader)
{
    for (const Object* object : m_objects) {
        //        if (object != viewCameraObject) {
        if (object->selected()) {
            object->draw(shader, m_localTransform, m_worldTransform);
        } else {
            object->draw(shader);
        }
        //        }
    }
}

void Scene::prepareHierarchy(ulong frameTime)
{
    //    for (const Object& object : m_models) {
    for (const Object* object : m_objects) {
        //	    glm::mat4 model(1.0);
        //        glm::mat4 modelMatrix(1.0);
        //        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.01));
        //        modelMatrix = glm::rotate(modelMatrix, 1.57f, glm::vec3(1, 0, 0));
        //        m_shader->setMat4("model", modelMatrix);

        //        model.Draw(modelMatrix, shader, frameTime);
        object->prepareHierarchy(frameTime);
        //        object->updateBoundingBox();
        //        model.prepareHierarchy(frameTime);
    }

    //    if (m_autoUpdateBoundingBox) {
    //        if (FormTimeline::play()) {
    //            updateBoundingBox();
    //        } else {

    //            if (FormTimeline::m_animationTimeChanged) {
    //                FormTimeline::m_animationTimeChanged = false;

    //                updateBoundingBox();
    //            }
    //        }
    //    }
    //    updateSceneBox();
}

void Scene::updateLightsShadowMap()
{
    //    m_fun->glGetIntegerv(GL_FRAMEBUFFER, &m_fbo);
    //    glEnable(GL_CULL_FACE);
    //    glCullFace(GL_FRONT_AND_BACK);

    glDisable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    for (DirLight& dirLight : m_dirLights) {
        //        dirLight.useShader();
        //                object->draw(shader, false, m_localTransform, m_worldTransform);
        Shader& shader = (dirLight.selected()) ? (dirLight.depthShader(m_localTransform, m_worldTransform)) : (dirLight.depthShader());
        //        Shader & shader = dirLight.depthShader();
        //        m_fun->glBindFramebuffer(GL_FRAMEBUFFER, 1);
        renderScene(shader);
        //        glCullFace(GL_BACK);
        //        m_fun->glBindFramebuffer(GL_FRAMEBUFFER, 1);
        //        dirLight.showDepth();
    }
    for (PointLight& pointLight : m_pointLights) {
        Shader& shader = (pointLight.selected()) ? (pointLight.depthShader(m_localTransform, m_worldTransform)) : (pointLight.depthShader());
        renderScene(shader);
    }
    for (SpotLight& spotLight : m_spotLights) {
        Shader& shader = (spotLight.selected()) ? (spotLight.depthShader(m_localTransform, m_worldTransform)) : (spotLight.depthShader());
        renderScene(shader);
    }
    //    m_fun->glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glCullFace(GL_BACK);
    glDisable(GL_CULL_FACE);
    m_fun->glBindFramebuffer(GL_FRAMEBUFFER, 1);
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
    } else {
        m_skyBox->draw(viewMatrix, projectionMatrix);
    }

    //    if (m_selectObject != nullptr && m_selectObject->m_type == Object::Type::POINT_LIGHT) {
    //        const PointLight& pointLight = static_cast<const PointLight&>(*m_selectObject);
    //        m_skyBox->draw(viewMatrix, projectionMatrix, pointLight.depthMap());
    //    } else {
    //        if (view.m_shade == Shader::Type::RENDERED) {
    //            m_skyBox->draw(viewMatrix, projectionMatrix);
    //        }
    //    }

    //    shader.setMat4("model", onesMatrix);
    //    glLoadIdentity();
    //    return;
    //    return;

    const Shader& shader = view.shader();
    //    shader.use();
    //    shader.setBool("hasSkyBox", false);

    //    const glm::mat4& viewTransform = view.m_transformMatrix;
    //    const glm::mat4& m_worldTransform = view.m_worldTransform;
    //    const glm::mat4& m_localTransform = m_localTransform;
    //    const glm::mat4& viewLocalTransform = m_localTransform;
    //    const glm::mat4& m_worldTransform = m_worldTransform;

    GLint polygonMode;
    glGetIntegerv(GL_POLYGON_MODE, &polygonMode);

    //    return;
    //    shader.setBool("userColor", true);
    //    shader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    //    shader.setMat4("model", onesMatrix);
    //    for (const glm::vec3 & dot : m_dots) {
    //        DotGeometry::draw(glm::translate(onesMatrix, dot), shader, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), 20.0f);
    //    }
    //    for (const Frustum & frustum : m_frustums) {
    //        frustum.draw(shader);
    //    }
    //    shader.setBool("userColor", false);

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
    shader.setBool("userColor", true);
    //    m_rootNode->drawBoundingBox(modelMatrix, shader);
    if (view.m_shade != Shader::Type::RENDERED) {
        shader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        m_box.draw(shader);
    }
    if (view.boundingBox()) {
        //        for (const Model& model : m_models) {
        for (const Object* object : m_objects) {
            //            model.m_box.draw(modelMatrix, shader);
            if (object != viewCameraObject) {

                object->drawBoundingBox(shader);
                //                if (object->selected()) {
                //                    //                    shader.setMat4("model", m_localTransform, m_worldTransform);

                //                } else {
                //                    object->drawBoundingBox(shader);
                //                    //                    shader.setMat4("model", onesMatrix);
                //                }
            }
            //            if (object->m_selected) {

            ////                object->drawBoundingBox(m_worldTransform, shader);
            //            } else {
            //                object->drawBoundingBox(onesMatrix, shader);
            //            }
        }
    }
    shader.setBool("userColor", false);

    //    for (uint i = 0; i < m_dirLights.size(); ++i) {
    //        const DirLight& dirLight = m_dirLights[i];

    //        dirLight.draw(shader);
    //        //        qDebug() << "draw light";
    //    }

    if (view.m_shade == Shader::Type::RENDERED) {
        shader.setBool("shadow", m_computeShadow);

        //                for (const DirLight & dirLight : m_dirLights) {
        uint nbDirLight = m_dirLights.size();
        shader.setInt("nbDirLight", nbDirLight);
        for (uint i = 0; i < nbDirLight; ++i) {
            const DirLight& dirLight = m_dirLights[i];

            //                        dirLight.draw(shader);
            //            shader.setInt("shadowMap", 5 + i);
            shader.setInt("dirLight[" + QString::number(i).toStdString() + "].id", i);
            shader.setInt("dirLight[" + QString::number(i).toStdString() + "].shadowMap", 5 + i);
            glActiveTexture(GL_TEXTURE5 + i);
            glBindTexture(GL_TEXTURE_2D, dirLight.depthMap());
            if (dirLight.selected()) {
                shader.setMat4("dirLight[" + QString::number(i).toStdString() + "].lightSpaceMatrix", dirLight.lightSpaceMatrix(m_localTransform));
                shader.setVec3("dirLight[" + QString::number(i).toStdString() + "].direction", glm::vec4(dirLight.direction(m_localTransform), 1.0f));
            } else {
                //                shader.setMat4("lightSpaceMatrix", dirLight.lightSpaceMatrix());
                shader.setMat4("dirLight[" + QString::number(i).toStdString() + "].lightSpaceMatrix", dirLight.lightSpaceMatrix());
                shader.setVec3("dirLight[" + QString::number(i).toStdString() + "].direction", glm::vec4(dirLight.direction(onesMatrix), 1.0f));
            }

            //            shader.setVec3("dirLight[" + QString::number(i).toStdString() + "].ambient", dirLight.m_ambient);
            shader.setVec3("dirLight[" + QString::number(i).toStdString() + "].ambient", glm::vec3(0.2f));
            //            shader.setVec3("dirLight[" + QString::number(i).toStdString() + "].diffuse", dirLight.m_diffuse);
            shader.setVec3("dirLight[" + QString::number(i).toStdString() + "].diffuse", glm::vec3(1.0f));
            //            shader.setVec3("dirLight[" + QString::number(i).toStdString() + "].specular", dirLight.m_specular);
            shader.setVec3("dirLight[" + QString::number(i).toStdString() + "].specular", glm::vec3(1.0f));

            //            shader.setVec3("dirLight[" + QString::number(0).toStdString() + "].direction", -0.2f, -1.0f, -0.3f);
            //            shader.setVec3("dirLight[" + QString::number(0).toStdString() + "].ambient", 0.05f, 0.05f, 0.05f);
            //            shader.setVec3("dirLight[" + QString::number(0).toStdString() + "].diffuse", 0.4f, 0.4f, 0.4f);
            //            shader.setVec3("dirLight[" + QString::number(0).toStdString() + "].specular", 0.5f, 0.5f, 0.5f);

            //                    shader.setVec3("dirLight.ambient", dirLight.m_ambient);
            //                    shader.setVec3("dirLight.diffuse", dirLight.m_diffuse);
            //                    shader.setVec3("dirLight.specular", dirLight.m_specular);
        }

        uint nbPointLight = m_pointLights.size();
        const uint MAX_POINT_LIGHT = 20;
        shader.setInt("nbPointLight", nbPointLight);
        for (uint i = 0; i < MAX_POINT_LIGHT; ++i) {
            shader.setInt("pointLights[" + QString::number(i).toStdString() + "].shadowMap", 5 + i + nbDirLight);
        }
        for (uint i = 0; i < nbPointLight; ++i) {
            const PointLight& pointLight = m_pointLights[i];
            shader.setInt("pointLights[" + QString::number(i).toStdString() + "].id", i + nbDirLight);
            glActiveTexture(GL_TEXTURE5 + i + nbDirLight);
            glBindTexture(GL_TEXTURE_CUBE_MAP, pointLight.depthMap());
            if (pointLight.selected()) {
                shader.setVec3("pointLights[" + QString::number(i).toStdString() + "].position", pointLight.position(m_localTransform, m_worldTransform));
            } else {
                shader.setVec3("pointLights[" + QString::number(i).toStdString() + "].position", pointLight.position());
            }
            shader.setFloat("pointLights[" + QString::number(i).toStdString() + "].constant", 1.0f);
            //            shader.setFloat("pointLights[" + QString::number(i).toStdString() + "].linear", 0.09f);
            shader.setFloat("pointLights[" + QString::number(i).toStdString() + "].linear", 0.00f);
            //            shader.setFloat("pointLights[" + QString::number(i).toStdString() + "].quadratic", 0.032f);
            shader.setFloat("pointLights[" + QString::number(i).toStdString() + "].quadratic", 0.000005f);
            //            shader.setVec3("pointLights[" + QString::number(i).toStdString() + "].ambient", pointLight.m_ambient);
            shader.setVec3("pointLights[" + QString::number(i).toStdString() + "].ambient", glm::vec3(0.0f));
            //            shader.setVec3("pointLights[" + QString::number(i).toStdString() + "].diffuse", pointLight.m_diffuse);
            shader.setVec3("pointLights[" + QString::number(i).toStdString() + "].diffuse", glm::vec3(1.0f));
            //            shader.setVec3("pointLights[" + QString::number(i).toStdString() + "].specular", pointLight.m_specular);
            shader.setVec3("pointLights[" + QString::number(i).toStdString() + "].specular", glm::vec3(1.0f));
        }

        uint nbSpotLight = m_spotLights.size();
        shader.setInt("nbSpotLight", nbSpotLight);
        for (uint i = 0; i < nbSpotLight; ++i) {
            const SpotLight& spotLight = m_spotLights[i];
            shader.setVec3("spotLights[" + QString::number(i).toStdString() + "].direction", spotLight.direction(m_localTransform));
            shader.setFloat("spotLights[" + QString::number(i).toStdString() + "].cutOff", glm::cos(glm::radians(12.5f)));
            shader.setFloat("spotLights[" + QString::number(i).toStdString() + "].outerCutOff", glm::cos(glm::radians(15.0f)));

            shader.setInt("spotLights[" + QString::number(i).toStdString() + "].id", nbDirLight + i);
            shader.setInt("spotLights[" + QString::number(i).toStdString() + "].shadowMap", nbDirLight + MAX_POINT_LIGHT + 5 + i);
            glActiveTexture(GL_TEXTURE5 + nbDirLight + MAX_POINT_LIGHT + i);
            glBindTexture(GL_TEXTURE_2D, spotLight.depthMap());

            if (spotLight.selected()) {

                shader.setVec3("spotLights[" + QString::number(i).toStdString() + "].position", spotLight.position(m_localTransform, m_worldTransform));
                shader.setMat4("spotLights[" + QString::number(i).toStdString() + "].lightSpaceMatrix", spotLight.lightSpaceMatrix(m_localTransform));
            } else {
                shader.setVec3("spotLights[" + QString::number(i).toStdString() + "].position", spotLight.position());
                shader.setMat4("spotLights[" + QString::number(i).toStdString() + "].lightSpaceMatrix", spotLight.lightSpaceMatrix());
            }
            shader.setFloat("spotLights[" + QString::number(i).toStdString() + "].constant", 1.0f);
            //            shader.setFloat("spotLights[" + QString::number(i).toStdString() + "].linear", 0.09f);
            shader.setFloat("spotLights[" + QString::number(i).toStdString() + "].linear", 0.00f);
            //            shader.setFloat("spotLights[" + QString::number(i).toStdString() + "].quadratic", 0.032f);
            shader.setFloat("spotLights[" + QString::number(i).toStdString() + "].quadratic", 0.0000000f);

            //            shader.setVec3("spotLights[" + QString::number(i).toStdString() + "].ambient", spotLight.m_ambient);
            shader.setVec3("spotLights[" + QString::number(i).toStdString() + "].ambient", glm::vec3(0.0f));
            //            shader.setVec3("spotLights[" + QString::number(i).toStdString() + "].diffuse", spotLight.m_diffuse);
            shader.setVec3("spotLights[" + QString::number(i).toStdString() + "].diffuse", glm::vec3(1.0f));
            //            shader.setVec3("spotLights[" + QString::number(i).toStdString() + "].specular", spotLight.m_specular);
            shader.setVec3("spotLights[" + QString::number(i).toStdString() + "].specular", glm::vec3(1.0f));
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
    //    glEnable(GL_MULTISAMPLE);
    for (const Object* object : m_objects) {
        if (object != viewCameraObject) {
            if (object->selected()) {
                object->draw(shader, view.dotCloud(), m_localTransform, m_worldTransform);

            } else {

                object->draw(shader, view.dotCloud(), onesMatrix, onesMatrix);
            }
        }
    }
    //    glDisable(GL_MULTISAMPLE);
    switch (view.m_mode) {
    case MainWindow3dView::Mode::OBJECT:
        break;
    case MainWindow3dView::Mode::EDIT:
        if (m_selectObject != nullptr) {
            shader.setBool("userColor", true);

            glPolygonMode(GL_FRONT, GL_LINE);
            shader.setVec4("color", glm::vec4(1.0f, 0.5f, 0.0f, 1.0f));
            //        glLineWidth(4);
            //        glPolygonMode(GL_FRONT, GL_LINE);
            glLineWidth(2);
            m_selectObject->draw(shader, false, m_localTransform, m_worldTransform);

            shader.setVec4("color", glm::vec4(1.0f, 0.5f, 0.0f, 1.0f));
            glPointSize(6.0f);
            m_selectObject->draw(shader, true, m_localTransform, m_worldTransform);

            //        for (uint i = 0; i < m_selected.size(); ++i) {
            //            if (m_selected[i]) {
            //                //                qDebug() << "draw " << i;
            //                DotGeometry::draw(glm::translate(glm::mat4(1.0f), m_controlPoints[i]) * worldTransform * m_transform, shader, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), 8);
            //            }
            //        }
            //        m_fun->glPointSize(5.0f);
            //            shader.setVec4("color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
            //            glPointSize(6.0f);
            //            m_selectObject->draw(shader, true, viewLocalTransform, m_worldTransform);
            //            shader.setVec4("color", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
            //            shader.setVec4("color", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
            if (m_selectObject->modelType() == Model::PARAM_CURVE) {
                //                const ParamModel& paramModel = static_cast<ParamModel&>(*m_selectObject->m_model);
                const BSplineCurve& splineCurve = static_cast<BSplineCurve&>(*m_selectObject->getModel());

                splineCurve.drawSelected(shader, m_localVertexTransform, m_worldVertexTransform);
            } else if (m_selectObject->modelType() == Model::PARAM_SURFACE) {
                const BSplineSurface& splineSurface = static_cast<BSplineSurface&>(*m_selectObject->getModel());
                splineSurface.drawSelected(shader, m_localVertexTransform, m_worldVertexTransform);
            }

            shader.setBool("userColor", false);
        }
        break;
    case MainWindow3dView::Mode::POSE:
        break;
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
        if (object->selected()) {
            //            model.Draw(modelMatrix, shader);
            //            if (object != m_selectObject) {
            object->draw(shader, m_localTransform, m_worldTransform);
            //            }
            //            else {
            //                object->draw(shader, viewLocalTransform, m_worldTransform);

            //            }
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
        if (object->selected()) {
            //            model.Draw(modelMatrix, shader);
            //            if (object != m_selectObject) {
            object->draw(shader, m_localTransform, m_worldTransform);
            //            }
            //            else {
            //                object->draw(shader, viewLocalTransform, m_worldTransform);

            //            }

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
            if (object->selected()) {

                object->draw(*normalShader, view.dotCloud(), m_localTransform, m_worldTransform);
            } else {
                object->draw(*normalShader, view.dotCloud(), onesMatrix, onesMatrix);
            }
        }
    }

    // -------------------------------- SKELETON
    if (view.skeleton()) {
        //        modelMatrix = glm::mat4(1.0f);
        //        for (const Model& model : m_models) {
        for (Object& object : m_models) {
            //	    glm::mat4 model(1.0);
            //        glm::mat4 modelMatrix(1.0);
            //        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.01));
            //        modelMatrix = glm::rotate(modelMatrix, 1.57f, glm::vec3(1, 0, 0));
            //        m_shader->setMat4("model", modelMatrix);

            if (object.modelType() == Model::MESH) {
                if (object.selected()) {
                    //                object.m_model.DrawHierarchy(viewLocalTransform, viewMatrix, projectionMatrix, cameraPos, m_worldTransform);
                    static_cast<MeshModel*>(object.getModel())->DrawHierarchy(m_localTransform, viewMatrix, projectionMatrix, cameraPos, m_worldTransform);
                    //                object.m_model->DrawHierarchy(m_localTransform, viewMatrix, projectionMatrix, cameraPos, m_worldTransform);
                    //                object.m_model.DrawHierarchy()

                    //                model.m_model.DrawHierarchy(m_localTransform, view, m_worldTransform);
                } else {
                    //                model.DrawHierarchy(onesMatrix, view);
                    //                object.m_model.DrawHierarchy(onesMatrix, viewMatrix, projectionMatrix, cameraPos);
                    static_cast<MeshModel*>(object.getModel())->DrawHierarchy(onesMatrix, viewMatrix, projectionMatrix, cameraPos);
                    //                object.m_model.DrawHierarchy(onesMatrix, viewMatrix, projectionMatrix, cameraPos);
                }
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
    if (view.m_mode == MainWindow3dView::Mode::EDIT) {

    } else {
        for (const Object* object : m_objects) {
            if (object->selected()) {
                //            model.Draw(modelMatrix, shader);
                //            model.Draw(modelMatrix, shader, view.m_shade, view.dotCloud());

                float dist = glm::length(glm::vec3(object->transform()[3]) - cameraPos);
                // TODO
                //            AxisGeometry::draw(m_worldTransform * object->m_model.m_transform * m_localTransform * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f) * 0.5f * object->m_model.m_box.radius()), shader);
                AxisGeometry::draw(m_worldTransform * object->transform() * glm::scale(m_localTransform, glm::vec3(1.0f) * dist), shader);
                DotGeometry::draw(m_worldTransform * object->transform() * m_localTransform, shader);
                //            object->drawOrigin(m_worldTransform, viewTransform, shader);
            }

            if (object == m_selectObject) {
                DotGeometry::draw(m_worldTransform * object->transform() * m_localTransform, shader, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
                //            DotGeometry::draw(m_worldTransform * object->m_model->m_transform * m_localTransform, shader, glm::vec4(1.0f, 0.5f, 0.0f, 1.0f));
            }
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

        float lineSize = 10000.0f;

        //        shader.setMat4("model", onesMatrix);
        if (view.m_axisLocal) {
            //            for (const Model& model : m_models) {
            for (const Object* object : m_objects) {
                if (object->selected()) {
                    shader.setMat4("model", object->transform());

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
                if (object->selected()) {

                    //                } else {
                    // ---------------- GLOBAL AXIS
                    glm::vec3 translate = object->transform()[3];
                    switch (view.m_transform) {
                    case MainWindow3dView::Transform::TRANSLATE:
                    case MainWindow3dView::Transform::SCALE:
                        switch (view.m_axisFollow) {
                        case 0:
                            LineGeometry::draw(glm::vec3(-lineSize, 0.0f, 0.0f) + translate, glm::vec3(lineSize, 0.0f, 0.0f) + translate);
                            break;
                        case 1:
                            //                        LineGeometry::draw(m_worldTransform, shader, glm::vec3(0.0f, -lineSize, 0.0f), glm::vec3(0.0f, lineSize, 0.0f));
                            LineGeometry::draw(glm::vec3(0.0f, -lineSize, 0.0f) + translate, glm::vec3(0.0f, lineSize, 0.0f) + translate);
                            break;
                        case 2:
                            //                        LineGeometry::draw(m_worldTransform, shader, glm::vec3(0.0f, 0.0f, -lineSize), glm::vec3(0.0f, 0.0f, lineSize));
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
                            //                        LineGeometry::draw(m_worldTransform, shader, glm::vec3(0.0f, -lineSize, 0.0f), glm::vec3(0.0f, lineSize, 0.0f));
                            LineGeometry::draw(glm::vec3(0.0f, -lineSize, 0.0f), glm::vec3(0.0f, lineSize, 0.0f));
                            break;
                        case 2:
                            //                        LineGeometry::draw(m_worldTransform, shader, glm::vec3(0.0f, 0.0f, -lineSize), glm::vec3(0.0f, 0.0f, lineSize));
                            LineGeometry::draw(glm::vec3(0.0f, 0.0f, -lineSize), glm::vec3(0.0f, 0.0f, lineSize));
                            break;
                        }
                        break;
                    }
                }
            }
        }
        shader.setBool("userColor", false);
    } // -------------------------------- END DRAW AXIS TRANSFORM

    // ----------------------------------- DRAW RECTANGLE SELECTION
    //    view.drawRect();

    if (view.m_rightClicked) {
        const QPoint& p = view.m_posFirstRightClick;
        const QPoint& p2 = view.m_posMouse;

        int width = view.width();
        int height = view.height();
        float x = p.x() * 2.0f / width - 1.0f;
        float y = -p.y() * 2.0f / height + 1.0f;
        float x2 = p2.x() * 2.0f / width - 1.0f;
        float y2 = -p2.y() * 2.0f / height + 1.0f;

        shader.setMat4("model", onesMatrix);
        shader.setMat4("view", onesMatrix);
        shader.setMat4("projection", onesMatrix);
        shader.setBool("userColor", true);
        shader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        //        LineGeometry::draw(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, -0.5f, 0.0f));
        LineGeometry::draw(glm::vec3(x, y, 0.0f), glm::vec3(x2, y, 0.0f));
        LineGeometry::draw(glm::vec3(x2, y, 0.0f), glm::vec3(x2, y2, 0.0f));
        LineGeometry::draw(glm::vec3(x2, y2, 0.0f), glm::vec3(x, y2, 0.0f));
        LineGeometry::draw(glm::vec3(x, y2, 0.0f), glm::vec3(x, y, 0.0f));
        shader.setBool("userColor", false);
    }

    //    glPolygonMode(GL_FRONT, polygonMode);
    //    shader.setMat4("projection", projectionMatrix);
}

void Scene::objectSelectRay(const Ray& ray, bool additional)
{
    //    qDebug() << "--------------------------------------------------";
    //    updateBoundingBox();
    //    for (auto & camera : m_cameras) {
    //        camera->updateBoundingBox();
    //    }

    //    std::vector<const Model *> models;
    //    models.insert(models.end(), m_models.begin(), m_models.end());

    //    uint iModelMin = 0;
    uint iObjectMin = 0;
    //    uint iMeshMin = 0;
    //    uint iBoneMin = 0;
    //    uint iTriangleMin = 0;

    //    float depth;

    float depthMin = Ray::MAX_RAY_LENGTH;
    //    bool first = t;
    //    bool find = false;
    std::vector<glm::vec3> triangles;

    std::vector<float> distances(m_objects.size());
    std::list<uint> nearestModel;
    uint iObject = 0;
    //    for (uint iObject = 0; iObject < m_objects.size(); ++iObject) {
    for (Object* object : m_objects) {
        //    for (uint iModel = 0; iModel < m_models.size(); ++iModel) {
        //        distances[iModel] = glm::length(m_models ray.m_source)
        //        const Model& model = m_models[iModel];
        //        const Object& object = m_objects
        if (!additional) {

            object->setSelected(false);
        }

        distances[iObject] = std::abs(glm::length(object->box().center() - ray.m_source) - object->box().radius());
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

    //    qDebug() << "nb Objects " << m_objects.size();
    //    for (uint iObject : nearestModel) {
    //        qDebug() << m_objects[iObject]->name().c_str() << distances[iObject];
    //    }
    //    qDebug() << "------------------------";

    for (uint iObject : nearestModel) {
        //    iObject = 0;
        //    for (const Object* object : m_objects) {
        const Object* object = m_objects[iObject];

        float dist = distances[iObject];
        //                qDebug() << m_objects[iObject]->m_model->name().c_str() << distances[iObject];
        //                qDebug() << object->m_model.filename().c_str() << distances[iObject];

        if (depthMin < dist) {
            break;
        }
        //                qDebug() << "model " << model.filename().c_str() << iModel << " dist " << dist;

        //    }
        //    return;

        //    for (uint iModel = 0; iModel < m_models.size(); ++iModel) {
        //    for (const Model& model : m_models) {
        //        const Model& model = m_models[iModel];
        //        model.objectFinderRay(ray);
        //        model.selectRay(ray);
        //        model.selectObject(ray, depthMin, find, iModelMin, iMeshMin, iBoneMin, iTriangleMin);
        float depth;

        if (object->box().intersect(ray, depth)) {

            //            switch (object->m_model.m_type) {

            //            case Model::MESH:
            if (object->modelType() == Model::PARAM_CURVE || object->modelType() == Model::PARAM_SURFACE) {
                //                const ParamModel & paramModel = static_cast<const ParamModel&>(*object->m_model);
                //                for (const glm::vec3 & ptsCtrl : paramModel.m_controlPoints) {
                if (depth < depthMin) {
                    iObjectMin = iObject;
                    depthMin = depth;
                }
                //                                            }

            } else if (object->modelType() == Model::MESH) {
                const MeshModel& meshModel = static_cast<const MeshModel&>(*object->model());

                //            for (uint iMesh = 0; iMesh < object->m_model.m_meshes.size(); ++iMesh) {
                for (uint iMesh = 0; iMesh < meshModel.m_meshes.size(); ++iMesh) {
                    //        for (const Mesh& mesh : m_meshes) {
                    const Mesh& mesh = meshModel.m_meshes[iMesh];

                    if (mesh.m_box.intersect(ray, depth)) {
                        //                qDebug() << "select mesh " << mesh.m_name.c_str();
                        // ----------------------------------------- FIXED MESH
                        if (mesh.m_bones.size() == 0) {
                            for (uint iTriangle = 0; iTriangle < mesh.m_indices.size() / 3; ++iTriangle) {
                                uint i3 = iTriangle * 3;

                                glm::mat4 transform = object->transform() * mesh.m_transform;
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
                                        //                                    qDebug() << "intersect model " << object->m_model.filename().c_str() << depth;

                                        iObjectMin = iObject;
                                        depthMin = depth;
                                        //                                        iMeshMin = iMesh;
                                        //                                        iTriangleMin = iTriangle;
                                    }
                                    //                                }
                                }
                            }

                        } else {

                            // ------------------------------------------------ ANIMATE
                            for (uint iBone = 0; iBone < mesh.m_bones.size(); ++iBone) {
                                //                for (const Bone& bone : mesh.m_bones) {
                                const Bone& bone = mesh.m_bones[iBone];

                                if (bone.m_box.intersect(ray, depth)) {
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
                                            glm::mat4 transform = object->transform() * bone.m_recurseModel * bone.m_offsetMatrix;
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
                                                    //                                                qDebug() << "intersect model " << object->m_model.filename().c_str() << depth;
                                                    //                                    depthMin = std::min(depthMin, depth);
                                                    iObjectMin = iObject;
                                                    depthMin = depth;
                                                    //                                                    iMeshMin = iMesh;
                                                    //                                                    iBoneMin = iBone;
                                                    //                                                    iTriangleMin = iTriangle;
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
                //                break;
            }

            //            case Model::PARAM:
            //                break;
        } // if insersect

        //        ++iObject;
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
        //        qDebug() << "intersect model " << object->m_model.filename().c_str() << depth;

        if (additional) {
            m_objects[iObjectMin]->setSelected(!m_objects[iObjectMin]->selected());
        } else {

            m_objects[iObjectMin]->setSelected(true);
        }

        m_selectObject = m_objects[iObjectMin];

        switch (m_selectObject->modelType()) {
        case Model::PARAM_CURVE:
            //            Q_ASSERT(FormContextSurface::m_formContextSurface != nullptr);
            //            Q_ASSERT(FormContextCurve::m_formContextCurve != nullptr);
            FormContextSurface::clearContext();
            //                FormContextSurface::m_formContextSurface->clear();
            //            FormContextCurve::initContext(static_cast<BSplineCurve*>(m_selectObject->model()));
            FormContextCurve::initContext(static_cast<BSplineCurve*>(m_selectObject->getModel()));
            //            if (FormContextCurve::m_formContextCurve != nullptr) {
            //                FormContextCurve::m_formContextCurve->initNewSpline(static_cast<BSplineCurve*>(m_selectObject->m_model));
            //            }
            break;

        case Model::PARAM_SURFACE:
            FormContextCurve::clearContext();
            FormContextSurface::initContext(static_cast<BSplineSurface*>(m_selectObject->getModel()));
            //            if (FormContextSurface::m_formContextSurface != nullptr) {
            //                FormContextSurface::m_formContextSurface->initNewSurface(static_cast<BSplineSurface*>(m_selectObject->m_model));
            //            }

            //            Q_ASSERT(FormContextSurface::m_formContextSurface != nullptr);
            //            Q_ASSERT(FormContextCurve::m_formContextCurve != nullptr);
            //            FormContextCurve::m_formContextCurve->clear();
            break;
        }

        //        ray.m_length = depthMin;
        //        ray.m_hit = true;
        //        Ray hitRay (ray.m_source, ray.m_direction, depthMin);
        m_rays.emplace_back(ray.m_source, ray.m_direction, depthMin, std::move(triangles));
    } else {
        m_rays.emplace_back(ray.m_source, ray.m_direction);
        //        m_selectObject = m_objects[iObjectMin];
    }
    //    for (Model & model : m_models) {

    //    }
    //    m_rays.emplace_back(std::move(ray));
    //    m_rays.push_back(ray);
}

void Scene::vertexSelectRay(const Ray& ray, bool additional)
{
    //    qDebug() << "vertexSelectRay";

    if (m_selectObject != nullptr) {
        //        m_selectVertices.clear();

        if (m_selectObject->modelType() == Model::PARAM_CURVE) {
            BSplineCurve& splineCurve = static_cast<BSplineCurve&>(*m_selectObject->getModel());

            //            for (const glm::vec3 & vertex : paramModel.m_controlPoints) {
            splineCurve.vertexSelectRay(ray, additional);
        } else if (m_selectObject->modelType() == Model::PARAM_SURFACE) {
            BSplineSurface& splineSurface = static_cast<BSplineSurface&>(*m_selectObject->getModel());
            splineSurface.vertexSelectRay(ray, additional);
        }
    }
}

void Scene::vertexSelectFrustum(const Frustum& frustum, bool additional)
{
    //void Scene::vertexSelectFrustum(const glm::mat4 &projectionMatrix, const glm::mat4 &viewMatrix, bool additional)
    //{
    if (m_selectObject != nullptr) {
        if (m_selectObject->modelType() == Model::PARAM_CURVE) {
            BSplineCurve& splineCurve = static_cast<BSplineCurve&>(*m_selectObject->getModel());
            //            splineCurve.vertexSelectFrustum(projectionMatrix, viewMatrix, additional);
            splineCurve.vertexSelectFrustum(frustum, additional);

            m_frustums.clear();
            m_frustums.emplace_back(std::move(frustum));
        }
    }
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

void Scene::addModel(std::string file, const glm::vec3& spawn)
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
    //    m_models.emplace_back(file);
    //    m_models.emplace_back(std::move(MeshModel(file)));
    m_models.emplace_back(file);

    //    m_models[m_models.size() - 1].m_transform = glm::translate(glm::mat4(1.0f), origin);
    m_models.back().setTransform(glm::translate(glm::mat4(1.0f), spawn));
    //    m_models.back().m_model->updateBoundingBox();

    m_objects.push_back(&m_models.back());

    //    std::cout << &m_models[0] << std::endl;
    updateSceneItemModel();
    //    updateSceneBox();
    //    updateSceneBox();
}

void Scene::delModel(std::string file)
{

    qDebug() << "[SCENE] delete model : " << file.c_str();
    //    const auto & it = m_models.find(file);
    //    Q_ASSERT(it != m_models.end());
    //    m_models.erase(it);

    //    m_models.remove(file);
    //    std::pair<std::string, Model> & pair =
    //    updateSceneBox();
}

void Scene::updateSceneItemModel()
{
    m_sceneModel.clear();

    //    QStandardItemModel model;
    QStandardItem* parentItem = m_sceneModel.invisibleRootItem();
    for (const Object& object : m_models) {
        QStandardItem* item = new QStandardItem(object.name().c_str());
        parentItem->appendRow(item);

        //        object.buildItemModel(item);
    }

    emit m_sceneModel.dataChanged(m_sceneModel.index(0, 0), m_sceneModel.index(0, 0));
    //    for (int i = 0; i < 4; ++i) {
    //        QStandardItem* item = new QStandardItem(QString("item %0").arg(i));
    //        item->setData(QVariant("fuck"));
    //        parentItem->appendRow(item);
    //        parentItem = item;
    //    }
    //    updateBoundingBox();
    //    updateSceneBox();
}

void Scene::clear()
{
    m_objects.clear();
    m_models.clear();
    m_cameras.clear();
    m_dirLights.clear();
}

void Scene::load(std::ifstream& file)
{
    FormTimeline::clearAnimation();
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
        //        m_models.emplace_back(file);
        m_models.emplace_back(file);
        //        m_models.back().updateBoundingBox();

        m_objects.push_back(&m_models.back());
    }

    //    m_cameras.clear();

    //    for (const MainWindow3dView* view : *m_views) {
    //        m_objects.push_back(view->m_camera);
    //    }
    m_cameras.clear();
    Session::load(size, file);
    for (uint i = 0; i < size; ++i) {
        //        Camera::Type type;
        //        type = static_cast<Camera::Type>(Session::loadEnum(file));

        //        Camera * camera = new Camera();
        Camera* camera = new Camera(file);
        //        camera->m_model->updateBoundingBox();

        //        switch (type) {
        //        case Camera::WORLD:
        //            camera = new CameraWorld(file);
        //            //            m_objects.push_back(camera);
        //            break;

        //        case Camera::FPS:
        //            camera = new CameraFps(file);
        //            //            m_objects.push_back(camera);
        //            break;
        //        }
        m_cameras.push_back(camera);
        m_objects.push_back(camera);
    }

    m_dirLights.clear();
    Session::load(size, file);
    for (uint i = 0; i < size; ++i) {
        m_dirLights.emplace_back(file);
        m_objects.push_back(&m_dirLights.back());
    }

    m_pointLights.clear();
    Session::load(size, file);
    for (uint i = 0; i < size; ++i) {
        m_pointLights.emplace_back(file);
        m_objects.push_back(&m_pointLights.back());
    }

    m_spotLights.clear();
    Session::load(size, file);
    for (uint i = 0; i < size; ++i) {
        m_spotLights.emplace_back(file);
        m_objects.push_back(&m_spotLights.back());
    }

    FormTimeline::load(file);

    updateSceneItemModel();
    //    for (const MainWindow3dView * view : *m_views) {
    //        view->updateCameraId();
    //    }
    //    updateSceneBox();
}

void Scene::save(std::ofstream& file)
{
    //    file.write(reinterpret_cast<const char *>(&size), sizeof(size));
    uint size = m_models.size();
    Session::save(size, file);
    for (const Object& object : m_models) {
        //        object.m_model->save(file);
        object.save(file);
    }

    size = m_cameras.size();
    Session::save(size, file);
    for (Camera* camera : m_cameras) {
        camera->save(file);
    }

    size = m_dirLights.size();
    Session::save(size, file);
    for (const DirLight& dirLight : m_dirLights) {
        dirLight.save(file);
    }

    size = m_pointLights.size();
    Session::save(size, file);
    for (const PointLight& pointLight : m_pointLights) {
        pointLight.save(file);
    }

    size = m_spotLights.size();
    Session::save(size, file);
    for (const SpotLight& spotLight : m_spotLights) {
        spotLight.save(file);
    }

    FormTimeline::save(file);

    //    qDebug() << "[SCENE] " << m_itemModel.rowCount();
}

//void Scene::updateBoundingBox()
//{
//    qDebug() << "dirLights";
//    m_dirLights.emplace_back(glm::vec3(0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
//        glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
//    //        m_dirLights.push_back(5);
//    for (Model& model : m_models) {
//        model.updateBoundingBox();
//    }
//    for (const Object* object : m_objects) {
//        object->m_model->updateBoundingBox();
//    }
//}

void Scene::updateSceneBox()
{
    //    updateBoundingBox();

    m_box.clear();
    for (const Object& object : m_models) {
        m_box << object.box();
    }
}

void Scene::setSelectRootTransform(const glm::mat4& transformMatrix, const glm::mat4& worldTransform, MainWindow3dView::Mode mode)
{
    //    for (Object& object : m_models) {
    switch (mode) {
    case MainWindow3dView::Mode::OBJECT:

        for (Object* object : m_objects) {
            if (object->selected()) {
                //            model.m_rootNode->m_transformation *= transformMatrix;
                object->setTransform(worldTransform * object->transform() * transformMatrix);
                //                object->m_model->updateBoundingBox();
                //            model.m_rootNode->m_transformation = model.m_rootNode->m_transformation * transformMatrix;
            }
        }
        break;

    case MainWindow3dView::Mode::EDIT:
        if (m_selectObject != nullptr) {
            m_selectObject->updateSelectedVertexPosition(transformMatrix, worldTransform);
            //            switch (m_selectObject->m_model->m_type) {

            //            }
        }
        break;
    }
    //    updateBoundingBox();
}

void Scene::setSelectToOriginTransform()
{
    //    for (Object& object : m_models) {
    for (Object* object : m_objects) {
        if (object->selected()) {
            //            camera.m_target = model.m_rootNode->m_transformation[3];
            //            camera.m_target = model.m_transform[3];
            object->setTransform(glm::mat4(1.0f));
            //            object->m_model->updateBoundingBox();
        }
    }
}

void Scene::setSelectFocus(CameraWorld& camera)
{
    //    for (const Object& object : m_models) {
    for (const Object* object : m_objects) {
        if (object->selected()) {
            //            camera.m_target = model.m_rootNode->m_transformation[3];
            //            camera.m_target = object->m_model.m_transform[3];
            camera.setTarget(object->transform()[3]);
            break;
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
    switch (m_selectObject->modelType()) {
    case Model::PARAM_CURVE:
        FormContextCurve::clearContext();
        break;

    case Model::PARAM_SURFACE:
        FormContextSurface::clearContext();
        break;
    }

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
    //    qDebug() << "object clear";
    //    std::cout << "object clear" << std::endl;
    std::vector<Camera*> newCameras;
    newCameras.reserve(10);
    for (Camera* camera : m_cameras) {
        if (!camera->selected()) {
            newCameras.emplace_back(camera);
            m_objects.push_back(camera);
        }
    }

    std::vector<Object> newModels;
    newModels.reserve(10);
    for (Object& object : m_models) {
        //        if (model.m_selected) {
        //            m_objects.remove(&model);
        //        }
        if (!object.selected()) {
            //            std::cout << object.m_model->name() << "not selected" << std::endl;
            //        else {
            newModels.emplace_back(std::move(object));
            m_objects.push_back(&newModels.back());
            //            newModels[++cpt] = std::move(model);
        }
    }
    //    std::cout << "models moving" << std::endl;
    m_models = std::move(newModels);
    //    std::cout << "models moved" << std::endl;

    std::vector<DirLight> newDirLights;
    newDirLights.reserve(10);
    for (DirLight& dirLight : m_dirLights) {
        if (!dirLight.selected()) {
            newDirLights.emplace_back(std::move(dirLight));
            m_objects.push_back(&newDirLights.back());
        }
    }
    m_dirLights = std::move(newDirLights);

    std::vector<PointLight> newPointLights;
    newPointLights.reserve(10);
    for (PointLight& pointLight : m_pointLights) {
        if (!pointLight.selected()) {
            newPointLights.emplace_back(std::move(pointLight));
            m_objects.push_back(&newPointLights.back());
        }
    }
    m_pointLights = std::move(newPointLights);

    std::vector<SpotLight> newSpotLights;
    newSpotLights.reserve(10);
    for (SpotLight& spotLight : m_spotLights) {
        if (!spotLight.selected()) {
            newSpotLights.emplace_back(std::move(spotLight));
            m_objects.push_back(&newSpotLights.back());
        }
    }
    m_spotLights = std::move(newSpotLights);

    //    std::cout << "dirLights moved" << std::endl;

    //    for (DirLight & dirLight : m_dirLights) {
    //        if (! dirLight.m_s)
    //    }
    //    for (Camera & camera : m_cameras) {
    //    FormContextCurve::m_formContextCurve->m_model = nullptr;

    //    }

    //    m_objects = std::move(newObjects);
}

void Scene::addLight(Light::Type lightType, const glm::vec3 position)
{
    //        m_dirLights.push_back(5);

    switch (lightType) {
    case Light::Type::SUN:

        //        m_dirLights.emplace_back(glm::vec3(0.0f, 0.0f, -2000.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),
        //            glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        m_dirLights.emplace_back(glm::vec3(0.0f, 0.0f, -2000.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        //        m_dirLights.back().updateBoundingBox();
        m_objects.push_back(&m_dirLights.back());
        //        //        m_dirLights.push_back(Light(position));

        break;

    case Light::Type::AREA:
        break;

    case Light::Type::SPOT:
        m_spotLights.emplace_back(position, glm::vec3(0.0f, 1.0f, 0.0f));
        m_objects.push_back(&m_spotLights.back());
        break;

    case Light::Type::POINT:
        m_pointLights.emplace_back(position);
        m_objects.push_back(&m_pointLights.back());
        break;
    }
}

void Scene::addDefaultCamera()
{
    m_cameras.emplace_back(new Camera(60.0f));
    m_objects.push_back(m_cameras.back());
}

void Scene::addCurve(BSplineCurve::Type type)
{
    //    m_models.push_back(new ParamModel());
    //    m_models.emplace_back(new ParamModel());
    //    m_models.emplace_back(new BSplineCurve);
    //    m_models.push_back(new BSplineCurve);
    //    m_models.emplace_back(new BSplineCurve);

    //    m_models.emplace_back(Curve());
    //    m_models.push_back(Object(Curve()));
    //    m_objects.push_back(&m_models.back());
    addModel(new BSplineCurve(type));
}

void Scene::addSurface(BSplineSurface::Type type)
{
    //    m_models.emplace_back(new BSplineSurface);
    //    m_objects.push_back(&m_models.back());
    addModel(new BSplineSurface(type));
}

void Scene::addModel(Model* model)
{
    m_models.emplace_back(model);
    //    model->updateBoundingBox();
    m_objects.push_back(&m_models.back());
    //    updateSceneBox();
}

void Scene::addRay(Ray&& ray)
{
    m_rays.emplace_back(ray);
}

void Scene::addDot(const glm::vec3& dot)
{
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

void Scene::removeNoViewCamera()
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

//ParamModel* Scene::getParamModel()
//{
//    for (Object& object : m_models) {
//        if (object.m_model->m_type == Model::PARAM) {
//            return static_cast<ParamModel*>(object.m_model);
//            //            return object.m_model;
//            break;
//        }
//    }

//    return nullptr;
//}

BSplineCurve* Scene::getBsplineCurve()
{
    for (Object& object : m_models) {
        if (object.selected()) {
            if (object.modelType() == Model::PARAM_CURVE) {
                //            ParamModel * paramModel =  static_cast<ParamModel*>(object.m_model);
                BSplineCurve* splineCurve = static_cast<BSplineCurve*>(object.getModel());
                return splineCurve;
                //            if (paramModel->m_type == ParamModel::Type::BSPLINE_CURVE) {
                //                return dynamic_cast<BSplineCurve*>(paramModel);
                //            }
                //            //            return object.m_model;
                break;
            }
        }
    }

    return nullptr;
}

BSplineSurface* Scene::getBsplineSurface()
{
    for (Object& object : m_models) {
        if (object.selected()) {
            if (object.modelType() == Model::PARAM_SURFACE) {
                //            ParamModel * paramModel =  static_cast<ParamModel*>(object.m_model);
                BSplineSurface* splineSurface = static_cast<BSplineSurface*>(object.getModel());
                return splineSurface;
                //            if (paramModel->m_type == ParamModel::Type::BSPLINE_CURVE) {
                //                return dynamic_cast<BSplineCurve*>(paramModel);
                //            }
                //            //            return object.m_model;
                break;
            }
        }
    }

    return nullptr;
}

//void Scene::removeCamera(Camera *camera)
//{
////    m_objects.erase(m_objects.begin() + 0);

//}

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
