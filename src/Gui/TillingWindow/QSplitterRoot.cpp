#include "Gui/TillingWindow/QSplitterRoot.h"

#include <QDebug>

QSplitterRoot::QSplitterRoot(QWidget* parent)
    : QSplitterNode(parent)
    , m_setting("Goliath-Engine", "splitterRoot")
{
//    QWidget * widget;
//    widget= new QWidget();
//    widget->setStyleSheet("background-color: black;");
//    addWidget(widget);
//    widget= new QWidget();
//    widget->setStyleSheet("background-color: red;");
//    addWidget(widget);
//    widget= new QWidget();
//    widget->setStyleSheet("background-color: purple;");
//    addWidget(widget);
//    widget= new QWidget();
//    widget->setStyleSheet("background-color: yellow;");
//    addWidget(widget);

//    QList<int> mySize;
//    mySize.append(m_setting.value("splitter0", 2).toInt());
//    mySize.append(m_setting.value("splitter1", 35).toInt());
//    mySize.append(m_setting.value("splitter2", 37).toInt());
//    mySize.append(m_setting.value("splitter3", 27).toInt());
//    setSizes(mySize);
}

//void QSplitterRoot::setup()
//{
//    qDebug() << "QSplitterRoot::setup()";

//}
