#ifndef FORMCONTEXTANIMATION_H
#define FORMCONTEXTANIMATION_H

#include <QWidget>

namespace Ui {
class FormContextAnimation;
}

class FormContextAnimation : public QWidget
{
    Q_OBJECT
public:
    static bool m_dqsEnable;
    static void toggle();

public:
    explicit FormContextAnimation(QWidget *parent = nullptr);
    ~FormContextAnimation();

private slots:
    void on_radioButton_lbs_clicked();

    void on_radioButton_dqs_clicked();

private:
    static std::list<FormContextAnimation *> m_contexts;
    Ui::FormContextAnimation *ui;
};

#endif // FORMCONTEXTANIMATION_H
