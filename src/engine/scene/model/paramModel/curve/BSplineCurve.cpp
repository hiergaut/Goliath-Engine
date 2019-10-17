#include "BSplineCurve.h"

//BSplineCurve::BSplineCurve()
//{

//}
#include <session/Session.h>

#include <QDebug>
#include <engine/scene/Scene.h>
#include <opengl/geometry/DotGeometry.h>
#include <engine/scene/model/paramModel/surface/BSplineSurface.h>

const uint g_buffMaxVertices = 100 * sizeof(glm::vec3);
//const uint g_maxLenKnots = 13;

BSplineCurve::BSplineCurve(Type type)
    : Model(glm::mat4(1.0f), Model::PARAM_CURVE)
//    : ParamModel(Model::Type::BSPLINE_CURVE)
{
    setupGL();
//    m_k = 3;
//    m_dotPerEdge = 10;
//    m_knots.resize(g_maxLenKnots);

    switch (type) {
    case Type::SPLINE:
        m_controlPoints.emplace_back(-400.0f, -400.0f, 0.0f);
        m_controlPoints.emplace_back(-200.0f, 400.0f, 0.0f);
        m_controlPoints.emplace_back(200.0f, -400.0f, 0.0f);
        m_controlPoints.emplace_back(400.0f, 400.0f, 0.0f);
//        m_periodic = false;
        setUniform();
        break;

    case Type::CIRCLE:
        m_controlPoints.emplace_back(-400.0f, -400.0f, 0.0f);
        m_controlPoints.emplace_back(-400.0f, 400.0f, 0.0f);
        m_controlPoints.emplace_back(400.0f, 400.0f, 0.0f);
        m_controlPoints.emplace_back(400.0f, -400.0f, 0.0f);
//        m_periodic = false;
        setUniform();
        break;

    case Type::CIRCLE8:
        m_controlPoints.emplace_back(0.0f, -400.0f, 0.0f);
        m_controlPoints.emplace_back(-400.0f, -400.0f, 0.0f);
        m_controlPoints.emplace_back(-400.0f, 0.0f, 0.0f);
        m_controlPoints.emplace_back(-400.0f, 400.0f, 0.0f);
        m_controlPoints.emplace_back(0.0f, 400.0f, 0.0f);
        m_controlPoints.emplace_back(400.0f, 400.0f, 0.0f);
        m_controlPoints.emplace_back(400.0f, 0.0f, 0.0f);
        m_controlPoints.emplace_back(400.0f, -400.0f, 0.0f);
        m_controlPoints.emplace_back(0.0f, -400.0f, 0.0f);

//        m_periodic = false;

        m_knots[0] = 0.0f;
        m_knots[1] = 0.0f;
        m_knots[2] = 0.0f;
        m_knots[3] = 0.25f;
        m_knots[4] = 0.25f;
        m_knots[5] = 0.5f;
        m_knots[6] = 0.5f;
        m_knots[7] = 0.75f;
        m_knots[8] = 0.75f;
        m_knots[9] = 1.0f;
        m_knots[10] = 1.0f;
        m_knots[11] = 1.0f;
        break;

    default:
        Q_ASSERT(false);
        break;
    }

    //    m_controlPoints.emplace_back(-200.0f, 0.0f, 0.0f);
    //    m_controlPoints.emplace_back(-150.0f, 0.0f, 0.0f);
    //    m_controlPoints.emplace_back(-100.0f, 100.0f, 0.0f);
    //    m_controlPoints.emplace_back(100.0f, 100.0f, 0.0f);
    //    m_controlPoints.emplace_back(150.0f, 0.0f, 0.0f);
    //    m_controlPoints.emplace_back(200.0f, 0.0f, 0.0f);

    m_selected.resize(m_controlPoints.size());
    for (uint i = 0; i < m_selected.size(); ++i) {
        m_selected[i] = false;
    }

    for (uint i = 0; i < m_controlPoints.size() - 1; ++i) {
        m_indices.emplace_back(i, i + 1);
    }

    //    m_indices.emplace_back(0, 1);
    //    m_indices.emplace_back(1, 2);
    //    m_indices.emplace_back(2, 3);

    //    for (uint i = 0; i < g_maxLenKnots; ++i) {
    //        //        knots[i] = i;
    //        m_knots[i] = i;
    //    }

    updateCurve();
}

