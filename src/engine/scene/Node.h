#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
//#include "mesh.h"
#include "mesh/mesh.h"

#include <opengl/geometry/uvSphereGeometry.h>
#include <opengl/geometry/boneGeometry.h>
#include "animation/Animation.h"


class Node
{
public:

public:
    Node(const aiNode * ai_node, const Meshes & meshes, const Animations & animations);
    void buildItemModel(QStandardItem * parent) const;
//    Node(const Node & node);
//    ~Node();
    void draw(const Shader & shader, glm::mat4 model) const;

    uint recurseNbBones() const;
    uint recurseNbNodes() const;
    uint recurseNbBonesVertex() const;

//public:
//    std::string name() const;
//    int numChildren() const;
private:
    const Meshes & m_meshes;
    const Bone * m_bone;
    std::vector<const Animation*> m_animations;
    uint m_nbNodes;
    uint m_nbBones;
    uint m_nbBonesVertex;
//    const Node * m_root;
//    uint m_nbNodeAnim;
    std::vector<const NodeAnim*> m_nodeAnims;

    std::vector<Node> m_children;

    BoneGeometry m_boneGeometry;

//    UvSphereGeometry m_sphere;
//    Mesh * mMesh;
//    std::vector<const Mesh*> m_meshes;
    std::vector<uint> m_iMeshes;
    const std::string m_name;
//    uint m_numChildren = 0;
//    uint m_numMeshes = 0;

    glm::mat4 m_transformation;

};

#endif // NODE_H
