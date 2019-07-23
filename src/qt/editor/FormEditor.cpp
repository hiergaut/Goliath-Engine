#include "FormEditor.h"
#include "ui_FormEditor.h"

#include <QDebug>

FormEditor::FormEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormEditor)
{
    ui->setupUi(this);

//    connect(ui->labelOpener_bottomLeft, &QLabelOpener::addingNewHSplit, this, &FormEditor::onNewHSplitAdded);
//    connect(ui->labelOpener_bottomLeft, &QLabelOpener::addingNewVSplit, this, &FormEditor::onNewVSplitAdded);

    connect(ui->labelOpener_bottomLeft, &QLabelOpener::addingNewHSplit, this, &FormEditor::addingNewHSplit);
    connect(ui->labelOpener_bottomLeft, &QLabelOpener::addingNewVSplit, this, &FormEditor::addingNewVSplit);

//    connect(ui->labelOpener_bottomLeft, &QLabelOpener::addingNewHSplit, parent, &FormEditor::addingNewHSplit);
//    connect(ui->labelOpener_bottomLeft, &QLabelOpener::addingNewVSplit, parent, &FormEditor::addingNewVSplit);

}

FormEditor::~FormEditor()
{
    delete ui;
}

//void FormEditor::onNewHSplitAdded(QMouseEvent *ev)
//{
//    qDebug() << this << ": onNewHSplitAdded";

//}

//void FormEditor::onNewVSplitAdded(QMouseEvent *ev)
//{
//    qDebug() << this << ": onNewVSplitAdded";

//}
