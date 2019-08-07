//#pragma once

#ifndef ASSIMP_H
#define ASSIMP_H

#include <glm/glm.hpp>
#include <assimp/scene.h>

glm::mat4 aiMatrix4x4ToGlm(const aiMatrix4x4& from);
glm::vec3 aiVec3ToGlm(const aiVector3D& from);
glm::vec3 aiColor3ToGlm(const aiColor3D& from);
glm::vec2 aiVec2ToGlm(const aiVector2D& from);



#endif // ASSIMP_H
