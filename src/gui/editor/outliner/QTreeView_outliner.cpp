#include "QTreeView_outliner.h"

#include <QStandardItemModel>
//#include <engine/Scene.h>
#include <QMouseEvent>
//#include <engine/Environment.h>
#include <QDebug>
#include <QList>

#include <QLabel>

QStandardItemModel * QTreeView_outliner::m_modelScene = nullptr;

QTreeView_outliner::QTreeView_outliner(QWidget *parent) : QTreeView(parent)
{

//    setModel(model);
//    setModel(g_scene.model());
//    setModel(g_env.m_scene.itemModel());
    Q_ASSERT(m_modelScene != nullptr);
//    setModel(m_model);

      this->setModel(m_modelScene);

//    qDebug() << "[TreeView]" << this << m_modelScene << m_modelScene->rowCount() << m_modelScene->columnCount();

    connect(m_modelScene, &QStandardItemModel::dataChanged, this, &QTreeView_outliner::on_changingData);
//    connect(m_modelScene, &QStandardItemModel::rowsInserted, this, &QTreeView_outliner::on_changingData);


//    this->setRootIndex(m_modelScene->index(0, 0));
//    this->setCurrentIndex(m_modelScene->index(0, 0));
//    setExpandsOnDoubleClick(true);
//    expandAll();

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

void QTreeView_outliner::on_changingData()
{
//    qDebug() << "data changed";
    expandAll();

}

void QTreeView_outliner::setModelScene(QStandardItemModel *modelScene)
{
    m_modelScene = modelScene;
}
