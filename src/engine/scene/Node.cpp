#include "Node.h"

#include <assimp/Assimp.h>

Node::Node(const aiNode* ai_node, const Meshes& meshes, const Animations& animations)
    : m_meshes(meshes)
    //    , m_root(root)
    //    , m_isRoot(false)
    , m_bone(nullptr)
    , m_name(ai_node->mName.C_Str())
//    , m_sphere(0.001)
{
    //    m_nbNodeAnim = 0;
    for (const Animation& animation : animations) {
        if (m_name == animation.m_skeletonName) {
            m_animations.emplace_back(&animation);
        }

        for (const NodeAnim& nodeAnim : animation.m_channels) {
            if (m_name == nodeAnim.m_nodeName) {
                m_nodeAnims.emplace_back(&nodeAnim);
                //                ++m_nbNodeAnim;
                break;
            }
        }
    }
    Q_ASSERT(m_nodeAnims.size() == 0 || m_nodeAnims.size() == animations.size());

    for (const Mesh& mesh : meshes) {
        for (const Bone& bone : mesh.m_bones) {
            if (bone.m_name == m_name) {
                m_bone = &bone;
            }
        }
    }

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
    this->m_transformation = aiMatrix4x4ToGlm(ai_node->mTransformation);

    m_children.clear();
    for (uint i = 0; i < ai_node->mNumChildren; i++) {
        //        newNode->m_children[i] = assimpProcessNode(this->mChildren[i], scene, depth + 1);
        //        newNode->m_children[i] = assimpProcessNode(ai_node->mChildren[i]);
        //        const Node * son = assimpProcessNode(ai_node->mChildren[i], scene, depth);

        //        m_children.push_back(Node(ai_node->mChildren[i]));
        m_children.emplace_back(ai_node->mChildren[i], m_meshes, animations);
        //        this->m_children.push_back(son);
        //        this->m_children.push_back(assimpProcessNode(ai_node->mChildren[i], scene, depth));
    }
    Q_ASSERT(this->m_children.size() == ai_node->mNumChildren);

    if (m_animations.size() > 0) {
        m_nbNodes = recurseNbNodes();
        m_nbBones = recurseNbBones();
        m_nbBonesVertex = recurseNbBonesVertex();
    }
}

void Node::buildItemModel(QStandardItem* parent) const
{
    QStandardItem* item;
    //    mat4BuildItemModel(m_transformation, item);
    if (m_animations.size() > 0) {
        item = new QStandardItem(QIcon(":/icons/skeleton.png"), "'" + QString(m_name.c_str()) + "'");

        QStandardItem* item2 = new QStandardItem(QIcon(":/icons/animations.png"), "animations  " + QString::number(m_animations.size()));
        item->appendRow(item2);

        for (const Animation* animation : m_animations) {
            animation->buildItemModel(item2);
            //            QStandardItem* item3 = new QStandardItem(QIcon(":/icons/animation.png"), QString("'") + animation->m_name.c_str() + "'  duration:" + QString::number(animation->m_duration) + "  ticksPerSecond:" + QString::number(animation->m_ticksPerSecond));
            //            item2->appendRow(item3);
        }

//        item2 = new QStandardItem("Pose");
        item2 = new QStandardItem(QIcon(":/icons/pose.png"), "Pose '" + QString(m_name.c_str()) + "'  " + QString::number(m_children.size()) + "  " + QString::number(m_nodeAnims.size()) + "  nbNodes:" + QString::number(m_nbNodes) + "  nbBones:" + QString::number(m_nbBones) + "  nbBonesVertex:" + QString::number(m_nbBonesVertex));
        item->appendRow(item2);

        parent->appendRow(item);

        item = item2;
        //        QStandardItem * item3 = new QStandardItem(QString(m_name.c_str()) + "  nbBones")

    } else if (m_bone != nullptr) {
        //        QStandardItem* item2 = new QStandardItem(QString("bone : ") + m_bone->m_name.c_str());
        item = new QStandardItem(QIcon(":/icons/boneVertex.png"), "'" + QString(m_name.c_str()) + "'  " + QString::number(m_children.size()) + "  " + QString::number(m_nodeAnims.size()));

        Q_ASSERT(m_nodeAnims.size() > 0);
        parent->appendRow(item);
        //        item->appendRow(item2);
    } else if (m_nodeAnims.size() > 0) {
        //        QStandardItem* item2 = new QStandardItem(QString("bone : ") + m_bone->m_name.c_str());
        item = new QStandardItem(QIcon(":/icons/bone.png"), "'" + QString(m_name.c_str()) + "'  " + QString::number(m_children.size()) + "  " + QString::number(m_nodeAnims.size()));
        parent->appendRow(item);

        //        item->appendRow(item2);
    } else {
        item = new QStandardItem(QIcon(":/icons/node.png"), "'" + QString(m_name.c_str()) + "'  " + QString::number(m_children.size()) + "  " + QString::number(m_nodeAnims.size()));
        parent->appendRow(item);
    }

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

void Node::draw(const Shader& shader, glm::mat4 model) const
{
    //    shader.setMat4("model", model);
    //    shader.setMat4("model", m_transformation);
    //    model = glm::translate(model, glm::vec3(1, 1, 1));
    //    glm::vec3 pos = model[3];

    model = model * m_transformation;

    if (m_bone != nullptr) {
        m_bone->m_transform = model * m_bone->m_offsetMatrix;
//        m_bone->m_transform = m_bone->m_offsetMatrix;
    }
//        shader.setMat4("model", model);
    //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //    for (uint i = 0; i < m_iMeshes.size(); ++i) {
    //        const Mesh& mesh = m_meshes[m_iMeshes[i]];

    //        mesh.draw(shader);
    //    }

//    if (m_bone != nullptr) {

//    }

    //    m_boneGeometry.draw(model, shader, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0.1));

    //    m_sphere.draw();
//    shader.setBool("isSkeleton", false);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    for (const Node& node : m_children) {
        //        node.draw(shader, m_transformation * model);
        glm::vec3 childPos = glm::vec3(node.m_transformation[3]);

        if (m_bone != nullptr) {
            m_boneGeometry.draw(model, shader, glm::vec3(0), childPos);
        } else {
            m_boneGeometry.drawLine(model, shader, glm::vec3(0), childPos);
        }

        node.draw(shader, model);
    }
}

uint Node::recurseNbBones() const
{
    uint nbBones = (m_nodeAnims.size() > 0) ? 1 : 0;

    for (const Node& children : m_children) {
        nbBones += children.recurseNbBones();
    }
    return nbBones;
}

uint Node::recurseNbNodes() const
{
    uint nbNodes = m_children.size();

    for (const Node& children : m_children) {
        nbNodes += children.recurseNbNodes();
    }
    return nbNodes;
}

uint Node::recurseNbBonesVertex() const
{
    uint nbBones = (m_bone != nullptr) ? 1 : 0;

    for (const Node& children : m_children) {
        nbBones += children.recurseNbBonesVertex();
    }
    return nbBones;
}
