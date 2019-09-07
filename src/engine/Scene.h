#ifndef SCENE_H
#define SCENE_H

#include <QStandardItemModel>
//#include <opengl/model.h>
#include "scene/model.h"
#include <opengl/shader.h>
#include <opengl/grid.h>
#include <gui/editor/3dview/MainWindow3dView.h>
#include <opengl/axis.h>

//#include <QObject>
//#include <QWidget>
#include <map>

#include <opengl/rayTracer/Ray.h>
//#include <opengl/rayTracer/RayTracer.h>
#include <opengl/camera/CameraWorld.h>

class Scene {
//    Q_OBJECT
public:
    static QStandardItemModel m_sceneModel;
    bool m_autoUpdateBoundingBox = false;

public:
    Scene();
    //    QStandardItemModel *model() const;

    //    class iterator {
    //    public:
    //        iterator(const Scene & scene);

    //    private:

    //    };
    void initialize();

    //    const_it begin() const {
    ////        return iterator(*this);
    //        return m_models.begin();
    //    }
    void prepareHierarchy(ulong frameTime);
    void draw(const MainWindow3dView &view);

    void selectRay(const Ray & ray, bool additional = false);

//    void unselectRay(const Ray & ray);

    void addModel(std::string file);
    void delModel(std::string file);

    void updateSceneModel();
//    void modelChanged();

    void load(std::ifstream & file);
    void save(std::ofstream & file);

    void updateBoundingBox();

    void setSelectRootTransform(const glm::mat4 & transformMatrix, const glm::mat4 &worldTransform);
    void setSelectToOriginTransform();
    void setSelectFocus(CameraWorld & camera);
    void deleteSelected();


private:
//    void clear();

private:
//    std::vector<std::string> m_modelPaths;

//    QStandardItemModel m_materialModel;
//    std::list<std::pair<std::string, Model>> m_models;
//    std::map<std::string, Model> m_models;
    std::vector<Model> m_models;
//    Shader* m_shader;

    std::list<const MainWindow3dView *> * m_views;

    Model* m_cameraModel = nullptr;
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

//static Scene g_scene;

#endif // SCENE_H