BSplineCurve::BSplineCurve(std::ifstream& file)
    : Model(file)
//    : ParamModel(file)
//    , m_type(Model::BSplineCurve)
//    , m_type = Model::PARAM_CURVE
{
    m_type = Model::PARAM_CURVE;

    Session::load(m_controlPoints, file);
    Session::load(m_k, file);
//    Session::load(&m_knots[0], g_maxLenKnots, file);

    //    Session::load(m_indices, file);
    //    qDebug() << "BSplineCurve";
    //    m_transform = glm::mat4(1.0f);

    //    m_controlPoints.clear();
    //    m_controlPoints.emplace_back(-200.0f, 0.0f, 0.0f);
    //    m_controlPoints.emplace_back(-150.0f, 0.0f, 0.0f);
    //    m_controlPoints.emplace_back(-100.0f, 100.0f, 0.0f);
    //    m_controlPoints.emplace_back(100.0f, 100.0f, 0.0f);
    //    m_controlPoints.emplace_back(150.0f, 0.0f, 0.0f);
    //    m_controlPoints.emplace_back(200.0f, 0.0f, 0.0f);

    m_selected.resize(m_controlPoints.size());
    for (uint i = 0; i < m_selected.size(); ++i) {
        m_selected[i] = false;
    }

    for (uint i = 0; i < m_controlPoints.size() - 1; ++i) {
        m_indices.emplace_back(i, i + 1);
    }

    //    m_indices.clear();
    //    m_indices.emplace_back(0, 1);
    //    m_indices.emplace_back(1, 2);
    //    m_indices.emplace_back(2, 3);

    //    Q_ASSERT(m_controlPoints.size() == );
    //    Q_ASSERT(m_indices.size() == 3);

    //    uint k = 3; // C0
    setupGL();

//    m_k = 3;
//    m_dotPerEdge = 10;
//    m_knots.resize(g_maxLenKnots);
//    for (uint i = 0; i < g_maxLenKnots; ++i) {
//        //        knots[i] = i;
//        m_knots[i] = i;
//    }
    setUniform();

    updateCurve();
}

BSplineCurve::~BSplineCurve()
{
    std::cout << "\033[35m";
    std::cout << "[BSplinCurve] '" << name() << "' deleted " << this << std::endl;
    std::cout << "\033[0m";
}

void BSplineCurve::setupGL()
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
    m_fun->glBufferData(GL_ARRAY_BUFFER, g_buffMaxVertices, &m_controlPoints[0], GL_DYNAMIC_DRAW);
    m_fun->glEnableVertexAttribArray(0);
    m_fun->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    m_fun->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    //    m_fun->glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(glm::uvec2), &m_indices[0], GL_STATIC_DRAW);
    m_fun->glBufferData(GL_ELEMENT_ARRAY_BUFFER, g_buffMaxVertices, &m_indices[0], GL_DYNAMIC_DRAW);

    m_fun->glBindVertexArray(0);

    m_fun->glGenVertexArrays(1, &m_vao2);
    m_fun->glGenBuffers(1, &m_vbo2);
    m_fun->glGenBuffers(1, &m_ebo2);
    //    m_fun->glGenBuffers(1, &m_vbo2);

    m_fun->glBindVertexArray(m_vao2);
    m_fun->glBindBuffer(GL_ARRAY_BUFFER, m_vbo2);
    //    m_fun->glBufferData(GL_ARRAY_BUFFER, m_curve.size() * sizeof(glm::vec3), &m_curve[0], GL_STATIC_DRAW);
    m_fun->glBufferData(GL_ARRAY_BUFFER, g_buffMaxVertices, &m_curve[0], GL_DYNAMIC_DRAW);
    m_fun->glEnableVertexAttribArray(0);
    m_fun->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    m_fun->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo2);
    //    m_fun->glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_curveIndiceLines.size() * sizeof(glm::uvec2), &m_curveIndiceLines[0], GL_STATIC_DRAW);
    m_fun->glBufferData(GL_ELEMENT_ARRAY_BUFFER, g_buffMaxVertices, &m_curveIndiceLines[0], GL_DYNAMIC_DRAW);

    m_fun->glBindVertexArray(0);
}

void BSplineCurve::save(std::ofstream& file) const
{
    Model::save(file);

    Session::save(m_controlPoints, file);
    Session::save(m_k, file);
//    Session::save(&m_knots[0], g_maxLenKnots, file);
    //    Session::save(m_indices, file);
}

