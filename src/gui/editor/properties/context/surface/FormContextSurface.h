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
    explicit FormContextSurface(QWidget *parent = nullptr);
    ~FormContextSurface();

   void updateSpinKnots();

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

private:
    Ui::FormContextSurface *ui;

    QDoubleSpinBox * m_spinUKnots[13];
    QDoubleSpinBox * m_spinVKnots[13];

    BSplineSurface * m_model = nullptr;
};

#endif // FORMCONTEXTSURFACE_H
