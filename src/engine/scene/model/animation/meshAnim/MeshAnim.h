#ifndef MESHANIM_H
#define MESHANIM_H

#include <assimp/scene.h>
#include <vector>
#include <QStandardItem>

class MeshAnim
{
public:
    MeshAnim(const aiMeshAnim * ai_meshAnim);
    MeshAnim(std::ifstream & file);
    void buildItemModel(QStandardItem * parent) const;

    void save(std::ofstream & file) const;

private:
    std::string m_name;
    std::vector<std::pair<double, uint>> m_meshKeys;
};

#endif // MESHANIM_H
