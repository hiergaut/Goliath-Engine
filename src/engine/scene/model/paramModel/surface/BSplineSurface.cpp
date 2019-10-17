#include "BSplineSurface.h"

//BSplineSurface::BSplineSurface()
//{

//}
#include <session/Session.h>

#include <QDebug>
#include <opengl/geometry/DotGeometry.h>

const uint g_buffMaxVertices = 100000 * sizeof(glm::vec3);
//const uint BSplineSurface::g_maxLenKnots = 13:

BSplineSurface::BSplineSurface(BSplineSurface::Type type)
    : Model(glm::mat4(1.0f), Model::PARAM_SURFACE)
//    : ParamModel(Model::Type::BSPLINE_CURVE)
{

    //    m_controlPoints.emplace_back(-200.0f, 0.0f, 0.0f);
    //    m_controlPoints.emplace_back(-150.0f, 0.0f, 0.0f);
    //    m_controlPoints.emplace_back(-100.0f, 100.0f, 0.0f);
    //    m_controlPoints.emplace_back(100.0f, 100.0f, 0.0f);
    //    m_controlPoints.emplace_back(150.0f, 0.0f, 0.0f);
    //    m_controlPoints.emplace_back(200.0f, 0.0f, 0.0f);
    //    for (uint i = 0; i < m_nbCtrlPoints[0]; ++i) {
    //        for (uint j = 0; j < m_nbCtrlPoints[1]; ++j) {
    //            m_controlPoints[i][j] = glm::vec3(i * 100.0f, j * 100.0f, 0.0f);
    //            m_selected[i][j] = false;
    //        }
    //    }
    uint middleI;
    uint middleJ;
    float radius;
    float radiusIn;
    float pick;
    float pickDown;

    switch (type) {

    case Type::TOMB:
        m_nbCtrlPoints[0] = 5;
        m_nbCtrlPoints[1] = 6;
        m_k[0] = 2;
        m_k[1] = 2;
        middleI = m_nbCtrlPoints[0] / 2;
        middleJ = m_nbCtrlPoints[1] / 2;
        for (uint i = 0; i < m_nbCtrlPoints[0]; ++i) {
            for (uint j = 0; j < m_nbCtrlPoints[1]; ++j) {
                if (i == middleI && j == middleJ) {
                    m_controlPoints[i][j] = glm::vec3(i * 100.0f, j * 100.0f, 300.0f);
                } else if (i == middleI || j == middleJ) {
                    //            if (i == j) {
                    m_controlPoints[i][j] = glm::vec3(i * 100.0f, j * 100.0f, 100.0f);
                } else {
                    m_controlPoints[i][j] = glm::vec3(i * 100.0f, j * 100.0f, 0.0f);
                }
                //                m_selected[i][j] = false;
            }
        }
        //        setUniform(0);
        //        setUniform(1);

        break;

    case Type::PLANE:
        m_nbCtrlPoints[0] = 10;
        m_nbCtrlPoints[1] = 10;
        m_dotPerEdge[0] = 5;
        m_dotPerEdge[1] = 5;
        for (uint i = 0; i < m_nbCtrlPoints[0]; ++i) {
            for (uint j = 0; j < m_nbCtrlPoints[1]; ++j) {
                m_controlPoints[i][j] = glm::vec3(100.0f * i, 100.0f * j, 0.0f);
            }
        }
        break;

    case Type::SPHERE:
        m_nbCtrlPoints[0] = 4;
        m_nbCtrlPoints[1] = 4;
        radius = 100.0f;
        pick = 2.0f;
        pickDown = 0.5f;
        //        m_controlPoints[0][4] = glm::vec3(0, -pickDown * radius, pickDown * radius);
        //        m_controlPoints[1][4] = glm::vec3(0, pickDown * radius, pickDown * radius);
        //        m_controlPoints[2][4] = glm::vec3(0, pickDown * radius, -pickDown * radius);
        //        m_controlPoints[3][4] = glm::vec3(0, -pickDown * radius, -pickDown * radius);
        //        m_controlPoints[4][4] = glm::vec3(0, -pickDown * radius, pickDown * radius);

        m_controlPoints[0][3] = glm::vec3(-radius, -radius, radius);
        m_controlPoints[1][3] = glm::vec3(-radius, radius, radius);
        m_controlPoints[2][3] = glm::vec3(-radius, radius, -radius);
        m_controlPoints[3][3] = glm::vec3(-radius, -radius, -radius);
        //        m_controlPoints[4][3] = glm::vec3(-radius, -radius, radius);

        m_controlPoints[0][2] = glm::vec3(0, -pick * radius, pick * radius);
        m_controlPoints[1][2] = glm::vec3(0, pick * radius, pick * radius);
        m_controlPoints[2][2] = glm::vec3(0, pick * radius, -pick * radius);
        m_controlPoints[3][2] = glm::vec3(0, -pick * radius, -pick * radius);
        //        m_controlPoints[4][2] = glm::vec3(0, -pick * radius, pick * radius);

        m_controlPoints[0][1] = glm::vec3(radius, -radius, radius);
        m_controlPoints[1][1] = glm::vec3(radius, radius, radius);
        m_controlPoints[2][1] = glm::vec3(radius, radius, -radius);
        m_controlPoints[3][1] = glm::vec3(radius, -radius, -radius);
        //        m_controlPoints[4][1] = glm::vec3(radius, -radius, radius);

        m_controlPoints[0][0] = glm::vec3(0, -pickDown * radius, pickDown * radius);
        m_controlPoints[1][0] = glm::vec3(0, pickDown * radius, pickDown * radius);
        m_controlPoints[2][0] = glm::vec3(0, pickDown * radius, -pickDown * radius);
        m_controlPoints[3][0] = glm::vec3(0, -pickDown * radius, -pickDown * radius);
        //        m_controlPoints[4][0] = glm::vec3(0, -pickDown * radius, pickDown * radius);

        //        setUniform(0);
        //        setUniform(1);

        //        m_k[0] = 2;
        //        m_k[1] = 2;
        //        m_periodic[0] = true;
        //        m_periodic[1] = true;

        break;

    case Type::THOR:
        m_nbCtrlPoints[0] = 4;
        m_nbCtrlPoints[1] = 4;
        radius = 200.0f;
        radiusIn = 100.0f;
        //        m_controlPoints[0][4] = glm::vec3(0, -pickDown * radius, pickDown * radius);
        //        m_controlPoints[1][4] = glm::vec3(0, pickDown * radius, pickDown * radius);
        //        m_controlPoints[2][4] = glm::vec3(0, pickDown * radius, -pickDown * radius);
        //        m_controlPoints[3][4] = glm::vec3(0, -pickDown * radius, -pickDown * radius);
        //        m_controlPoints[4][4] = glm::vec3(0, -pickDown * radius, pickDown * radius);

        //        m_controlPoints[4][1] = glm::vec3(radius, -radius, radius);
        m_controlPoints[0][3] = glm::vec3(-radiusIn, -radius + -radiusIn, 0);
        m_controlPoints[1][3] = glm::vec3(0, -radius + -2 * radiusIn, 0);
        m_controlPoints[2][3] = glm::vec3(radiusIn, -radius + -radiusIn, 0);
        m_controlPoints[3][3] = glm::vec3(0, -radius, 0);

        m_controlPoints[0][2] = glm::vec3(-radiusIn, 0, -radius + -radiusIn);
        m_controlPoints[1][2] = glm::vec3(0, 0, -radius + -2 * radiusIn);
        m_controlPoints[2][2] = glm::vec3(radiusIn, 0, -radius - radiusIn);
        m_controlPoints[3][2] = glm::vec3(0, 0, -radius);

        m_controlPoints[0][1] = glm::vec3(-radiusIn, radius + radiusIn, 0);
        m_controlPoints[1][1] = glm::vec3(0, radius + 2 * radiusIn, 0);
        m_controlPoints[2][1] = glm::vec3(radiusIn, radius + radiusIn, 0);
        m_controlPoints[3][1] = glm::vec3(0, radius, 0);

        m_controlPoints[0][0] = glm::vec3(-radiusIn, 0, radius + radiusIn);
        m_controlPoints[1][0] = glm::vec3(0, 0, radius + 2 * radiusIn);
        m_controlPoints[2][0] = glm::vec3(radiusIn, 0, radius + radiusIn);
        m_controlPoints[3][0] = glm::vec3(0, 0, radius);
        //        m_controlPoints[4][0] = glm::vec3(0, -pickDown * radius, pickDown * radius);

        //        setUniform(0);
        //        setUniform(1);

        //        m_k[0] = 2;
        //        m_k[1] = 2;
        //        m_periodic[0] = true;
        //        m_periodic[1] = true;

        break;

    case Type::POT:
        m_nbCtrlPoints[0] = 7;
        m_nbCtrlPoints[1] = 6;
        radius = 50;
//        int h[7] = { 500, 450, 350, 350, 200, 50, 0 };
//        int r[7] = { 100, 50, 50, 300, 300, 50, 200 };
        int h[7] = { 0, 50, 200, 400, 400, 450, 500 };
        int r[7] = { 150, 50, 200, 200, 50, 50, 100 };

        for (uint i = 0; i < 7; ++i) {
            m_controlPoints[i][0] = glm::vec3(-r[i], -r[i], h[i]);
            m_controlPoints[i][1] = glm::vec3(-r[i], 0, h[i]);
            m_controlPoints[i][2] = glm::vec3(-r[i], r[i], h[i]);
            m_controlPoints[i][3] = glm::vec3(r[i], r[i], h[i]);
            m_controlPoints[i][4] = glm::vec3(r[i], 0, h[i]);
            m_controlPoints[i][5] = glm::vec3(r[i], -r[i], h[i]);
        }

        break;
    }

    setUniform(0);
    setUniform(1);

    for (uint i = 0; i < g_maxSize; ++i) {
        for (uint j = 0; j < g_maxSize; ++j) {
            m_selected[i][j] = false;
        }
    }

    //    m_selected.resize(m_controlPoints.size());
    //    for (uint i = 0; i < m_selected.size(); ++i) {
    //        m_selected[i] = false;
    //    }
    //    for (uint i = 0; i < g_maxSize; ++i) {
    //        for (uint j = 0; j < g_maxSize; ++j) {
    //            m_indices.emplace_back(i * g_maxSize + j, i * g_maxSize + j + 1);
    //        }
    //    }

    //    m_indices.emplace_back(0, 1);
    //    m_indices.emplace_back(1, 2);
    //    m_indices.emplace_back(2, 3);

    setupGL();

    for (uint i = 0; i < 2; ++i) {
        //        m_k[i] = 2;
        //        m_dotPerEdge[i] = 5;
        //        m_knots[i].resize(g_maxLenKnots);
        for (uint j = 0; j < g_maxLenKnots; ++j) {
            //        knots[i] = i;
            m_knots[i][j] = j;
        }
    }

    updateSurface();
}

