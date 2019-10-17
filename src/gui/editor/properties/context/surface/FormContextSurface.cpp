#include "FormContextSurface.h"
#include "ui_FormContextSurface.h"

#include <engine/scene/Scene.h>

FormContextSurface* FormContextSurface::m_formContextSurface = nullptr;

FormContextSurface::FormContextSurface(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::FormContextSurface)
{
    ui->setupUi(this);
    m_spinKnots[0][0] = ui->doubleSpinBox_u0;
    m_spinKnots[0][1] = ui->doubleSpinBox_u1;
    m_spinKnots[0][2] = ui->doubleSpinBox_u2;
    m_spinKnots[0][3] = ui->doubleSpinBox_u3;
    m_spinKnots[0][4] = ui->doubleSpinBox_u4;
    m_spinKnots[0][5] = ui->doubleSpinBox_u5;
    m_spinKnots[0][6] = ui->doubleSpinBox_u6;
    m_spinKnots[0][7] = ui->doubleSpinBox_u7;
    m_spinKnots[0][8] = ui->doubleSpinBox_u8;
    m_spinKnots[0][9] = ui->doubleSpinBox_u9;
    m_spinKnots[0][10] = ui->doubleSpinBox_u10;
    m_spinKnots[0][11] = ui->doubleSpinBox_u11;
    m_spinKnots[0][12] = ui->doubleSpinBox_u12;
    m_spinKnots[0][13] = ui->doubleSpinBox_u13;
    m_spinKnots[0][14] = ui->doubleSpinBox_u14;
    m_spinKnots[0][15] = ui->doubleSpinBox_u15;

    m_spinKnots[1][0] = ui->doubleSpinBox_v0;
    m_spinKnots[1][1] = ui->doubleSpinBox_v1;
    m_spinKnots[1][2] = ui->doubleSpinBox_v2;
    m_spinKnots[1][3] = ui->doubleSpinBox_v3;
    m_spinKnots[1][4] = ui->doubleSpinBox_v4;
    m_spinKnots[1][5] = ui->doubleSpinBox_v5;
    m_spinKnots[1][6] = ui->doubleSpinBox_v6;
    m_spinKnots[1][7] = ui->doubleSpinBox_v7;
    m_spinKnots[1][8] = ui->doubleSpinBox_v8;
    m_spinKnots[1][9] = ui->doubleSpinBox_v9;
    m_spinKnots[1][10] = ui->doubleSpinBox_v10;
    m_spinKnots[1][11] = ui->doubleSpinBox_v11;
    m_spinKnots[1][12] = ui->doubleSpinBox_v12;
    m_spinKnots[1][13] = ui->doubleSpinBox_v13;
    m_spinKnots[1][14] = ui->doubleSpinBox_v14;
    m_spinKnots[1][15] = ui->doubleSpinBox_v15;

    //    m_model = Scene::m_scene->getBsplineSurface();
    initNewSurface(Scene::m_scene->getBsplineSurface());

    m_formContextSurface = this;
}

FormContextSurface::~FormContextSurface()
{
    m_formContextSurface = nullptr;
    delete ui;
}

void FormContextSurface::updateSpinKnots()
{
    for (uint uv = 0; uv < 2; ++uv) {
        uint n;
        uint m;
        if (m_model->m_periodic[uv]) {
            n = m_model->m_nbCtrlPoints[uv] - 1 + m_model->m_k[uv] - 1;
            m = n + 1 + m_model->m_k[uv];
        }
        else {
            n = m_model->m_nbCtrlPoints[uv] - 1;
            m = n + 1 + m_model->m_k[uv];
        }

//        uint m = m_model->m_nbCtrlPoints[uv] + m_model->m_k[uv];
        for (uint i = 0; i < 16; ++i) {
            m_spinKnots[uv][i]->setStyleSheet("background-color: none");

            m_spinKnots[uv][i]->setValue(m_model->m_knots[uv][i]);

            if (i < m) {
                m_spinKnots[uv][i]->setEnabled(true);

//                if (m_model->m_k[uv] - 1 <= i && i <= m_model->m_nbCtrlPoints[uv]) {
                if (m_model->m_k[uv] - 1 <= i && i <= n + 1) {
                    m_spinKnots[uv][i]->setStyleSheet("background-color: cyan");
                }
            } else {
                //            m_spinKnots[i]->setValue(0.0);
                m_spinKnots[uv][i]->setEnabled(false);
            }
        }
    }

//    m = m_model->m_nbCtrlPoints[1] + m_model->m_k[1];
//    for (uint i = 0; i < 13; ++i) {
//        m_spinVKnots[i]->setStyleSheet("background-color: none");

//        m_spinVKnots[i]->setValue(m_model->m_knots[1][i]);

//        if (i < m) {
//            m_spinVKnots[i]->setEnabled(true);

//            if (m_model->m_k[1] - 1 <= i && i <= m_model->m_nbCtrlPoints[1]) {
//                m_spinVKnots[i]->setStyleSheet("background-color: cyan");
//            }
//        } else {
//            //            m_spinKnots[i]->setValue(0.0);
//            m_spinVKnots[i]->setEnabled(false);
//        }
//    }
    ////            ui->dou
}

