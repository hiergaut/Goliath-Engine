#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <glm/glm.hpp>
//#include <vector>

#include "geometry/CubeGeometry.h"

#include <opengl/rayTracer/Ray.h>

class BoundingBox // AABB
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
    float radius() const;

    void draw(const Shader &shader) const;

    bool intersect(const Ray & ray) const;

//    std::vector<glm::vec3> corners(glm::mat4 basis) const;

private:
//    glm::vec3 m_min;
//    glm::vec3 m_max;
    glm::vec3 m_bounds[2];

    const static CubeGeometry * m_cube;
//    std::vector<glm::vec3> m_vertices;

};

#endif // BOUNDINGBOX_H
