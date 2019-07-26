#ifndef GRID_H
#define GRID_H

#include "version.h"
#include <glm/glm.hpp>
#include <vector>

namespace {
    struct vertex {
        glm::vec3 Position;
    };
}

//struct Line {
//    vertex a;
//    vertex b;
//};

class Grid {
public:

//    Grid() {}
    Grid()
    {
        //        Vertex a;
        //        Vertex b;
        vertex v;
//        Line l;
        for (int i = -10; i < 10; ++i) {
            //            for (int j = -10; j < 10; ++j) {
            v.Position = glm::vec3(i, -10, 0);
            m_vertices.push_back(v);
            v.Position = glm::vec3(i, 10, 0);
            m_vertices.push_back(v);
            //            }
            v.Position = glm::vec3(-10, i, 0);
            m_vertices.push_back(v);
            v.Position = glm::vec3(10, i, 0);
            m_vertices.push_back(v);
        }
        //        fun = QOpenGLContext
        fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
        setup();
    }

    void draw()
    {
        fun->glBindVertexArray(m_vao);
        fun->glDrawArrays(GL_LINES, 0, m_vertices.size());
        fun->glBindVertexArray(0);
    }

private:
    void setup()
    {
        //        unsigned int vbo;
        fun->glGenVertexArrays(1, &m_vao);
        fun->glGenBuffers(1, &m_vbo);

        fun->glBindVertexArray(m_vao);
        fun->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        fun->glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(vertex), &m_vertices[0], GL_STATIC_DRAW);

        fun->glEnableVertexAttribArray(0);
        fun->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);

        fun->glBindVertexArray(0);
    }

private:
    unsigned int m_vbo;
    unsigned int m_vao;
    //    std::vector<float> m_vertices;
//    std::vector<Line> m_lines;
    std::vector<vertex> m_vertices;
    QOpenGLFunctionsCore* fun;
};

#endif // GRID_H
