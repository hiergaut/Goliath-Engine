#ifndef BONE_H
#define BONE_H

#include <iostream>
#include <assimp/scene.h>
#include <vector>
#include <glm/glm.hpp>
#include <QStandardItem>

#include <opengl/BoundingBox.h>

class Bone
{
public:
    std::string m_name;
    std::vector<std::pair<uint, float>> m_weights;
    glm::mat4 m_offsetMatrix;

    mutable glm::mat4 m_transform;
    mutable glm::mat4 m_recurseModel;


    mutable BoundingBox m_box;


public:
    Bone(const aiBone * ai_bone);
    Bone(std::ifstream & file);

    Bone(const Bone &) = delete;
    Bone(Bone &&) noexcept = default;

    ~Bone();

    void buildItemModel(QStandardItem * parent) const;

    void save(std::ofstream & file) const;

//    glm::vec3 min() const;
//    glm::vec3 max() const;

private:
//    Meshes * m_meshes;

};

#endif // BONE_H
