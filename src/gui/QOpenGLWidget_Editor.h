#ifndef QOPENGLWIDGET_EDITOR_H
#define QOPENGLWIDGET_EDITOR_H

//#include <QWidget>
#include <QOpenGLWidget>
#include <opengl/model.h>
#include <vector>
#include <opengl/grid.h>
#include <opengl/axis.h>
#include <gui/QSplitterNode.h>
#include <gui/editor/3dview/QOpenGLWidget_3dView.h>
#include <engine/Scene.h>
#include <QMainWindow>

class QOpenGLWidget_Editor : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit QOpenGLWidget_Editor(QWidget *parent = nullptr, QMainWindow * mainWindow = nullptr);

//    void addView(const QOpenGLWidget_3dView * view);


//    std::vector<const QOpenGLWidget_3dView *> * views();
    void loadNewModel(std::string filename);
    void load(std::ifstream & filename);
    void save(std::ofstream & filename);


    void setViews(std::list<const QOpenGLWidget_3dView *> *views);

protected:
    void initializeGL() override;
//    void resizeGL(int w, int h) override;
    void paintGL() override;


signals:

public slots:

private:
//    void loadEnv(std::string filename);

private:
    std::list<const QOpenGLWidget_3dView*> * m_views;
//    std::vector<Model> m_models;
    QMainWindow * m_mainWindow;
    Grid * m_grid;
    Axis * m_axis;

    Shader * m_shader;
    Scene m_scene;
//    Model * m_scene;

    uint64_t m_deltaTime;
    uint64_t m_lastFrame;
    float m_fps;
    int m_cpt = 0;
//    QSplitterNode * m_splitterRoot;


};

#endif // QOPENGLWIDGET_EDITOR_H
