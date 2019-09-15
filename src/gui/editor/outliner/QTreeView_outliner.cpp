#include "QTreeView_outliner.h"

#include <QStandardItemModel>
//#include <engine/Scene.h>
#include <QMouseEvent>
//#include <engine/Environment.h>
#include <QDebug>
#include <QList>

#include <QLabel>
#include "ItemModelPackage.h"

QStandardItemModel * QTreeView_outliner::m_modelScene = nullptr;

QTreeView_outliner::QTreeView_outliner(QWidget *parent) : QTreeView(parent)
{

//    setModel(model);
//    setModel(g_scene.model());
//    setModel(g_env.m_scene.itemModel());
    Q_ASSERT(m_modelScene != nullptr);
//    setModel(m_model);

      this->setModel(m_modelScene);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);

//    qDebug() << "[TreeView]" << this << m_modelScene << m_modelScene->rowCount() << m_modelScene->columnCount();

    connect(m_modelScene, &QStandardItemModel::dataChanged, this, &QTreeView_outliner::on_changingData);
//    connect(m_modelScene, &QStandardItemModel::rowsInserted, this, &QTreeView_outliner::on_changingData);


    connect(this, &QTreeView::clicked, this, &QTreeView_outliner::on_click);


    expandAll();

    for (uint i =0; i <m_modelScene->rowCount(); ++i) {
//        qDebug() << m_modelScene->data(m_modelScene->index(i, 0));
        const QModelIndex & index = m_modelScene->index(i, 0);
        collapse(index);
    }

//    this->setRootIndex(m_modelScene->index(0, 0));
//    this->setCurrentIndex(m_modelScene->index(0, 0));
//    setExpandsOnDoubleClick(true);
//    expandAll();
//    setStyleSheet("background-color: white;");

}

void QTreeView_outliner::mousePressEvent(QMouseEvent *event)
{
//    qDebug() << this;
    QTreeView::mousePressEvent(event);
//    qDebug() << "[TreeView]" << this << m_modelScene << m_modelScene->rowCount() << m_modelScene->columnCount();
//    qDebug() << m_modelScene->item(0, 0);
    event->ignore();
    //    expandAll();
}

void QTreeView_outliner::setFocusPolicy(Qt::FocusPolicy policy)
{
    QTreeView::setFocusPolicy(policy);
}

QWidget *QTreeView_outliner::widget()
{
    return this;
}

void QTreeView_outliner::on_changingData()
{
//    qDebug() << "data changed";
    expandAll();

    for (uint i =0; i <m_modelScene->rowCount(); ++i) {
//        qDebug() << m_modelScene->data(m_modelScene->index(i, 0));
        const QModelIndex & index = m_modelScene->index(i, 0);
        collapse(index);
    }
}

void QTreeView_outliner::on_click(const QModelIndex &index)
{
//    qDebug() << "outliner on_click " << m_modelScene->data(index, Qt::UserRole).data();

    ItemModelPackage::click(m_modelScene->data(index, Qt::UserRole));
//    void * package = m_modelScene->data(index, Qt::UserRole).data();
//    if (package != nullptr) {
//        auto data = ItemModelPackage::unpack(package);
//        ItemModelPackage::click(package);
//    }


}

void QTreeView_outliner::setModelScene(QStandardItemModel *modelScene)
{
    m_modelScene = modelScene;
}
