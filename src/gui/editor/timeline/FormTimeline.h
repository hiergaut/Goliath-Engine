#ifndef FORMTIMELINE_H
#define FORMTIMELINE_H

#include <QWidget>

#include <AnimTimeline/FormAnimTimeline.h>

#include <engine/scene/animation/Animation.h>

class FormTimeline : public QWidget
{
        Q_OBJECT

public:
    explicit FormTimeline(QWidget * parent = nullptr);
    ~FormTimeline();

    static void setAnimation(const Animation *animation);

private:
    static std::list<FormTimeline*> m_timelines;
//    static FormAnimTimeline m_animTimeline;
    const static Animation * m_animation;

    FormAnimTimeline * m_animTimeline;

};

#endif // FORMTIMELINE_H
