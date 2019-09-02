#include "Bone.h"

#include <assimp/Assimp.h>
#include <session/Session.h>

Bone::Bone(const aiBone* ai_bone, const std::vector<uint>& indices)
    : m_name(ai_bone->mName.C_Str())
    , m_indices(indices)
{

    //    for (aiVertexWeight * ai_vertexWeight : ai_bone->mWeights) {
    for (uint i = 0; i < ai_bone->mNumWeights; ++i) {
        const aiVertexWeight& ai_vertexWeight = ai_bone->mWeights[i];

        m_weights.emplace_back(ai_vertexWeight.mVertexId, ai_vertexWeight.mWeight);
    }
    m_offsetMatrix = aiMatrix4x4ToGlm(ai_bone->mOffsetMatrix);
}

Bone::Bone(std::ifstream& file, const std::vector<uint>& indices)
    : m_indices(indices)
{
    Session::load(m_name, file);
    Session::load(m_weights, file);
    Session::load(m_offsetMatrix, file);

    Session::load(m_transform, file);
}

Bone::~Bone()
{
    std::cout << "\033[35m";
    std::cout << "[BONE] '" << m_name << "' deleted " << this << std::endl;
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

void Bone::save(std::ofstream& file) const
{
    Session::save(m_name, file);
    Session::save(m_weights, file);
    Session::save(m_offsetMatrix, file);

    Session::save(m_transform, file);
}

void Bone::setupTriangles()
{
    Q_ASSERT(m_indices.size() % 3 == 0);
    Q_ASSERT(m_iTriangles.empty());

    for (const auto& pair : m_weights) {
        const uint iVertex = pair.first;

        for (uint i = 0; i < m_indices.size() / 3; ++i) {
            uint i3 = i * 3;
            uint v0 = m_indices[i3];
            uint v1 = m_indices[i3 + 1];
            uint v2 = m_indices[i3 + 2];

            if (iVertex == v0 || iVertex == v1 || iVertex == v2) {
                m_iTriangles.insert(i);
            }
        }
    }
}

//glm::vec3 Bone::min() const
//{
//    glm::vec3 m;
////    glm::vec3 diag = m_box.m_max - m_box.m_min;
//    for (glm::vec3 corner : m_box.corners()) {
//        glm::vec3 pos = glm::vec4(corner, 0.0) * m_transform;

//    }

//}

//glm::vec3 Bone::max() const
//{

//}
