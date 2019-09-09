#include "uvSphereGeometry.h"

#include <assert.h>
#include <opengl/version.h>
//#define GL_GLEXT_PROTOTYPES 1
//#include <GL/gl.h>
//#include <GL/glext.h>
#include <glm/gtc/matrix_transform.hpp>

//UvSphereGeometry::UvSphereGeometry(float radius, uint nbSlices)
//    : m_radius(radius)
//    , m_nbSlices(nbSlices)
//    , m_nbRings(nbSlices)
QOpenGLFunctionsCore * UvSphereGeometry::m_fun = nullptr;
uint UvSphereGeometry::m_vao;
uint UvSphereGeometry::m_nbIndices;

void UvSphereGeometry::initializeGL()
{
    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();

      int m_nbRings = 10;
      int m_nbSlices = 10;
      float m_radius = 1.0f;
    // -----------------------------------------------------------------

    uint nbRect = m_nbSlices * (m_nbRings - 1);
    uint nbTriangle = nbRect * 2 + m_nbSlices * 2;
    uint nbVertices = nbRect + m_nbSlices + 2;

    //    std::cout << "nbVertices =" << nbVertices << std::endl;
    //    std::cout << "nbTriangles =" << nbTriangle << std::endl;

    std::vector<glm::vec3> m_vertices(nbVertices);
    std::vector<glm::vec3> m_normals(nbVertices);
    std::vector<uint> m_indices(nbTriangle * 3);
//    m_vertices.clear();
//    m_normals.clear();
//    m_indices.clear();
//    m_vertices = std::vector<glm::vec3>(nbVertices);
//    m_normals = std::vector<glm::vec3>(nbVertices);
//    m_indices = std::vector<uint>(3 * nbTriangle);

    int iNorthPole = nbVertices - 2;
    m_vertices[iNorthPole] = glm::vec3(0, 0, m_radius);
    //    m_vertices[iNorthPole + 1] = m_radius;
    //    m_vertices[iNorthPole + 2] = 0;
    m_normals[iNorthPole] = glm::vec3(0, 0, 1);
    //    m_normals[iNorthPole + 1] = 1;
    //    m_normals[iNorthPole + 2] = 0;

    int iSouthPole = nbVertices - 1;
    m_vertices[iSouthPole] = glm::vec3(0, 0, -m_radius);
    //    m_vertices[iSouthPole + 1] = -m_radius;
    //    m_vertices[iSouthPole + 2] = 0;
    m_normals[iSouthPole] = glm::vec3(0, 0, -1);
    //    m_normals[iSouthPole + 1] = -1;
    //    m_normals[iSouthPole + 2] = 0;

    float deltaRing = M_PI / (m_nbRings + 1);
    float deltaSlice = 2 * M_PI / m_nbSlices;

    int i = 0;

    for (int iRing = 0, iVertice = 0; iRing < m_nbRings; ++iRing) {
        float teta = (iRing + 1) * deltaRing;

        for (int iSlice = 0; iSlice < m_nbSlices; ++iSlice, ++iVertice) {
            float alpha = iSlice * deltaSlice;

            float y = sin(teta) * cos(alpha);
            float x = sin(alpha) * sin(teta);
            float z = cos(teta);

            m_normals[iVertice] = glm::vec3(x, y, z);
            //            m_normals[iVertice + 1] = y;
            //            m_normals[iVertice + 2] = z;

            float module2 = x * x + y * y + z * z;
            //        std::cout << "module :" << module << std::endl;
            assert(abs(module2 - 1.0) < 1e-6);

            m_vertices[iVertice] = glm::vec3(x * m_radius, y * m_radius, z * m_radius);
            //            m_vertices[iVertice + 1] = y * m_radius;
            //            m_vertices[iVertice + 2] = z * m_radius;

            int topLeft = iRing * m_nbSlices + iSlice;
            int topRight = (iSlice == m_nbSlices - 1) ? (iRing * m_nbSlices) : (topLeft + 1);

            if (iRing == 0) {
                m_indices[i++] = topRight;
                m_indices[i++] = topLeft;
                m_indices[i++] = nbVertices - 2;
            }

            if (iRing == m_nbRings - 1) {
                m_indices[i++] = topLeft;
                m_indices[i++] = topRight;
                m_indices[i++] = nbVertices - 1;
            }

            if (iRing != m_nbRings - 1) {
                int bottomLeft = topLeft + m_nbSlices;

                m_indices[i++] = topLeft;
                m_indices[i++] = topRight;
                m_indices[i++] = bottomLeft;

                m_indices[i++] = bottomLeft;
                m_indices[i++] = topRight;
                m_indices[i++] = topRight + m_nbSlices;
            }
        }
    }

    assert(i == nbTriangle * 3);
    //  glDeleteBuffers(1, &_vbo);
    //  glDeleteBuffers(1, &_nbo);
    //  glDeleteBuffers(1, &_ebo);
    assert(m_vertices.size() == m_normals.size());
    assert(m_indices.size() == 3 * nbTriangle);

    m_nbIndices = 3 * nbTriangle;

    //   1. Generate geometry buffers
    uint m_vbo;
    m_fun->glGenBuffers(1, &m_vbo);
    uint m_nbo;
    m_fun->glGenBuffers(1, &m_nbo);
    uint m_ebo;
    m_fun->glGenBuffers(1, &m_ebo);
    m_fun->glGenVertexArrays(1, &m_vao);
    // 2. Bind Vertex Array Object
    m_fun->glBindVertexArray(m_vao);
    // 3. Copy our vertices array in a buffer for OpenGL to use
    //    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    //    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(GLfloat),
    //        m_vertices.data(), GL_DYNAMIC_DRAW);
    //    // 4. Then set our vertex attributes pointers
    //    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
    //        (GLvoid*)0);
    //    glEnableVertexAttribArray(0);
    //    // 5. Copy our normals array in a buffer for OpenGL to use
    //    glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
    //    glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(GLfloat),
    //        m_normals.data(), GL_DYNAMIC_DRAW);
    //    // 6. Copy our vertices array in a buffer for OpenGL to use
    //    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
    //        (GLvoid*)0);
    //    glEnableVertexAttribArray(1);
    //    // 7. Copy our index array in a element buffer for OpenGL to use
    //    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    //    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLfloat),
    //        m_indices.data(), GL_DYNAMIC_DRAW);
    //    // 6. Unbind the VAO
    //    glBindVertexArray(0);

    //  float radius = 1;

    // --------------------------- RESENT DATA TO BUFFER ------------------------
    m_fun->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    m_fun->glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3),
        m_vertices.data(), GL_STATIC_DRAW);
    // 4. Then set our vertex attributes pointers
      m_fun->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                            (GLvoid *)0);
      m_fun->glEnableVertexAttribArray(0);
    // 5. Copy our normals array in a buffer for OpenGL to use
    m_fun->glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
    m_fun->glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(glm::vec3),
        m_normals.data(), GL_STATIC_DRAW);
    // 6. Copy our vertices array in a buffer for OpenGL to use
      m_fun->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                            (GLvoid *)0);
      m_fun->glEnableVertexAttribArray(1);
    // 7. Copy our index array in a element buffer for OpenGL to use
    m_fun->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    m_fun->glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLfloat),
        m_indices.data(), GL_STATIC_DRAW);

    m_fun->glBindVertexArray(0);
}


//UvSphereGeometry::~UvSphereGeometry()
//{
//    glDeleteBuffers(1, &m_vbo);
//    glDeleteBuffers(1, &m_nbo);
//    glDeleteBuffers(1, &m_ebo);
//    glDeleteVertexArrays(1, &m_vao);
//}

//void UvSphereGeometry::draw()
//void UvSphereGeometry::draw(const glm::vec3 &position, float radius)
void UvSphereGeometry::draw(const Shader &shader, const glm::vec3 &position, float radius)
{
    Q_ASSERT(m_fun != nullptr);

//    glm::mat4 model(1.0f);
//    model = glm::scale(model, glm::vec3(radius));
//    model = glm::translate(model, position);
//    shader.setMat4("model", model);

    m_fun->glBindVertexArray(m_vao);
    m_fun->glDrawElements(GL_TRIANGLES, m_nbIndices, GL_UNSIGNED_INT, nullptr);
    m_fun->glBindVertexArray(0);
}
