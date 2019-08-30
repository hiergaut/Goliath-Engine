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
    glm::mat4 m_transformation = glm::mat4(1.0f);
    mutable QStandardItem * m_itemTransformation = nullptr;

public:
    Node(const aiNode * ai_node, Meshes *meshes, Animations *animations);
    Node(std::ifstream & file, Meshes *meshes, Animations *animations);
    void buildItemModel(QStandardItem * parent) const;
//    Node(const Node & node);
//    ~Node();
//    void prepareHierarchy(glm::mat4 & model) const;
//    void prepareHierarchy(glm::mat4 & model, const Animation & animation, double animationTime) const;
    void prepareHierarchy(glm::mat4 model, const Animation *animation = nullptr, double animationTime = 0.0) const;
//    void drawBones(const Shader & shader, glm::mat4 model, const Animation *animation = nullptr, double animationTime = 0.0) const;
    void drawHierarchy(const BoneGeometry &boneGeometry, const glm::mat4 & modelMatrix) const;

    uint recurseNbBones() const;
    uint recurseNbNodes() const;
    uint recurseNbBonesVertex() const;

    void onClick() const;
    void save(std::ofstream & file) const;

    void updateReferences(Meshes *meshes, Animations *animations);

//public:
//    std::string name() const;
    //    int numChildren() const;
private:
    Meshes * m_meshes;
    Animations * m_animations;
//    const Bone * m_bone = nullptr;
//    uint iBone = -1;
    bool m_isBone = false;
    std::pair<uint, uint> m_iBone;

//    std::vector<const Animation*> m_animations; // only skeleton root
    std::vector<uint> m_iAnimations;
    uint m_nbNodes = 0; // only root
    uint m_nbBones = 0; // only root
    uint m_nbBonesVertex = 0; // only root
//    const Node * m_root;
//    uint m_nbNodeAnim;
//    std::vector<const NodeAnim*> m_nodeAnims;
//    std::map<std::string, const NodeAnim*> m_nodeAnims;
    std::map<std::string, std::pair<uint, uint>> m_nodeAnims;

    std::vector<Node> m_children;

//    BoneGeometry m_boneGeometry;

//    UvSphereGeometry m_sphere;
//    Mesh * mMesh;
//    std::vector<const Mesh*> m_meshes;
    std::vector<uint> m_iMeshes;
    const std::string m_name;
//    uint m_numChildren = 0;
//    uint m_numMeshes = 0;

    mutable glm::mat4 m_recurseModel; // computed


};

#endif // NODE_H
