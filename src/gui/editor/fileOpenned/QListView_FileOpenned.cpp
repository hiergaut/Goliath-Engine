#include "QListView_FileOpenned.h"
#include <fstream>

#include <QDebug>
#include <QKeyEvent>

QStandardItemModel * QListView_FileOpenned::m_modelFileOpenned = nullptr;


QListView_FileOpenned::QListView_FileOpenned(QWidget *parent) : QListView(parent)
{
    Q_ASSERT(m_modelFileOpenned != nullptr);

    this->setModel(m_modelFileOpenned);

}


void QListView_FileOpenned::setModelFileOpenned(QStandardItemModel *modelFileOpenned)
{
    m_modelFileOpenned = modelFileOpenned;
}

void QListView_FileOpenned::keyPressEvent(QKeyEvent *ev)
{
//    qDebug() << "keyPressEvent" << ev;
    if (ev->key() == Qt::Key_Delete) {

//        this->selectedIndexes();
        QModelIndexList indexes = selectedIndexes();
        Q_ASSERT(indexes.size() == 1);

//        QString fileToRemove = m_modelFileOpenned->data(indexes.first()).toString();
//        qDebug() << "remove " << fileToRemove;

        m_modelFileOpenned->removeRow(indexes.first().row());

    }

}
