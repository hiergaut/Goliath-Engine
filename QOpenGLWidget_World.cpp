#include "QOpenGLWidget_World.h"
#include <QTime>
#include <QtMath>

#include <QKeyEvent>
#include <QPainter>

QOpenGLWidget_World::QOpenGLWidget_World(QWidget* parent)
    : QOpenGLWidget(parent)
    , m_vbo(QOpenGLBuffer::VertexBuffer)
    , camera(QVector3D(0, 0, 3))
//    , m_ebo(QOpenGLBuffer::IndexBuffer)
{
//    cameraPos = QVector3D(0, 0, 3);
//    cameraFront = QVector3D(0, 0, -1);
//    cameraUp = QVector3D(0, 1, 0);


//    setAutoFillBackground(false);
    setMouseTracking(true);
//    cursor().setPos(100, 100);

//    setAcceptDrops(true);
}

QOpenGLWidget_World::~QOpenGLWidget_World()
{
    makeCurrent();
    delete m_texture;


    //    doneCurrent();
}

void QOpenGLWidget_World::initializeGL()
{
    initializeOpenGLFunctions();

    QImage img(":/texture/wall.jpg");
    Q_ASSERT(!img.isNull());
    //    m_texture = new QOpenGLTexture(img.scaled(200, 200));
    //    m_texture = new QOpenGLTexture(img.scaled(32, 36).mirrored());
    m_texture = new QOpenGLTexture(img);
    //    m_texture->setWrapMode(QOpenGLTexture::MirroredRepeat);
    m_texture->setMinificationFilter(QOpenGLTexture::Nearest);
    m_texture->setMagnificationFilter(QOpenGLTexture::Nearest);

    QImage img2(":/texture/awesomeface.png");
    Q_ASSERT(!img.isNull());
    //    m_texture2 = new QOpenGLTexture(img2.mirrored(false, true));
    m_texture2 = new QOpenGLTexture(img2);
    //    m_texture->generateMipMaps();

    // ---------------------------------------------------------------------

    //    glClearColor(1, 0, 0, 0.5);
    QOpenGLShader vShader(QOpenGLShader::Vertex, this);
    vShader.compileSourceFile(":/first.vsh");

    QOpenGLShader fShader(QOpenGLShader::Fragment, this);
    fShader.compileSourceFile(":/first.fsh");

    m_program.addShader(&vShader);
    m_program.addShader(&fShader);
    m_program.link();
    m_program.release();
    //    m_program.bind();
    // ---------------------------------------------------------------------

    m_vao.create();
    m_vao.bind();

    GLfloat vertices[] = {
        //        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
        //        0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
        //        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        //        -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top left

        //        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
        //        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
        //        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        //        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // top left
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
    };

    m_vbo.create();
    m_vbo.bind();
    m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vbo.allocate(vertices, sizeof(vertices));

    //    GLuint indices[] = {
    //        0, 1, 3, // first triangle
    //        1, 2, 3, // second triangle

    //        1, 0, 5,
    //        5, 0, 4,

    //        7, 4, 5,
    //        6, 4, 5,

    //        4, 3, 5,
    //        3, 2, 5,

    //        3, 4, 0,
    //        4, 7, 4,

    //        2, 1, 5,
    //        1, 6, 5
    //    };

    //    m_ebo.create();
    //    m_ebo.bind();
    //    m_ebo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    //    m_ebo.allocate(indices, sizeof(indices));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    //    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    //    glEnableVertexAttribArray(1);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    m_vbo.release();
    m_vao.release();

    // ---------------------------------------------------------------------
    //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_MULTISAMPLE);
}

void QOpenGLWidget_World::resizeGL(int w, int h)
{
    updateProjection();
}