BSplineSurface::BSplineSurface(std::ifstream& file)
    : Model(file)
//    : ParamModel(file)
//    , m_type(Model::BSplineSurface)
//    , m_type = Model::PARAM_CURVE
{
    m_type = Model::PARAM_SURFACE;

    Session::load(m_nbCtrlPoints[0], file);
    Session::load(m_nbCtrlPoints[1], file);
    //    Session::load(&m_controlPoints[0][0], m_nbCtrlPoints[0] * m_nbCtrlPoints[1], file);
    Session::load(&m_controlPoints[0][0], g_maxSize * g_maxSize, file);

    Session::load(m_k, 2, file);
    Session::load(&m_knots[0][0], 2 * g_maxLenKnots, file);

    Session::load(&m_periodic[0], 2, file);

    //    Session::load(m_indices, file);
    //    qDebug() << "BSplineSurface";
    //    m_transform = glm::mat4(1.0f);

    //    m_controlPoints.clear();
    //    m_controlPoints.emplace_back(-200.0f, 0.0f, 0.0f);
    //    m_controlPoints.emplace_back(-150.0f, 0.0f, 0.0f);
    //    m_controlPoints.emplace_back(-100.0f, 100.0f, 0.0f);
    //    m_controlPoints.emplace_back(100.0f, 100.0f, 0.0f);
    //    m_controlPoints.emplace_back(150.0f, 0.0f, 0.0f);
    //    m_controlPoints.emplace_back(200.0f, 0.0f, 0.0f);

    for (uint i = 0; i < g_maxSize; ++i) {
        for (uint j = 0; j < g_maxSize; ++j) {
            m_selected[i][j] = false;
        }
    }
    //    m_selected.resize(m_controlPoints.size());
    //    for (uint i = 0; i < m_selected.size(); ++i) {
    //        m_selected[i] = false;
    //    }
    //    for (uint i = 0; i < m_controlPoints.size() - 1; ++i) {
    //        m_indices.emplace_back(i, i + 1);
    //    }
    //    for (uint i = 0; i < g_maxSize; ++i) {
    //        for (uint j = 0; j < g_maxSize; ++j) {
    //            m_indices.emplace_back(i * g_maxSize + j, i * g_maxSize + j + 1);
    //        }
    //    }

    //    m_indices.clear();
    //    m_indices.emplace_back(0, 1);
    //    m_indices.emplace_back(1, 2);
    //    m_indices.emplace_back(2, 3);

    //    Q_ASSERT(m_controlPoints.size() == );
    //    Q_ASSERT(m_indices.size() == 3);

    //    uint k = 3; // C0
    setupGL();

    //    m_k = 3;
    //    m_dotPerEdge = 5;
    //    m_knots.resize(g_maxLenKnots);
    //    for (uint i = 0; i < g_maxLenKnots; ++i) {
    //        //        knots[i] = i;
    //        m_knots[i] = i;
    //    }
    //    for (uint i = 0; i < 2; ++i) {
    //        //        m_k[i] = 2;
    //        //        m_dotPerEdge[i] = 5;
    //        //        m_knots[i].resize(g_maxLenKnots);
    //        for (uint j = 0; j < g_maxLenKnots; ++j) {
    //            //        knots[i] = i;
    //            m_knots[i][j] = j;
    //        }
    //    }

    updateSurface();
}

