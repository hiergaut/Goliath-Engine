#include "FormContextLight.h"
#include "ui_FormContextLight.h"

#include <QDebug>
#include <engine/scene/light/PointLight.h>
#include <engine/scene/light/SpotLight.h>

Light* FormContextLight::m_light = nullptr;
std::list<FormContextLight*> FormContextLight::m_forms;

FormContextLight::FormContextLight(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::FormContextLight)
{
    ui->setupUi(this);

    //    setDisabled(true);
    setEnabled(false);
    m_forms.emplace_back(this);

    //    connect(ui->frame_ambient, &QFrame::wheelEvent, this, &FormContextLight::on_ambient_valueChanged);
}

FormContextLight::~FormContextLight()
{
    delete ui;

    m_forms.remove(this);
}

void FormContextLight::setLight(Light* light)
{
    m_light = light;

    for (auto* form : m_forms) {
        form->updateUi();
        //        qDebug() << "selected";
    }
}

void FormContextLight::updateUi()
{
    if (m_light == nullptr) {
        setEnabled(false);
        return;
    }
    //    ui->lineEdit_current->setText(m_light)

    ui->doubleSpinBox_ambient_red->setValue(m_light->m_ambient.r);
    ui->doubleSpinBox_ambient_green->setValue(m_light->m_ambient.g);
    ui->doubleSpinBox_ambient_blue->setValue(m_light->m_ambient.b);
    ui->frame_ambient->setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(m_light->m_ambient.r * 255).arg(m_light->m_ambient.g * 255).arg(m_light->m_ambient.b * 255));

    ui->doubleSpinBox_diffuse_red->setValue(m_light->m_diffuse.r);
    ui->doubleSpinBox_diffuse_green->setValue(m_light->m_diffuse.g);
    ui->doubleSpinBox_diffuse_blue->setValue(m_light->m_diffuse.b);
    ui->frame_diffuse->setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(m_light->m_diffuse.r * 255).arg(m_light->m_diffuse.g * 255).arg(m_light->m_diffuse.b * 255));

    ui->doubleSpinBox_specular_red->setValue(m_light->m_specular.r);
    ui->doubleSpinBox_specular_green->setValue(m_light->m_specular.g);
    ui->doubleSpinBox_specular_blue->setValue(m_light->m_specular.b);
    ui->frame_specular->setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(m_light->m_specular.r * 255).arg(m_light->m_specular.g * 255).arg(m_light->m_specular.b * 255));

    //    switch (m_light->m_type) {
    if (m_light->m_type == Light::Type::SPOT) {
        SpotLight* light = static_cast<SpotLight*>(m_light);

        ui->doubleSpinBox_constant->setValue(light->m_constant);
        ui->doubleSpinBox_linear->setValue(light->m_linear);
        ui->doubleSpinBox_quadratic->setValue(light->m_quadratic);

        ui->groupBox_attenuation->setEnabled(true);
        ui->groupBox_spot->setEnabled(true);

    } else if (m_light->m_type == Light::Type::POINT) {
        PointLight* light = static_cast<PointLight*>(m_light);

        ui->doubleSpinBox_constant->setValue(light->m_constant);
        ui->doubleSpinBox_linear->setValue(light->m_linear);
        ui->doubleSpinBox_quadratic->setValue(light->m_quadratic);

        ui->groupBox_attenuation->setEnabled(true);
        ui->groupBox_spot->setEnabled(false);
    }
    else {
        ui->groupBox_attenuation->setEnabled(false);
        ui->groupBox_spot->setEnabled(false);
    }
    //    ui->doubleSpinBox_constant->setValue(m_light.m_)

    setEnabled(true);
}

void FormContextLight::on_doubleSpinBox_ambient_red_valueChanged(double arg1)
{
    //    qDebug() << "red";
    if (m_light != nullptr) {
        m_light->m_ambient[0] = arg1;
    }
}
void FormContextLight::on_doubleSpinBox_ambient_green_valueChanged(double arg1)
{
    if (m_light != nullptr) {
        m_light->m_ambient[1] = arg1;
    }
}

void FormContextLight::on_doubleSpinBox_ambient_blue_valueChanged(double arg1)
{
    if (m_light != nullptr) {
        m_light->m_ambient[2] = arg1;
    }
}

void FormContextLight::on_doubleSpinBox_diffuse_red_valueChanged(double arg1)
{

    if (m_light != nullptr) {
        m_light->m_diffuse[0] = arg1;
    }
}
void FormContextLight::on_doubleSpinBox_diffuse_green_valueChanged(double arg1)
{

    if (m_light != nullptr) {
        m_light->m_diffuse[1] = arg1;
    }
}

