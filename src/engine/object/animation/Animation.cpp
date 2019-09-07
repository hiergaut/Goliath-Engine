#include "Animation.h"

//#include <QObject>
#include <assert.h>
#include <QDebug>


#include <gui/editor/outliner/ItemModelPackage.h>
#include <gui/editor/timeline/FormTimeline.h>

Animation::Animation(const aiAnimation* ai_animation)
//    : m_name(ai_animation->mName.C_Str())
{
    std::string str(ai_animation->mName.C_Str());

    m_name = str.substr(str.find_first_of('|') +1);
    m_skeletonName = str.substr(0, str.find_first_of('|'));


    for (uint i =0; i<ai_animation->mNumChannels; ++i) {
        const aiNodeAnim * ai_nodeAnim = ai_animation->mChannels[i];
        m_channels.emplace_back(ai_nodeAnim);
    }

    m_duration = ai_animation->mDuration;

    for (uint i =0; i <ai_animation->mNumMeshChannels; ++i) {
        const aiMeshAnim * ai_meshAnim = ai_animation->mMeshChannels[i];
        m_meshChannels.emplace_back(ai_meshAnim);
    }

    m_ticksPerSecond = ai_animation->mTicksPerSecond;

//    Q_ASSERT(ai_animation->mNumMorphMeshChannels == 0);
    assert(ai_animation->mNumMorphMeshChannels == 0);
}

Animation::Animation(std::ifstream &file)
{
    Session::load(m_skeletonName, file);
    Session::load(m_name, file);
    Session::load(m_duration, file);
    Session::load(m_ticksPerSecond, file);

    uint size;
//    file.read(reinterpret_cast<char *>(&size), sizeof(size));
    Session::load(size, file);
    for (uint i =0; i <size; ++i) {
        m_channels.emplace_back(file);
    }

    Session::load(size, file);
    for (uint i =0; i <size; ++i) {
        m_meshChannels.emplace_back(file);
    }
}

Animation::~Animation()
{
    std::cout << "\033[35m";
    std::cout << "[ANIMATION] '" << m_name << "' deleted " << this << std::endl;
    std::cout << "\033[0m";
}

void Animation::buildItemModel(QStandardItem *parent) const
{
//        QStandardItem* item = new QStandardItem(QIcon(":/icons/animation.png"), QString("'") + m_name.c_str() + "'  skeleton:'" + m_skeletonName.c_str() + "'  duration:" + QString::number(m_duration) + "  ticksPerSecond:" + QString::number(m_ticksPerSecond));
        QStandardItem* item = new QStandardItem(QIcon(":/icons/animation.png"), QString("'") + m_name.c_str() + "'  duration:" + QString::number(m_duration) + "  ticksPerSecond:" + QString::number(m_ticksPerSecond) + "  nodeAnim:" + QString::number(m_channels.size()));
        parent->appendRow(item);

//        ItemModelPackage * package = new ItemModelPackage(this);
//        item->setData(QVariant::fromValue((void*)package), Qt::UserRole);


        ItemModelPackage::store(this, *item);
//        qDebug() << "store animation " << this << item->data(Qt::DisplayRole);
//        qDebug() << "store animation " << this << item->data(Qt::DisplayRole);

//        item->setData(QVariant(str));

//        QStandardItem* item2 = new QStandardItem("nodeAnim  " + QString::number(m_channels.size()));
////        parent->appendRow(item);
//        item->appendRow(item2);
//        for (const NodeAnim & nodeAnim : m_channels) {
//            nodeAnim.buildItemModel(item2);
//        }

//        item2 = new QStandardItem("meshAnim  " + QString::number(m_meshChannels.size()));
//        item->appendRow(item2);
//        for (const MeshAnim & meshAnim : m_meshChannels) {
//            meshAnim.buildItemModel(item2);
//        }


}

void Animation::onClick() const
{
    qDebug() << "Animation::onClick " << this << m_name.c_str();

    FormTimeline::setAnimation(this);

}

void Animation::save(std::ofstream &file) const
{

    Session::save(m_skeletonName, file);
    Session::save(m_name, file);
    Session::save(m_duration, file);
    Session::save(m_ticksPerSecond, file);

    uint size = m_channels.size();
//    file.read(reinterpret_cast<char *>(&size), sizeof(size));
    Session::save(size, file);
    for (uint i =0; i <size; ++i) {
//        m_channels.emplace_back(file);
//        Session::save(m_channels[i], file);
        m_channels[i].save(file);
    }

    size = m_meshChannels.size();
    Session::save(size, file);
    for (uint i =0; i <size; ++i) {
//        m_meshChannels.emplace_back(file);
//        Session::save(m_meshChannels[i], file);
        m_meshChannels[i].save(file);
    }
}


