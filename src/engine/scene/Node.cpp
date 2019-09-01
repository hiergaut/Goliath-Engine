#include "Node.h"

#include <assimp/Assimp.h>

#include <glm/common.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <gui/editor/outliner/ItemModelPackage.h>

#include <gui/editor/timeline/FormTimeline.h>

Node::Node(const aiNode* ai_node, Meshes* meshes, Animations* animations)
    : m_meshes(meshes)
    , m_animations(animations)
    //    , m_root(root)
    //    , m_isRoot(false)
    //    , m_bone(nullptr)
    , m_name(ai_node->mName.C_Str())
//    , m_sphere(0.001)
{
    //    std::cout << "Node " << ai_node << std::endl;

    //    m_nbNodeAnim = 0;
    for (uint i = 0; i < animations->size(); ++i) {
        //    for (const Animation& animation : animations) {
        const Animation& animation = (*animations)[i];

        if (m_name == animation.m_skeletonName) {
            //            m_animations.emplace_back(&animation);
            m_iAnimations.emplace_back(i);
        }

        //        for (const NodeAnim& nodeAnim : animation.m_channels) {
        for (uint j = 0; j < animation.m_channels.size(); ++j) {
            const NodeAnim& nodeAnim = animation.m_channels[j];

            if (m_name == nodeAnim.m_nodeName) {
                //                m_nodeAnims.emplace_back(&nodeAnim);
                //                m_nodeAnims.insert(std::make_pair(animation.m_name, &nodeAnim));
                m_nodeAnims.insert(std::make_pair(animation.m_name, std::make_pair(i, j)));
                //                ++m_nbNodeAnim;
                break;
            }
        }
    }
    Q_ASSERT(m_nodeAnims.size() == 0 || m_nodeAnims.size() == animations->size());

    //    for (const Mesh& mesh : meshes) {
    for (uint i = 0; i < meshes->size(); ++i) {
        const Mesh& mesh = (*meshes)[i];
        //        for (const Bone& bone : mesh.m_bones) {
        for (uint j = 0; j < mesh.m_bones.size(); ++j) {
            const Bone& bone = mesh.m_bones[j];

            if (bone.m_name == m_name) {
                //                m_bone = &bone;
                m_iBone = std::make_pair(i, j);
                m_isBone = true;
                break;
            }
        }
        if (m_isBone) {
            break;
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

    if (m_iAnimations.size() > 0) {
        m_nbNodes = recurseNbNodes();
        m_nbBones = recurseNbBones();
        m_nbBonesVertex = recurseNbBonesVertex();

        //        m_transformation = glm::mat4(1);
        //        m_transformation = glm::inverse(m_transformation);
    }
}

Node::Node(std::ifstream& file, Meshes* meshes, Animations* animations)
    : m_meshes(meshes)
    , m_animations(animations)
{
    Session::load(m_transformation, file);
    Session::load(m_isBone, file);
    if (m_isBone) {
        Session::load(m_iBone, file);
    }

    Session::load(m_iAnimations, file);
    Session::load(m_nbNodes, file);
    Session::load(m_nbBones, file);
    Session::load(m_nbBonesVertex, file);

    Session::load(m_nodeAnims, file);

    uint size;
    Session::load(size, file);
    for (uint i = 0; i < size; ++i) {
        m_children.emplace_back(file, meshes, animations);
    }

    Session::load(m_iMeshes, file);
    Session::load(const_cast<std::string&>(m_name), file);
    Session::load(m_recurseModel, file);
}

void Node::buildItemModel(QStandardItem* parent) const
{
    QStandardItem* item;

    if (m_iAnimations.size() > 0) {
        item = new QStandardItem(QIcon(":/icons/skeleton.png"), "'" + QString(m_name.c_str()) + "'");

        QStandardItem* item2 = new QStandardItem(QIcon(":/icons/animations.png"), "animations  " + QString::number(m_iAnimations.size()));
        item->appendRow(item2);

        //        for (const Animation* animation : m_animations) {
        for (uint iAnimation : m_iAnimations) {
            const Animation& animation = (*m_animations)[iAnimation];

            animation.buildItemModel(item2);
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

    } else if (m_isBone) {
        //        QStandardItem* item2 = new QStandardItem(QString("bone : ") + m_bone->m_name.c_str());
        const Bone& bone = (*m_meshes)[m_iBone.first].m_bones[m_iBone.second];
        item = new QStandardItem(QIcon(":/icons/boneVertex.png"), "'" + QString(m_name.c_str()) + "'  " + QString::number(m_children.size()) + "  " + QString::number(m_nodeAnims.size()) + "  nbVertex:" + QString::number(bone.m_weights.size()));

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

    //        m_itemTransformation = mat4BuildItemModel(m_transformation, item);
    QStandardItem* item2 = new QStandardItem("transformation");
    m_itemTransformation = new QStandardItem;
    mat4BuildItemModel(m_transformation, m_itemTransformation);
    item2->appendRow(m_itemTransformation);
    item->appendRow(item2);

    //    if (m_nodeAnims.size() > 0) {
    //        QStandardItem* item2 = new QStandardItem("nodeAnim  " + QString::number(m_nodeAnims.size()));
    //        //        parent->appendRow(item);
    //        item->appendRow(item2);
    //        for (const auto& pair : m_nodeAnims) {
    //            QStandardItem* item3 = new QStandardItem(pair.first.c_str());
    //            item2->appendRow(item3);

    //            std::pair<uint, uint> pair2 = pair.second;

    //            Q_ASSERT(pair2.first < m_animations->size());
    //            Q_ASSERT(pair2.second < (*m_animations)[pair2.first].m_channels.size());
    //            const NodeAnim& nodeAnim = (*m_animations)[pair2.first].m_channels[pair2.second];
    //            //            pair.second->buildItemModel(item2);
    //            nodeAnim.buildItemModel(item3);
    //        }
    //    }

    for (ulong i = 0; i < m_iMeshes.size(); ++i) {
        //        QStandardItem * item2 = new QStandardItem("mesh:" + QString::number(node->m_meshes[i]) + ", " + m_meshes[node->m_meshes[i]]);
        //        QStandardItem * item2 = new QStandardItem(QString::number(node->m_meshes[i]) + "  " + m_meshes[node->m_meshes[i]]);

        Q_ASSERT(m_iMeshes[i] < m_meshes->size());
        //        Q_ASSERT(node->m_numMeshes == node->m_iMeshes.size());
        const Mesh& mesh = (*m_meshes)[m_iMeshes[i]];
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
        return glm::mat4_cast(rotationKeys[nbKeys - 1].second);
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

void Node::prepareHierarchy(glm::mat4 model, const Animation* animation, double animationTime) const
{
    if (animation == nullptr) {
        m_recurseModel = model * m_transformation;
        //        m_recurseModel = model;

    } else {
        const auto& it = m_nodeAnims.find(animation->m_name);

        if (it != m_nodeAnims.end()) {
            //            const NodeAnim& nodeAnim = *it->second;
            std::pair<uint, uint> pair = it->second;
            Q_ASSERT(pair.first < m_animations->size());
            Q_ASSERT(pair.second < (*m_animations)[pair.first].m_channels.size());
            const NodeAnim& nodeAnim = (*m_animations)[pair.first].m_channels[pair.second];
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
            m_recurseModel = model * transformation;
            //            mat4BuildItemModel(transformation, m_itemTransformation);
        } else {
            m_recurseModel = model * m_transformation;
            //            mat4BuildItemModel(m_transformation, m_itemTransformation);
        }
    }

    if (m_isBone) {
        //        m_bone->m_transform = model * m_bone->m_offsetMatrix;
        const Bone& bone = (*m_meshes)[m_iBone.first].m_bones[m_iBone.second];
        bone.m_transform = m_recurseModel * bone.m_offsetMatrix;

        bone.m_recurseModel = m_recurseModel;

        //        bone.m_transform = m_recurseModel;
        //                m_bone->m_transform = m_bone->m_offsetMatrix;
    }


    //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    for (const Node& node : m_children) {
        node.prepareHierarchy(m_recurseModel, animation, animationTime);
    }

    for (uint iMesh : m_iMeshes) {
        Mesh& mesh = (*m_meshes)[iMesh];

        mesh.m_transform = m_recurseModel;

        mesh.updateBoundingBox();
    }
}

void Node::drawHierarchy(const BoneGeometry& boneGeometry, const glm::mat4& modelMatrix) const
{
    glm::mat4 model = modelMatrix * m_recurseModel;
    for (const Node& node : m_children) {
        //        node.draw(shader, m_transformation * model);
        glm::vec3 childPos = glm::vec3(node.m_transformation[3]);

        if (m_isBone) {
            boneGeometry.draw(model, glm::vec3(0), childPos);

            //            const Bone& bone = (*m_meshes)[m_iBone.first].m_bones[m_iBone.second];
            //            bone.m_box.draw(model, shader);

        } else {
            //            m_boneGeometry.draw(model, shader, glm::vec3(0), childPos);
            boneGeometry.drawLine(model, glm::vec3(0), childPos);
        }

        node.drawHierarchy(boneGeometry, modelMatrix);
    }
}

//void Node::drawBoundingBox(const glm::mat4& modelMatrix, const Shader& shader) const
//{
////    glm::mat4 model = modelMatrix * m_recurseModel;
//    if (m_isBone) {

//        const Bone& bone = (*m_meshes)[m_iBone.first].m_bones[m_iBone.second];
//        uint id = m_iBone.second;
//        float r, g, b;
//        r = (id % 3) / 2.0f;
//        id /= 3;
//        g = (id % 3) / 2.0f;
//        id /= 3;
//        b = (id % 3) / 2.0f;

//        shader.setVec3("color", glm::vec3(r, g, b));

//        if (FormTimeline::animation() == nullptr) {
//            bone.m_box.draw(modelMatrix, shader);
//        }
//        else {
////            bone.m_box.draw(model, shader);
//            bone.m_box.draw(modelMatrix * bone.m_transform, shader);
//        }
//    }


//    for (const Node& node : m_children) {
//        node.drawBoundingBox(modelMatrix, shader);
//    }
//}

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
    uint nbBones = (m_isBone) ? 1 : 0;

    for (const Node& children : m_children) {
        nbBones += children.recurseNbBonesVertex();
    }
    return nbBones;
}

void Node::onClick() const
{
    FormTimeline::setAnimation(nullptr);
}

void Node::save(std::ofstream& file) const
{
    Session::save(m_transformation, file);
    Session::save(m_isBone, file);
    if (m_isBone) {
        Session::save(m_iBone, file);
    }

    Session::save(m_iAnimations, file);
    Session::save(m_nbNodes, file);
    Session::save(m_nbBones, file);
    Session::save(m_nbBonesVertex, file);

    Session::save(m_nodeAnims, file);

    uint size = m_children.size();
    Session::save(size, file);
    for (uint i = 0; i < size; ++i) {
        //        m_children.emplace_back(file, meshes, animations);
        //        Session::save(m_children[i], file);
        m_children[i].save(file);
    }

    Session::save(m_iMeshes, file);
    Session::save(m_name, file);
    Session::save(m_recurseModel, file);
}

void Node::updateReferences(Meshes* meshes, Animations* animations)
{
    //    const_cast<Meshes&>(m_meshes) = meshes;
    m_meshes = meshes;
    //    const_cast<Animations&>(m_animations) = animations;
    m_animations = animations;

    for (Node& node : m_children) {
        node.updateReferences(meshes, animations);
    }
}