BSplineSurface::~BSplineSurface()
{
    std::cout << "\033[35m";
    std::cout << "[BSplinCurve] '" << name() << "' deleted " << this << std::endl;
    std::cout << "\033[0m";
}

void BSplineSurface::setupGL()
{
    //    qDebug() << "setupGL";
    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    Q_ASSERT(m_fun != nullptr);

    m_fun->glGenVertexArrays(1, &m_vao);
    m_fun->glGenBuffers(1, &m_vbo);
    m_fun->glGenBuffers(1, &m_ebo);
    //    m_fun->glGenBuffers(1, &m_vbo2);

    m_fun->glBindVertexArray(m_vao);
    m_fun->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    //    m_fun->glBufferData(GL_ARRAY_BUFFER, m_controlPoints.size() * sizeof(glm::vec3), &m_controlPoints[0], GL_STATIC_DRAW);
    m_fun->glBufferData(GL_ARRAY_BUFFER, g_buffMaxVertices, &m_controlPoints[0][0], GL_DYNAMIC_DRAW);
    m_fun->glEnableVertexAttribArray(0);
    m_fun->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    m_fun->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    //    m_fun->glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(glm::uvec2), &m_indices[0], GL_STATIC_DRAW);
    m_fun->glBufferData(GL_ELEMENT_ARRAY_BUFFER, g_buffMaxVertices, &m_indices[0], GL_DYNAMIC_DRAW);

    m_fun->glBindVertexArray(0);

    m_fun->glGenVertexArrays(1, &m_vao2);
    m_fun->glGenBuffers(1, &m_vbo2);
    m_fun->glGenBuffers(1, &m_nbo2);
    m_fun->glGenBuffers(1, &m_ebo2);
    //    m_fun->glGenBuffers(1, &m_vbo2);

    m_fun->glBindVertexArray(m_vao2);
    m_fun->glBindBuffer(GL_ARRAY_BUFFER, m_vbo2);
    //    m_fun->glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), &m_vertices[0], GL_STATIC_DRAW);
    m_fun->glBufferData(GL_ARRAY_BUFFER, g_buffMaxVertices, &m_vertices[0], GL_DYNAMIC_DRAW);
    m_fun->glEnableVertexAttribArray(0);
    m_fun->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    m_fun->glBindBuffer(GL_ARRAY_BUFFER, m_nbo2);
    //    m_fun->glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), &m_vertices[0], GL_STATIC_DRAW);
    m_fun->glBufferData(GL_ARRAY_BUFFER, g_buffMaxVertices, &m_normals[0], GL_DYNAMIC_DRAW);
    m_fun->glEnableVertexAttribArray(1);
    m_fun->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    m_fun->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo2);
    //    m_fun->glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indiceTriangles.size() * sizeof(glm::uvec2), &m_indiceTriangles[0], GL_STATIC_DRAW);
    m_fun->glBufferData(GL_ELEMENT_ARRAY_BUFFER, g_buffMaxVertices, &m_indiceTriangles[0], GL_DYNAMIC_DRAW);

    m_fun->glBindVertexArray(0);
}

