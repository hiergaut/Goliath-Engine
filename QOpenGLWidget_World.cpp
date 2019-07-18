#include "QOpenGLWidget_World.h"
#include <QTime>
#include <QtMath>

#include <QKeyEvent>
#include <QPainter>

QOpenGLWidget_World::QOpenGLWidget_World(QWidget* parent)
    : QOpenGLWidget(parent)
//    , m_vbo(QOpenGLBuffer::VertexBuffer)
    , camera(QVector3D(0, 0, 3))
//    , m_ebo(QOpenGLBuffer::IndexBuffer)
{

//    setAutoFillBackground(false);
    setMouseTracking(true);
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
//    m_texture->setMinificationFilter(QOpenGLTexture::Nearest);
//    m_texture->setMagnificationFilter(QOpenGLTexture::Nearest);
    m_texture->setMinificationFilter(QOpenGLTexture::Linear);
    m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
//    m_texture->generateMipMaps();

    QImage img2(":/texture/awesomeface.png");
    Q_ASSERT(!img.isNull());
    //    m_texture2 = new QOpenGLTexture(img2.mirrored(false, true));
    m_texture2 = new QOpenGLTexture(img2);
    //    m_texture->generateMipMaps();

    // ---------------------------------------------------------------------
    QOpenGLShader vShader(QOpenGLShader::Vertex, this);
    QOpenGLShader fShader(QOpenGLShader::Fragment, this);

    vShader.compileSourceFile(":/shader/first.vsh");
    fShader.compileSourceFile(":/shader/first.fsh");
    m_program.addShader(&vShader);
    m_program.addShader(&fShader);
    m_program.link();
//    m_program.release();

//    QOpenGLShader vShader2(QOpenGLShader::Vertex, this);
//    QOpenGLShader fShader2(QOpenGLShader::Fragment, this);
    vShader.compileSourceFile(":/shader/light.vsh");
    fShader.compileSourceFile(":/shader/light.fsh");
    m_programLight.addShader(&vShader);
    m_programLight.addShader(&fShader);
    m_programLight.link();
//    m_programLight.release();
    // ---------------------------------------------------------------------
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f
    };



    m_vao.create();
    m_vao.bind();

    QOpenGLBuffer vbo(QOpenGLBuffer::VertexBuffer);
    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo.allocate(vertices, sizeof(vertices));

    //    m_ebo.bind();
    //    m_ebo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    //    m_ebo.allocate(indices, sizeof(indices));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof (GLfloat), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    //    glEnableVertexAttribArray(1);
    m_vao.release();
//    m_vao.bind();

//    m_vaoLight.create();
//    m_vaoLight.bind();

//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
//    glEnableVertexAttribArray(0);

//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);


//    m_vaoLight.release();
////    m_vao.release();
//    vbo.release();

    // ---------------------------------------------------------------------
//        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_LIGHT0);
//    glEnable(GL_LIGHTING);
//    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
//    glEnable(GL_COLOR_MATERIAL);
//    glEnable(GL_MULTISAMPLE);
}

void QOpenGLWidget_World::resizeGL(int w, int h)
{
    updateProjection();
}

void QOpenGLWidget_World::paintGL()
{
    uint64_t currentFrame = QDateTime::currentMSecsSinceEpoch();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    fps += 1000.0 / deltaTime;
    if (cpt % 60 == 0) {
        qDebug() << "fps : " << fps / 60.0;
        fps = 0.0;
    }

    cameraMove();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // -------------------------------------------------------------------------------
    m_vao.bind();

    m_program.bind();
    m_texture->bind();
    m_texture2->bind(1);
    m_program.setUniformValue("texture1", 0);
    m_program.setUniformValue("texture2", 1);

    m_program.setUniformValue("view", camera.GetViewMatrix());
    m_program.setUniformValue("projection", m_projection);

//    lightPos[0].setX(1.0 + sin(currentFrame * 0.01) * 2.0f);
//    lightPos[0].setY(sin(currentFrame * 0.01 / 2.0) * 1.0f);
    m_program.setUniformValue("lightPos", lightPos[0]);
    m_program.setUniformValue("lightColor", 1.0, 1.0, 1.0);
    m_program.setUniformValue("viewPos", camera.Position);

//    m_program.setUniformValue("lightColor")

//    m_programLight.bind();
//    m_vaoLight.bind();
    //    m_program.setUniformValue("ourColor", 0.0f, greenValue, 0.0f, 1.0f);
    for (int i = 0; i < 10; ++i) {
        QMatrix4x4 model;
        model.translate(cubePositions[i]);
        model.rotate(static_cast<int>(currentFrame / 10) % 360, cubePositions[i]);
//        model.scale(sin(currentFrame * 0.001), 1, 1);
        //        model.rotate(0.1 * time++, 1, 0.3, 05);
        m_program.setUniformValue("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }


    m_programLight.bind();
    m_programLight.setUniformValue("view", camera.GetViewMatrix());
    m_programLight.setUniformValue("projection", m_projection);
//    m_vaoLight.bind();
    for (int i =0; i <1; ++i) {
        QMatrix4x4 model;
        model.translate(lightPos[i]);
        model.scale(0.2);
        m_programLight.setUniformValue("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }


    //    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //        m_program.release();
    //        m_vao.release();

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
    float dx = event->x() - lastPos.x();
    float dy = event->y() - lastPos.y();

    setCursorToCenter();
    camera.ProcessMouseMovement(dx, -dy);
}

void QOpenGLWidget_World::wheelEvent(QWheelEvent *event)
{
    float dy = event->delta() * 0.1f;

    camera.ProcessMouseScroll(dy);
    updateProjection();
}

void QOpenGLWidget_World::focusInEvent(QFocusEvent *event)
{
    setCursorToCenter();
    setCursor(Qt::BlankCursor);
}

void QOpenGLWidget_World::setCursorToCenter()
{
    lastPos = QPoint(width() / 2, height() / 2);
    QPoint glob = mapToGlobal(lastPos);
    QCursor::setPos(glob);
}

void QOpenGLWidget_World::cameraMove()
{
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
}

void QOpenGLWidget_World::updateProjection()
{
    m_projection.setToIdentity();
    m_projection.perspective(camera.Zoom, width() / float(height()), 0.01f, 100.0f);
}
