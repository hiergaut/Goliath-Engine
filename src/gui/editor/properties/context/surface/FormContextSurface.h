#ifndef FORMCONTEXTSURFACE_H
#define FORMCONTEXTSURFACE_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <engine/scene/model/paramModel/surface/BSplineSurface.h>

namespace Ui {
class FormContextSurface;
}

class FormContextSurface : public QWidget
{
    Q_OBJECT

public:
    static FormContextSurface * m_formContextSurface;

public:
    explicit FormContextSurface(QWidget *parent = nullptr);
    ~FormContextSurface();

   void updateSpinKnots();
   void initNewSurface(BSplineSurface * spline);
   void clear();
   static void clearContext();
   static void initContext(BSplineSurface * spline);

private slots:
    void on_spinBox_uN_valueChanged(int arg1);
    void on_spinBox_uK_valueChanged(int arg1);
    void on_spinBox_uAccuracy_valueChanged(int arg1);
    void on_doubleSpinBox_u0_valueChanged(double arg1);
    void on_doubleSpinBox_u1_valueChanged(double arg1);
    void on_doubleSpinBox_u2_valueChanged(double arg1);
    void on_doubleSpinBox_u3_valueChanged(double arg1);
    void on_doubleSpinBox_u4_valueChanged(double arg1);
    void on_doubleSpinBox_u5_valueChanged(double arg1);
    void on_doubleSpinBox_u6_valueChanged(double arg1);
    void on_doubleSpinBox_u7_valueChanged(double arg1);
    void on_doubleSpinBox_u8_valueChanged(double arg1);
    void on_doubleSpinBox_u9_valueChanged(double arg1);
    void on_doubleSpinBox_u10_valueChanged(double arg1);
    void on_doubleSpinBox_u11_valueChanged(double arg1);
    void on_doubleSpinBox_u12_valueChanged(double arg1);

    void on_spinBox_vN_valueChanged(int arg1);
    void on_spinBox_vK_valueChanged(int arg1);
    void on_spinBox_vAccuracy_valueChanged(int arg1);
    void on_doubleSpinBox_v0_valueChanged(double arg1);
    void on_doubleSpinBox_v1_valueChanged(double arg1);
    void on_doubleSpinBox_v2_valueChanged(double arg1);
    void on_doubleSpinBox_v3_valueChanged(double arg1);
    void on_doubleSpinBox_v4_valueChanged(double arg1);
    void on_doubleSpinBox_v5_valueChanged(double arg1);
    void on_doubleSpinBox_v6_valueChanged(double arg1);
    void on_doubleSpinBox_v7_valueChanged(double arg1);
    void on_doubleSpinBox_v8_valueChanged(double arg1);
    void on_doubleSpinBox_v9_valueChanged(double arg1);
    void on_doubleSpinBox_v10_valueChanged(double arg1);
    void on_doubleSpinBox_v11_valueChanged(double arg1);
    void on_doubleSpinBox_v12_valueChanged(double arg1);

//    void on_toolButton_uClampRight_triggered(QAction *arg1);
//    void on_toolButton_uClampLeft_triggered(QAction *arg1);
//    void on_toolButton_uUniform_triggered(QAction *arg1);
//    void on_toolButton_vClampRight_triggered(QAction *arg1);
//    void on_toolButton_vClampLeft_triggered(QAction *arg1);
//    void on_toolButton_vUniform_triggered(QAction *arg1);
    void on_checkBox_uPeriodic_stateChanged(int arg1);
    void on_checkBox_vPeriodic_stateChanged(int arg1);

    void on_toolButton_uClampLeft_clicked();
    void on_toolButton_uClampRight_clicked();
    void on_toolButton_uUniform_clicked();
    void on_toolButton_vClampLeft_clicked();
    void on_toolButton_vClampRight_clicked();
    void on_toolButton_vUniform_clicked();

    void on_doubleSpinBox_v13_valueChanged(double arg1);

    void on_doubleSpinBox_v14_valueChanged(double arg1);

    void on_doubleSpinBox_u14_valueChanged(double arg1);

    void on_doubleSpinBox_u13_valueChanged(double arg1);

    void on_doubleSpinBox_u15_valueChanged(double arg1);

    void on_doubleSpinBox_v15_valueChanged(double arg1);

private:
    Ui::FormContextSurface *ui;

//    QDoubleSpinBox * m_spinUKnots[13];
//    QDoubleSpinBox * m_spinVKnots[13];
    QDoubleSpinBox * m_spinKnots[2][16];

    BSplineSurface * m_model = nullptr;
};

#endif // FORMCONTEXTSURFACE_H
