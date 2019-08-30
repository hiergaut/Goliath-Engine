#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <glm/glm.hpp>
//#include <vector>

#include "geometry/CubeGeometry.h"

class BoundingBox
{
public:
    BoundingBox();

    void clear();
    void operator <<(const glm::vec3 & position);
    glm::vec3 center() const;

    void draw(glm::mat4 modelMatrix, const Shader &shader) const;

private:
    glm::vec3 m_min;
    glm::vec3 m_max;

//    std::vector<glm::vec3> m_vertices;
    CubeGeometry m_cube;

};

#endif // BOUNDINGBOX_H
