#include "SkyBoxGeometry.h"

//SkyBoxGeometry::SkyBoxGeometry()
//{

//}


QOpenGLFunctionsCore* SkyBoxGeometry::m_fun = nullptr;
uint SkyBoxGeometry::m_vao;

void SkyBoxGeometry::initializeGL()
{
//    float radius = 0.5f;

//    std::vector<glm::vec3> m_vertices;
//    m_vertices.emplace_back(-radius, -radius, -radius);
//    m_vertices.emplace_back(-radius, radius, -radius);
//    m_vertices.emplace_back(radius, radius, -radius);
//    m_vertices.emplace_back(radius, -radius, -radius);

//    m_vertices.emplace_back(-radius, -radius, radius);
//    m_vertices.emplace_back(-radius, radius, radius);
//    m_vertices.emplace_back(radius, radius, radius);
//    m_vertices.emplace_back(radius, -radius, radius);

//    std::vector<glm::vec3> m_normals;
//    m_normals = m_vertices;
//    for (glm::vec3& vec : m_normals) {
//        vec = glm::normalize(vec);
//    }

//    std::vector<glm::uvec2> m_indices;
//    m_indices.emplace_back(0, 1);
//    m_indices.emplace_back(1, 2);
//    m_indices.emplace_back(2, 3);
//    m_indices.emplace_back(3, 0);


//    m_indices.emplace_back(4, 5);
//    m_indices.emplace_back(5, 6);
//    m_indices.emplace_back(6, 7);
//    m_indices.emplace_back(7, 4);

//    m_indices.emplace_back(0, 4);
//    m_indices.emplace_back(1, 5);
//    m_indices.emplace_back(2, 6);
//    m_indices.emplace_back(3, 7);

    float skyboxVertices[] = {
        // positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };


    //    Q_ASSERT(m_fun != nullptr);
    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    Q_ASSERT(m_fun != nullptr);

    m_fun->glGenVertexArrays(1, &m_vao);
    uint m_vbo;
    m_fun->glGenBuffers(1, &m_vbo);
//    uint m_ebo;
//    m_fun->glGenBuffers(1, &m_ebo);
//    uint m_nbo;
//    m_fun->glGenBuffers(1, &m_nbo);

    m_fun->glBindVertexArray(m_vao);

    m_fun->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
//    m_fun->glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), &m_vertices[0], GL_STATIC_DRAW);
    m_fun->glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    m_fun->glEnableVertexAttribArray(0);
    m_fun->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

//    m_fun->glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
//    m_fun->glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(glm::vec3), &m_normals[0], GL_STATIC_DRAW);
//    m_fun->glEnableVertexAttribArray(1);
//    m_fun->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

//    m_fun->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
//    m_fun->glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(glm::uvec2), &m_indices[0], GL_STATIC_DRAW);

    //    m_fun->glGenVertexArrays(1, &m_vao2);
    //    m_fun->glBindVertexArray(m_vao2);
    //    m_fun->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    //    m_fun->glBindBuffer(GL_ARRAY_BUFFER, m_nbo);

    //    m_fun->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo2);
    //    m_fun->glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesLine.size() * sizeof(glm::uvec2), &m_indicesLine[0], GL_STATIC_DRAW);
    //    m_fun->glEnableVertexAttribArray(1);
    //    m_fun->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    m_fun->glBindVertexArray(0);
}

void SkyBoxGeometry::draw()
{
    Q_ASSERT(m_fun != nullptr);
    //    m_shader->use();
    //    m_shader->setMat4("model", modelMatrix);
    //    m_shader->setMat4("view", viewMatrix);
    //    m_shader->setMat4("projection", projectionMatrix);

    //    shader.setBool("contour", true);
    //    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();

    m_fun->glBindVertexArray(m_vao);
    m_fun->glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, nullptr);
    m_fun->glBindVertexArray(0);
    //    shader.setBool("contour", false);
}
