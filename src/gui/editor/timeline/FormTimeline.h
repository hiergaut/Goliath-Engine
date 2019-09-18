#ifndef FORMTIMELINE_H
#define FORMTIMELINE_H

#include <QWidget>

#include <AnimTimeline/FormAnimTimeline.h>

#include <engine/scene/model/meshModel/animation/Animation.h>

#include "../TemplateMenuBar.h"
#include <engine/scene/Scene.h>

class FormTimeline : public QWidget, public TemplateMenuBar {
    Q_OBJECT

public:
    static bool m_animationTimeChanged;

public:
    explicit FormTimeline(QWidget* parent = nullptr);
    ~FormTimeline();

    static void setAnimation(const Animation* animation);

    static bool play();

    static void setAnimationTime(double value);
    void updateTimeline();

    static const Animation *animation();


    static double animationTime();

    void setFocusPolicy(Qt::FocusPolicy policy) override;
    QWidget * widget() override;

    static void save(std::ofstream & file);
    static void load(std::ifstream & file);


//    static void setScene(Scene *scene);

signals:

public slots:
    void onCursorChange(double time);
    void onPlay();
    void onPause();

private:
//    static Scene * m_scene;

    static std::list<FormTimeline*> m_timelines;
    //    static FormAnimTimeline m_animTimeline;

    FormAnimTimeline* m_animTimeline;

    const static Animation* m_animation;
    static double m_animationTime;
    static bool m_play;


};

#endif // FORMTIMELINE_H
