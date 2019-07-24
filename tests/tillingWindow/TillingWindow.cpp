#include "TillingWindow.h"
#include "ui_TillingWindow.h"

TillingWindow::TillingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TillingWindow)
{
    ui->setupUi(this);
}

TillingWindow::~TillingWindow()
{
    delete ui;
}
