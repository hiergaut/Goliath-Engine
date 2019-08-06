#include "MainWindowProperties.h"
#include "ui_MainWindowProperties.h"

#include "context/material/FormContextMaterial.h"

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

void MainWindowProperties::setContext(Properties::e_context context)
{
    delete centralWidget();

    switch (context) {
    case Properties::e_context::MATERIAL:
        setCentralWidget(new FormContextMaterial);
        break;

    }

    centralWidget()->setFocusPolicy(Qt::ClickFocus);

}

void MainWindowProperties::on_actionMaterial_triggered()
{
    setContext(Properties::e_context::MATERIAL);

}
