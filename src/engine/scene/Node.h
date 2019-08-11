#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
//#include "mesh.h"
#include "mesh/mesh.h"

#include <opengl/geometry/uvSphereGeometry.h>
#include <opengl/geometry/boneGeometry.h>


class Node
{
public:

public:
    Node(const aiNode * ai_node, const Meshes & meshes);
    void buildItemModel(QStandardItem * parent) const;
//    Node(const Node & node);
//    ~Node();
    void draw(const Shader & shader, glm::mat4 model) const;

//public:
//    std::string name() const;
//    int numChildren() const;
private:
    const Meshes & m_meshes;

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