void FormContextSurface::initNewSurface(BSplineSurface* spline)
{
    m_model = spline;

    if (m_model != nullptr) {
        ui->lineEdit_name->setText(m_model->name().c_str());

        ui->spinBox_uK->setValue(m_model->m_k[0]);
        ui->spinBox_uN->setValue(m_model->m_nbCtrlPoints[0]);
        ui->spinBox_uAccuracy->setValue(m_model->m_dotPerEdge[0]);
        ui->spinBox_uK->setMaximum(m_model->m_nbCtrlPoints[0]);

        ui->spinBox_vK->setValue(m_model->m_k[1]);
        ui->spinBox_vN->setValue(m_model->m_nbCtrlPoints[1]);
        ui->spinBox_vAccuracy->setValue(m_model->m_dotPerEdge[1]);
        ui->spinBox_vK->setMaximum(m_model->m_nbCtrlPoints[1]);

        ui->checkBox_uPeriodic->setDown(m_model->m_periodic[0]);
        ui->checkBox_vPeriodic->setDown(m_model->m_periodic[1]);

        updateSpinKnots();
    }

    setEnabled(true);
}

void FormContextSurface::clear()
{
    if (m_model != nullptr) {
        m_model = nullptr;
    }

    this->setEnabled(false);
}

void FormContextSurface::clearContext()
{
    if (m_formContextSurface != nullptr) {
        m_formContextSurface->clear();
    }
}

void FormContextSurface::initContext(BSplineSurface* spline)
{
    if (m_formContextSurface != nullptr) {
        m_formContextSurface->initNewSurface(spline);
    }
}

void FormContextSurface::on_spinBox_uN_valueChanged(int arg1)
{
    //    m_model->setu
}

void FormContextSurface::on_spinBox_uK_valueChanged(int arg1)
{
    if (m_model != nullptr) {
        m_model->setUk(arg1);
        updateSpinKnots();
    }
}

void FormContextSurface::on_spinBox_uAccuracy_valueChanged(int arg1)
{
    if (m_model != nullptr) {
        m_model->setUDotPerEdge(arg1);
        //    m_model->updateSurface();
    }
}

void FormContextSurface::on_doubleSpinBox_u0_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[0][0] = arg1;
        m_model->updateSurface();
    }
}

void FormContextSurface::on_doubleSpinBox_u1_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[0][1] = arg1;
        m_model->updateSurface();
    }
}

void FormContextSurface::on_doubleSpinBox_u2_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[0][2] = arg1;
        m_model->updateSurface();
    }
}

void FormContextSurface::on_doubleSpinBox_u3_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[0][3] = arg1;
        m_model->updateSurface();
    }
}

void FormContextSurface::on_doubleSpinBox_u4_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[0][4] = arg1;
        m_model->updateSurface();
    }
}

void FormContextSurface::on_doubleSpinBox_u5_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[0][5] = arg1;
        m_model->updateSurface();
    }
}

void FormContextSurface::on_doubleSpinBox_u6_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[0][6] = arg1;
        m_model->updateSurface();
    }
}

void FormContextSurface::on_doubleSpinBox_u7_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[0][7] = arg1;
        m_model->updateSurface();
    }
}

void FormContextSurface::on_doubleSpinBox_u8_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[0][8] = arg1;
        m_model->updateSurface();
    }
}

void FormContextSurface::on_doubleSpinBox_u9_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[0][9] = arg1;
        m_model->updateSurface();
    }
}

void FormContextSurface::on_doubleSpinBox_u10_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[0][10] = arg1;
        m_model->updateSurface();
    }
}

void FormContextSurface::on_doubleSpinBox_u11_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[0][11] = arg1;
        m_model->updateSurface();
    }
}

void FormContextSurface::on_doubleSpinBox_u12_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[0][12] = arg1;
        m_model->updateSurface();
    }
}


void FormContextSurface::on_doubleSpinBox_u13_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[0][13] = arg1;
        m_model->updateSurface();
    }

}
void FormContextSurface::on_doubleSpinBox_u14_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[0][14] = arg1;
        m_model->updateSurface();
    }

}
void FormContextSurface::on_doubleSpinBox_u15_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[0][15] = arg1;
        m_model->updateSurface();
    }

}


void FormContextSurface::on_spinBox_vN_valueChanged(int arg1)
{
}

void FormContextSurface::on_spinBox_vK_valueChanged(int arg1)
{
    if (m_model != nullptr) {
        m_model->setVk(arg1);
        updateSpinKnots();
    }
}

void FormContextSurface::on_spinBox_vAccuracy_valueChanged(int arg1)
{
    if (m_model != nullptr) {
        m_model->setVDotPerEdge(arg1);
        //    m_model->updateSurface();
    }
}

void FormContextSurface::on_doubleSpinBox_v0_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[1][0] = arg1;
        m_model->updateSurface();
    }
}

void FormContextSurface::on_doubleSpinBox_v1_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[1][1] = arg1;
        m_model->updateSurface();
    }
}

