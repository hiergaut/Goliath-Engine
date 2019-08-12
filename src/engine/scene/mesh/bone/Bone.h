#ifndef BONE_H
#define BONE_H

#include <iostream>
#include <assimp/scene.h>
#include <vector>
#include <glm/glm.hpp>
#include <QStandardItem>

class Bone
{
public:
    std::string m_name;
    std::vector<std::pair<uint, float>> m_weights;
    glm::mat4 m_offsetMatrix;

    mutable glm::mat4 m_transform;

public:
    Bone(const aiBone * ai_bone);
    ~Bone();

    void buildItemModel(QStandardItem * parent) const;

private:

};

#endif // BONE_H
