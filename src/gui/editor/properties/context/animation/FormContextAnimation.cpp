#include "FormContextAnimation.h"
#include "ui_FormContextAnimation.h"

bool FormContextAnimation::m_dqsEnable = false;
std::list<FormContextAnimation *> FormContextAnimation::m_contexts;

void FormContextAnimation::toggle()
{
    if (m_dqsEnable) {
        for (FormContextAnimation * context : m_contexts) {
            context->ui->radioButton_lbs->click();
        }
    }
    else {
        for (FormContextAnimation * context : m_contexts) {
            context->ui->radioButton_dqs->click();
        }
    }

//    m_dqsEnable = ! m_dqsEnable;
}

FormContextAnimation::FormContextAnimation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormContextAnimation)
{
    ui->setupUi(this);

    m_contexts.push_back(this);
}

FormContextAnimation::~FormContextAnimation()
{
    delete ui;

    m_contexts.remove(this);
}

void FormContextAnimation::on_radioButton_lbs_clicked()
{
    m_dqsEnable = false;
}

void FormContextAnimation::on_radioButton_dqs_clicked()
{
    m_dqsEnable = true;
}
