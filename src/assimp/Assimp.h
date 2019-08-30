//#pragma once

#ifndef ASSIMP_H
#define ASSIMP_H

#include <glm/glm.hpp>
#include <assimp/scene.h>
#include <glm/gtc/quaternion.hpp>

glm::mat4 aiMatrix4x4ToGlm(const aiMatrix4x4& from);
glm::mat3 aiMatrix3x3ToGlm(const aiMatrix3x3& from);

glm::vec3 aiVec3ToGlm(const aiVector3D& from);
glm::vec3 aiColor3ToGlm(const aiColor3D& from);
glm::vec2 aiVec2ToGlm(const aiVector2D& from);

glm::quat aiQuatToGlm(const aiQuaternion & from);


#include <QStandardItem>
void mat4BuildItemModel(const glm::mat4 matrix, QStandardItem* item);


#endif // ASSIMP_H
