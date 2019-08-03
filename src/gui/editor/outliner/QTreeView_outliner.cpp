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



}

void QTreeView_outliner::mousePressEvent(QMouseEvent *event)
{
    qDebug() << this;
    event->ignore();
}

void QTreeView_outliner::setModelScene(QStandardItemModel *modelScene)
{
    m_modelScene = modelScene;
}
