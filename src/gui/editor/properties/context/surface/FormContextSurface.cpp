#include "FormContextSurface.h"
#include "ui_FormContextSurface.h"

#include <engine/scene/Scene.h>

FormContextSurface::FormContextSurface(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::FormContextSurface)
{
    ui->setupUi(this);
    m_spinUKnots[0] = ui->doubleSpinBox_u0;
    m_spinUKnots[1] = ui->doubleSpinBox_u1;
    m_spinUKnots[2] = ui->doubleSpinBox_u2;
    m_spinUKnots[3] = ui->doubleSpinBox_u3;
    m_spinUKnots[4] = ui->doubleSpinBox_u4;
    m_spinUKnots[5] = ui->doubleSpinBox_u5;
    m_spinUKnots[6] = ui->doubleSpinBox_u6;
    m_spinUKnots[7] = ui->doubleSpinBox_u7;
    m_spinUKnots[8] = ui->doubleSpinBox_u8;
    m_spinUKnots[9] = ui->doubleSpinBox_u9;
    m_spinUKnots[10] = ui->doubleSpinBox_u10;
    m_spinUKnots[11] = ui->doubleSpinBox_u11;
    m_spinUKnots[12] = ui->doubleSpinBox_u12;

    m_spinVKnots[0] = ui->doubleSpinBox_v0;
    m_spinVKnots[1] = ui->doubleSpinBox_v1;
    m_spinVKnots[2] = ui->doubleSpinBox_v2;
    m_spinVKnots[3] = ui->doubleSpinBox_v3;
    m_spinVKnots[4] = ui->doubleSpinBox_v4;
    m_spinVKnots[5] = ui->doubleSpinBox_v5;
    m_spinVKnots[6] = ui->doubleSpinBox_v6;
    m_spinVKnots[7] = ui->doubleSpinBox_v7;
    m_spinVKnots[8] = ui->doubleSpinBox_v8;
    m_spinVKnots[9] = ui->doubleSpinBox_v9;
    m_spinVKnots[10] = ui->doubleSpinBox_v10;
    m_spinVKnots[11] = ui->doubleSpinBox_v11;
    m_spinVKnots[12] = ui->doubleSpinBox_v12;

    m_model = Scene::m_scene->getBsplineSurface();

    if (m_model != nullptr) {
        ui->lineEdit_name->setText(m_model->name().c_str());

        ui->spinBox_uK->setValue(m_model->m_k[0]);
        ui->spinBox_uN->setValue(m_model->m_nbLine);
        ui->spinBox_uAccuracy->setValue(m_model->m_dotPerEdge[0]);
        ui->spinBox_uK->setMaximum(m_model->m_nbLine);

        ui->spinBox_vK->setValue(m_model->m_k[1]);
        ui->spinBox_vN->setValue(m_model->m_nbCol);
        ui->spinBox_vAccuracy->setValue(m_model->m_dotPerEdge[1]);
        ui->spinBox_vK->setMaximum(m_model->m_nbCol);

        updateSpinKnots();
    }
}

FormContextSurface::~FormContextSurface()
{
    delete ui;
}

void FormContextSurface::updateSpinKnots()
{
    uint m = m_model->m_nbLine + m_model->m_k[0];
    for (uint i = 0; i < 13; ++i) {
        m_spinUKnots[i]->setStyleSheet("background-color: none");

        m_spinUKnots[i]->setValue(m_model->m_knots[0][i]);

        if (i < m) {
            m_spinUKnots[i]->setEnabled(true);

            if (m_model->m_k[0] - 1 <= i && i <= m_model->m_nbLine) {
                m_spinUKnots[i]->setStyleSheet("background-color: cyan");
            }
        } else {
            //            m_spinKnots[i]->setValue(0.0);
            m_spinUKnots[i]->setEnabled(false);
        }
    }

    m = m_model->m_nbCol + m_model->m_k[1];
    for (uint i = 0; i < 13; ++i) {
        m_spinVKnots[i]->setStyleSheet("background-color: none");

        m_spinVKnots[i]->setValue(m_model->m_knots[1][i]);

        if (i < m) {
            m_spinVKnots[i]->setEnabled(true);

            if (m_model->m_k[1] - 1 <= i && i <= m_model->m_nbCol) {
                m_spinVKnots[i]->setStyleSheet("background-color: cyan");
            }
        } else {
            //            m_spinKnots[i]->setValue(0.0);
            m_spinVKnots[i]->setEnabled(false);
        }
    }
    ////            ui->dou
}

void FormContextSurface::on_spinBox_uN_valueChanged(int arg1)
{
//    m_model->setu
}

void FormContextSurface::on_spinBox_uK_valueChanged(int arg1)
{
    m_model->setUk(arg1);
    updateSpinKnots();
}

void FormContextSurface::on_spinBox_uAccuracy_valueChanged(int arg1)
{
    m_model->setUDotPerEdge(arg1);
//    m_model->updateSurface();

}

