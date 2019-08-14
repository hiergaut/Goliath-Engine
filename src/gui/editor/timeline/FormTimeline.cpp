#include "FormTimeline.h"

#include <QLayout>
//#include <QHBoxLayout>
#include <QList>

//FormAnimTimeline FormTimeline::m_animTimeline;
const Animation * FormTimeline::m_animation = nullptr;
std::list<FormTimeline*> FormTimeline::m_timelines;

FormTimeline::FormTimeline(QWidget *parent) : QWidget(parent)
{
//    Q_ASSERT(m_animation != nullptr);

//    QWidget * widget = new FormAnimTimeline(this);
    m_animTimeline = new FormAnimTimeline(this);

    QLayout * layout = new QHBoxLayout;
    layout->addWidget(m_animTimeline);

    layout->setMargin(0);

    setLayout(layout);


    m_timelines.push_back(this);
}

FormTimeline::~FormTimeline()
{
    m_timelines.remove(this);
    delete m_animTimeline;

}

void FormTimeline::setAnimation(const Animation *animation)
{
    m_animation = animation;

    for (auto timeline : m_timelines) {
//        timeline->setAnimation(animation);
        FormAnimTimeline * animTimeline = timeline->m_animTimeline;
        animTimeline->onClearKeyPoses();

        animTimeline->onChangeDuration(animation->m_duration / animation->m_ticksPerSecond);

        for (uint i =0; i <animation->m_duration; ++i) {
            animTimeline->onAddingKeyPose(i / animation->m_ticksPerSecond);
        }

//        for ()


    }
}