void FormContextSurface::on_doubleSpinBox_v2_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[1][2] = arg1;
        m_model->updateSurface();
    }
}

void FormContextSurface::on_doubleSpinBox_v3_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[1][3] = arg1;
        m_model->updateSurface();
    }
}

void FormContextSurface::on_doubleSpinBox_v4_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[1][4] = arg1;
        m_model->updateSurface();
    }
}

void FormContextSurface::on_doubleSpinBox_v5_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[1][5] = arg1;
        m_model->updateSurface();
    }
}

void FormContextSurface::on_doubleSpinBox_v6_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[1][6] = arg1;
        m_model->updateSurface();
    }
}

void FormContextSurface::on_doubleSpinBox_v7_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[1][7] = arg1;
        m_model->updateSurface();
    }
}

void FormContextSurface::on_doubleSpinBox_v8_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[1][8] = arg1;
        m_model->updateSurface();
    }
}

void FormContextSurface::on_doubleSpinBox_v9_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[1][9] = arg1;
        m_model->updateSurface();
    }
}

void FormContextSurface::on_doubleSpinBox_v10_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[1][10] = arg1;
        m_model->updateSurface();
    }
}

void FormContextSurface::on_doubleSpinBox_v11_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[1][11] = arg1;
        m_model->updateSurface();
    }
}

void FormContextSurface::on_doubleSpinBox_v12_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[1][12] = arg1;
        m_model->updateSurface();
    }
}

void FormContextSurface::on_doubleSpinBox_v13_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[1][13] = arg1;
        m_model->updateSurface();
    }

}

void FormContextSurface::on_doubleSpinBox_v14_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[1][14] = arg1;
        m_model->updateSurface();
    }

}


void FormContextSurface::on_doubleSpinBox_v15_valueChanged(double arg1)
{
    if (m_model != nullptr) {
        m_model->m_knots[1][15] = arg1;
        m_model->updateSurface();
    }


}

//void FormContextSurface::on_toolButton_uClampRight_triggered(QAction* arg1)
//{
//    qDebug() << "toolButton";
//    if (m_model != nullptr) {
//        m_model->uClampEnd();
//        updateSpinKnots();
//    }
//}

//void FormContextSurface::on_toolButton_uClampLeft_triggered(QAction* arg1)
//{
//    qDebug() << "toolButton";
//    if (m_model != nullptr) {
//        m_model->uClampStart();
//        updateSpinKnots();
//    }
//}

//void FormContextSurface::on_toolButton_uUniform_triggered(QAction* arg1)
//{
//    qDebug() << "toolButton";
//    if (m_model != nullptr) {
//        m_model->uSetUniform();
//        updateSpinKnots();
//        m_model->updateSurface();
//    }
//}

//void FormContextSurface::on_toolButton_vClampRight_triggered(QAction* arg1)
//{
//    if (m_model != nullptr) {
//        m_model->uClampEnd();
//        updateSpinKnots();
//    }
//}

//void FormContextSurface::on_toolButton_vClampLeft_triggered(QAction* arg1)
//{
//    if (m_model != nullptr) {
//        m_model->uClampStart();
//        updateSpinKnots();
//    }
//}

//void FormContextSurface::on_toolButton_vUniform_triggered(QAction* arg1)
//{
//    if (m_model != nullptr) {
//        m_model->vSetUniform();
//        updateSpinKnots();
//        m_model->updateSurface();
//    }
//}

void FormContextSurface::on_checkBox_uPeriodic_stateChanged(int arg1)
{
    qDebug() << "periodic";
    if (m_model != nullptr) {
        m_model->m_periodic[0] = arg1 > 1;
        m_model->updateSurface();
        updateSpinKnots();
    }
}

void FormContextSurface::on_checkBox_vPeriodic_stateChanged(int arg1)
{
    if (m_model != nullptr) {
        m_model->m_periodic[1] = arg1 > 1;
        m_model->updateSurface();
        updateSpinKnots();
    }
}

void FormContextSurface::on_toolButton_uClampLeft_clicked()
{
    if (m_model != nullptr) {
        m_model->uClampStart();
        updateSpinKnots();
    }
}

void FormContextSurface::on_toolButton_uClampRight_clicked()
{
    if (m_model != nullptr) {
        m_model->uClampEnd();
        updateSpinKnots();
    }
}

void FormContextSurface::on_toolButton_uUniform_clicked()
{
    if (m_model != nullptr) {
        m_model->uSetUniform();
        updateSpinKnots();
        m_model->updateSurface();
    }
}

void FormContextSurface::on_toolButton_vClampLeft_clicked()
{
    if (m_model != nullptr) {
        m_model->vClampStart();
        updateSpinKnots();
    }
}

void FormContextSurface::on_toolButton_vClampRight_clicked()
{
    if (m_model != nullptr) {
        m_model->vClampEnd();
        updateSpinKnots();
    }
}

void FormContextSurface::on_toolButton_vUniform_clicked()
{
    if (m_model != nullptr) {
        m_model->vSetUniform();
        updateSpinKnots();
        m_model->updateSurface();
    }
}
