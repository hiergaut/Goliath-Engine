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

#include "Object.h"
#include <engine/scene/model/paramModel/curve/BSplineCurve.h>
//#include "curve/Curve.h"

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
    std::vector<DirLight> m_dirLights;

    Material m_solid = Material("solid", 2.0f, glm::vec3(0.5f), glm::vec3(0.0f), glm::vec3(0.5f, 0.5f, 1.0f));
//    std::vector<Curve> m_curves;


public:
    static Scene * m_scene;

    Scene();
    //    QStandardItemModel *model() const;

    //    class iterator {
    //    public:
    //        iterator(const Scene & scene);

    //    private:

    //    };
    void initializeGL();

    //    const_it begin() const {
    ////        return iterator(*this);
    //        return m_models.begin();
    //    }
    void prepareHierarchy(ulong frameTime);
    void draw(const MainWindow3dView &view);

    void objectSelectRay(const Ray & ray, bool additional = false);
    void vertexSelectRay(const Ray & ray, bool additional = false);

//    void unselectRay(const Ray & ray);

    void addModel(std::string file, const glm::vec3 & spawn);
    void delModel(std::string file);

    void updateSceneItemModel();
//    void modelChanged();

    void clear();
    void load(std::ifstream & file);
    void save(std::ofstream & file);

    void updateBoundingBox();

    void setSelectRootTransform(const glm::mat4 & transformMatrix, const glm::mat4 &worldTransform, MainWindow3dView::Mode mode);
    void setSelectToOriginTransform();
    void setSelectFocus(CameraWorld & camera);
    void deleteSelected();

    void addLight(Light::Type lightType, const glm::vec3 position);
//    void addCamera(float fov, const glm::vec3 & position, const glm::vec3 &target);
    void addDefaultCamera();
    void addCurve();
    void addSurface();
    void addModel(Model * model);

    void updateTransformationMatrix(float dx, float dy);

//    void removeCamera(uint iCamera);
    void removeNoViewCamera();
//    void removeCamera(Camera * camera);
//    ParamModel * getParamModel();
    BSplineCurve *getBsplineCurve();
//    Bsp * getParamModel();

private:
//    void clear();

private:
//    std::vector<std::string> m_modelPaths;

//    QStandardItemModel m_materialModel;
//    std::list<std::pair<std::string, Model>> m_models;
//    std::map<std::string, Model> m_models;

//    Shader* m_shader;

    std::list<const MainWindow3dView *> * m_views; // cameras


//    Shader* m_shaderCamera;
//    std::vector<const CameraWorld*> m_cameras;
//    Axis * m_axis;
    Shader * normalShader;

    Grid * m_grid;
    bool initialized = false;


    std::vector<Ray> m_rays;
//    BoneGeometry * m_bone;


public:
//    QStandardItemModel* itemModel();
//    std::vector<MainWindow3dView *> views() const;
//    std::vector<const CameraWorld &> & cameras() const;
    void setViews(std::list<const MainWindow3dView *> *views);
    const QStandardItemModel & itemModel() const;
    QStandardItemModel * fileOpennedModel();
};


#endif // SCENE_H