void BSplineCurve::prepareHierarchy(ulong frameTime) const
{
}

void BSplineCurve::draw(const Shader& shader, bool dotCloud, const glm::mat4& localTransform, const glm::mat4& worldTransform) const
{
    Q_ASSERT(m_fun != nullptr);
    m_fun->glLineWidth(2.0f);

    //    shader.setBool("userColor", true);
    //    shader.setVec4("color", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

    if (dotCloud) {
        //        for (uint i = 0; i < m_selected.size(); ++i) {
        //            if (m_selected[i]) {
        //                //                qDebug() << "draw " << i;
        //                DotGeometry::draw(glm::translate(glm::mat4(1.0f), m_controlPoints[i]) * worldTransform * m_transform, shader, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), 8);
        //            }
        //        }
        m_fun->glPointSize(5.0f);
        shader.setBool("userColor", true);

        shader.setMat4("model", worldTransform * m_transform * localTransform);
        m_fun->glBindVertexArray(m_vao);
        shader.setVec4("color", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
        m_fun->glDrawArrays(GL_POINTS, 0, m_controlPoints.size());

        shader.setVec4("color", glm::vec4(1.0f, 0.5f, 0.0f, 1.0f));
        m_fun->glBindVertexArray(m_vao2);
        m_fun->glDrawArrays(GL_POINTS, 0, m_curve.size());

        //        shader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        //        shader.setMat4("model", worldTransform * m_transform * localTransform);
        m_fun->glBindVertexArray(m_vao);
        m_fun->glLineWidth(0.5f);
        shader.setBool("userColor", true);
        shader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 0.5f));
        m_fun->glDrawElements(GL_LINES, m_indices.size() * 2, GL_UNSIGNED_INT, nullptr);

    } else {

        //    m_fun->glDrawArrays(GL_LINES, 0, 4);
        //    m_fun->glEnable(GL_POINT_SMOOTH);
        //    m_fun->glLineWidth(1.0f);
        //    m_fun->glBindVertexArray(0);

        shader.setMat4("model", worldTransform * m_transform * localTransform);
        shader.setBool("userColor", true);

        shader.setVec4("color", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
        m_fun->glBindVertexArray(m_vao2);
        //    m_fun->glDrawArrays(GL_LINES, 0, 4);
        //    m_fun->glEnable(GL_POINT_SMOOTH);
        //    m_fun->glPointSize(5.0f);
        m_fun->glDrawElements(GL_LINES, m_curveIndiceLines.size() * 2, GL_UNSIGNED_INT, nullptr);
        //    m_fun->glLineWidth(2.0f);

//        m_fun->glLineWidth(0.5f);
//        shader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 0.5f));
//        m_fun->glBindVertexArray(m_vao);
//        m_fun->glDrawElements(GL_LINES, m_indices.size() * 2, GL_UNSIGNED_INT, nullptr);

        //        m_fun->glDrawArrays(GL_POINTS, 0, m_curve.size());
        //    m_fun->glLineWidth(1.0f);
    }

    m_fun->glBindVertexArray(0);
    shader.setBool("userColor", false);
    m_fun->glPointSize(1.0f);
    m_fun->glLineWidth(1.0f);
}

void BSplineCurve::draw(const Shader& shader, const glm::mat4& localTransform, const glm::mat4& worldTransform) const
{
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

void BSplineCurve::drawSelected(const Shader& shader, const glm::mat4& localTransform, const glm::mat4& worldTransform) const
{
    for (uint i = 0; i < m_selected.size(); ++i) {
        if (m_selected[i]) {
            //                qDebug() << "draw " << i;
            DotGeometry::draw(worldTransform * m_transform * glm::translate(glm::mat4(1.0f), m_controlPoints[i]) * localTransform, shader, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), 10);
        }
    }
}

void BSplineCurve::updateBoundingBox() const
{
    m_box.clear();
    for (const glm::vec3 vertex : m_controlPoints) {
        m_box << m_transform * glm::vec4(vertex, 1.0f);
    }
}

void BSplineCurve::drawBoundingBox(const Shader& shader) const
{
    shader.setBool("userColor", true);
    //    m_rootNode->drawBoundingBox(modelMatrix, shader);
    shader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m_box.draw(shader);

    shader.setBool("userColor", false);
}

