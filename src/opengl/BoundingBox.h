#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <glm/glm.hpp>
//#include <vector>

#include "geometry/CubeGeometry.h"

class BoundingBox
{
public:
//    const static CubeGeometry m_cube;


public:
    BoundingBox();

    void clear();
    void operator <<(const glm::vec3 & position);
    void operator <<(const BoundingBox box);

//    BoundingBox operator *(glm::mat4 mat) const;

    glm::vec3 center() const;

    void draw(glm::mat4 modelMatrix, const Shader &shader) const;

//    std::vector<glm::vec3> corners(glm::mat4 basis) const;

private:
    glm::vec3 m_min;
    glm::vec3 m_max;

    const static CubeGeometry * m_cube;
//    std::vector<glm::vec3> m_vertices;

};

#endif // BOUNDINGBOX_H
