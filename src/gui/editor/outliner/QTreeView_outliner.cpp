#include "QTreeView_outliner.h"

#include <QStandardItemModel>
#include <engine/Scene.h>
#include <QMouseEvent>

QTreeView_outliner::QTreeView_outliner(QWidget *parent) : QTreeView(parent)
{

//    setModel(model);
    setModel(g_scene.model());


}

void QTreeView_outliner::mousePressEvent(QMouseEvent *event)
{
    event->ignore();
}
