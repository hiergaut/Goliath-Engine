#include "QTreeView_outliner.h"

#include <QStandardItemModel>
//#include <engine/Scene.h>
#include <QMouseEvent>
#include <engine/Environment.h>

QTreeView_outliner::QTreeView_outliner(QWidget *parent) : QTreeView(parent)
{

//    setModel(model);
//    setModel(g_scene.model());
    setModel(g_env.m_scene.itemModel());



}

void QTreeView_outliner::mousePressEvent(QMouseEvent *event)
{
    event->ignore();
}