void BSplineCurve::updateSelectedVertexPosition(const glm::mat4& localTransform, const glm::mat4& worldTransform)
{

    for (uint i = 0; i < m_selected.size(); ++i) {
        if (m_selected[i]) {
            //                qDebug() << "draw " << i;
            //            DotGeometry::draw(glm::translate(glm::mat4(1.0f), m_controlPoints[i]) * worldTransform * m_transform, shader, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), 10);
            m_controlPoints[i] = worldTransform * glm::vec4(m_controlPoints[i], 1.0f) * localTransform;
        }
    }
    updateCurve();
}

void BSplineCurve::vertexSelectRay(const Ray& ray, bool additional)
{

    for (uint i = 0; i < m_controlPoints.size(); ++i) {
        if (!additional) {
            m_selected[i] = false;
        }

        const glm::vec3& vertex = m_transform * glm::vec4(m_controlPoints[i], 1.0f);
        //                    qDebug() << "vertex " << i;

        if (ray.intersect(vertex)) {
            //                    qDebug() << "intersect " << i;
            //                    m_selectVertices.emplace_back(i);
            if (additional) {
                m_selected[i] = !m_selected[i];
            } else {
                m_selected[i] = true;
            }
        }
    }
}

void BSplineCurve::vertexSelectFrustum(const Frustum& frustum, bool additional)
{
    //    glm::vec3 origin(0.0f);
    //    if (frustum.encompass(origin)) {
    //        qDebug() << "good";
    //    }
    //        qDebug() << "--------------------------------";
    //    return;

    for (uint i = 0; i < m_controlPoints.size(); ++i) {
        if (!additional) {
            m_selected[i] = false;
        }

        const glm::vec3& vertex = m_transform * glm::vec4(m_controlPoints[i], 1.0f);
        //        const glm::vec3& vertex = glm::vec4(m_controlPoints[i], 1.0f) * m_transform;
        //        qDebug() << "vertex " << i;
        Scene::m_scene->addDot(vertex + glm::vec3(10.0f, 10.0f, 10.0f));

        qDebug() << vertex.x << vertex.y << vertex.z;

        //        if (std::abs(vertex.x) < 1.0f && std::abs(vertex.y) < 1.0f) {
        if (frustum.encompass(vertex)) {
            //        if (ray.intersect(vertex)) {
            //                    qDebug() << "intersect " << i;
            //                    m_selectVertices.emplace_back(i);
            if (additional) {
                m_selected[i] = !m_selected[i];
            } else {
                m_selected[i] = true;
            }
        }
    }
    qDebug() << "--------------------------------";
}

std::string BSplineCurve::name() const
{
    return "BSplineCurve";
}

void BSplineCurve::setK(uint k)
{
    m_k = k;

    updateCurve();
}

void BSplineCurve::setDotPerEdge(uint dotPerEdge)
{
    m_dotPerEdge = dotPerEdge;

    updateCurve();
}

//glm::vec3 deBoor(float u, uint m, const uint k, const float knots[], const std::vector<glm::vec3>& controlPoints)
//{
//    int dec = 0;
//    int i = k;
//    //        qDebug() << "loop";
//    while (knots[i] < u) {
//        ++i;
//        ++dec;
//        Q_ASSERT(i < m);
//    }
//    //        qDebug() << "end loop";
//    //        dec -= k - 1;
//    //        dec =

//    glm::vec3 pts[k];
//    for (uint i = 0; i < k; ++i) {
//        Q_ASSERT(i + dec < controlPoints.size());
//        //            pts[i] = m_controlPoints[i + dec];
//        pts[i] = controlPoints[i + dec];
//    }

//    //        for (uint i = k - 1; i > 0; --i) {
//    //            for (uint j = 0; j < i; ++j) {
//    //                float a = (knots[dec + k + j + 1] - u) /
//    //                        (knots[dec + k +j + 1] - knots[dec + dec + k - i]);

//    //                pts[j] = a * pts[j] + (1 - a) * pts[j + 1];
//    //            }
//    ////            ++dec;
//    //        }
//    uint l = k;
//    uint k2 = k;
//    for (uint j = 0; j < l - 1; ++j) {
//        for (uint i = 0; i < k2 - 1; ++i) {
//            float a = (knots[dec + k2 + i] - u) / (knots[dec + k2 + i] - knots[dec + 1 + i]);
//            pts[i] = a * pts[i] + (1 - a) * pts[i + 1];
//        }
//        --k2;
//        ++dec;
//    }

