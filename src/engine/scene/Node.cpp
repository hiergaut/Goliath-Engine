#include "Node.h"

#include <assimp/Assimp.h>

Node::Node(const aiNode * ai_node, const Meshes & meshes)
    : m_meshes(meshes)
    , m_name(ai_node->mName.C_Str())
//    , m_sphere(0.001)
{
    // process each mesh located at the current node
    m_iMeshes.clear();
    for (unsigned int i = 0; i < ai_node->mNumMeshes; i++) {
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
        m_children.emplace_back(ai_node->mChildren[i], m_meshes);
//        this->m_children.push_back(son);
//        this->m_children.push_back(assimpProcessNode(ai_node->mChildren[i], scene, depth));
    }
    Q_ASSERT(this->m_children.size() == ai_node->mNumChildren);

    this->m_transformation = aiMatrix4x4ToGlm(ai_node->mTransformation);

}

void Node::buildItemModel(QStandardItem *parent) const
{
    QStandardItem* item = new QStandardItem(QIcon(":/icons/node.png"), "'" + QString(m_name.c_str()) + "'  " + QString::number(m_children.size()));
    parent->appendRow(item);


    mat4BuildItemModel(m_transformation, item);

    for (ulong i = 0; i < m_iMeshes.size(); ++i) {
        //        QStandardItem * item2 = new QStandardItem("mesh:" + QString::number(node->m_meshes[i]) + ", " + m_meshes[node->m_meshes[i]]);
        //        QStandardItem * item2 = new QStandardItem(QString::number(node->m_meshes[i]) + "  " + m_meshes[node->m_meshes[i]]);

        Q_ASSERT(m_iMeshes[i] < m_meshes.size());
        //        Q_ASSERT(node->m_numMeshes == node->m_iMeshes.size());
        const Mesh& mesh = m_meshes[m_iMeshes[i]];
//        modelRecurseMesh(mesh, item);
        mesh.buildItemModel(item);
        //        QStandardItem * item2 = new QStandardItem("mesh : " + QString::number(node->m_meshes[i]));
        //        item->appendRow(item2);
    }

    //    std::cout << "node nbchildren : " << node->m_numChildren << std::endl;
    for (int i = 0; i < m_children.size(); ++i) {
//        modelRecurseNode(m_children[i], item);
        m_children[i].buildItemModel(item);
    }

    //    parent->appendRow(new QStandardItem(str));

}

void Node::draw(const Shader &shader, glm::mat4 model) const
{
//    shader.setMat4("model", model);
//    shader.setMat4("model", m_transformation);
//    model = glm::translate(model, glm::vec3(1, 1, 1));
//    glm::vec3 pos = model[3];

    model = model * m_transformation;

    shader.setMat4("model", model);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    for (uint i = 0; i <m_iMeshes.size(); ++i) {
        const Mesh & mesh = m_meshes[m_iMeshes[i]];

        mesh.draw(shader);
    }
//    m_boneGeometry.draw(model, shader, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0.1));

//    m_sphere.draw();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    for (const Node & node : m_children) {
//        node.draw(shader, m_transformation * model);
        glm::vec3 childPos = glm::vec3(node.m_transformation[3]);
        m_boneGeometry.draw(model, shader, glm::vec3(0), childPos);


        node.draw(shader, model);
    }

}
