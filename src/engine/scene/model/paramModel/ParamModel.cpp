#include "ParamModel.h"
#include <QDebug>

const uint g_buffMaxVertices = 100 * sizeof(glm::vec3);

ParamModel::ParamModel()
    : Model(glm::mat4(1.0f), Model::PARAM)
{

    m_controlPoints.emplace_back(-150.0f, 0.0f, 100.0f);
    m_controlPoints.emplace_back(-100.0f, 100.0f, 100.0f);
    m_controlPoints.emplace_back(100.0f, 100.0f, 100.0f);
    m_controlPoints.emplace_back(150.0f, 0.0f, 100.0f);

    m_indices.emplace_back(0, 1);
    m_indices.emplace_back(1, 2);
    m_indices.emplace_back(2, 3);

    setupGL();

    m_k = 3;
    updateCurve();
}

ParamModel::ParamModel(std::ifstream& file)
    : Model(file)
{
    //    Session::load(m_controlPoints, file);
    //    Session::load(m_indices, file);
    //    qDebug() << "ParamModel";

//    m_controlPoints.clear();
    m_controlPoints.emplace_back(-200.0f, 0.0f, 100.0f);
    m_controlPoints.emplace_back(-150.0f, 0.0f, 100.0f);
    m_controlPoints.emplace_back(-100.0f, 100.0f, 100.0f);
    m_controlPoints.emplace_back(100.0f, 100.0f, 100.0f);
    m_controlPoints.emplace_back(150.0f, 0.0f, 100.0f);
    m_controlPoints.emplace_back(200.0f, 0.0f, 100.0f);

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

    m_k = 3;
    updateCurve();
}

void ParamModel::setupGL()
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

void ParamModel::save(std::ofstream& file) const
{
    Model::save(file);

    //    Session::save(m_controlPoints, file);
    //    Session::save(m_indices, file);
}

void ParamModel::prepareHierarchy(ulong frameTime) const
{
}

void ParamModel::draw(const Shader& shader, bool dotCloud, const glm::mat4& localTransform, const glm::mat4& worldTransform) const
{
    Q_ASSERT(m_fun != nullptr);
    shader.setMat4("model", worldTransform * m_transform * localTransform);
    shader.setBool("userColor", true);
    shader.setVec4("color", glm::vec4(1.0f, 0.5f, 0.5f, 1.0f));
    m_fun->glPointSize(5.0f);
    //    m_fun->glLineWidth(1.0f);

    m_fun->glBindVertexArray(m_vao);
    //    m_fun->glDrawArrays(GL_LINES, 0, 4);
    //    m_fun->glEnable(GL_POINT_SMOOTH);
    //    m_fun->glDrawElements(GL_LINES, m_indices.size() * 2, GL_UNSIGNED_INT, nullptr);
    m_fun->glDrawArrays(GL_POINTS, 0, m_controlPoints.size());
    //    m_fun->glLineWidth(1.0f);
    //    m_fun->glBindVertexArray(0);

    shader.setVec4("color", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    m_fun->glBindVertexArray(m_vao2);
    //    m_fun->glDrawArrays(GL_LINES, 0, 4);
    //    m_fun->glEnable(GL_POINT_SMOOTH);
    //    m_fun->glPointSize(5.0f);
    m_fun->glDrawElements(GL_LINES, m_curveIndiceLines.size() * 2, GL_UNSIGNED_INT, nullptr);
    //    m_fun->glLineWidth(2.0f);
    m_fun->glDrawArrays(GL_POINTS, 0, m_curve.size());
    //    m_fun->glLineWidth(1.0f);
    m_fun->glBindVertexArray(0);

    shader.setBool("userColor", false);
    m_fun->glPointSize(1.0f);
    m_fun->glLineWidth(1.0f);
}

void ParamModel::draw(const Shader& shader, const glm::mat4& localTransform, const glm::mat4& worldTransform) const
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

void ParamModel::updateBoundingBox() const
{
}

void ParamModel::drawBoundingBox(const Shader& shader) const
{
}

std::string ParamModel::name() const
{
    return "BSpline";
}

void ParamModel::setK(uint k)
{
    m_k = k;

    updateCurve();
}

void ParamModel::updateCurve()
{
    uint n = m_controlPoints.size() - 1;
//    std::cout << "n: " << n << std::endl;
    uint m = m_k + n + 1;
    float knots[m];
    for (uint i = 0; i < m; ++i) {
        knots[i] = i;
    }

    //    float u = 2.5f;
    m_curve.clear();
    uint nbPtCtl = (n * 5) + 1;
    for (uint iPtCtl = 0; iPtCtl < nbPtCtl; ++iPtCtl) {
        float u = (float)iPtCtl / (nbPtCtl - 1) * (n - m_k + 2) + (m_k - 1);
        //        qDebug() << "u: " << u;
//        std::cout << u << std::endl;
        if (iPtCtl == 0) {
            Q_ASSERT(qAbs(knots[m_k - 1] - u) < 1e-5);
        } else if (iPtCtl == nbPtCtl - 1) {
            Q_ASSERT(qAbs(knots[n + 1] - u) < 1e-5);
        }
        Q_ASSERT(knots[m_k - 1] <= u && u <= knots[n + 1]);

        int dec = 0;
        int i = m_k;
        //        qDebug() << "loop";
        while (knots[i] < u) {
            ++i;
            ++dec;
            Q_ASSERT(i < m);
        }
        //        qDebug() << "end loop";
        //        dec -= k - 1;
        //        dec =

        glm::vec3 pts[m_k];
        for (uint i = 0; i < m_k; ++i) {
            Q_ASSERT(i + dec < m_controlPoints.size());
            pts[i] = m_controlPoints[i + dec];
        }

        //        for (uint i = k - 1; i > 0; --i) {
        //            for (uint j = 0; j < i; ++j) {
        //                float a = (knots[dec + k + j + 1] - u) /
        //                        (knots[dec + k +j + 1] - knots[dec + dec + k - i]);

        //                pts[j] = a * pts[j] + (1 - a) * pts[j + 1];
        //            }
        ////            ++dec;
        //        }
        uint l = m_k;
        uint k2 = m_k;
        for (uint j = 0; j < l - 1; ++j) {
            for (uint i = 0; i < k2 - 1; ++i) {
                float a = (knots[dec + k2 + i] - u) / (knots[dec + k2 + i] - knots[dec + 1 + i]);
                pts[i] = a * pts[i] + (1 - a) * pts[i + 1];
            }
            --k2;
            ++dec;
        }
        m_curve.push_back(pts[0]);
    }

    m_curveIndiceLines.clear();
    for (uint i = 0; i < m_curve.size() - 1; ++i) {
        m_curveIndiceLines.emplace_back(i, i + 1);
    }


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

void ParamModel::buildItemModel(QStandardItem* parent) const
{
    //    QStandardItem* item2 = new QStandardItem("transformation");
    //    m_itemTransformation = new QStandardItem;
    //    mat4BuildItemModel(m_transformation, m_itemTransformation);
    //    item2->appendRow(m_itemTransformation);
    //    item->appendRow(item2);

    //    for (const glm::vec3& vertex : m_controlPoints) {
    //        QStandardItem* item = new QStandardItem(QString::number(vertex.x) + "  " + QString::number(vertex.y) + "  " + QString::number(vertex.z));
    //        parent->appendRow(item);
    //    }
}
