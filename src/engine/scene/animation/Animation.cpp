#include "Animation.h"

//#include <QObject>
#include <assert.h>

Animation::Animation(const aiAnimation* ai_animation)
//    : m_name(ai_animation->mName.C_Str())
{
    std::string str(ai_animation->mName.C_Str());

    m_name = str.substr(str.find_first_of('|') +1);
    m_skeletonName = str.substr(0, str.find_first_of('|'));


    for (uint i =0; i<ai_animation->mNumChannels; ++i) {
        const aiNodeAnim * ai_nodeAnim = ai_animation->mChannels[i];
        m_channels.emplace_back(ai_nodeAnim);
    }

    m_duration = ai_animation->mDuration;

    for (uint i =0; i <ai_animation->mNumMeshChannels; ++i) {
        const aiMeshAnim * ai_meshAnim = ai_animation->mMeshChannels[i];
        m_meshChannels.emplace_back(ai_meshAnim);
    }

    m_ticksPerSecond = ai_animation->mTicksPerSecond;

//    Q_ASSERT(ai_animation->mNumMorphMeshChannels == 0);
    assert(ai_animation->mNumMorphMeshChannels == 0);
}

void Animation::buildItemModel(QStandardItem *parent) const
{
//        QStandardItem* item = new QStandardItem(QIcon(":/icons/animation.png"), QString("'") + m_name.c_str() + "'  skeleton:'" + m_skeletonName.c_str() + "'  duration:" + QString::number(m_duration) + "  ticksPerSecond:" + QString::number(m_ticksPerSecond));
        QStandardItem* item = new QStandardItem(QIcon(":/icons/animation.png"), QString("'") + m_name.c_str() + "'  duration:" + QString::number(m_duration) + "  ticksPerSecond:" + QString::number(m_ticksPerSecond) + "  nodeAnim:" + QString::number(m_channels.size()));
        parent->appendRow(item);


//        QStandardItem* item2 = new QStandardItem("nodeAnim  " + QString::number(m_channels.size()));
////        parent->appendRow(item);
//        item->appendRow(item2);
//        for (const NodeAnim & nodeAnim : m_channels) {
//            nodeAnim.buildItemModel(item2);
//        }

//        item2 = new QStandardItem("meshAnim  " + QString::number(m_meshChannels.size()));
//        item->appendRow(item2);
//        for (const MeshAnim & meshAnim : m_meshChannels) {
//            meshAnim.buildItemModel(item2);
//        }


}


