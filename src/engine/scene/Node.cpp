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
//Node* Model::assimpProcessNode(aiNode* node, const aiScene* scene, int depth)
//{

//    Q_ASSERT(node->mName.length != 0);
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

}

//Node::~Node()
//{

//}
