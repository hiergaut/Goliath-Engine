#include "FormContextCurve.h"
#include "ui_FormContextCurve.h"

#include <engine/scene/Scene.h>

FormContextCurve::FormContextCurve(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::FormContextCurve)
{
    ui->setupUi(this);

    m_spinKnots[0] = ui->doubleSpinBox_0;
    m_spinKnots[1] = ui->doubleSpinBox_1;
    m_spinKnots[2] = ui->doubleSpinBox_2;
    m_spinKnots[3] = ui->doubleSpinBox_3;
    m_spinKnots[4] = ui->doubleSpinBox_4;
    m_spinKnots[5] = ui->doubleSpinBox_5;
    m_spinKnots[6] = ui->doubleSpinBox_6;
    m_spinKnots[7] = ui->doubleSpinBox_7;
    m_spinKnots[8] = ui->doubleSpinBox_8;
    m_spinKnots[9] = ui->doubleSpinBox_9;
    m_spinKnots[10] = ui->doubleSpinBox_10;
    m_spinKnots[11] = ui->doubleSpinBox_11;
    m_spinKnots[12] = ui->doubleSpinBox_12;


//    m_model = Scene::m_scene->getParamModel();
    m_model = Scene::m_scene->getBsplineCurve();

//    Q_ASSERT(m_model != nullptr);
    if (m_model != nullptr) {
        ui->lineEdit_name->setText(m_model->name().c_str());
        ui->spinBox_k->setValue(m_model->m_k);
        ui->spinBox_n->setValue(m_model->m_controlPoints.size() - 1);
        ui->spinBox_dotPerEdge->setValue(m_model->m_dotPerEdge);

        ui->spinBox_k->setMaximum(m_model->m_controlPoints.size());

        //        QLayout * horizontal = new QLayout()
        //        for (uint i = 0; i < m_model->m_controlPoints.size() + m_model->m_k; ++i) {
        //            QHBoxLayout* layout = new QHBoxLayout;
        //            QLabel* label = new QLabel("u0");
        //            QSpinBox* spin = new QSpinBox;
        //            layout->addWidget(label);
        //            layout->addWidget(spin);
        //            ui->verticalLayout_knots->addLayout(layout);
        //        }
        //        }
        //        //        ui->groupBox_knots->
        updateSpinKnots();
    }

//    m_initialized = true;
}

FormContextCurve::~FormContextCurve()
{
    delete ui;
}

void FormContextCurve::updateSpinKnots()
{
    uint m = m_model->m_controlPoints.size() + m_model->m_k;
    for (uint i = 0; i < 13; ++i) {
        m_spinKnots[i]->setStyleSheet("background-color: none");

            m_spinKnots[i]->setValue(m_model->m_knots[i]);

        if (i < m) {
            m_spinKnots[i]->setEnabled(true);

            if (m_model->m_k - 1 <= i && i <= m_model->m_controlPoints.size()) {
                m_spinKnots[i]->setStyleSheet("background-color: cyan");
            }
        } else {
//            m_spinKnots[i]->setValue(0.0);
            m_spinKnots[i]->setEnabled(false);
        }
    }
    ////            ui->dou
}

//void FormContextCurve::setK(uint k)
//{

//}

void FormContextCurve::on_spinBox_k_valueChanged(int arg1)
{
    //    qDebug() << arg1;
//    Q_ASSERT(m_initialized);

    m_model->setK(arg1);
    updateSpinKnots();
}

void FormContextCurve::on_spinBox_dotPerEdge_valueChanged(int arg1)
{
//    Q_ASSERT(m_initialized);
    m_model->setDotPerEdge(arg1);
}

void FormContextCurve::on_doubleSpinBox_0_valueChanged(double arg1)
{
//    qDebug() << "value changed";
    m_model->m_knots[0] = arg1;
    m_model->updateCurve();
}

void FormContextCurve::on_doubleSpinBox_1_valueChanged(double arg1)
{
    m_model->m_knots[1] = arg1;
    m_model->updateCurve();
}

void FormContextCurve::on_doubleSpinBox_2_valueChanged(double arg1)
{
    m_model->m_knots[2] = arg1;
    m_model->updateCurve();
}

void FormContextCurve::on_doubleSpinBox_3_valueChanged(double arg1)
{
    m_model->m_knots[3] = arg1;
    m_model->updateCurve();
}

void FormContextCurve::on_doubleSpinBox_4_valueChanged(double arg1)
{
    m_model->m_knots[4] = arg1;
    m_model->updateCurve();
}

void FormContextCurve::on_doubleSpinBox_5_valueChanged(double arg1)
{
    m_model->m_knots[5] = arg1;
    m_model->updateCurve();
}

void FormContextCurve::on_doubleSpinBox_6_valueChanged(double arg1)
{
    m_model->m_knots[6] = arg1;
    m_model->updateCurve();
}

void FormContextCurve::on_doubleSpinBox_7_valueChanged(double arg1)
{
    m_model->m_knots[7] = arg1;
    m_model->updateCurve();
}

void FormContextCurve::on_doubleSpinBox_8_valueChanged(double arg1)
{
    m_model->m_knots[8] = arg1;
    m_model->updateCurve();
}

void FormContextCurve::on_doubleSpinBox_9_valueChanged(double arg1)
{
    m_model->m_knots[9] = arg1;
    m_model->updateCurve();
}

void FormContextCurve::on_doubleSpinBox_10_valueChanged(double arg1)
{
    m_model->m_knots[10] = arg1;
    m_model->updateCurve();
}

void FormContextCurve::on_doubleSpinBox_11_valueChanged(double arg1)
{
    m_model->m_knots[11] = arg1;
    m_model->updateCurve();
}

void FormContextCurve::on_doubleSpinBox_12_valueChanged(double arg1)
{
    m_model->m_knots[12] = arg1;
    m_model->updateCurve();
}
