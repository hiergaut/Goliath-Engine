#ifndef ANIMATION_H
#define ANIMATION_H

#include <assimp/scene.h>
#include "nodeAnim/NodeAnim.h"
#include "meshAnim/MeshAnim.h"
#include <vector>
#include <QStandardItem>

class Animation
{

public:
    Animation(const aiAnimation * ai_animation);

    void buildItemModel(QStandardItem * parent) const;

private:
    std::vector<NodeAnim> m_channels;
    double m_duration;
    std::vector<MeshAnim> m_meshChannels;
    std::string m_name;
    double m_ticksPerSecond;

};

#endif // ANIMATION_H
