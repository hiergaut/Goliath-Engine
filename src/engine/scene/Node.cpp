#include "Node.h"

#include <assimp/Assimp.h>

#include <glm/common.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <gui/editor/outliner/ItemModelPackage.h>

#include <gui/editor/timeline/FormTimeline.h>

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
                //                m_nodeAnims.emplace_back(&nodeAnim);
                m_nodeAnims.insert(std::make_pair(animation.m_name, &nodeAnim));
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

    //    if (m_iMeshes.size() > 0) {
    //        m_transformation = glm::mat4(1);
    ////        m_transformation = glm::inverse(m_transformation);
    //    }

    if (m_animations.size() > 0) {
        m_nbNodes = recurseNbNodes();
        m_nbBones = recurseNbBones();
        m_nbBonesVertex = recurseNbBonesVertex();

        //        m_transformation = glm::mat4(1);
        //        m_transformation = glm::inverse(m_transformation);
    }
}

void Node::buildItemModel(QStandardItem* parent) const
{
    QStandardItem* item;

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

        ItemModelPackage::store(this, *item2);
//        ItemModelPackage::store(*item2);


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
    mat4BuildItemModel(m_transformation, item);

    if (m_nodeAnims.size() > 0) {
        QStandardItem* item2 = new QStandardItem("nodeAnim  " + QString::number(m_nodeAnims.size()));
        //        parent->appendRow(item);
        item->appendRow(item2);
        for (const auto& pair : m_nodeAnims) {
            pair.second->buildItemModel(item2);
        }
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

glm::mat4 interpolatedRotation(const std::vector<std::pair<double, glm::quat>>& rotationKeys, double animationTime)
{
    const uint nbKeys = rotationKeys.size();
    Q_ASSERT(nbKeys > 1);
    uint iRotNext = 1;
    while (iRotNext < nbKeys && rotationKeys[iRotNext].first < animationTime)
        ++iRotNext;
    if (iRotNext == nbKeys) {
        return glm::mat4_cast(rotationKeys[nbKeys -1].second);
    }
    Q_ASSERT(iRotNext < nbKeys);
    Q_ASSERT(iRotNext > 0);

    uint iRot = iRotNext - 1;
    //            std::cout << "iRot " << iRot << std::endl;

    const glm::quat& quat = rotationKeys[iRot].second;
    const glm::quat& quatNext = rotationKeys[iRotNext].second;
    //            const glm::quat& quat = glm::normalize(rotationKeys[iRot].second);
    //            const glm::quat& quatNext = glm::normalize(rotationKeys[iRotNext].second);

    double deltaTime = rotationKeys[iRotNext].first - rotationKeys[iRot].first;
    //            std::cout << "deltaTime " << deltaTime << std::endl;
    double factor = (animationTime - rotationKeys[iRot].first) / deltaTime;
    //            double factor = animationTime / ;
    Q_ASSERT(0.0 <= factor && factor <= 1.0);
    //            std::cout << "factor " << factor << std::endl;
    //            quat = glm::normalize(quat);
    //            quatNext = glm::normalize(quatNext);
    //            glm::quat quatInterpolate = glm::lerp(quat, quatNext, static_cast<float>(factor));
    //            glm::quat quatInterpolate = glm::mix(quat, quatNext, static_cast<float>(factor));
    glm::quat quatInterpolate = glm::slerp(quat, quatNext, static_cast<float>(factor));
    //            quatInterpolate = glm::normalize(quatInterpolate);

    return glm::mat4_cast(quatInterpolate);
}

glm::vec3 interpolatedTranslation(const std::vector<std::pair<double, glm::vec3>>& translationKeys, double animationTime)
{
    const uint nbKeys = translationKeys.size();
    Q_ASSERT(nbKeys > 1);
    uint iTransNext = 1;
    while (iTransNext < nbKeys && translationKeys[iTransNext].first < animationTime)
        ++iTransNext;
    if (iTransNext == nbKeys) {
        return translationKeys[nbKeys - 1].second;
    }
    Q_ASSERT(iTransNext < nbKeys);
    Q_ASSERT(iTransNext > 0);

    uint iTrans = iTransNext - 1;
    //            std::cout << "iTrans " << iRot << std::endl;

    const glm::vec3& trans = translationKeys[iTrans].second;
    const glm::vec3& transNext = translationKeys[iTransNext].second;

    double deltaTime = translationKeys[iTransNext].first - translationKeys[iTrans].first;
    //            std::cout << "deltaTime " << deltaTime << std::endl;
    float factor = (animationTime - translationKeys[iTrans].first) / deltaTime;
    //            double factor = animationTime / ;
    Q_ASSERT(0.0 <= factor && factor <= 1.0);
    //            std::cout << "factor " << factor << std::endl;
    //            glm::vec3 transIntepolate = glm::mix(trans, transNext, static_cast<float>(factor));
    glm::vec3 transIntepolate = trans + factor * (transNext - trans);

    return transIntepolate;
    //            return glm::mat4_cast(quatInterpolate);
}

glm::vec3 interpolatedScale(const std::vector<std::pair<double, glm::vec3>>& scaleKeys, double animationTime)
{
    uint nbKeys = scaleKeys.size();

    Q_ASSERT(nbKeys > 1);
    uint iScaleNext = 1;
    while (iScaleNext < nbKeys && scaleKeys[iScaleNext].first < animationTime)
        ++iScaleNext;
    if (iScaleNext == nbKeys) {
        return scaleKeys[nbKeys - 1].second;
    }
    Q_ASSERT(iScaleNext < nbKeys);
    Q_ASSERT(iScaleNext > 0);

    uint iTrans = iScaleNext - 1;
    //            std::cout << "iTrans " << iRot << std::endl;

    const glm::vec3& scale = scaleKeys[iTrans].second;
    const glm::vec3& scaleNext = scaleKeys[iScaleNext].second;

    double deltaTime = scaleKeys[iScaleNext].first - scaleKeys[iTrans].first;
    //            std::cout << "deltaTime " << deltaTime << std::endl;
    double factor = (animationTime - scaleKeys[iTrans].first) / deltaTime;
    //            double factor = animationTime / ;
    Q_ASSERT(0.0 <= factor && factor <= 1.0);
    //            std::cout << "factor " << factor << std::endl;
    glm::vec3 scaleInterpolate = glm::mix(scale, scaleNext, static_cast<float>(factor));

    return scaleInterpolate;
    //            return glm::mat4_cast(quatInterpolate);
}

void Node::prepareHierarchy(glm::mat4 model, const Animation * animation, double animationTime) const
{
    if (animation == nullptr) {
        m_model = model * m_transformation;

    } else {
        const auto& it = m_nodeAnims.find(animation->m_name);

        if (it != m_nodeAnims.end()) {
            const NodeAnim& nodeAnim = *it->second;
            Q_ASSERT(nodeAnim.m_rotationKeys.size() > 0);

            //            double animationTime = animation->m_duration;

            glm::mat4 transformation(1.0f);
            //        glm::mat4 translation(1.0f);
            //        translation = glm::translate(translation, nodeAnim.m_positionKeys[0].second);
            //            transformation = glm::translate(transformation, nodeAnim.m_positionKeys[0].second);
            transformation = glm::translate(transformation, interpolatedTranslation(nodeAnim.m_positionKeys, animationTime));

            //        glm::mat4 rotation(1.0f);
            //            const auto & rotationKeys = nodeAnim.m_rotationKeys;
            //        transformation = glm::rotate(transformation, nodeAnim.m_rotationKeys[0].second);
            //        transformation =   transformation * glm::mat4_cast(quat);
            //        rotation =   glm::mat4_cast(quat) * rotation;
            //        transformation = glm::mat4_cast(quat) *  transformation;
            //            transformation = transformation * glm::mat4_cast(quat);
            //            transformation = transformation * glm::mat4_cast(quatInterpolate);
            //            transformation = transformation * interpolatedRotation(nodeAnim.m_rotationKeys, animationTime);
            transformation = transformation * interpolatedRotation(nodeAnim.m_rotationKeys, animationTime);

            //        glm::mat4 scale(1.0f);
            //        scale = glm::scale(scale, nodeAnim.m_scalingKeys[0].second);
            //            transformation = glm::scale(transformation, nodeAnim.m_scalingKeys[0].second);
            transformation = glm::scale(transformation, interpolatedScale(nodeAnim.m_scalingKeys, animationTime));

            //        glm::mat4 translation(1.0f);
            //        model = model * translation * rotation * scale;
            m_model = model * transformation;
        } else {
            m_model = model * m_transformation;
        }
    }

    if (m_bone != nullptr) {
        //        m_bone->m_transform = model * m_bone->m_offsetMatrix;
        m_bone->m_transform = m_model * m_bone->m_offsetMatrix;
        //        m_bone->m_transform = m_bone->m_offsetMatrix;
    }

    for (uint iMesh : m_iMeshes) {
        const Mesh& mesh = m_meshes[iMesh];

        mesh.m_transform = m_model;
    }

//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    for (const Node& node : m_children) {
        node.prepareHierarchy(m_model, animation, animationTime);
    }


}

void Node::draw(const BoneGeometry &boneGeometry, const glm::mat4 &modelMatrix) const
{
    glm::mat4 model = modelMatrix * m_model;
    for (const Node& node : m_children) {
        //        node.draw(shader, m_transformation * model);
        glm::vec3 childPos = glm::vec3(node.m_transformation[3]);

        if (m_bone != nullptr) {
            boneGeometry.draw(model, glm::vec3(0), childPos);
        } else {
            //            m_boneGeometry.draw(model, shader, glm::vec3(0), childPos);
            boneGeometry.drawLine(model, glm::vec3(0), childPos);
        }

//        node.draw(shader, model, animation, animationTime);
//        node.prepareHierarchy(m_model, animation, animationTime);
        node.draw(boneGeometry, modelMatrix);
    }

}


//void Node::draw(const Shader& shader, glm::mat4 model, const Animation* animation, double animationTime) const
//{
//}

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

void Node::onClick() const
{
    FormTimeline::setAnimation(nullptr);
}
