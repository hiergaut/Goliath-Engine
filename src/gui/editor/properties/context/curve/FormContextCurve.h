#ifndef FORMCONTEXTCURVE_H
#define FORMCONTEXTCURVE_H

#include <QWidget>
#include <engine/scene/model/paramModel/ParamModel.h>

namespace Ui {
class FormContextCurve;
}

class FormContextCurve : public QWidget
{
    Q_OBJECT

public:
    explicit FormContextCurve(QWidget *parent = nullptr);
    ~FormContextCurve();

//    void setK(uint k);

private slots:
    void on_spinBox_k_valueChanged(int arg1);

private:
    Ui::FormContextCurve *ui;

    ParamModel * m_model = nullptr;

};

#endif // FORMCONTEXTCURVE_H
