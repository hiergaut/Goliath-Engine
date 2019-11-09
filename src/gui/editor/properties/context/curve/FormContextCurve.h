#ifndef FORMCONTEXTCURVE_H
#define FORMCONTEXTCURVE_H

#include <QWidget>
//#include <engine/scene/model/paramModel/ParamModel.h>
#include <engine/scene/model/paramModel/curve/BSplineCurve.h>
#include <QDoubleSpinBox>

namespace Ui {
class FormContextCurve;
}


class FormContextCurve : public QWidget
{
    Q_OBJECT

public:
    static FormContextCurve * m_formContextCurve;
    BSplineCurve * m_model = nullptr;

public:
    explicit FormContextCurve(QWidget *parent = nullptr);
    ~FormContextCurve();

   void updateSpinKnots();
   void updateWeights();
//    void setK(uint k);
   void initNewSpline(BSplineCurve * spline);
   void clear();
   static void clearContext();
   static void initContext(BSplineCurve * spline);

private slots:
    void on_spinBox_k_valueChanged(int arg1);
    void on_spinBox_dotPerEdge_valueChanged(int arg1);

    void on_doubleSpinBox_0_valueChanged(double arg1);
    void on_doubleSpinBox_1_valueChanged(double arg1);
    void on_doubleSpinBox_2_valueChanged(double arg1);
    void on_doubleSpinBox_3_valueChanged(double arg1);
    void on_doubleSpinBox_4_valueChanged(double arg1);
    void on_doubleSpinBox_5_valueChanged(double arg1);
    void on_doubleSpinBox_6_valueChanged(double arg1);
    void on_doubleSpinBox_7_valueChanged(double arg1);
    void on_doubleSpinBox_8_valueChanged(double arg1);
    void on_doubleSpinBox_9_valueChanged(double arg1);
    void on_doubleSpinBox_10_valueChanged(double arg1);
    void on_doubleSpinBox_11_valueChanged(double arg1);
    void on_doubleSpinBox_12_valueChanged(double arg1);

    void on_pushButton_clampStart_clicked();
    void on_pushButton_clampEnd_clicked();
    void on_pushButton_uniform_clicked();

//    void on_pushButton_periodic_clicked();

    void on_checkBox_periodic_stateChanged(int arg1);

    void on_doubleSpinBox_p0_valueChanged(double arg1);
    void on_doubleSpinBox_p1_valueChanged(double arg1);
    void on_doubleSpinBox_p2_valueChanged(double arg1);
    void on_doubleSpinBox_p3_valueChanged(double arg1);
    void on_doubleSpinBox_p4_valueChanged(double arg1);
    void on_doubleSpinBox_p5_valueChanged(double arg1);
    void on_doubleSpinBox_p6_valueChanged(double arg1);
    void on_doubleSpinBox_p7_valueChanged(double arg1);
    void on_doubleSpinBox_p8_valueChanged(double arg1);

private:
    Ui::FormContextCurve *ui;

//    ParamModel * m_model = nullptr;
//    = nullptr;


    QDoubleSpinBox * m_spinKnots[13];
    QDoubleSpinBox * m_weights[9];

//    bool m_initialized = false;

};

#endif // FORMCONTEXTCURVE_H