void BSplineSurface::setUniform(uint uv)
{
    //    for (uint i = 0; i < 2; ++i) {
    //        m_k[i] = 2;
    //        m_dotPerEdge[i] = 5;
    //        m_knots[i].resize(g_maxLenKnots);
    for (uint j = 0; j < g_maxLenKnots; ++j) {
        //        knots[i] = i;
        m_knots[uv][j] = j;
    }
    //    }
}

void BSplineSurface::save(std::ofstream& file) const
{
    Model::save(file);

    Session::save(m_nbCtrlPoints[0], file);
    Session::save(m_nbCtrlPoints[1], file);
    //    Session::save(&m_controlPoints[0][0], m_nbCtrlPoints[0] * m_nbCtrlPoints[1], file);
    Session::save(&m_controlPoints[0][0], g_maxSize * g_maxSize, file);

    Session::save(m_k, 2, file);
    Session::save(&m_knots[0][0], 2 * g_maxLenKnots, file);

    Session::save(&m_periodic[0], 2, file);

    //    Session::save(m_controlPoints, file);

    //    Session::save(m_indices, file);
}

void BSplineSurface::prepareHierarchy(ulong frameTime) const
{
}

void BSplineSurface::draw(const Shader& shader, bool dotCloud, const glm::mat4& localTransform, const glm::mat4& worldTransform) const
{
    Q_ASSERT(m_fun != nullptr);
    m_fun->glLineWidth(1.0f);

    if (dotCloud) {
        //        for (uint i = 0; i < m_selected.size(); ++i) {
        //            if (m_selected[i]) {
        //                //                qDebug() << "draw " << i;
        //                DotGeometry::draw(glm::translate(glm::mat4(1.0f), m_controlPoints[i]) * worldTransform * m_transform, shader, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), 8);
        //            }
        //        }
        m_fun->glPointSize(6.0f);
        shader.setBool("userColor", true);

        shader.setMat4("model", worldTransform * m_transform * localTransform);
        m_fun->glBindVertexArray(m_vao);
        shader.setVec4("color", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
        m_fun->glDrawArrays(GL_POINTS, 0, m_nbCtrlPoints[0] * m_nbCtrlPoints[1]);

        m_fun->glPointSize(4.0f);
        shader.setVec4("color", glm::vec4(1.0f, 0.5f, 0.0f, 1.0f));
        m_fun->glBindVertexArray(m_vao2);
        m_fun->glDrawArrays(GL_POINTS, 0, m_vertices.size());

        //        shader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        //        shader.setMat4("model", worldTransform * m_transform * localTransform);

        //        m_fun->glLineWidth(0.5f);
        //        shader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        //        m_fun->glBindVertexArray(m_vao);
        //        for (uint i = 0; i < m_nbCtrlPoints[0]; ++i) {
        //            m_fun->glDrawElements(GL_LINES, m_nbCtrlPoints[1] * 2, GL_UNSIGNED_INT, (void*)(g_maxSize * i * 2 * sizeof(unsigned int)));
        //        }
        m_fun->glBindVertexArray(m_vao);
        m_fun->glLineWidth(0.5f);
        shader.setBool("userColor", true);
        shader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 0.5f));
        //                        for (uint i =0; i <m_nbCtrlPoints[0]; ++i) {
        m_fun->glDrawElements(GL_LINES, m_indices.size() * 2, GL_UNSIGNED_INT, (void*)0);

    } else {

        //    m_fun->glDrawArrays(GL_LINES, 0, 4);
        //    m_fun->glEnable(GL_POINT_SMOOTH);
        //    m_fun->glDrawElements(GL_LINES, m_indices.size() * 2, GL_UNSIGNED_INT, nullptr);
        //    m_fun->glLineWidth(1.0f);
        //    m_fun->glBindVertexArray(0);
        //    m_fun->glLineWidth(2.0f);

        shader.setMat4("model", worldTransform * m_transform * localTransform);
        //        shader.setBool("userColor", true);
        //        shader.setVec4("color", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
        m_fun->glBindVertexArray(m_vao2);
        //    m_fun->glDrawArrays(GL_LINES, 0, 4);
        //    m_fun->glEnable(GL_POINT_SMOOTH);
        //    m_fun->glPointSize(5.0f);
        //        m_fun->glDrawElements(GL_LINES, m_indiceTriangles.size() * 2, GL_UNSIGNED_INT, nullptr);

        m_fun->glDrawElements(GL_TRIANGLES, m_indiceTriangles.size() * 3, GL_UNSIGNED_INT, nullptr);

        //    m_fun->glLineWidth(2.0f);
        //        m_fun->glDrawArrays(GL_POINTS, 0, m_vertices.size());
        //    m_fun->glLineWidth(1.0f);

        //        m_fun->glLineWidth(0.5f);
        //        shader.setBool("userColor", true);
        //        shader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        //        m_fun->glBindVertexArray(m_vao);
        //        //                        for (uint i =0; i <m_nbCtrlPoints[0]; ++i) {
        //        m_fun->glDrawElements(GL_LINES, m_indices.size() * 2, GL_UNSIGNED_INT, (void*)0);
        //                        }
    }

    m_fun->glBindVertexArray(0);
    shader.setBool("userColor", false);
    m_fun->glPointSize(1.0f);
    m_fun->glLineWidth(1.0f);
}

