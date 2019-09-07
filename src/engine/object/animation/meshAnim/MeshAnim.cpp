#include "MeshAnim.h"
#include <session/Session.h>

MeshAnim::MeshAnim(const aiMeshAnim* ai_meshAnim)
{
    m_name = ai_meshAnim->mName.C_Str();
}

MeshAnim::MeshAnim(std::ifstream &file)
{
    Session::load(m_name, file);
    Session::load(m_meshKeys, file);
}

void MeshAnim::buildItemModel(QStandardItem* parent) const
{

    QStandardItem* item = new QStandardItem(QString(m_name.c_str()) + "  nbMeshKeys:" + QString::number(m_meshKeys.size()));
    parent->appendRow(item);
}

void MeshAnim::save(std::ofstream &file) const
{
    Session::save(m_name, file);
    Session::save(m_meshKeys, file);
}
