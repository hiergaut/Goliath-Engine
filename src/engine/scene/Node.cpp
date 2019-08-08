#include "Node.h"

//std::string Node::name() const
//{
//    return m_name;
//}
#include <assimp/Assimp.h>

//int Node::numChildren() const
//{
//    return m_numChildren;
//}

Node::Node(const aiNode * ai_node)
    : m_name(ai_node->mName.C_Str())
{
//    std::cout << "fuck" << std::endl;

//    m_children.clear();
//    Node* node = new Node(ai_node);

    //            for (int i = 0; i < depth; ++i) {
    //                std::cout << "\t";
    //            }
    //            std::cout << "node: " << node->mName.C_Str();
    //            std::cout << ", numMeshes: " << node->mNumMeshes;
    //            std::cout << ", numChildren: " << node->mNumChildren;
    //            std::cout << std::endl;

    //    newNode->m_numMeshes = node->mNumMeshes;
    //    newNode->m_iMeshes.resize(newNode->m_numMeshes);

    // process each mesh located at the current node
    m_iMeshes.clear();
    for (unsigned int i = 0; i < ai_node->mNumMeshes; i++) {
        // the node object only contains indices to index the actual objects in the scene.
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        //        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        //        newNode->m_meshes.push_back(1);
        //        m_meshes.push_back(assimpProcessMesh(mesh, scene, depth + 1));

        //        newNode->m_meshes[i] = m_meshes.size() - 1;
        //        node->m_iMeshes[i] = ai_node->mMeshes[i];
//        Q_ASSERT(0 <= ai_node->mMeshes[i] && ai_node->mMeshes[i] < m_meshes.size());
        //        auto iMeshes = ai_node->mMeshes[i];
//        this->m_iMeshes.push_back(ai_node->mMeshes[i]);
        m_iMeshes.emplace_back(ai_node->mMeshes[i]);
        //        newNode->m_meshes.push_back(&m_meshes.back());
        //        newNode->m_transformation = this->mTransformation
    }
    Q_ASSERT(this->m_iMeshes.size() == ai_node->mNumMeshes);
    // after we've processed all of the m_meshes (if any) we then recursively process each of the children nodes
    //    newNode->m_numChildren = ai_node->mNumChildren;
    //    newNode->m_children.resize(newNode->m_numChildren);

    m_children.clear();
    for (uint i = 0; i < ai_node->mNumChildren; i++) {
        //        newNode->m_children[i] = assimpProcessNode(this->mChildren[i], scene, depth + 1);
        //        newNode->m_children[i] = assimpProcessNode(ai_node->mChildren[i]);
//        const Node * son = assimpProcessNode(ai_node->mChildren[i], scene, depth);

//        m_children.push_back(Node(ai_node->mChildren[i]));
        m_children.emplace_back(ai_node->mChildren[i]);
//        this->m_children.push_back(son);
//        this->m_children.push_back(assimpProcessNode(ai_node->mChildren[i], scene, depth));
    }
    Q_ASSERT(this->m_children.size() == ai_node->mNumChildren);

    this->m_transformation = aiMatrix4x4ToGlm(ai_node->mTransformation);

}

//Node::Node(const Node &node)
//    : m_children(std::move(node.m_children))
//{
////    m_children = std::move(node.m_children);

//}

//Node::~Node()
//{
//    for (Node * node : m_children) {
//        delete node;
//    }

//}
//    std::cout << "assimpProcessNode " << this << " " << &this->m_iMeshes[0] << " " << node->m_iMeshes.size() << " " << &node->m_children[0] << " " << node->m_children.size() << std::endl;
//    std::cout << "assimpProcessNode " << this << " " << &this->m_iMeshes << " " << this->m_iMeshes.size() << " " << &this->m_children << " " << this->m_children.size() << std::endl;
//    for (uint i =0; i <this->m_iMeshes.size(); ++i) {
//        std::cout << "mesh " << &this->m_iMeshes[i] << " " << this->m_iMeshes[i] << std::endl;
//    }
//    for  (uint i =0; i <this->m_children.size(); ++i) {
//        std::cout << "child " << &this->m_children[i] << std::endl;
//    }
//    Q_ASSERT(this->m_children.size() == 0);
//    return this;
//Node* Model::assimpProcessNode(aiNode* this, const aiScene* scene, int depth)
//{

//    Q_ASSERT(this->mName.length != 0);
    //    qDebug() << node->mName.C_Str();
//    Node* newNode = new Node(node->mName.C_Str());
    //    Node* newNode = new Node("fuck");
    //    std::cout << "newnode : " << newNode << std::endl;

    //            for (int i = 0; i < depth; ++i) {
    //                std::cout << "\t";
//    m_numChildren = ai_node->mNumChildren;
////    m_children.resize(m_numChildren);
//    for (unsigned int i = 0; i < m_numChildren; i++) {
////        m_children[i] = assimpProcessNode(ai_node->mChildren[i], scene);
//        m_children.push_back(Node(ai_node->mChildren[i]));
////        m_children[i] = Node(ai_node->mChildren[i]);
////        qDebug() << "push back";
//    }
//    Q_ASSERT(m_numChildren == m_children.size());

//    //            }
//    //            std::cout << "node: " << node->mName.C_Str();
//    //            std::cout << ", numMeshes: " << node->mNumMeshes;
//    //            std::cout << ", numChildren: " << node->mNumChildren;
//    //            std::cout << std::endl;

//    m_numMeshes = ai_node->mNumMeshes;
////    m_meshes.resize(m_numMeshes);
//    // process each mesh located at the current node
//    for (unsigned int i = 0; i < m_numMeshes; i++) {
//        // the node object only contains indices to index the actual objects in the scene.
//        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
//        //        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
//        //        newNode->m_meshes.push_back(1);
//        //        m_meshes.push_back(assimpProcessMesh(mesh, scene, depth + 1));

//        //        newNode->m_meshes[i] = m_meshes.size() - 1;
////        m_meshes[i] = ai_node->mMeshes[i];
//        Q_ASSERT(ai_node->mMeshes[i] < 100);
//        m_iMeshes.push_back(ai_node->mMeshes[i]);
//        //        newNode->m_meshes.push_back(&m_meshes.back());
//        //        newNode->m_transformation = node->mTransformation
//    }
//    // after we've processed all of the m_meshes (if any) we then recursively process each of the children nodes

//    m_transformation = aiMatrix4x4ToGlm(ai_node->mTransformation);

//    return newNode;
//}

