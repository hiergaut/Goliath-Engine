#include "QSplitterNode.h"

#include <QDebug>
#include <QSettings>
#include <QCryptographicHash>
#include <sstream>
#include <iostream>

#include <QSplitterHandle>

QSplitterNode::QSplitterNode(QWidget* parent, QString name)
    : QSplitter(parent)
    , m_name(name)
{

    //    connect(this, &QSplitterNode::splitterMoved, this, &QSplitterNode::onSplitterMoved);
    //    connect(this, SIGNAL(splitterMoved(int, int)), this, SLOT(onSplitterMoved(int, int)));
    //    qDebug() << this << ": handleWidth = " << this->handleWidth();
    //    qDebug() << this << handle(0);
    //    qDebug() << this << ": handle(0) = " << handle(0);
//    setStyleSheet("background-color: " + 222);

//    QByteArray array = QCryptographicHash::hash(this);

//    QString ptr = QString::number(this);
//    qDebug() << this;
//    std::ostringstream address;
//    address << (void const *) this;
//    std::string str = address.str();

//    std::cout << str << std::endl;

//    int rand1 = 100 + qrand() % 155;
//    int rand2 = 100 + qrand() % 155;
//    int rand3 = 100 + qrand() % 155;
////    this->setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(rand1).arg(rand2).arg(rand3));
///
///

//    setMouseTracking(true);
}

//void QSplitterNode::setup()
//{
//    for (int i = 0; i < 3; ++i) {
//        qDebug() << this << ": handle(" << i << ") = " << handle(i);
//    }

//    //    for (int i =0; i <count(); ++i) {

//    //    }
//}

void QSplitterNode::loadSetting()
{
    int rand1 = 100 + qrand() % 155;
    int rand2 = 100 + qrand() % 155;
    int rand3 = 100 + qrand() % 155;
    this->setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(rand1).arg(rand2).arg(rand3));

    QSettings settings("Goliath-Engine", "splitterTree");
    settings.beginGroup("splitterTree");


    m_sizes = settings.value(m_name).value<QList<int>>();
    qDebug() << m_sizes;

//    m_nbSons = settings.value(m_name + "m_nbSons", 0).toInt();
//    for (int i =0; i <m_nbSons; ++i) {
//        QSplitterNode node(this, "root" + QString::number(i));
////        node.setup();
//        node.loadSetting();
//        m_sons.push_back(node);
////        m_sons.insert(0, node);
//    }

    settings.endGroup();
}

void QSplitterNode::resizeEvent(QResizeEvent* ev)
{
    //    qDebug() << this << ": resizeEvent";
    QSplitter::resizeEvent(ev);
}

void QSplitterNode::moveSplitter(int pos, int index)
{
    qDebug() << this << ": moveSplitter";
}

void QSplitterNode::mouseMoveEvent(QMouseEvent *)
{
    qDebug() << this << ": mouseMoveEvent";

}

void QSplitterNode::mousePressEvent(QMouseEvent*)
{
    qDebug() << this << ": mousePressEvent";
    //    connect(this->handle(3), SIGNAL(mousePressEvent()), this, SLOT(onHandleMousePressEvent()));
    //    qDebug() << this << ": handle(0) = " << handle(0);
}

//void QSplitterNode::dragEnterEvent(QDragEnterEvent *)
//{
//    qDebug() << this << ": dragEnterEvent";

//}

void QSplitterNode::onSplitterMoved(int pos, int index)
{
    qDebug() << this << ": onSplitterMoved";
}