void BSplineSurface::draw(const Shader& shader, const glm::mat4& localTransform, const glm::mat4& worldTransform) const
{
    shader.setMat4("model", worldTransform * m_transform * localTransform);
    //        shader.setBool("userColor", true);
    //        shader.setVec4("color", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    m_fun->glBindVertexArray(m_vao2);
    //    m_fun->glDrawArrays(GL_LINES, 0, 4);
    //    m_fun->glEnable(GL_POINT_SMOOTH);
    //    m_fun->glPointSize(5.0f);
    //        m_fun->glDrawElements(GL_LINES, m_indiceTriangles.size() * 2, GL_UNSIGNED_INT, nullptr);
    m_fun->glDrawElements(GL_TRIANGLES, m_indiceTriangles.size() * 3, GL_UNSIGNED_INT, nullptr);
    //    m_fun->glLineWidth(2.0f);
    //    Q_ASSERT(m_fun != nullptr);
    //    shader.setMat4("model", worldTransform * m_transform * localTransform);
    //    shader.setBool("userColor", true);
    //    shader.setVec4("color", glm::vec4(1.0f, 0.5f, 0.5f, 1.0f));

    //    m_fun->glBindVertexArray(m_vao);
    ////    m_fun->glDrawArrays(GL_LINES, 0, 4);
    //    m_fun->glPointSize(10.0f);
    //    m_fun->glDrawElements(GL_LINES, m_indices.size() * 2, GL_UNSIGNED_INT, nullptr);
    //    m_fun->glLineWidth(2.0f);
    //    m_fun->glDrawArrays(GL_POINTS, 0, m_controlPoints.size());
    //    m_fun->glLineWidth(1.0f);
    //    m_fun->glBindVertexArray(0);

    //    shader.setBool("userColor", false);
}

void BSplineSurface::drawSelected(const Shader& shader, const glm::mat4& localTransform, const glm::mat4& worldTransform) const
{
    //    for (uint i = 0; i < m_selected.size(); ++i) {
    for (uint i = 0; i < m_nbCtrlPoints[0]; ++i) {
        for (uint j = 0; j < m_nbCtrlPoints[1]; ++j) {
            if (m_selected[i][j]) {
                //                qDebug() << "draw " << i;
                DotGeometry::draw(glm::translate(glm::mat4(1.0f), m_controlPoints[i][j]) * worldTransform * m_transform, shader, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), 10);
                //                DotGeometry::draw(glm::translate(glm::mat4(1.0f), m_controlPoints[i][j]) * worldTransform * m_transform, shader, glm::vec4(1.0f, 0.5f, 0.0f, 1.0f), 10);
            }
        }
    }
}

void BSplineSurface::updateBoundingBox() const
{
    m_box.clear();
    //    for (const glm::vec3 vertex : m_controlPoints) {
    for (uint i = 0; i < m_nbCtrlPoints[0]; ++i) {
        for (uint j = 0; j < m_nbCtrlPoints[1]; ++j) {
            const glm::vec3 vertex = m_controlPoints[i][j];
            m_box << m_transform * glm::vec4(vertex, 1.0f);
        }
    }
}

void BSplineSurface::drawBoundingBox(const Shader& shader) const
{
    shader.setBool("userColor", true);
    //    m_rootNode->drawBoundingBox(modelMatrix, shader);
    shader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m_box.draw(shader);

    shader.setBool("userColor", false);
}

void BSplineSurface::updateSelectedVertexPosition(const glm::mat4& localTransform, const glm::mat4& worldTransform)
{

    //    for (uint i = 0; i < m_selected.size(); ++i) {
    for (uint i = 0; i < m_nbCtrlPoints[0]; ++i) {
        for (uint j = 0; j < m_nbCtrlPoints[1]; ++j) {
            if (m_selected[i][j]) {
                //                qDebug() << "draw " << i;
                //            DotGeometry::draw(glm::translate(glm::mat4(1.0f), m_controlPoints[i]) * worldTransform * m_transform, shader, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), 10);
                m_controlPoints[i][j] = worldTransform * glm::vec4(m_controlPoints[i][j], 1.0f) * localTransform;
            }
        }
    }
    updateSurface();
}

void BSplineSurface::vertexSelectRay(const Ray& ray, bool additional)
{

    //    for (uint i = 0; i < m_controlPoints.size(); ++i) {
    for (uint i = 0; i < m_nbCtrlPoints[0]; ++i) {
        for (uint j = 0; j < m_nbCtrlPoints[1]; ++j) {
            if (!additional) {
                m_selected[i][j] = false;
            }

            const glm::vec3& vertex = m_transform * glm::vec4(m_controlPoints[i][j], 1.0f);
            //                    qDebug() << "vertex " << i;

            if (ray.intersect(vertex)) {
                //                    qDebug() << "intersect " << i;
                //                    m_selectVertices.emplace_back(i);
                if (additional) {
                    m_selected[i][j] = !m_selected[i][j];
                } else {
                    m_selected[i][j] = true;
                }
            }
        }
    }
}

void BSplineSurface::clamp(uint uv, bool start)
{
    qDebug() << "clamp";

    if (start) {
        float kValue = m_knots[uv][m_k[uv] - 1];

        for (uint i = 0; i < m_k[uv] - 1; ++i) {
            m_knots[uv][i] = kValue;
        }
        //    updateCurve();
        updateSurface();
    } else {

        float endValue = m_knots[uv][m_nbCtrlPoints[uv]];
        for (uint i = m_nbCtrlPoints[uv] + 1; i < g_maxLenKnots; ++i) {
            m_knots[uv][i] = endValue;
        }
        //        updateCurve();
        updateSurface();
    }
}

void BSplineSurface::uSetUniform()
{
    setUniform(0);
}

void BSplineSurface::vSetUniform()
{
    setUniform(1);
}

void BSplineSurface::uClampStart()
{
    clamp(0, true);
}

void BSplineSurface::uClampEnd()
{
    clamp(0, false);
}

void BSplineSurface::vClampStart()
{
    clamp(1, true);
}

void BSplineSurface::vClampEnd()
{
    clamp(1, false);
}

std::string BSplineSurface::name() const
{
    return "BSplineSurface";
}

