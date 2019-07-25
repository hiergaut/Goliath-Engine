#include "FormEditor.h"
#include "ui_FormEditor.h"

#include <QDebug>


FormEditor::FormEditor(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::FormEditor)
//    , m_parent(static_cast<QSplitterNode*>(parent))
{
    ui->setupUi(this);

    //    connect(ui->labelOpener_bottomLeft, &QLabelOpener::addingNewHSplit, this, &FormEditor::onNewHSplitAdded);
    //    connect(ui->labelOpener_bottomLeft, &QLabelOpener::addingNewVSplit, this, &FormEditor::onNewVSplitAdded);

//    connect(ui->labelOpener_bottomLeft, &QLabelOpener::addingNewHSplit, this, &FormEditor::onNewHSplitAdded);
//    connect(ui->labelOpener_bottomLeft, &QLabelOpener::addingNewVSplit, this, &FormEditor::onNewVSplitAdded);

    //    connect(ui->labelOpener_bottomLeft, &QLabelOpener::addingNewHSplit, parent, &FormEditor::addingNewHSplit);
    //    connect(ui->labelOpener_bottomLeft, &QLabelOpener::addingNewVSplit, parent, &FormEditor::addingNewVSplit);
        int rand1 = 100 + qrand() % 155;
        int rand2 = 100 + qrand() % 155;
        int rand3 = 100 + qrand() % 155;
        setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(rand1).arg(rand2).arg(rand3));
}

FormEditor::~FormEditor()
{
    delete ui;
}

//void FormEditor::onNewHSplitAdded(QMouseEvent *ev)
//{
////    qDebug() << this << ": onNewHSplitAdded";
////    m_parent->onNewHSplitAdded(ev);

//}

//void FormEditor::onNewVSplitAdded(QMouseEvent *ev)
//{
////    qDebug() << this << ": onNewVSplitAdded";

////    m_parent->onNewVSplitAdded(ev);
//}
