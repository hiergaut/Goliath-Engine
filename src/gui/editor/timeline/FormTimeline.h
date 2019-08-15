#ifndef FORMTIMELINE_H
#define FORMTIMELINE_H

#include <QWidget>

#include <AnimTimeline/FormAnimTimeline.h>

#include <engine/scene/animation/Animation.h>

class FormTimeline : public QWidget {
    Q_OBJECT

public:

public:
    explicit FormTimeline(QWidget* parent = nullptr);
    ~FormTimeline();

    static void setAnimation(const Animation* animation);

    static bool play();

    static void setAnimationTime(double value);

    static const Animation *animation();


    static double animationTime();

signals:

public slots:
    void onCursorChange(double time);
    void onPlay();

private:
    static std::list<FormTimeline*> m_timelines;
    //    static FormAnimTimeline m_animTimeline;

    FormAnimTimeline* m_animTimeline;

    const static Animation* m_animation;
    static double m_animationTime;
    static bool m_play;
};

#endif // FORMTIMELINE_H
