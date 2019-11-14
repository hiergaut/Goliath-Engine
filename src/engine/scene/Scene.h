#ifndef SCENE_H
#define SCENE_H

#include <QStandardItemModel>
//#include <opengl/model.h>
#include "model/Model.h"
#include <opengl/shader.h>
#include <opengl/grid.h>
#include <gui/editor/3dview/MainWindow3dView.h>
#include <opengl/axis.h>

//#include <QObject>
//#include <QWidget>
#include <map>

#include <opengl/rayTracer/Ray.h>
//#include <opengl/rayTracer/RayTracer.h>
#include <engine/scene/camera/CameraWorld.h>
#include "light/Light.h"
#include "light/DirLight.h"
#include "light/PointLight.h"
#include "light/SpotLight.h"

#include "Object.h"
#include <engine/scene/model/paramModel/curve/BSplineCurve.h>
#include "model/paramModel/surface/BSplineSurface.h"
//#include "curve/Curve.h"
#include <opengl/Frustum.h>
#include "light/SkyBox.h"

class Scene {
//    Q_OBJECT
public:
    QStandardItemModel m_sceneModel;
    bool m_autoUpdateBoundingBox = false;


    glm::mat4 m_localTransform = glm::mat4(1.0);
    glm::mat4 m_worldTransform = glm::mat4(1.0);

    glm::mat4 m_localVertexTransform = glm::mat4(1.0f);
    glm::mat4 m_worldVertexTransform= glm::mat4(1.0f);

//    static Model* m_cameraModel;
//    static Model* m_lightDirModel;

    Object * m_selectObject = nullptr;
//    std::vector<uint> m_selectVertices;
    std::vector<Object *> m_objects;

//    std::vector<Model> m_models;
    std::vector<Object> m_models;
    static std::vector<Camera*> m_cameras; // legacy
    std::vector<Light *> m_lights;
    std::vector<DirLight> m_dirLights;
    std::vector<PointLight> m_pointLights;
//    std::vector<bool> m_shadowComputedPointLights;
//    std::vector<glm::vec3> m_positionPointLights;
    std::vector<SpotLight> m_spotLights;

    Material m_solid = Material("solid", 2.0f, glm::vec3(0.5f), glm::vec3(0.0f), glm::vec3(0.5f, 0.5f, 1.0f));
//    std::vector<Curve> m_curves;
    BoundingBox m_box;

    bool m_computeShadow = true;
    uint m_nbComputePointLightShadow;
    bool m_zPrepass = false;
//    bool m_multiSampling = true;
    std::list<const MainWindow3dView *> * m_views; // cameras

    Shader * m_minimalShader;
//    bool m_oneModelTransformChanged = false;
//    bool m_viewTransformActive = false;
//    uint m_shadowMapDetail = 0;
//    uint m_cptShadowMapDetail = 0;

    uint m_iLightDepthMap = 0;
    bool m_bloomEnable = false;
//    uint m_nbLight;
    bool m_firstDraw = true;

    int m_tessellationLevel = 1;


public:
    QOpenGLFunctionsCore * m_fun;
    static Scene * m_scene;

    Scene();
    //    QStandardItemModel *model() const;

    //    class iterator {
    //    public:
    //        iterator(const Scene & scene);

    //    private:

    //    };
    void initializeGL();
    void renderScene(const Shader &shader);
//    void renderNoColorScene();

    //    const_it begin() const {
    ////        return iterator(*this);
    //        return m_models.begin();
    //    }
    void prepareHierarchy(ulong frameTime);
    void updateLightsShadowMap();
    void updateAllLightsShadowMap();
    void draw(const MainWindow3dView &view, const int x, const int y, const int viewWidth, const int viewHeight);

    void objectSelectRay(const Ray & ray, bool additional = false);
    void vertexSelectRay(const Ray & ray, bool additional = false);
//    void vertexSelectFrustum(const glm::mat4 & projectionMatrix, const glm::mat4 & viewMatrix, bool additional = false);
    void vertexSelectFrustum(const Frustum & frustum, bool additional = false);

//    void unselectRay(const Ray & ray);

    void addModel(std::string file, const glm::vec3 & spawn);
    void delModel(std::string file);

    void updateSceneItemModel();
//    void modelChanged();

    void clear();
    void load(std::ifstream & file);
    void save(std::ofstream & file);

//    void updateBoundingBox();
    void updateSceneBox();

    void setSelectRootTransform(const glm::mat4 & transformMatrix, const glm::mat4 &worldTransform, MainWindow3dView::Mode mode);
    void setSelectToOriginTransform();
    void setSelectFocus(CameraWorld & camera);
    void deleteSelected();

    void addLight(Light::Type lightType, const glm::vec3 position);
//    void updateNbLight();
//    void addCamera(float fov, const glm::vec3 & position, const glm::vec3 &target);
    void addDefaultCamera();
    void addCurve(BSplineCurve::Type type);
    void addSurface(BSplineSurface::Type type);
    void addModel(Model * model);
    void addRay(Ray && ray);
    void addDot(const glm::vec3 & dot);

//    void updateTransformationMatrix(float dx, float dy);

//    void removeCamera(uint iCamera);
    void removeNoViewCamera();
//    void removeCamera(Camera * camera);
//    ParamModel * getParamModel();
    BSplineCurve *getBsplineCurve();
    BSplineSurface *getBsplineSurface();
//    Bsp * getParamModel();

private:
//    void clear();
    void prepareLightUniform(const MainWindow3dView &view, const Shader &shader);
    void zPrepass(const Shader & shader);
    void drawBoundingBox(const MainWindow3dView &view, const Shader &shader, const Object *viewCameraObject, bool multiSample);
    void drawRay(const MainWindow3dView &view, const Shader &shader, uint polygonMode);
    void drawSkyBox(const MainWindow3dView &view, bool multiSample, const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix);

    void drawSpecificMode(const MainWindow3dView & view, const Shader & shader);
    void drawContours(const Shader &shader, uint polygonMode);
    void drawNormal(const MainWindow3dView & view, const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix);
    void drawSkeleton(const MainWindow3dView &view, const Shader &shader, const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix, glm::vec3 &cameraPos);
    void drawOriginModel(const MainWindow3dView & view, const Shader & shader, const glm::vec3 &cameraPos);
    void drawAxisTransform(const MainWindow3dView & view, const Shader & shader);
    void drawRectangleSelection(const MainWindow3dView & view, const Shader & shader);

private:
//    std::vector<std::string> m_modelPaths;

//    QStandardItemModel m_materialModel;
//    std::list<std::pair<std::string, Model>> m_models;
//    std::map<std::string, Model> m_models;

//    Shader* m_shader;
//    GLint m_fbo;



//    Shader* m_shaderCamera;
//    std::vector<const CameraWorld*> m_cameras;
//    Axis * m_axis;
    Shader * normalShader;

    Grid * m_grid;
    bool initialized = false;


    std::vector<Ray> m_rays;
    std::vector<Frustum> m_frustums;
    std::vector<glm::vec3> m_dots;
//    BoneGeometry * m_bone;
    SkyBox * m_skyBox;

    Shader * m_bloomShader;
    Shader * m_blurShader;




public:
//    QStandardItemModel* itemModel();
//    std::vector<MainWindow3dView *> views() const;
//    std::vector<const CameraWorld &> & cameras() const;
    void setViews(std::list<const MainWindow3dView *> *views);
    const QStandardItemModel & itemModel() const;
    QStandardItemModel * fileOpennedModel();
};


#endif // SCENE_H
