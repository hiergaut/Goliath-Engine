#include "QListView_FileOpenned.h"
#include <fstream>

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
