#include "Bone.h"

#include <assimp/Assimp.h>

Bone::Bone(const aiBone* ai_bone)
    : m_name(ai_bone->mName.C_Str())
{

    //    for (aiVertexWeight * ai_vertexWeight : ai_bone->mWeights) {
    for (uint i = 0; i < ai_bone->mNumWeights; ++i) {
        const aiVertexWeight& ai_vertexWeight = ai_bone->mWeights[i];

        m_weights.emplace_back(ai_vertexWeight.mVertexId, ai_vertexWeight.mWeight);
    }
    m_offsetMatrix = aiMatrix4x4ToGlm(ai_bone->mOffsetMatrix);
}

Bone::~Bone()
{
    std::cout << "\033[31m";
    std::cout << "[BONE] '" << m_name << "' destruct " << this << std::endl;
    std::cout << "\033[0m";
}

void Bone::buildItemModel(QStandardItem* parent) const
{
    QStandardItem* item = new QStandardItem(QIcon(":/icons/vertex.png"), QString("'") + m_name.c_str() + "'  weights:" + QString::number(m_weights.size()));
    parent->appendRow(item);

//    QStandardItem * item2 = new QStandardItem("offsetMatrix");
//    item->appendRow(item2);

//    mat4BuildItemModel(m_offsetMatrix, item);

//    for (const auto & pair : m_weights) {

//    for (const auto & pair : m_weights) {
//        QStandardItem * item3 = new QStandardItem(QString("vertexId:" +QString::number(pair.first) + "  weight:" + QString::number(pair.second)));
//        item->appendRow(item3);
//    }
//    }
}