//void QOpenGLWidget_World::paintGLprivate()
void QOpenGLWidget_World::paintGL()
{
    //    makeCurrent();
    //    glPushMatrix();
    //    qDebug() << "paintGL";
    uint64_t currentFrame = QDateTime::currentMSecsSinceEpoch();
    //    qDebug() << currentFrame;
    //    qDebug() << static_cast<int>(currentFrame / 100);
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    //        qDebug() << "fps : " << 1000.0 / deltaTime;
    fps += 1000.0 / deltaTime;
    if (cpt % 60 == 0) {
        qDebug() << "fps : " << fps / 60.0;
        fps = 0.0;
    }

    cameraMove();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_texture->bind();
    m_texture2->bind(1);
    m_program.setUniformValue("texture1", 0);
    m_program.setUniformValue("texture2", 1);

    //    QMatrix4x4 transform;
    //    transform.setToIdentity();
    //    transform.scale(abs(sin(time * 0.01)));
    //    transform.rotate(time++, 0, 0, 1);
    //    transform.translate(0.5, -0.5, 0.0);
    //    m_program.setUniformValue("transform", transform);

//    QMatrix4x4 view;
    //    float radius = 10;
    //    float camX = sin(0.01 * time) * radius;
    //    float camZ = cos(0.01 * time) * radius;
    //    view.translate(0, 0, -3);
    //    view.lookAt(QVector3D(camX, 0, camZ), QVector3D(0, 0, 0), QVector3D(0, 1, 0));
//    m_view.setToIdentity();
//    m_view.lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
//    m_view = camera.GetViewMatrix();
    m_program.setUniformValue("view", camera.GetViewMatrix());

    //    QMatrix4x4 projection;
    //    projection.perspective(60, width() / float(height()), 0.01, 100);
    m_program.setUniformValue("projection", m_projection);

    m_program.bind();
    m_vao.bind();

    //    float timeValue = QTime::currentTime().msec();
    //    float greenValue = sin(time += 0.1) / 2.0f + 0.5f;
    //    m_program.setUniformValue("ourColor", 0.0f, greenValue, 0.0f, 1.0f);

    for (int i = 0; i < 10; ++i) {
        QMatrix4x4 model;
        model.translate(cubePositions[i]);
        model.rotate(static_cast<int>(currentFrame / 10) % 360, cubePositions[i]);
        //        model.rotate(0.1 * time++, 1, 0.3, 05);
        m_program.setUniformValue("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    //    doneCurrent();

    //    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //        m_program.release();
    //        m_vao.release();
    //    ++time;

    update();
    ++cpt;
}

void QOpenGLWidget_World::keyPressEvent(QKeyEvent* event)
{
    //    qDebug() << "keyPressEvent";

    switch (event->key()) {
    case Qt::Key_Up:
    case Qt::Key_Comma:
        //        cameraPos += cameraFront * cameraSpeed;
        frontDir = 1;
        break;

    case Qt::Key_Down:
    case Qt::Key_O:

        frontDir = -1;
        //        cameraPos -= cameraFront * cameraSpeed;
        break;

    case Qt::Key_Left:
    case Qt::Key_A:
        sideDir = -1;
        //        cameraPos -= QVector3D::crossProduct(cameraFront, cameraUp).normalized() * cameraSpeed;
        break;

    case Qt::Key_Right:
    case Qt::Key_E:
        sideDir = 1;
        //        cameraPos += QVector3D::crossProduct(cameraFront, cameraUp).normalized() * cameraSpeed;
        break;
    }
}

void QOpenGLWidget_World::keyReleaseEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_Up:
    case Qt::Key_Comma:
    case Qt::Key_Down:
    case Qt::Key_O:
        frontDir = 0;
        break;

    case Qt::Key_Left:
    case Qt::Key_A:
    case Qt::Key_Right:
    case Qt::Key_E:
        sideDir = 0;
        break;
    }
}

void QOpenGLWidget_World::mousePressEvent(QMouseEvent* event)
{
//    qDebug() << "fuck";
}

void QOpenGLWidget_World::mouseMoveEvent(QMouseEvent* event)
{
//    qDebug() << "mouseMoveEvent " << event;

    float dx = event->x() - lastPos.x();
    float dy = event->y() - lastPos.y();

//    float sensitivity = 0.1f;
//    dx *= sensitivity;
//    dy *= sensitivity;

//    yaw += dx;
////    qDebug() << yaw;
///


//    pitch -= dy;
//    pitch = qMax(qMin(90.0f, pitch), -90.0f);

//    QVector3D front;
////    front.setX(sin(yaw));
////    front.setY(cos(pitch));
////    front.setZ(cos(yaw));
//    front.setX(cos(qDegreesToRadians(yaw)) * cos(qDegreesToRadians(pitch)));
//    front.setY(sin(qDegreesToRadians(pitch)));
//    front.setZ(sin(qDegreesToRadians(yaw)) * cos(qDegreesToRadians(pitch)));

//    front.normalize();

//    cameraFront = front;

    setCursorToCenter();
    camera.ProcessMouseMovement(dx, -dy);

    //    lastPos = event->pos();
}

void QOpenGLWidget_World::wheelEvent(QWheelEvent *event)
{
    float dy = event->delta() * 0.1f;
//    qDebug() << dy;
//    fov -= dy * 0.1f;
//    fov = qMax(qMin(170.0f, fov), 1.0f);

    camera.ProcessMouseScroll(dy);
    updateProjection();

}

void QOpenGLWidget_World::focusInEvent(QFocusEvent *event)
{
//    qDebug() << "focusInEvent";
    setCursorToCenter();
//    setCursor(Qt::BlankCursor);
}

void QOpenGLWidget_World::setCursorToCenter()
{
    lastPos = QPoint(width() / 2, height() / 2);
    QPoint glob = mapToGlobal(lastPos);
    QCursor::setPos(glob);
}

void QOpenGLWidget_World::cameraMove()
{
//    float cameraSpeed = 0.01 * deltaTime;
    //    float cameraSpeed = 0.1;
    if (frontDir == 1) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    else if (frontDir == -1) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }

    if (sideDir == 1) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    else if (sideDir == -1) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
//    cameraPos += frontDir * cameraFront * cameraSpeed;
//    cameraPos += sideDir * QVector3D::crossProduct(cameraFront, cameraUp).normalized() * cameraSpeed;
}

void QOpenGLWidget_World::updateProjection()
{
    m_projection.setToIdentity();
    m_projection.perspective(camera.Zoom, width() / float(height()), 0.01f, 100.0f);
}

//void QOpenGLWidget_World::paintEvent(QPaintEvent *e)
//{
////    paintGLprivate();
//    qDebug() << "paintEvent" << e;
////    paintGL();

//    QPainter painter(this);
////    painter.setBackground(Qt::gray);
//    painter.drawText(QPoint(0, 0), "fuck");
//    painter.setBackground(QBrush(Qt::gray));

//    painter.setPen(Qt::red);
//    painter.drawLine(rect().topLeft(), rect().bottomRight());
////    painter.end();
//}

//void QOpenGLWidget_World::makeObject()
//{
////    QVector<GLfloat> vertData;

////    vertData.append(vertices);
////    vertData.insert(vertData.end(), 9, vertices[0]);

//}
