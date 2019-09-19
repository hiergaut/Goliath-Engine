#include "ParamModel.h"

ParamModel::ParamModel()
    : Model(glm::mat4(1.0f), Model::PARAM)
{

    m_vertices.emplace_back(-150.0f, 0.0f, 100.0f);
    m_vertices.emplace_back(-100.0f, 100.0f, 100.0f);
    m_vertices.emplace_back(100.0f, 100.0f, 100.0f);
    m_vertices.emplace_back(150.0f, 0.0f, 100.0f);

    m_indices.emplace_back(0, 1);
    m_indices.emplace_back(1, 2);
    m_indices.emplace_back(2, 3);

    setupGL();
}

ParamModel::ParamModel(std::ifstream &file)
    : Model(file)
{
    Session::load(m_vertices, file);
    Session::load(m_indices, file);

//    m_vertices.clear();
//    m_vertices.emplace_back(-150.0f, 0.0f, 100.0f);
//    m_vertices.emplace_back(-100.0f, 100.0f, 100.0f);
//    m_vertices.emplace_back(100.0f, 100.0f, 100.0f);
//    m_vertices.emplace_back(150.0f, 0.0f, 100.0f);

//    m_indices.clear();
//    m_indices.emplace_back(0, 1);
//    m_indices.emplace_back(1, 2);
//    m_indices.emplace_back(2, 3);
    Q_ASSERT(m_vertices.size() == 4);
    Q_ASSERT(m_indices.size() == 3);


    setupGL();
}

void ParamModel::setupGL()
{
    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    Q_ASSERT(m_fun != nullptr);

    m_fun->glGenVertexArrays(1, &m_vao);
    m_fun->glGenBuffers(1, &m_vbo);
    m_fun->glGenBuffers(1, &m_ebo);

    m_fun->glBindVertexArray(m_vao);
    m_fun->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    m_fun->glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), &m_vertices[0], GL_STATIC_DRAW);
    m_fun->glEnableVertexAttribArray(0);
    m_fun->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    m_fun->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    m_fun->glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(glm::uvec2), &m_indices[0], GL_STATIC_DRAW);

    m_fun->glBindVertexArray(0);

}

void ParamModel::save(std::ofstream &file) const
{
    Model::save(file);

    Session::save(m_vertices, file);
    Session::save(m_indices, file);

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

    m_fun->glBindVertexArray(m_vao);
//    m_fun->glDrawArrays(GL_LINES, 0, 4);
    m_fun->glDrawElements(GL_LINES, m_indices.size() * 2, GL_UNSIGNED_INT, nullptr);
    m_fun->glBindVertexArray(0);

    shader.setBool("userColor", false);
}

void ParamModel::draw(const Shader& shader, const glm::mat4& localTransform, const glm::mat4& worldTransform) const
{
    Q_ASSERT(m_fun != nullptr);
    shader.setMat4("model", worldTransform * m_transform * localTransform);
    shader.setBool("userColor", true);
    shader.setVec4("color", glm::vec4(1.0f, 0.5f, 0.5f, 1.0f));

    m_fun->glBindVertexArray(m_vao);
//    m_fun->glDrawArrays(GL_LINES, 0, 4);
    m_fun->glDrawElements(GL_LINES, m_indices.size() * 2, GL_UNSIGNED_INT, nullptr);
    m_fun->glBindVertexArray(0);

    shader.setBool("userColor", false);
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

void ParamModel::buildItemModel(QStandardItem* parent) const
{
//    QStandardItem* item2 = new QStandardItem("transformation");
//    m_itemTransformation = new QStandardItem;
//    mat4BuildItemModel(m_transformation, m_itemTransformation);
//    item2->appendRow(m_itemTransformation);
//    item->appendRow(item2);

    for (const glm::vec3 & vertex : m_vertices) {
        QStandardItem * item = new QStandardItem(QString::number(vertex.x) + "  " +  QString::number(vertex.y) + "  " +  QString::number(vertex.z));
        parent->appendRow(item);
    }



}
