#include "FormEditor.h"
#include "ui_FormEditor.h"

FormEditor::FormEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormEditor)
{
    ui->setupUi(this);
}

FormEditor::~FormEditor()
{
    delete ui;
}