void BSplineSurface::setUk(uint k)
{
    m_k[0] = k;
    //    m_k[1] = k;

    updateSurface();
}
void BSplineSurface::setVk(uint k)
{
    m_k[1] = k;

    updateSurface();
}

void BSplineSurface::setUDotPerEdge(uint dotPerEdge)
{
    m_dotPerEdge[0] = dotPerEdge;
    //    m_dotPerEdge[1] = dotPerEdge;

    updateSurface();
}
void BSplineSurface::setVDotPerEdge(uint dotPerEdge)
{
    m_dotPerEdge[1] = dotPerEdge;

    updateSurface();
}

glm::vec3 BSplineSurface::deBoor(float u, uint m, const uint k, const float knots[], const std::vector<glm::vec3>& controlPoints)
{
    int dec = 0;
    int i = k;
    //        qDebug() << "loop";
    while (knots[i] < u) {
        ++i;
        ++dec;
        Q_ASSERT(i < m);
    }
    //        qDebug() << "end loop";
    //        dec -= k - 1;
    //        dec =

    glm::vec3 pts[k];
    for (uint i = 0; i < k; ++i) {
        Q_ASSERT(i + dec < controlPoints.size());
        //            pts[i] = m_controlPoints[i + dec];
        pts[i] = controlPoints[i + dec];
    }

    //        for (uint i = k - 1; i > 0; --i) {
    //            for (uint j = 0; j < i; ++j) {
    //                float a = (knots[dec + k + j + 1] - u) /
    //                        (knots[dec + k +j + 1] - knots[dec + dec + k - i]);

    //                pts[j] = a * pts[j] + (1 - a) * pts[j + 1];
    //            }
    ////            ++dec;
    //        }
    uint l = k;
    uint k2 = k;
    for (uint j = 0; j < l - 1; ++j) {
        for (uint i = 0; i < k2 - 1; ++i) {
            float a = (knots[dec + k2 + i] - u) / (knots[dec + k2 + i] - knots[dec + 1 + i]);
            pts[i] = a * pts[i] + (1 - a) * pts[i + 1];
        }
        --k2;
        ++dec;
    }

    return pts[0];
}

std::vector<glm::vec3> BSplineSurface::calcCurve(const std::vector<glm::vec3>& ptsCtrl, const uint k, const uint dotPerEdge, const float knots[])
{

    std::vector<glm::vec3> curve;

    //    uint n = m_nbCtrlPoints[0] -1;
    uint n = ptsCtrl.size() - 1;
    //    std::cout << "n: " << n << std::endl;
    uint m = k + n + 1;

    //    uint nbPtCtl = ((n + 1) * dotPerEdge);
    //    uint nbPtCtl = n + 1;
    uint nbPtCtl = n + 1 - (k - 1);
    //    std::vector<glm::vec3> curve(nbPtCtl);
    //    const float start = knots[k - 1];
    //    const float end = knots[n + 1];
    //    const float period = end - start;

    for (uint iPtCtl = 0; iPtCtl < nbPtCtl + 1; ++iPtCtl) {
        for (uint iDot = 0; iDot < dotPerEdge; ++iDot) {
            //        float u = (float)iPtCtl / (nbPtCtl - 1) * (n - m_k + 2) + (m_k - 1);
            const float start = knots[k - 1 + iPtCtl];
            const float end = knots[k + iPtCtl];
            const float period = end - start;

            //            float u = (float)iPtCtl / (nbPtCtl - 1) * period + start;
            float u = (iDot * period) / dotPerEdge + start;

            //        qDebug() << "u: " << u;
            //        std::cout << u << std::endl;
            if (iPtCtl == nbPtCtl) {
                u = knots[n + 1];
            }
            //            if (iPtCtl == 0 && iDot == 0) {
            //                Q_ASSERT(qAbs(knots[k - 1] - u) < 1e-5);
            //            } else if (iPtCtl == nbPtCtl && iDot == 0) {
            //                Q_ASSERT(qAbs(knots[n + 1] - u) < 1e-5);
            //            }
            Q_ASSERT(knots[k - 1] <= u && u <= knots[n + 1]);

            //        m_vertices.push_back(worldTransform * glm::vec4(pts[0], 1.0f) * localTransform);
            //        m_vertices.push_back(pts[0]);
            //        m_vertices.push_back(deBoor(u, m, m_k[0], m_knots[0], ))
            //            curve.emplace_back(deBoor(u, m, k, knots, ptsCtrl));
            curve.emplace_back(BSplineSurface::deBoor(u, m, k, knots, ptsCtrl));

            if (iPtCtl == nbPtCtl) {
                break;
            }
        }
        //        curve[iPtCtl] =
    }
    //    Q_ASSERT(nbPtCtl == curve.size());
    Q_ASSERT(nbPtCtl * dotPerEdge + 1 == curve.size());
    Q_ASSERT(nbPtCtl > 0);

    return curve;
    //    return std::move(curve);
}

