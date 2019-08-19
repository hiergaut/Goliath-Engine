#ifndef QOPENGLWIDGET_EDITOR_H
#define QOPENGLWIDGET_EDITOR_H

//#include <QWidget>
#include <QOpenGLWidget>
//#include <opengl/model.h>
#include <engine/scene/model.h>
#include <vector>
#include <opengl/grid.h>
#include <opengl/axis.h>
#include <gui/QSplitterNode.h>
#include <gui/editor/3dview/MainWindow3dView.h>
#include <engine/Scene.h>
#include <QMainWindow>

#include <opengl/TextRendering.h>
#include <QStatusBar>

class QOpenGLWidget_Editor : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit QOpenGLWidget_Editor(QWidget *parent = nullptr, QMainWindow * mainWindow = nullptr);

//    void addView(const MainWindow3dView * view);


//    std::vector<const MainWindow3dView *> * views();
    void loadNewModel(std::string file);
    void load(std::ifstream & file);
    void save(std::ofstream & file);


    void setViews(std::list<const MainWindow3dView *> *views);

//    const Scene * scene() const;

//    void clear();

    void setStatusBar(QStatusBar *statusBar);

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

//    TextRendering m_textRender;

//    Shader * m_shader;
    Scene m_scene;

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


};

#endif // QOPENGLWIDGET_EDITOR_H
