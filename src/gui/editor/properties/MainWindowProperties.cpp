#include "MainWindowProperties.h"
#include "ui_MainWindowProperties.h"

#include "context/material/FormContextMaterial.h"
#include "context/curve/FormContextCurve.h"
#include "context/surface/FormContextSurface.h"
#include "context/debug/FormContextDebug.h"
#include "context/light/FormContextLight.h"
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


//    case Type::DEBUG:
//        setCentralWidget(new FormContextDebug);
//        ui->menuCurrentContext->setTitle("Debug");
//        break;

    case Type::LIGHT:
        setCentralWidget(new FormContextLight);
        ui->menuCurrentContext->setTitle("Light");
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

void MainWindowProperties::on_actionDebug_triggered()
{
//    setContext(Type::DEBUG);
}

void MainWindowProperties::on_actionLight_triggered()
{
    setContext(Type::LIGHT);
}
