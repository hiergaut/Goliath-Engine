#include "QOpenGLWidget_World.h"
#include <QTime>
#include <QtMath>

QOpenGLWidget_World::QOpenGLWidget_World(QWidget* parent)
    : QOpenGLWidget(parent)
    , m_vbo(QOpenGLBuffer::VertexBuffer)
    , m_ebo(QOpenGLBuffer::IndexBuffer)
{
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
    Q_ASSERT(! img.isNull());
//    m_texture = new QOpenGLTexture(img.scaled(200, 200));
//    m_texture = new QOpenGLTexture(img.scaled(32, 36).mirrored());
    m_texture = new QOpenGLTexture(img);
//    m_texture->setWrapMode(QOpenGLTexture::ClampToEdge);
    m_texture->setMinificationFilter(QOpenGLTexture::Nearest);
    m_texture->setMagnificationFilter(QOpenGLTexture::Nearest);

    QImage img2(":/texture/awesomeface.png");
    Q_ASSERT(! img.isNull());
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
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // top left
    };

    m_vbo.create();
    m_vbo.bind();
    m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vbo.allocate(vertices, sizeof(vertices));

    GLuint indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3 // second triangle
    };

    m_ebo.create();
    m_ebo.bind();
    m_ebo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_ebo.allocate(indices, sizeof(indices));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    m_vbo.release();
    m_vao.release();

    //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void QOpenGLWidget_World::resizeGL(int w, int h)
{
    //    m_projection.setToIdentity();
    //    m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);
}

void QOpenGLWidget_World::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_texture->bind();
    m_texture2->bind(1);
    m_program.setUniformValue("texture1", 0);
    m_program.setUniformValue("texture2", 1);

    QMatrix4x4 transform;
//    transform.setToIdentity();
    transform.translate(0.5, -0.5, 0.0);
    transform.rotate(time++, 0, 0, 1);
    transform.scale(sin(time * 0.01));

    m_program.setUniformValue("transform", transform);

    m_program.bind();
    m_vao.bind();


    //    float timeValue = QTime::currentTime().msec();
    //    float greenValue = sin(time += 0.1) / 2.0f + 0.5f;
    //    m_program.setUniformValue("ourColor", 0.0f, greenValue, 0.0f, 1.0f);

//    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //    m_program.release();
    //    m_vao.release();
    update();
}

//void QOpenGLWidget_World::makeObject()
//{
////    QVector<GLfloat> vertData;

////    vertData.append(vertices);
////    vertData.insert(vertData.end(), 9, vertices[0]);

//}