void FormContextSurface::on_doubleSpinBox_u0_valueChanged(double arg1)
{
    m_model->m_knots[0][0] = arg1;
    m_model->updateSurface();
}

void FormContextSurface::on_doubleSpinBox_u1_valueChanged(double arg1)
{
    m_model->m_knots[0][1] = arg1;
    m_model->updateSurface();
}

void FormContextSurface::on_doubleSpinBox_u2_valueChanged(double arg1)
{
    m_model->m_knots[0][2] = arg1;
    m_model->updateSurface();
}

void FormContextSurface::on_doubleSpinBox_u3_valueChanged(double arg1)
{
    m_model->m_knots[0][3] = arg1;
    m_model->updateSurface();
}

void FormContextSurface::on_doubleSpinBox_u4_valueChanged(double arg1)
{
    m_model->m_knots[0][4] = arg1;
    m_model->updateSurface();
}

void FormContextSurface::on_doubleSpinBox_u5_valueChanged(double arg1)
{
    m_model->m_knots[0][5] = arg1;
    m_model->updateSurface();
}

void FormContextSurface::on_doubleSpinBox_u6_valueChanged(double arg1)
{
    m_model->m_knots[0][6] = arg1;
    m_model->updateSurface();
}

void FormContextSurface::on_doubleSpinBox_u7_valueChanged(double arg1)
{
    m_model->m_knots[0][7] = arg1;
    m_model->updateSurface();
}

void FormContextSurface::on_doubleSpinBox_u8_valueChanged(double arg1)
{
    m_model->m_knots[0][8] = arg1;
    m_model->updateSurface();
}

void FormContextSurface::on_doubleSpinBox_u9_valueChanged(double arg1)
{
    m_model->m_knots[0][9] = arg1;
    m_model->updateSurface();
}

void FormContextSurface::on_doubleSpinBox_u10_valueChanged(double arg1)
{
    m_model->m_knots[0][10] = arg1;
    m_model->updateSurface();
}

void FormContextSurface::on_doubleSpinBox_u11_valueChanged(double arg1)
{
    m_model->m_knots[0][11] = arg1;
    m_model->updateSurface();
}

void FormContextSurface::on_doubleSpinBox_u12_valueChanged(double arg1)
{
    m_model->m_knots[0][12] = arg1;
    m_model->updateSurface();
}

void FormContextSurface::on_spinBox_vN_valueChanged(int arg1)
{
}

void FormContextSurface::on_spinBox_vK_valueChanged(int arg1)
{
    m_model->setVk(arg1);
    updateSpinKnots();
}

void FormContextSurface::on_spinBox_vAccuracy_valueChanged(int arg1)
{
    m_model->setVDotPerEdge(arg1);
//    m_model->updateSurface();
}

void FormContextSurface::on_doubleSpinBox_v0_valueChanged(double arg1)
{
    m_model->m_knots[1][0] = arg1;
    m_model->updateSurface();
}

void FormContextSurface::on_doubleSpinBox_v1_valueChanged(double arg1)
{
    m_model->m_knots[1][1] = arg1;
    m_model->updateSurface();
}

void FormContextSurface::on_doubleSpinBox_v2_valueChanged(double arg1)
{
    m_model->m_knots[1][2] = arg1;
    m_model->updateSurface();
}

void FormContextSurface::on_doubleSpinBox_v3_valueChanged(double arg1)
{
    m_model->m_knots[1][3] = arg1;
    m_model->updateSurface();
}

void FormContextSurface::on_doubleSpinBox_v4_valueChanged(double arg1)
{
    m_model->m_knots[1][4] = arg1;
    m_model->updateSurface();
}

void FormContextSurface::on_doubleSpinBox_v5_valueChanged(double arg1)
{
    m_model->m_knots[1][5] = arg1;
    m_model->updateSurface();
}

void FormContextSurface::on_doubleSpinBox_v6_valueChanged(double arg1)
{
    m_model->m_knots[1][6] = arg1;
    m_model->updateSurface();
}

void FormContextSurface::on_doubleSpinBox_v7_valueChanged(double arg1)
{
    m_model->m_knots[1][7] = arg1;
    m_model->updateSurface();
}

void FormContextSurface::on_doubleSpinBox_v8_valueChanged(double arg1)
{
    m_model->m_knots[1][8] = arg1;
    m_model->updateSurface();
}

void FormContextSurface::on_doubleSpinBox_v9_valueChanged(double arg1)
{
    m_model->m_knots[1][9] = arg1;
    m_model->updateSurface();
}

void FormContextSurface::on_doubleSpinBox_v10_valueChanged(double arg1)
{
    m_model->m_knots[1][10] = arg1;
    m_model->updateSurface();
}

void FormContextSurface::on_doubleSpinBox_v11_valueChanged(double arg1)
{
    m_model->m_knots[1][11] = arg1;
    m_model->updateSurface();
}

void FormContextSurface::on_doubleSpinBox_v12_valueChanged(double arg1)
{
    m_model->m_knots[1][12] = arg1;
    m_model->updateSurface();
}
