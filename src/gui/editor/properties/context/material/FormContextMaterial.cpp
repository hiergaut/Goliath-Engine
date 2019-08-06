#include "FormContextMaterial.h"
#include "ui_FormContextMaterial.h"

#include <engine/Scene.h>

FormContextMaterial::FormContextMaterial(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormContextMaterial)
{
    ui->setupUi(this);

    ui->listView->setModel(&Scene::m_sceneModel);
//    ui->listView->setRootIndex(Scene::m_sceneModel.index(1, 1));
//    ui->listView->setCurrentIndex(Scene::m_sceneModel.index(1, 1));
}

FormContextMaterial::~FormContextMaterial()
{
    delete ui;
}
