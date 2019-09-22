#ifndef FORMCONTEXTMATERIAL_H
#define FORMCONTEXTMATERIAL_H

#include <QWidget>

namespace Ui {
class FormContextMaterial;
}

class FormContextMaterial : public QWidget
{
    Q_OBJECT

public:
    explicit FormContextMaterial(QWidget *parent = nullptr);
    ~FormContextMaterial();

    void updateColor();

private slots:
    void on_doubleSpinBox_ambientR_valueChanged(double arg1);
    void on_doubleSpinBox_ambientG_valueChanged(double arg1);
    void on_doubleSpinBox_ambientB_valueChanged(double arg1);

    void on_doubleSpinBox_diffuseR_valueChanged(double arg1);
    void on_doubleSpinBox_diffuseG_valueChanged(double arg1);
    void on_doubleSpinBox_diffuseB_valueChanged(double arg1);

    void on_doubleSpinBox_specularR_valueChanged(double arg1);
    void on_doubleSpinBox_specularG_valueChanged(double arg1);
    void on_doubleSpinBox_specularB_valueChanged(double arg1);


    void on_doubleSpinBox_shininess_valueChanged(double arg1);

private:
    Ui::FormContextMaterial *ui;
};

#endif // FORMCONTEXTMATERIAL_H