void BSplineSurface::updateSurface(const glm::mat4& localTransform, const glm::mat4& worldTransform)
{
    //    std::vector<
    //    std::vector<glm::vec3> controlPoints(m_controlPoints);
    uint periodicLen[2] = { 0, 0 };
    for (uint i = 0; i < 2; ++i) {
        if (m_periodic[i]) {
            periodicLen[i] = m_k[i] - 1;
        }
    }

    glm::vec3 controlPoints[m_nbCtrlPoints[0] + periodicLen[0]][m_nbCtrlPoints[1] + periodicLen[1]];
    //    glm::vec3 controlPoints[m_nbCtrlPoints[0]][m_nbCtrlPoints[1]];
    for (uint i = 0; i < m_nbCtrlPoints[0]; ++i) {
        for (uint j = 0; j < m_nbCtrlPoints[1]; ++j) {
            if (m_selected[i][j]) {
                controlPoints[i][j] = worldTransform * glm::vec4(m_controlPoints[i][j], 1.0f) * localTransform;
            } else {
                controlPoints[i][j] = m_controlPoints[i][j];
            }
        }
    }
    for (uint j = 0; j < m_nbCtrlPoints[1]; ++j) {
        for (uint i = 0; i < periodicLen[0]; ++i) {
            controlPoints[i + m_nbCtrlPoints[0]][j] = controlPoints[i][j];
        }
    }
    //        for (uint i = 0; i < m_nbCtrlPoints[0] + periodicLen[0]; ++i) {
    for (uint i = 0; i < m_nbCtrlPoints[0] + periodicLen[0]; ++i) {
        for (uint j = 0; j < periodicLen[1]; ++j) {
            //                controlPoints[i][j + periodicLen[1]] = controlPoints[i][j];
            controlPoints[i][j + m_nbCtrlPoints[1]] = controlPoints[i][j];
        }
    }

    uint nbCtrlPoints[2] = { m_nbCtrlPoints[0] + periodicLen[0], m_nbCtrlPoints[1] + periodicLen[1] };

    //    for (uint uv =0; uv <2; ++uv) {
    //        if (m_periodic[uv]) {
    //            for (uint i =0; i <periodicLen[uv]; ++i) {
    //            }

    //        }
    //    }
    //    for (uint i =0; i <m_nbCtrlPoints[0] * m_nbCtrlPoints[1]; ++i) {
    //        m_indices.emplace_back(i, i + 1);
    //    }
    m_indices.clear();
    int diff = m_nbCtrlPoints[1] - m_nbCtrlPoints[0];
    //    int diff = nbCtrlPoints[1] - nbCtrlPoints[0];
    for (uint i = 0; i < nbCtrlPoints[0]; ++i) {
        for (uint j = 0; j < nbCtrlPoints[1] - 1; ++j) {
            //            m_indices.emplace_back(i * g_maxSize + j, i * g_maxSize + j + 1);
            m_indices.emplace_back(i * nbCtrlPoints[0] + j + i * diff, i * nbCtrlPoints[0] + j + 1 + i * diff);
        }
    }

    m_fun->glBindVertexArray(m_vao);
    m_fun->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    //    m_fun->glBufferData(GL_ARRAY_BUFFER, m_controlPoints.size() * sizeof(glm::vec3), &m_controlPoints[0], GL_STATIC_DRAW);
    //    m_fun->glBufferData(GL_ARRAY_BUFFER, g_buffMaxVertices, &m_controlPoints[0], GL_DYNAMIC_DRAW);
    //    m_fun->glBufferSubData(GL_ARRAY_BUFFER, 0, m_nbCtrlPoints[0] * m_nbCtrlPoints[1] * sizeof(glm::vec3), &controlPoints[0][0]);
    m_fun->glBufferSubData(GL_ARRAY_BUFFER, 0, nbCtrlPoints[0] * nbCtrlPoints[1] * sizeof(glm::vec3), &controlPoints[0][0]);

    //    m_fun->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER);
    m_fun->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    m_fun->glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, nbCtrlPoints[0] * (nbCtrlPoints[1] - 1) * sizeof(glm::uvec2), &m_indices[0]);
    m_fun->glEnableVertexAttribArray(0);

    //    return;
    //    uint n = m_controlPoints.size() - 1;
    //    float knots[m];
    //    float u = 2.5f;

    //    std::vector<std::vector<glm::vec3>> curves;
    uint nbLine = (nbCtrlPoints[0] - (m_k[0] - 1)) * m_dotPerEdge[0] + 1;
    uint nbCol = (nbCtrlPoints[1] - (m_k[1] - 1)) * m_dotPerEdge[1] + 1;
    glm::vec3 surfaces[nbLine][nbCol];
    //    for (uint i = 0; i < nbLine; ++i) {
    //        for (uint j = 0; j < nbCol; ++j) {
    //            surfaces[i][j] = glm::vec3(0.0f);
    //        }
    //    }

    for (uint i = 0; i < nbCtrlPoints[0]; ++i) {
        std::vector<glm::vec3> linePtCtrl;
        for (uint j = 0; j < nbCtrlPoints[1]; ++j) {
            linePtCtrl.emplace_back(controlPoints[i][j]);
        }
        std::vector<glm::vec3> curveLine(calcCurve(linePtCtrl, m_k[1], m_dotPerEdge[1], m_knots[1]));
        Q_ASSERT(curveLine.size() == nbCol);
        for (uint k = 0; k < nbCol; ++k) {
            surfaces[i][k] = curveLine[k];
        }
    }

    for (uint j = 0; j < nbCol; ++j) {
        std::vector<glm::vec3> colPtCtrl;
        for (uint i = 0; i < nbCtrlPoints[0]; ++i) {
            colPtCtrl.emplace_back(surfaces[i][j]);
        }
        std::vector<glm::vec3> curveCol(calcCurve(colPtCtrl, m_k[0], m_dotPerEdge[0], m_knots[0]));

        Q_ASSERT(curveCol.size() == nbLine);
        for (uint k = 0; k < nbLine; ++k) {
            surfaces[k][j] = curveCol[k];
        }
    }

    m_vertices.clear();
    m_normals.clear();
    m_indiceTriangles.clear();
    //    uint nbLine = curves.size();
    for (uint i = 0; i < nbLine; ++i) {
        //        uint nbCol = curves[i].size();
        for (uint j = 0; j < nbCol; ++j) {
            m_vertices.emplace_back(surfaces[i][j]);

            if (i < nbLine - 1 && j < nbCol - 1) {
                uint topLeft = i * nbCol + j;
                uint topRight = i * nbCol + j + 1;
                uint bottomLeft = (i + 1) * nbCol + j;
                uint bottomRight = (i + 1) * nbCol + j + 1;

                //                m_indiceTriangles.emplace_back(topLeft, bottomRight, bottomLeft);
                //                m_indiceTriangles.emplace_back(topLeft, topRight, bottomRight);
                m_indiceTriangles.emplace_back(topLeft, bottomLeft, bottomRight);
                m_indiceTriangles.emplace_back(topLeft, bottomRight, topRight);

                glm::vec3 topLeftBottomRight = surfaces[i + 1][j + 1] - surfaces[i][j];
                glm::vec3 topLeftTopRight = surfaces[i][j + 1] - surfaces[i][j];

                glm::vec3 normal = glm::normalize(glm::cross(topLeftBottomRight, topLeftTopRight));
                m_normals.emplace_back(std::move(normal));
            } else if (i == nbLine - 1 && j != nbCol - 1) {
                //                uint topLeft = (i - 1) * nbCol + j;
                //                uint bottomRight = i * nbCol + j +1;
                //                uint bottomLeft = i * nbCol + j;

                glm::vec3 bottomLeftTopLeft = surfaces[i - 1][j] - surfaces[i][j];
                glm::vec3 bottomLeftBottomRight = surfaces[i][j + 1] - surfaces[i][j];

                glm::vec3 normal = glm::normalize(glm::cross(bottomLeftBottomRight, bottomLeftTopLeft));
                m_normals.emplace_back(std::move(normal));
            } else if (j == nbCol - 1 && i != nbLine - 1) {
                glm::vec3 topRighttopLeft = surfaces[i][j - 1] - surfaces[i][j];
                glm::vec3 topRightBottomRight = surfaces[i + 1][j] - surfaces[i][j];

                glm::vec3 normal = glm::normalize(glm::cross(topRighttopLeft, topRightBottomRight));
                m_normals.emplace_back(std::move(normal));

            } else {
                Q_ASSERT(j == nbCol - 1 && i == nbLine - 1);
                glm::vec3 bottomRightTopRight = surfaces[i - 1][j] - surfaces[i][j];
                glm::vec3 bottomRightBottomLeft = surfaces[i][j - 1] - surfaces[i][j];

                glm::vec3 normal = glm::normalize(glm::cross(bottomRightTopRight, bottomRightBottomLeft));
                m_normals.emplace_back(std::move(normal));
            }
        }
    }

    //    for (uint i = 0; i < nbLine; ++i) {
    //        //        uint nbCol = curves[i].size();
    //        for (uint j = 0; j < nbCol; ++j) {
    //            if (i < nbLine - 1 && j < nbCol - 1) {
    //                uint topLeft = i * nbCol + j;
    //                uint topRight = i * nbCol + j + 1;
    //                uint bottomLeft = (i + 1) * nbCol + j;
    //                uint bottomRight = (i + 1) * nbCol + j + 1;

    //            }
    //        }
    //    }

    //    for (uint i = 0; i < m_vertices.size() - 1; ++i) {
    //        m_indiceTriangles.emplace_back(i, i + 1);
    //    }
    //    m_fun->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    //    m_fun->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    //    m_fun->glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(glm::uvec2), &m_indices[0], GL_STATIC_DRAW);
    //    m_fun->glBufferData(GL_ELEMENT_ARRAY_BUFFER, g_buffMaxVertices, &m_indices[0], GL_DYNAMIC_DRAW);

    m_fun->glBindVertexArray(m_vao2);
    //    m_fun->glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), &m_vertices[0], GL_STATIC_DRAW);
    //    m_fun->glEnableVertexAttribArray(0);
    //    m_fun->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    //    m_fun->glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indiceTriangles.size() * sizeof(glm::uvec2), &m_indiceTriangles[0], GL_STATIC_DRAW);
    //    m_fun->glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), &m_vertices[0], GL_STATIC_DRAW);
    // question : re bind or not for subData
    m_fun->glBindBuffer(GL_ARRAY_BUFFER, m_vbo2);
    //    m_fun->glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(glm::vec3), &m_vertices[0]);
    m_fun->glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(glm::vec3), &m_vertices[0]);
    //    m_fun->glEnableVertexAttribArray(0);
    //    m_fun->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    m_fun->glBindBuffer(GL_ARRAY_BUFFER, m_nbo2);
    m_fun->glBufferSubData(GL_ARRAY_BUFFER, 0, m_normals.size() * sizeof(glm::vec3), &m_normals[0]);

    //    m_fun->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo2);
    //    m_fun->glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indiceTriangles.size() * sizeof(glm::uvec2), &m_indiceTriangles[0], GL_STATIC_DRAW);
    m_fun->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo2);
    m_fun->glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_indiceTriangles.size() * sizeof(glm::uvec3), &m_indiceTriangles[0]);

    m_fun->glBindVertexArray(0);
}

void BSplineSurface::buildItemModel(QStandardItem* parent) const
{
    //    QStandardItem* item2 = new QStandardItem("transformation");
    //    m_itemTransformation = new QStandardItem;
    //    mat4BuildItemModel(m_transformation, m_itemTransformation);
    //    item2->appendRow(m_itemTransformation);
    //    item->appendRow(item2);

    //    for (const glm::vec3& vertex : m_controlPoints) {
    for (uint i = 0; i < m_nbCtrlPoints[0]; ++i) {
        QString str;
        for (uint j = 0; j < m_nbCtrlPoints[1]; ++j) {
            const glm::vec3& vertex = m_controlPoints[i][j];

            //            QStandardItem* item = new QStandardItem(QString::number(vertex.x) + "  " + QString::number(vertex.y) + "  " + QString::number(vertex.z));
            str += QString::number(vertex.x) + "  " + QString::number(vertex.y) + "  " + QString::number(vertex.z) + "   ";
            //            parent->appendRow(item);
        }
        QStandardItem* item = new QStandardItem(str);
        parent->appendRow(item);
    }
}
