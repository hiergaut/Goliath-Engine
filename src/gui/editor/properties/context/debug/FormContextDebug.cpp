#include "FormContextDebug.h"
#include "ui_FormContextDebug.h"

FormContextDebug::FormContextDebug(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormContextDebug)
{
    ui->setupUi(this);
}

FormContextDebug::~FormContextDebug()
{
    delete ui;
}
