#ifndef QOPENGLWIDGET_EDITOR_H
#define QOPENGLWIDGET_EDITOR_H

//#include <QWidget>
#include <QOpenGLWidget>
//#include <opengl/model.h>
#include <engine/scene/model/Model.h>
#include <vector>
#include <opengl/grid.h>
#include <opengl/axis.h>
#include <gui/QSplitterNode.h>
#include <gui/editor/3dview/MainWindow3dView.h>
#include <engine/scene/Scene.h>
#include <QMainWindow>

#include <opengl/TextRendering.h>
#include <QStatusBar>

#include <opengl/rayTracer/RayTracer.h>

class QOpenGLWidget_Editor : public QOpenGLWidget
{
    Q_OBJECT
public:
    static QOpenGLWidget_Editor * m_editor;
    bool m_initialized = false;

public:
    explicit QOpenGLWidget_Editor(QWidget *parent = nullptr, QMainWindow * mainWindow = nullptr);

//    void addView(const MainWindow3dView * view);


//    std::vector<const MainWindow3dView *> * views();
    void loadNewModel(std::string file);
    void clear();
    void load(std::ifstream & file);
    void save(std::ofstream & file);


    void setViews(std::list<const MainWindow3dView *> *views);

//    const Scene * scene() const;

//    void clear();

    void setStatusBar(QStatusBar *statusBar);

    void addLight(Light::Type lightType, const glm::vec3 position);
    void addDefaultCamera();
//    void addCameraWorld(float fov, glm::vec3 && position, glm::vec3 && target);
//    void deleteCamera(uint iCamera);
    void addCurve();
    void addSurface();

protected:
    void initializeGL() override;
//    void resizeGL(int w, int h) override;
    void paintGL() override;


signals:

public slots:
//    void on_rowInsertedInFileOpennedModel(const QModelIndex & parent, int start, int end);
//    void on_rowRemovedInFileOpennedModel(const QModelIndex & parent, int start, int end);

//    void on_sceneModelChanged();

private:
//    void loadEnv(std::string filename);

private:
    std::list<const MainWindow3dView*> * m_views;
//    std::vector<Model> m_models;
    QMainWindow * m_mainWindow;
    QStatusBar * m_statusBar;
//    Grid * m_grid;
    Axis * m_axis;

    Scene m_scene;
//    TextRendering m_textRender;

//    Shader * m_shader;
//    RayTracer m_rayTracer;

//    std::ostringstream m_stream;
//    std::stringstream m_stream;
//    Model * m_scene;
//    QStandardItemModel m_sceneModel;
//    QStandardItemModel m_fileOpennedModel;

    uint64_t m_deltaTime;
    uint64_t m_lastFrame;
    float m_duration = 0;
    float m_fps;
    int m_cpt = 1;
//    QSplitterNode * m_splitterRoot;
//    QTimer * m_renderTimer = nullptr;


};

#endif // QOPENGLWIDGET_EDITOR_H
