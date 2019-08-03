#ifndef SCENE_H
#define SCENE_H

#include <QStandardItemModel>
#include <opengl/model.h>
#include <opengl/shader.h>
#include <opengl/grid.h>
#include <gui/editor/3dview/QOpenGLWidget_3dView.h>

class Scene {
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
    void draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);
    void addModel(std::string file);

    void load(std::ifstream & file);
    void save(std::ofstream & file);

private:
    void clear();

private:
//    std::vector<std::string> m_modelPaths;
    QStandardItemModel m_itemModel;
    QStandardItemModel m_fileOpennedModel;

    std::vector<Model> m_models;
    Shader* m_shader;

    std::list<const QOpenGLWidget_3dView *> * m_views;

    Model* m_cameraModel;
    Shader* m_shaderCamera;
//    std::vector<const CameraWorld*> m_cameras;

    Grid * m_grid;


public:
//    QStandardItemModel* itemModel();
//    std::vector<QOpenGLWidget_3dView *> views() const;
//    std::vector<const CameraWorld &> & cameras() const;
    void setViews(std::list<const QOpenGLWidget_3dView *> *views);
};

//static Scene g_scene;

#endif // SCENE_H
