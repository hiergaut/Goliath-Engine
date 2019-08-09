#include "MeshAnim.h"

MeshAnim::MeshAnim(const aiMeshAnim* ai_meshAnim)
{
    m_name = ai_meshAnim->mName.C_Str();
}

void MeshAnim::buildItemModel(QStandardItem* parent) const
{

    QStandardItem* item = new QStandardItem(QString(m_name.c_str()) + "  nbMeshKeys:" + QString::number(m_meshKeys.size()));
    parent->appendRow(item);
}