void FormContextLight::on_doubleSpinBox_diffuse_blue_valueChanged(double arg1)
{
    if (m_light != nullptr) {
        m_light->m_diffuse[2] = arg1;
    }
}

void FormContextLight::on_doubleSpinBox_specular_red_valueChanged(double arg1)
{

    if (m_light != nullptr) {
        m_light->m_specular[0] = arg1;
    }
}
void FormContextLight::on_doubleSpinBox_specular_green_valueChanged(double arg1)
{

    if (m_light != nullptr) {
        m_light->m_specular[1] = arg1;
    }
}

void FormContextLight::on_doubleSpinBox_specular_blue_valueChanged(double arg1)
{
    //    qDebug() << "blue";

    if (m_light != nullptr) {
        m_light->m_specular[2] = arg1;
    }
}

void FormContextLight::on_doubleSpinBox_ambient_valueChanged(double arg1)
{
    if (m_light != nullptr) {
        float diff = arg1 - m_ambient;
        m_ambient = arg1;

        for (uint i = 0; i < 3; ++i) {
            m_light->m_ambient[i] += diff;
        }
        updateUi();
        //        ui->doubleSpinBox_ambient_red->setValue(ui->doubleSpinBox_ambient_red->value() + diff);
        //        ui->doubleSpinBox_ambient_green->setValue(ui->doubleSpinBox_ambient_green->value() + diff);
        //        ui->doubleSpinBox_ambient_blue->setValue(ui->doubleSpinBox_ambient_blue->value() + diff);
    }
}

void FormContextLight::on_doubleSpinBox_diffuse_valueChanged(double arg1)
{
    if (m_light != nullptr) {
        float diff = arg1 - m_diffuse;
        m_diffuse = arg1;

        for (uint i = 0; i < 3; ++i) {
            m_light->m_diffuse[i] += diff;
        }
        updateUi();
        //        ui->doubleSpinBox_diffuse->setValue(ui->doubleSpinBox_diffuse->value() + diff);
        //        ui->doubleSpinBox_diffuse->setValue(ui->doubleSpinBox_diffuse->value() + diff);
        //        ui->doubleSpinBox_diffuse->setValue(ui->doubleSpinBox_diffuse->value() + diff);
    }
}

void FormContextLight::on_doubleSpinBox_specular_valueChanged(double arg1)
{
    if (m_light != nullptr) {
        float diff = arg1 - m_specular;
        m_specular = arg1;

        for (uint i = 0; i < 3; ++i) {
            m_light->m_specular[i] += diff;
        }
        updateUi();
        //        ui->doubleSpinBox_specular->setValue(ui->doubleSpinBox_specular->value() + diff);
        //        ui->doubleSpinBox_specular->setValue(ui->doubleSpinBox_specular->value() + diff);
        //        ui->doubleSpinBox_specular->setValue(ui->doubleSpinBox_specular->value() + diff);
    }
}

void FormContextLight::on_doubleSpinBox_constant_valueChanged(double arg1)
{
    if (m_light != nullptr) {
        if (m_light->m_type == Light::Type::SPOT) {
            SpotLight* light = static_cast<SpotLight*>(m_light);

            light->m_constant = arg1;

        } else if (m_light->m_type == Light::Type::POINT) {
            PointLight* light = static_cast<PointLight*>(m_light);

            light->m_constant = arg1;
        }
        updateUi();
    }
}

void FormContextLight::on_doubleSpinBox_linear_valueChanged(double arg1)
{
    if (m_light != nullptr) {
        if (m_light->m_type == Light::Type::SPOT) {
            SpotLight* light = static_cast<SpotLight*>(m_light);

            light->m_linear = arg1;

        } else if (m_light->m_type == Light::Type::POINT) {
            PointLight* light = static_cast<PointLight*>(m_light);

            light->m_linear = arg1;
        }
        updateUi();
    }
}

void FormContextLight::on_doubleSpinBox_quadratic_valueChanged(double arg1)
{
    if (m_light != nullptr) {
        if (m_light->m_type == Light::Type::SPOT) {
            SpotLight* light = static_cast<SpotLight*>(m_light);

            light->m_quadratic = arg1;

        } else if (m_light->m_type == Light::Type::POINT) {
            PointLight* light = static_cast<PointLight*>(m_light);

            light->m_quadratic = arg1;
        }
        updateUi();
    }
}
