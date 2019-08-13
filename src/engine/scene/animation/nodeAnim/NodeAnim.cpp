#include "NodeAnim.h"

#include <assimp/Assimp.h>

NodeAnim::NodeAnim(const aiNodeAnim* ai_nodeAnim)
{
    m_nodeName = ai_nodeAnim->mNodeName.C_Str();

    for (uint i = 0; i < ai_nodeAnim->mNumPositionKeys; ++i) {
        const aiVectorKey& ai_positionKey = ai_nodeAnim->mPositionKeys[i];

        //        glm::vec3 v(aiVec3ToGlm(ai_positionKey.mValue));
        m_positionKeys.emplace_back(ai_positionKey.mTime, aiVec3ToGlm(ai_positionKey.mValue));
    }

    for (uint i = 0; i < ai_nodeAnim->mNumRotationKeys; ++i) {
        const aiQuatKey& ai_rotationKey = ai_nodeAnim->mRotationKeys[i];

        m_rotationKeys.emplace_back(ai_rotationKey.mTime, aiQuatToGlm(ai_rotationKey.mValue));
    }

    for (uint i = 0; i < ai_nodeAnim->mNumScalingKeys; ++i) {
        const aiVectorKey& ai_scaleKey = ai_nodeAnim->mScalingKeys[i];

        m_scalingKeys.emplace_back(ai_scaleKey.mTime, aiVec3ToGlm(ai_scaleKey.mValue));
    }
}

void NodeAnim::buildItemModel(QStandardItem* parent) const
{
    QString str;
    for (const auto & pair : m_positionKeys) {
        str += QString::number(pair.first) + " ";
    }
    QStandardItem* item = new QStandardItem(QString("'") + m_nodeName.c_str() + "'  nbPositionKeys:" + QString::number(m_positionKeys.size()) + "  nbRotationKeys:" + QString::number(m_rotationKeys.size()) + "  nbScaleKeys:" + QString::number(m_scalingKeys.size()) + "\n" + str);
    parent->appendRow(item);
}
