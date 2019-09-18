#include "FormTimeline.h"

#include <QLayout>
//#include <QHBoxLayout>
#include <QList>

//FormAnimTimeline FormTimeline::m_animTimeline;
const Animation* FormTimeline::m_animation = nullptr;
std::list<FormTimeline*> FormTimeline::m_timelines;
double FormTimeline::m_animationTime = 0.0;
bool FormTimeline::m_play = false;
bool FormTimeline::m_animationTimeChanged = false;

//Scene * FormTimeline::m_scene = nullptr;

#include <session/Session.h>

FormTimeline::FormTimeline(QWidget* parent)
    : QWidget(parent)
{
    //    Q_ASSERT(m_animation != nullptr);
//    Q_ASSERT(m_scene != nullptr);

    //    QWidget * widget = new FormAnimTimeline(this);
    m_animTimeline = new FormAnimTimeline(this);
    connect(m_animTimeline, &FormAnimTimeline::cursorChanged, this, &FormTimeline::onCursorChange);
    connect(m_animTimeline, &FormAnimTimeline::playClicked, this, &FormTimeline::onPlay);
    connect(m_animTimeline, &FormAnimTimeline::pauseClicked, this, &FormTimeline::onPause);

    QLayout* layout = new QHBoxLayout;
    layout->addWidget(m_animTimeline);

    layout->setMargin(0);

    setLayout(layout);

    m_timelines.push_back(this);

    updateTimeline();
}

FormTimeline::~FormTimeline()
{
    m_timelines.remove(this);
    delete m_animTimeline;
}

void FormTimeline::setAnimation(const Animation* animation)
{
    m_animation = animation;


    for (auto timeline : m_timelines) {
        //        timeline->setAnimation(animation);
        FormAnimTimeline* animTimeline = timeline->m_animTimeline;
        animTimeline->onClearKeyPoses();

        if (animation == nullptr)
            continue;

        double duration = animation->m_duration / animation->m_ticksPerSecond;
        animTimeline->onChangeDuration(duration);
        animTimeline->onChangeStart(0.0);
        animTimeline->onChangeEnd(duration);
        animTimeline->onChangeCursor(m_animationTime);


        std::set<double> keyPose;
        for (const NodeAnim & nodeAnim : animation->m_channels) {
            for (const auto & pair : nodeAnim.m_positionKeys) {
                keyPose.insert(pair.first);
            }
            for (const auto & pair : nodeAnim.m_rotationKeys) {
                keyPose.insert(pair.first);
            }
            for (const auto & pair : nodeAnim.m_scalingKeys) {
                keyPose.insert(pair.first);
            }
        }

        for (double d : keyPose) {
            animTimeline->onAddingKeyPose(d / animation->m_ticksPerSecond);
        }

//        for (uint i = 0; i < animation->m_duration; ++i) {
//            animTimeline->onAddingKeyPose(i / animation->m_ticksPerSecond);
//        }

        //        for ()
    }
}

void FormTimeline::onCursorChange(double time)
{
//    Q_ASSERT(m_scene != nullptr);

    if (m_animation != nullptr) {
        m_animationTime = time * m_animation->m_ticksPerSecond;
        m_animationTimeChanged = true;

        m_play = false;
        m_animTimeline->onSetPauseMode();
//        m_scene->updateBoundingBox();
    }
}

void FormTimeline::onPlay()
{
    m_play = true;
}

void FormTimeline::onPause()
{
    m_play = false;

}

//void FormTimeline::setScene(Scene *scene)
//{
//    m_scene = scene;
//}

double FormTimeline::animationTime()
{
    return m_animationTime;
}

void FormTimeline::setFocusPolicy(Qt::FocusPolicy policy)
{
    QWidget::setFocusPolicy(policy);

}

QWidget *FormTimeline::widget()
{
    return this;
}

void FormTimeline::save(std::ofstream &file)
{
    Session::save(m_animationTime, file);

}

void FormTimeline::load(std::ifstream &file)
{
    Session::load(m_animationTime, file);

    setAnimationTime(m_animationTime);

}

const Animation* FormTimeline::animation()
{
    return m_animation;
}

void FormTimeline::setAnimationTime(double value)
{
    if (m_animation == nullptr) {
        return;
    }
    m_animationTime = value;
    for (auto timeline : m_timelines) {
        //        timeline->setAnimation(animation);
        FormAnimTimeline* animTimeline = timeline->m_animTimeline;
        //        animTimeline->onClearKeyPoses();

        //        double duration = anim_duration / animation->m_ticksPerSecond;
        //        animTimeline->onChangeDuration(duration);
        //        animTimeline->onChangeStart(0.0);
        //        animTimeline->onChangeEnd(duration);
        animTimeline->onChangeCursor(m_animationTime / m_animation->m_ticksPerSecond);

        //        for (uint i =0; i <animation->m_duration; ++i) {
        //            animTimeline->onAddingKeyPose(i / animation->m_ticksPerSecond);
        //        }

        //        for ()
    }
}

void FormTimeline::updateTimeline()
{
        FormAnimTimeline* animTimeline = m_animTimeline;
        animTimeline->onClearKeyPoses();

        if (m_animation == nullptr)
            return;
//            continue;

        double duration = m_animation->m_duration / m_animation->m_ticksPerSecond;
        animTimeline->onChangeDuration(duration);
        animTimeline->onChangeStart(0.0);
        animTimeline->onChangeEnd(duration);
        animTimeline->onChangeCursor(m_animationTime);


        std::set<double> keyPose;
        for (const NodeAnim & nodeAnim : m_animation->m_channels) {
            for (const auto & pair : nodeAnim.m_positionKeys) {
                keyPose.insert(pair.first);
            }
            for (const auto & pair : nodeAnim.m_rotationKeys) {
                keyPose.insert(pair.first);
            }
            for (const auto & pair : nodeAnim.m_scalingKeys) {
                keyPose.insert(pair.first);
            }
        }

        for (double d : keyPose) {
            animTimeline->onAddingKeyPose(d / m_animation->m_ticksPerSecond);
        }


}

bool FormTimeline::play()
{
    return m_play;
}
