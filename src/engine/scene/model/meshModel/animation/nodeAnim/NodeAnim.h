#ifndef NODEANIM_H
#define NODEANIM_H

#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>
#include <QStandardItem>

class NodeAnim
{
public:
    std::string m_nodeName;
    std::vector<std::pair<double, glm::vec3>> m_positionKeys;
    std::vector<std::pair<double, glm::quat>> m_rotationKeys;
    std::vector<std::pair<double, glm::vec3>> m_scalingKeys;

public:
    NodeAnim(const aiNodeAnim * ai_nodeAnim);
    NodeAnim(std::ifstream & file);

    void buildItemModel(QStandardItem * parent) const;

    void save(std::ofstream & file) const;
};

#endif // NODEANIM_H
