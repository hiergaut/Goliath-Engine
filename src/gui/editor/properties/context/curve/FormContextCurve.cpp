#include "FormContextCurve.h"
#include "ui_FormContextCurve.h"

#include <engine/scene/Scene.h>

FormContextCurve::FormContextCurve(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormContextCurve)
{
    ui->setupUi(this);

    m_model = Scene::m_scene->getParamModel();

    if (m_model != nullptr) {
        ui->lineEdit_name->setText(m_model->name().c_str());
        ui->spinBox_k->setValue(m_model->m_k);
        ui->spinBox_n->setValue(m_model->m_controlPoints.size() - 1);

        ui->spinBox_k->setMaximum(m_model->m_controlPoints.size());
    }

}

FormContextCurve::~FormContextCurve()
{
    delete ui;
}

//void FormContextCurve::setK(uint k)
//{

//}

void FormContextCurve::on_spinBox_k_valueChanged(int arg1)
{
    qDebug() << arg1;

    m_model->setK(arg1);

}
