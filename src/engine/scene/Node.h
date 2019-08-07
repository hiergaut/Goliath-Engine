#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
//#include "mesh.h"
#include "mesh/mesh.h"


class Node
{
public:


    std::vector<Node*> m_children;
//    Mesh * mMesh;
//    std::vector<const Mesh*> m_meshes;
    std::vector<uint> m_iMeshes;
    const std::string m_name;
    uint m_numChildren = 0;
    uint m_numMeshes = 0;

    glm::mat4 m_transformation;

public:
    Node(const aiNode * ai_node);
//    ~Node();

//public:
//    std::string name() const;
//    int numChildren() const;
};

#endif // NODE_H
