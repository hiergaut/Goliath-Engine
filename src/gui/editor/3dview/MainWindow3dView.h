#ifndef MAINWINDOW3DVIEW_H
#define MAINWINDOW3DVIEW_H

#include <QMainWindow>

namespace Ui {
class MainWindow3dView;
}

//class MainWindow3dView : public QMainWindow
//{
//    Q_OBJECT

//public:
//    explicit MainWindow3dView(QWidget *parent = nullptr);
//    ~MainWindow3dView();

//private:
//    Ui::MainWindow3dView *ui;
//};

//#include "camera.h"
//#include "camera.h"
#include <opengl/CameraWorld.h>
//#include <opengl/camera.h>
//#include "shader.h"
#include <opengl/shader.h>
//#include "model.h"
//#include <opengl/model.h>
#include <QWidget>
#include <QMenu>

#include "../TemplateMenuBar.h"


class MainWindow3dView : public QMainWindow, public TemplateMenuBar {
    Q_OBJECT

public:
    explicit MainWindow3dView(QWidget* parent = nullptr);
    ~MainWindow3dView() override;


//    void setScene(Model *scene);
//    void addModel(std::string file);
    void load(std::ifstream & file);
    void save(std::ofstream & file);


signals:

protected:
    //    void initializeGL() override;
//    void resizeGL(int w, int h) override;
//    void paintGL() override;

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

    void focusInEvent(QFocusEvent* event) override;

    void resizeEvent(QResizeEvent *event) override;

    void setFocusPolicy(Qt::FocusPolicy policy) override;
    QWidget * widget() override;

private:
//    void setCursorToCenter();
//    void cameraMove();
//    void updateProjection();

private:
    Ui::MainWindow3dView *ui;

    bool m_middleClicked = false;

    bool m_ortho = false;
    float orthoSize = 10.0f;


    int frontDir = 0;
    int sideDir = 0;

    QPoint lastPos;
    bool m_shiftPressed = false;

//    Camera camera;
    CameraWorld m_camera;

    glm::mat4 m_projectionMatrix;

    static std::list<const MainWindow3dView*> * m_views;

//    std::list<QMenu> m_menus;

//    glm::mat4 m_viewMatrix;
//private:

public:
    glm::mat4 projectionMatrix() const;
    glm::mat4 viewMatrix() const;
    glm::mat4 projectionViewMatrix() const;
    static void setViews(std::list<const MainWindow3dView *> *views);

    const CameraWorld * camera() const;
//    std::list<QMenu> menus() const;
private slots:
    void on_actionWireFrame_triggered();
};


#endif // MAINWINDOW3DVIEW_H
