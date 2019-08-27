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
    std::string m_skeletonName;
    std::string m_name;
    double m_duration;
    double m_ticksPerSecond;
    std::vector<NodeAnim> m_channels;

public:
    Animation(const aiAnimation * ai_animation);
    Animation(std::ifstream & file);

    void buildItemModel(QStandardItem * parent) const;
    void onClick() const;

    void save(std::ofstream & file) const;

private:
    std::vector<MeshAnim> m_meshChannels;


};

using Animations = std::vector<Animation>;

#endif // ANIMATION_H