//    return pts[0];
//}

void BSplineCurve::updateCurve(const glm::mat4& localTransform, const glm::mat4& worldTransform)
{
    //    std::vector<
    std::vector<glm::vec3> controlPoints(m_controlPoints);
    for (uint i = 0; i < controlPoints.size(); ++i) {
        if (m_selected[i]) {
            controlPoints[i] = worldTransform * glm::vec4(m_controlPoints[i], 1.0f) * localTransform;
        }
    }

    if (m_periodic) {
        for (uint i = 0; i < m_k - 1; ++i) {
            controlPoints.emplace_back(m_controlPoints[i]);
        }
    }

//    uint n = controlPoints.size() - 1;
    //    std::cout << "n: " << n << std::endl;
//    uint m = m_k + n + 1;
    //    float knots[m];
    //    float u = 2.5f;
    m_curve = BSplineSurface::calcCurve(controlPoints, m_k, m_dotPerEdge, m_knots);
//    m_curve.clear();
//    //        uint nbPtCtl = ((n + 1) * m_dotPerEdge);
//    uint nbPtCtl = n + 2 - m_k;
//    //    const float start = m_knots[m_k - 1];
//    //    const float end = m_knots[n + 1];
//    //    const float period = end - start;
//    //    for (uint iPtCtl = 0; iPtCtl < nbPtCtl; ++iPtCtl) {
//    for (uint iPtCtl = 0; iPtCtl < nbPtCtl + 1; ++iPtCtl) {
//        for (uint iDot = 0; iDot < m_dotPerEdge; ++iDot) {
//            //        float u = (float)iPtCtl / (nbPtCtl - 1) * (n - m_k + 2) + (m_k - 1);
//            const float start = m_knots[m_k - 1 + iPtCtl];
//            const float end = m_knots[m_k + iPtCtl];
//            const float period = end - start;
//            float u = (iDot * period) / m_dotPerEdge + start;

//            if (iPtCtl == nbPtCtl) {
//                u = m_knots[n + 1];
//            }
//            //        qDebug() << "u: " << u;
//            //        std::cout << u << std::endl;
//            //            if (iPtCtl == 0) {
//            //                Q_ASSERT(qAbs(m_knots[m_k - 1] - u) < 1e-5);
//            //            } else if (iPtCtl == nbPtCtl - 1) {
//            //                Q_ASSERT(qAbs(m_knots[n + 1] - u) < 1e-5);
//            //            }
//            Q_ASSERT(m_knots[m_k - 1] <= u && u <= m_knots[n + 1]);
////            Q_ASSERT(2.0f <= u && u <= 4.0f);


////            int dec = 0;
////            int i = m_k;
////            //        qDebug() << "loop";
////            while (m_knots[i] < u) {
////                ++i;
////                ++dec;
////                Q_ASSERT(i < m);
////            }
////            //        qDebug() << "end loop";
////            //        dec -= k - 1;
////            //        dec =

////            glm::vec3 pts[m_k];
////            for (uint i = 0; i < m_k; ++i) {
////                Q_ASSERT(i + dec < controlPoints.size());
////                //            pts[i] = m_controlPoints[i + dec];
////                pts[i] = controlPoints[i + dec];
////            }

////            //        for (uint i = k - 1; i > 0; --i) {
////            //            for (uint j = 0; j < i; ++j) {
////            //                float a = (knots[dec + k + j + 1] - u) /
////            //                        (knots[dec + k +j + 1] - knots[dec + dec + k - i]);

////            //                pts[j] = a * pts[j] + (1 - a) * pts[j + 1];
////            //            }
////            ////            ++dec;
////            //        }
////            uint l = m_k;
////            uint k2 = m_k;
////            for (uint j = 0; j < l - 1; ++j) {
////                for (uint i = 0; i < k2 - 1; ++i) {
////                    float a = (m_knots[dec + k2 + i] - u) / (m_knots[dec + k2 + i] - m_knots[dec + 1 + i]);
////                    pts[i] = a * pts[i] + (1 - a) * pts[i + 1];
////                }
////                --k2;
////                ++dec;
////            }
////            //        m_curve.push_back(worldTransform * glm::vec4(pts[0], 1.0f) * localTransform);
////            m_curve.push_back(pts[0]);
//            m_curve.emplace_back(BSplineSurface::deBoor(u, m, m_k, m_knots, controlPoints));

//            if (iPtCtl == nbPtCtl) {
//                break;
//            }
//        }
//    }

    m_curveIndiceLines.clear();
    for (uint i = 0; i < m_curve.size() - 1; ++i) {
        m_curveIndiceLines.emplace_back(i, i + 1);
    }

    m_fun->glBindVertexArray(m_vao);
    m_fun->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    //    m_fun->glBufferData(GL_ARRAY_BUFFER, m_controlPoints.size() * sizeof(glm::vec3), &m_controlPoints[0], GL_STATIC_DRAW);
    //    m_fun->glBufferData(GL_ARRAY_BUFFER, g_buffMaxVertices, &m_controlPoints[0], GL_DYNAMIC_DRAW);
    m_fun->glBufferSubData(GL_ARRAY_BUFFER, 0, controlPoints.size() * sizeof(glm::vec3), &controlPoints[0]);
    //    m_fun->glEnableVertexAttribArray(0);
    //    m_fun->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    //    m_fun->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    //    m_fun->glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(glm::uvec2), &m_indices[0], GL_STATIC_DRAW);
    //    m_fun->glBufferData(GL_ELEMENT_ARRAY_BUFFER, g_buffMaxVertices, &m_indices[0], GL_DYNAMIC_DRAW);

    m_fun->glBindVertexArray(m_vao2);
    //    m_fun->glBufferData(GL_ARRAY_BUFFER, m_curve.size() * sizeof(glm::vec3), &m_curve[0], GL_STATIC_DRAW);
    //    m_fun->glEnableVertexAttribArray(0);
    //    m_fun->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    //    m_fun->glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_curveIndiceLines.size() * sizeof(glm::uvec2), &m_curveIndiceLines[0], GL_STATIC_DRAW);
    //    m_fun->glBufferData(GL_ARRAY_BUFFER, m_curve.size() * sizeof(glm::vec3), &m_curve[0], GL_STATIC_DRAW);
    m_fun->glBindBuffer(GL_ARRAY_BUFFER, m_vbo2);
    //    m_fun->glBufferSubData(GL_ARRAY_BUFFER, 0, m_curve.size() * sizeof(glm::vec3), &m_curve[0]);
    m_fun->glBufferSubData(GL_ARRAY_BUFFER, 0, m_curve.size() * sizeof(glm::vec3), &m_curve[0]);
    //    m_fun->glEnableVertexAttribArray(0);
    //    m_fun->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    //    m_fun->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo2);
    //    m_fun->glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_curveIndiceLines.size() * sizeof(glm::uvec2), &m_curveIndiceLines[0], GL_STATIC_DRAW);
    m_fun->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo2);
    m_fun->glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_curveIndiceLines.size() * sizeof(glm::uvec2), &m_curveIndiceLines[0]);

    m_fun->glBindVertexArray(0);
}

