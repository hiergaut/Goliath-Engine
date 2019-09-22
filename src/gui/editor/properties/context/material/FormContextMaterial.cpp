#include "FormContextMaterial.h"
#include "ui_FormContextMaterial.h"

#include <engine/scene/Scene.h>

FormContextMaterial::FormContextMaterial(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::FormContextMaterial)
{
    ui->setupUi(this);

    ui->listView->setModel(&Scene::m_scene->m_sceneModel);
    //    ui->listView->setRootIndex(Scene::m_sceneModel.index(1, 1));
    //    ui->listView->setCurrentIndex(Scene::m_sceneModel.index(1, 1));
    updateColor();
}

FormContextMaterial::~FormContextMaterial()
{
    delete ui;
}

void FormContextMaterial::updateColor()
{
    Material & solid = Scene::m_scene->m_solid;
    ui->doubleSpinBox_ambientR->setValue(solid.ambient().r);
    ui->doubleSpinBox_ambientG->setValue(solid.ambient().g);
    ui->doubleSpinBox_ambientB->setValue(solid.ambient().b);
    ui->frame_ambient->setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(solid.ambient().r * 255).arg(solid.ambient().g * 255).arg(solid.ambient().b * 255));
    ui->doubleSpinBox_diffuseR->setValue(solid.diffuse().r);
    ui->doubleSpinBox_diffuseG->setValue(solid.diffuse().g);
    ui->doubleSpinBox_diffuseB->setValue(solid.diffuse().b);
    ui->frame_diffuse->setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(solid.diffuse().r * 255).arg(solid.diffuse().g * 255).arg(solid.diffuse().b * 255));
    ui->doubleSpinBox_specularR->setValue(solid.specular().r);
    ui->doubleSpinBox_specularG->setValue(solid.specular().g);
    ui->doubleSpinBox_specularB->setValue(solid.specular().b);
    ui->frame_specular->setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(solid.specular().r * 255).arg(solid.specular().g * 255).arg(solid.specular().b * 255));

    ui->doubleSpinBox_shininess->setValue(solid.m_shininess);
}

void FormContextMaterial::on_doubleSpinBox_ambientR_valueChanged(double arg1)
{
    Scene::m_scene->m_solid.ambient().r = arg1;
    updateColor();
}

void FormContextMaterial::on_doubleSpinBox_ambientG_valueChanged(double arg1)
{
    Scene::m_scene->m_solid.ambient().g = arg1;
    updateColor();
}

void FormContextMaterial::on_doubleSpinBox_ambientB_valueChanged(double arg1)
{
    Scene::m_scene->m_solid.ambient().b = arg1;
    updateColor();
}

void FormContextMaterial::on_doubleSpinBox_diffuseR_valueChanged(double arg1)
{
    Scene::m_scene->m_solid.diffuse().r = arg1;
    updateColor();
}

void FormContextMaterial::on_doubleSpinBox_diffuseG_valueChanged(double arg1)
{
    Scene::m_scene->m_solid.diffuse().g = arg1;
    updateColor();
}

void FormContextMaterial::on_doubleSpinBox_diffuseB_valueChanged(double arg1)
{
    Scene::m_scene->m_solid.diffuse().b = arg1;
    updateColor();
}

void FormContextMaterial::on_doubleSpinBox_specularR_valueChanged(double arg1)
{
    Scene::m_scene->m_solid.specular().r = arg1;
    updateColor();
}

void FormContextMaterial::on_doubleSpinBox_specularG_valueChanged(double arg1)
{
    Scene::m_scene->m_solid.specular().g = arg1;
    updateColor();
}

void FormContextMaterial::on_doubleSpinBox_specularB_valueChanged(double arg1)
{
    Scene::m_scene->m_solid.specular().b = arg1;
    updateColor();
}

void FormContextMaterial::on_doubleSpinBox_shininess_valueChanged(double arg1)
{
    Scene::m_scene->m_solid.m_shininess = arg1;
    updateColor();
}
