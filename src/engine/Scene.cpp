#include "Scene.h"

Scene::Scene()
{

    m_model = new QStandardItemModel;

    QStandardItem * item0 = new QStandardItem("Scene");
//    QStandardItem * item1 = new QStandardItem("World");
//    item0->appendRow(item1);
    m_model->appendRow(item0);
//    model->appendColumn(item0);


}

QStandardItemModel *Scene::model() const
{
    return m_model;
}
