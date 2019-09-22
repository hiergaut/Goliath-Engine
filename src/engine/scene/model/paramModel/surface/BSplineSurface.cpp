#include "BSplineSurface.h"

//BSplineSurface::BSplineSurface()
//{

//}
#include <session/Session.h>

#include <QDebug>
#include <opengl/geometry/DotGeometry.h>

const uint g_buffMaxVertices = 10000 * sizeof(glm::vec3);
//const uint BSplineSurface::g_maxLenKnots = 13:

BSplineSurface::BSplineSurface()
    : Model(glm::mat4(1.0f), Model::PARAM_SURFACE)
//    : ParamModel(Model::Type::BSPLINE_CURVE)
{

    //    m_controlPoints.emplace_back(-200.0f, 0.0f, 0.0f);
    //    m_controlPoints.emplace_back(-150.0f, 0.0f, 0.0f);
    //    m_controlPoints.emplace_back(-100.0f, 100.0f, 0.0f);
    //    m_controlPoints.emplace_back(100.0f, 100.0f, 0.0f);
    //    m_controlPoints.emplace_back(150.0f, 0.0f, 0.0f);
    //    m_controlPoints.emplace_back(200.0f, 0.0f, 0.0f);
//    for (uint i = 0; i < m_nbLine; ++i) {
//        for (uint j = 0; j < m_nbCol; ++j) {
//            m_controlPoints[i][j] = glm::vec3(i * 100.0f, j * 100.0f, 0.0f);
//            m_selected[i][j] = false;
//        }
//    }
    uint middleI = m_nbLine / 2;
    uint middleJ = m_nbCol / 2;
    for (uint i = 0; i < m_nbLine; ++i) {
        for (uint j = 0; j < m_nbCol; ++j) {
            if (i == middleI || j == middleJ) {
                m_controlPoints[i][j] = glm::vec3(i * 100.0f, j * 100.0f, 100.0f);
            } else {
                m_controlPoints[i][j] = glm::vec3(i * 100.0f, j * 100.0f, 0.0f);
            }
            m_selected[i][j] = false;
        }
    }


    //    m_selected.resize(m_controlPoints.size());
    //    for (uint i = 0; i < m_selected.size(); ++i) {
    //        m_selected[i] = false;
    //    }

    //    m_indices.emplace_back(0, 1);
    //    m_indices.emplace_back(1, 2);
    //    m_indices.emplace_back(2, 3);

    setupGL();

    for (uint i = 0; i < 2; ++i) {
        m_k[i] = 2;
        m_dotPerEdge[i] = 5;
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

    Session::load(&m_controlPoints[0][0], m_nbLine * m_nbCol, file);

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

    //    m_selected.resize(m_controlPoints.size());
    //    for (uint i = 0; i < m_selected.size(); ++i) {
    //        m_selected[i] = false;
    //    }
    //    for (uint i = 0; i < m_controlPoints.size() - 1; ++i) {
    //        m_indices.emplace_back(i, i + 1);
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
    for (uint i = 0; i < 2; ++i) {
        m_k[i] = 2;
        m_dotPerEdge[i] = 5;
        //        m_knots[i].resize(g_maxLenKnots);
        for (uint j = 0; j < g_maxLenKnots; ++j) {
            //        knots[i] = i;
            m_knots[i][j] = j;
        }
    }

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
    //    m_fun->glGenBuffers(1, &m_ebo);
    //    m_fun->glGenBuffers(1, &m_vbo2);

    m_fun->glBindVertexArray(m_vao);
    m_fun->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    //    m_fun->glBufferData(GL_ARRAY_BUFFER, m_controlPoints.size() * sizeof(glm::vec3), &m_controlPoints[0], GL_STATIC_DRAW);
    m_fun->glBufferData(GL_ARRAY_BUFFER, g_buffMaxVertices, &m_controlPoints[0], GL_DYNAMIC_DRAW);
    m_fun->glEnableVertexAttribArray(0);
    m_fun->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    //    m_fun->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    //    m_fun->glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(glm::uvec2), &m_indices[0], GL_STATIC_DRAW);
    //    m_fun->glBufferData(GL_ELEMENT_ARRAY_BUFFER, g_buffMaxVertices, &m_indices[0], GL_DYNAMIC_DRAW);

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

void BSplineSurface::save(std::ofstream& file) const
{
    Model::save(file);

    Session::save(&m_controlPoints[0][0], m_nbLine * m_nbCol, file);

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
        m_fun->glDrawArrays(GL_POINTS, 0, m_nbLine * m_nbCol);

        m_fun->glPointSize(4.0f);
        shader.setVec4("color", glm::vec4(1.0f, 0.5f, 0.0f, 1.0f));
        m_fun->glBindVertexArray(m_vao2);
        m_fun->glDrawArrays(GL_POINTS, 0, m_vertices.size());

        //        shader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        //        shader.setMat4("model", worldTransform * m_transform * localTransform);

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
    for (uint i = 0; i < m_nbLine; ++i) {
        for (uint j = 0; j < m_nbCol; ++j) {
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
    for (uint i = 0; i < m_nbLine; ++i) {
        for (uint j = 0; j < m_nbCol; ++j) {
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
    for (uint i = 0; i < m_nbLine; ++i) {
        for (uint j = 0; j < m_nbCol; ++j) {
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
    for (uint i = 0; i < m_nbLine; ++i) {
        for (uint j = 0; j < m_nbCol; ++j) {
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

glm::vec3 deBoor(float u, uint m, const uint k, const float knots[], const std::vector<glm::vec3>& controlPoints)
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

std::vector<glm::vec3> calcCurve(const std::vector<glm::vec3>& ptsCtrl, const uint k, const uint dotPerEdge, const float knots[])
{

    std::vector<glm::vec3> curve;

    //    uint n = m_nbLine -1;
    uint n = ptsCtrl.size() - 1;
    //    std::cout << "n: " << n << std::endl;
    uint m = k + n + 1;
    uint nbPtCtl = ((n + 1) * dotPerEdge);
    //    std::vector<glm::vec3> curve(nbPtCtl);
    const float start = knots[k - 1];
    const float end = knots[n + 1];
    const float period = end - start;
    for (uint iPtCtl = 0; iPtCtl < nbPtCtl; ++iPtCtl) {
        //        float u = (float)iPtCtl / (nbPtCtl - 1) * (n - m_k + 2) + (m_k - 1);
        float u = (float)iPtCtl / (nbPtCtl - 1) * period + start;
        //        qDebug() << "u: " << u;
        //        std::cout << u << std::endl;
        if (iPtCtl == 0) {
            Q_ASSERT(qAbs(knots[k - 1] - u) < 1e-5);
        } else if (iPtCtl == nbPtCtl - 1) {
            Q_ASSERT(qAbs(knots[n + 1] - u) < 1e-5);
        }
        Q_ASSERT(knots[k - 1] <= u && u <= knots[n + 1]);

        //        m_vertices.push_back(worldTransform * glm::vec4(pts[0], 1.0f) * localTransform);
        //        m_vertices.push_back(pts[0]);
        //        m_vertices.push_back(deBoor(u, m, m_k[0], m_knots[0], ))
        curve.emplace_back(deBoor(u, m, k, knots, ptsCtrl));
        //        curve[iPtCtl] =
    }
    Q_ASSERT(nbPtCtl == curve.size());
    Q_ASSERT(nbPtCtl > 0);

    return curve;
    //    return std::move(curve);
}

void BSplineSurface::updateSurface(const glm::mat4& localTransform, const glm::mat4& worldTransform)
{
    //    std::vector<
    //    std::vector<glm::vec3> controlPoints(m_controlPoints);
    glm::vec3 controlPoints[m_nbLine][m_nbCol];
    for (uint i = 0; i < m_nbLine; ++i) {
        for (uint j = 0; j < m_nbCol; ++j) {
            if (m_selected[i][j]) {
                controlPoints[i][j] = worldTransform * glm::vec4(m_controlPoints[i][j], 1.0f) * localTransform;
            } else {
                controlPoints[i][j] = m_controlPoints[i][j];
            }
        }
    }
    m_fun->glBindVertexArray(m_vao);
    m_fun->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    //    m_fun->glBufferData(GL_ARRAY_BUFFER, m_controlPoints.size() * sizeof(glm::vec3), &m_controlPoints[0], GL_STATIC_DRAW);
    //    m_fun->glBufferData(GL_ARRAY_BUFFER, g_buffMaxVertices, &m_controlPoints[0], GL_DYNAMIC_DRAW);
    m_fun->glBufferSubData(GL_ARRAY_BUFFER, 0, m_nbLine * m_nbCol * sizeof(glm::vec3), &controlPoints[0]);
    //    m_fun->glEnableVertexAttribArray(0);

    //    return;
    //    uint n = m_controlPoints.size() - 1;
    //    float knots[m];
    //    float u = 2.5f;

    //    std::vector<std::vector<glm::vec3>> curves;
    uint nbLine = (m_nbLine)*m_dotPerEdge[0];
    uint nbCol = (m_nbCol)*m_dotPerEdge[1];
    glm::vec3 surfaces[nbLine][nbCol];
    //    for (uint i = 0; i < nbLine; ++i) {
    //        for (uint j = 0; j < nbCol; ++j) {
    //            surfaces[i][j] = glm::vec3(0.0f);
    //        }
    //    }

    for (uint i = 0; i < m_nbLine; ++i) {
        std::vector<glm::vec3> linePtCtrl;
        for (uint j = 0; j < m_nbCol; ++j) {
            linePtCtrl.emplace_back(controlPoints[i][j]);
        }
        std::vector<glm::vec3> curve(calcCurve(linePtCtrl, m_k[1], m_dotPerEdge[1], m_knots[1]));
        Q_ASSERT(curve.size() == nbCol);
        for (uint k = 0; k < nbCol; ++k) {
            surfaces[i][k] = curve[k];
        }
    }

    for (uint j = 0; j < nbCol; ++j) {
        std::vector<glm::vec3> colPtCtrl;
        for (uint i = 0; i < m_nbLine; ++i) {
            colPtCtrl.emplace_back(surfaces[i][j]);
        }
        std::vector<glm::vec3> curve2(calcCurve(colPtCtrl, m_k[0], m_dotPerEdge[0], m_knots[0]));

        Q_ASSERT(curve2.size() == nbLine);
        for (uint k = 0; k < nbLine; ++k) {
            surfaces[k][j] = curve2[k];
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
    for (uint i = 0; i < m_nbLine; ++i) {
        QString str;
        for (uint j = 0; j < m_nbCol; ++j) {
            const glm::vec3& vertex = m_controlPoints[i][j];

            //            QStandardItem* item = new QStandardItem(QString::number(vertex.x) + "  " + QString::number(vertex.y) + "  " + QString::number(vertex.z));
            str += QString::number(vertex.x) + "  " + QString::number(vertex.y) + "  " + QString::number(vertex.z) + "   ";
            //            parent->appendRow(item);
        }
        QStandardItem* item = new QStandardItem(str);
        parent->appendRow(item);
    }
}
