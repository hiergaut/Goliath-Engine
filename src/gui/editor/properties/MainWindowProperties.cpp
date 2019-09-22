#include "MainWindowProperties.h"
#include "ui_MainWindowProperties.h"

#include "context/material/FormContextMaterial.h"
#include "context/curve/FormContextCurve.h"
#include "context/surface/FormContextSurface.h"
#include <session/Session.h>

MainWindowProperties::MainWindowProperties(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowProperties)
{
    ui->setupUi(this);
}

MainWindowProperties::~MainWindowProperties()
{
    delete ui;
}

void MainWindowProperties::save(std::ofstream &file)
{
    Session::saveEnum(m_context, file);

}

void MainWindowProperties::load(std::ifstream &file)
{
    m_context = static_cast<Type>(Session::loadEnum(file));

    setContext(m_context);
//    switch (m_context) {
//    case Type::MATERIAL:
//        setCentralWidget(new FormContextMaterial);
//        break;

//    case Type::CURVE:
//        setCentralWidget(new FormContextCurve);
//        break;

//    }

//    centralWidget()->setFocusPolicy(Qt::ClickFocus);

}

void MainWindowProperties::setContext(Type context)
{
    delete centralWidget();
    m_context = context;

    switch (context) {
    case Type::MATERIAL:
        setCentralWidget(new FormContextMaterial);
        ui->menuCurrentContext->setTitle("Material");
        break;

    case Type::CURVE:
        setCentralWidget(new FormContextCurve);
        ui->menuCurrentContext->setTitle("Curve");
        break;

    case Type::SURFACE:
        setCentralWidget(new FormContextSurface);
        ui->menuCurrentContext->setTitle("Surface");
        break;

    }

    centralWidget()->setFocusPolicy(Qt::ClickFocus);

}

void MainWindowProperties::setFocusPolicy(Qt::FocusPolicy policy)
{
    QWidget::setFocusPolicy(policy);
}

QWidget *MainWindowProperties::widget()
{
    return this;
}

void MainWindowProperties::on_actionMaterial_triggered()
{
    setContext(Type::MATERIAL);

}

void MainWindowProperties::on_actionCurve_triggered()
{
    setContext(Type::CURVE);
}

void MainWindowProperties::on_actionSurface_triggered()
{
    setContext(Type::SURFACE);
}
