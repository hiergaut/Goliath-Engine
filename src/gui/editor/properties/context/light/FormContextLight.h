#ifndef FORMCONTEXTLIGHT_H
#define FORMCONTEXTLIGHT_H

#include <QWidget>
#include <engine/scene/light/Light.h>

namespace Ui {
class FormContextLight;
}

class FormContextLight : public QWidget {
    Q_OBJECT


public:
    explicit FormContextLight(QWidget* parent = nullptr);
    ~FormContextLight();

    static void setLight(Light * light);
    void updateUi();

private slots:
    void on_doubleSpinBox_ambient_red_valueChanged(double arg1);
    void on_doubleSpinBox_ambient_green_valueChanged(double arg1);
    void on_doubleSpinBox_ambient_blue_valueChanged(double arg1);

    void on_doubleSpinBox_diffuse_red_valueChanged(double arg1);
    void on_doubleSpinBox_diffuse_green_valueChanged(double arg1);
    void on_doubleSpinBox_diffuse_blue_valueChanged(double arg1);

    void on_doubleSpinBox_specular_red_valueChanged(double arg1);
    void on_doubleSpinBox_specular_green_valueChanged(double arg1);
    void on_doubleSpinBox_specular_blue_valueChanged(double arg1);

//    void on_ambient_valueChanged(QWheelEvent * event);

    void on_doubleSpinBox_ambient_valueChanged(double arg1);
    void on_doubleSpinBox_diffuse_valueChanged(double arg1);
    void on_doubleSpinBox_specular_valueChanged(double arg1);

    void on_doubleSpinBox_constant_valueChanged(double arg1);
    void on_doubleSpinBox_linear_valueChanged(double arg1);
    void on_doubleSpinBox_quadratic_valueChanged(double arg1);

private:
    Ui::FormContextLight* ui;
    static Light * m_light;
    static std::list<FormContextLight*> m_forms;

    float m_ambient = 0.0f;
    float m_diffuse = 0.0f;
    float m_specular = 0.0f;
};

#endif // FORMCONTEXTLIGHT_H
