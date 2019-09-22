#ifndef MAINWINDOW3DVIEW_H
#define MAINWINDOW3DVIEW_H


#include <QMainWindow>
//#include <opengl/axis.h>
//#include <engine/scene/Scene.h>
#include <QTimer>

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
//#include <opengl/CameraWorld.h>
//#include <opengl/camera.h>
//#include "shader.h"
#include <opengl/shader.h>
//#include "model.h"
//#include <opengl/model.h>
#include <QMenu>
#include <QWidget>

#include "../TemplateMenuBar.h"
//#include <opengl/camera/Camera.h>
#include <engine/scene/camera/Camera.h>
//#include <gui/editor/MainWindowEditor.h>
//#include <gui/QOpenGLWidget_Editor.h>
#include <opengl/rayTracer/Ray.h>
#include <opengl/shader.h>
#include <engine/scene/model/paramModel/curve/BSplineCurve.h>
#include <engine/scene/model/paramModel/surface/BSplineSurface.h>

class MainWindow3dView : public QMainWindow, public TemplateMenuBar {
    Q_OBJECT

public:
//    enum Shading {
//        //        WIRE_FRAME = 0,
//        SOLID = 0,
//        LOOK_DEV,
//        RENDERED,
//        NORMAL,
//        DEPTH,
//        VERTEX_GROUP,
//        size
//    } m_shade;
//    Shader::
    Shader::Type m_shade;


    enum Mode {
        OBJECT,
        EDIT,
        POSE
    } m_mode;

    enum Transform {
        TRANSLATE,
        ROTATE,
        SCALE
    } m_transform;

//    Mode m_mode;
//    Shading m_shade;
//    glm::mat4 m_transformMatrix = glm::mat4(1.0);
    glm::mat4 * m_localTransform = nullptr;
    glm::mat4 * m_worldTransform = nullptr;
//    glm::vec3 m_translate = glm::vec3(0.0f);
//    glm::mat4 m_worldTransform = glm::mat4(1.0);
    bool m_axisTransform = false;
    uint m_axisFollow =0;
    bool m_axisLocal = false;

//    Camera* m_camera = nullptr;
    mutable uint m_iCamera = 0;
    QTimer * m_timer = nullptr;
    QTimer * m_timerAutoUpdateCurve = nullptr;
    QTimer * m_timerAutoUpdateSurface = nullptr;

//    ParamModel * m_paramModelSelected = nullptr;
    BSplineCurve * m_splineCurve = nullptr;
    BSplineSurface * m_splineSurface = nullptr;

public:
    explicit MainWindow3dView(QWidget* parent = nullptr);
    ~MainWindow3dView() override;

    //    void setScene(Model *scene);
    //    void addModel(std::string file);
    void load(std::ifstream& file);
    void save(std::ofstream& file) const;

    void setMode(Mode mode);
    void setShading(Shader::Type shade);

//    static void glInitialize();

    void setCursorToCenter();

    void updateProjectionMatrix();

    void setTransformActive();
    void setTransformInactive();
    void sendTransformToScene();
//    void swapProjection();
    void updateCameraId() const;

signals:
//    void launchRayTracing(glm::vec3 source, glm::vec3 direction);

public slots:
    void onUpdateCameraFps();
    void onUpdateCurve();
    void onUpdateSurface();

protected:
    //    void initializeGL() override;
    //    void resizeGL(int w, int h) override;
//        void paintGL() override;
    void paintEvent(QPaintEvent * event) override;

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

//    bool eventFilter(QObject * obj, QEvent * event);

    void focusInEvent(QFocusEvent* event) override;

    void resizeEvent(QResizeEvent* event) override;

    void setFocusPolicy(Qt::FocusPolicy policy) override;
    QWidget* widget() override;


private:
    void updateOrthoProjection();
    void updatePersepectiveProjection();
    Ray clickRay(QMouseEvent * event);

    void updateTransformMatrix(float dx, float dy);

    //    void cameraMove();
    //    void updateProjection();

private:
    Ui::MainWindow3dView* ui;

    bool m_middleClicked = false;


    bool m_ortho = false;
    float orthoSize = 10.0f;

    bool m_alignAxis = false;


    bool m_shiftPressed = false;
    bool m_ctrlPressed = false;

    //    Camera camera;

    glm::mat4 m_projectionMatrix;

    static std::list<const MainWindow3dView*>* m_views;

    //    Shader* m_shader = nullptr;
    Mode m_previousMode;

//    static Shader* m_shaders[Shading::size];

    bool m_transformActive = false;
//    bool m_translateActive = false;
    bool m_firstTransform = false;
    QPoint m_memEventPos;
    float m_WheelPos;

    glm::vec3 m_memRight;
    glm::vec3 m_memUp;
    glm::vec3 m_memFront;

    float m_memAxisPos = 0.0f; //wheel

//    QPoint m_posClickPress;
//    QPoint m_posClickPress;

    //    Axis m_axis;

    //    std::list<QMenu> m_menus;

    //    glm::mat4 m_viewMatrix;
    //private:

public:
    glm::mat4 projectionMatrix() const;
    glm::mat4 projectionMatrixZoom() const;
    glm::mat4 viewMatrix() const;
    glm::mat4 projectionViewMatrix() const;
    static void setViews(std::list<const MainWindow3dView*>* views);

    const Camera* camera() const;
    //    std::list<QMenu> menus() const;
    const Shader& shader() const;
    bool xRays() const;
    bool skeleton() const;
    bool normal() const;
    bool boundingBox() const;
    bool dotCloud() const;
    bool intersectRay() const;

    bool vertexGroupShader() const;
    bool solid() const;

private slots:
    //    void on_actionWireFrame_triggered();
    void on_actionSolid_triggered();
    void on_actionLook_dev_triggered();
    void on_actionRendered_triggered();
    void on_actionNormal_triggered();
    void on_actionDepth_triggered();

    void on_actionWireFrame_triggered();
    void on_actionX_Rays_triggered();
    void on_actionSkeleton_triggered();
    void on_actionNormal_2_triggered();
    void on_actionObject_Mode_triggered();
    void on_actionEdit_Mode_triggered();
    void on_actionPose_Mode_triggered();
    void on_actionBoundingBox_triggered();
    void on_actionVertexGroup_triggered();
    void on_actionDotCloud_triggered();
    void on_actionDir_Light_triggered();
    void on_actionPoint_Light_triggered();
    void on_actionSpot_Light_triggered();
    void on_actionArea_Light_triggered();
    void on_actionIntersectRay_triggered();
//    void on_actionB_Spline_triggered();
    void on_actionBSpline_curve_triggered();
    void on_actionBSpline_surface_triggered();
};

#endif // MAINWINDOW3DVIEW_H