void BSplineCurve::buildItemModel(QStandardItem* parent) const
{
    //    QStandardItem* item2 = new QStandardItem("transformation");
    //    m_itemTransformation = new QStandardItem;
    //    mat4BuildItemModel(m_transformation, m_itemTransformation);
    //    item2->appendRow(m_itemTransformation);
    //    item->appendRow(item2);

    for (const glm::vec3& vertex : m_controlPoints) {
        QStandardItem* item = new QStandardItem(QString::number(vertex.x) + "  " + QString::number(vertex.y) + "  " + QString::number(vertex.z));
        parent->appendRow(item);
    }
}

void BSplineCurve::clampStart()
{
    float kValue = m_knots[m_k - 1];

    for (uint i = 0; i < m_k - 1; ++i) {
        m_knots[i] = kValue;
    }
    updateCurve();
}

void BSplineCurve::clampEnd()
{
    float endValue = m_knots[m_controlPoints.size()];
    for (uint i = m_controlPoints.size() + 1; i < g_maxLenKnots; ++i) {
        m_knots[i] = endValue;
    }
    updateCurve();
}

void BSplineCurve::setUniform()
{
    for (uint i = 0; i < g_maxLenKnots; ++i) {
        m_knots[i] = i;
    }
    //    updateCurve();
}
