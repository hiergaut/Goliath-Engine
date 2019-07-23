#include "QSplitterNode.h"

#include <QCryptographicHash>
#include <QDebug>
#include <QSettings>
#include <iostream>
#include <sstream>
#include <QLayout>

#include "editor/FormEditor.h"
#include <QSplitterHandle>

#include <QLabel>

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

                int rand1 = 100 + qrand() % 155;
                int rand2 = 100 + qrand() % 155;
                int rand3 = 100 + qrand() % 155;
                this->setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(rand1).arg(rand2).arg(rand3));

    //        setStyleSheet("background-color: black");
    ///
    ///

    //    setMouseTracking(true);
}

void QSplitterNode::setup()
{
    //    for (int i = 0; i < 3; ++i) {
    //        qDebug() << this << ": handle(" << i << ") = " << handle(i);
    //    }
    if (count() == 1) {
        FormEditor* w = static_cast<FormEditor*>(widget(0));
        connect(w, &FormEditor::addingNewHSplit, this, &QSplitterNode::onNewHSplitAdded);
        connect(w, &FormEditor::addingNewVSplit, this, &QSplitterNode::onNewVSplitAdded);

        qDebug() << this << ": leaf widget " << w;

    } else {
        for (int i = 0; i < count(); ++i) {
            QSplitterNode* node = static_cast<QSplitterNode*>(widget(i));
            node->setup();
            //            connect(w, &FormEditor::addingNewHSplit, this, &QSplitterNode::onNewHSplitAdded);
        }
    }
}

void QSplitterNode::loadSetting()
{
    //    int rand1 = 100 + qrand() % 155;
    //    int rand2 = 100 + qrand() % 155;
    //    int rand3 = 100 + qrand() % 155;
    //    this->setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(rand1).arg(rand2).arg(rand3));

    QSettings settings("Goliath-Engine", "splitterTree");
    settings.beginGroup("splitterTree");

    m_sizes = settings.value(m_name).value<QList<int>>();
    qDebug() << m_sizes;

    if (m_sizes.size() == 0) {
        FormEditor* widget;
        widget = new FormEditor(this);
        connect(widget, &FormEditor::addingNewHSplit, this, &QSplitterNode::onNewHSplitAdded);
        connect(widget, &FormEditor::addingNewVSplit, this, &QSplitterNode::onNewVSplitAdded);
        addWidget(widget);

        //        QSplitterNode * node = new QSplitterNode(this, m_name + QString::number(m_sizes.size()));
    }

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

void QSplitterNode::onNewHSplitAdded(QMouseEvent* ev)
{
    //    qDebug() << this << "onNewHSplitAdded";
    QSplitterNode* parent = static_cast<QSplitterNode*>(this->parentWidget());
    qDebug() << "parent : " << parent;

//    widget = new FormEditor(this);

    if (parent->orientation() == Qt::Horizontal) {
        qDebug() << "same orientation";

                QSplitterNode * node = new QSplitterNode(this->parentWidget());
                FormEditor * widget = new FormEditor(node);

                connect(widget, &FormEditor::addingNewHSplit, node, &QSplitterNode::onNewHSplitAdded);
                connect(widget, &FormEditor::addingNewVSplit, node, &QSplitterNode::onNewVSplitAdded);

//                addWidget(node);
                parent->addWidget(node);

    } else {
        qDebug() << "not same orientation";
//        FormEditor * son = static_cast<FormEditor*>(widget(0));
//        this = new QSplitterNode(parentWidget());
//        this->setOrientation(Qt::Horizontal);

        QSplitterNode * node = new QSplitterNode(this);
        node->setOrientation(Qt::Horizontal);

        QSplitterNode * node2 = new QSplitterNode(node);
        FormEditor * widget2 = new FormEditor(node2);
    connect(widget2, &FormEditor::addingNewHSplit, node2, &QSplitterNode::onNewHSplitAdded);
    connect(widget2, &FormEditor::addingNewVSplit, node2, &QSplitterNode::onNewVSplitAdded);


        parent->addWidget(node);
        setParent(node);

//        FormEditor * nodeForm = new FormEditor(node);

    }


    //    addWidget()
}

void QSplitterNode::onNewVSplitAdded(QMouseEvent* ev)
{
    qDebug() << this << "onNewVSplitAdded";
}

//void QSplitterNode::resizeEvent(QResizeEvent* ev)
//{
//    //    qDebug() << this << ": resizeEvent";
//    QSplitter::resizeEvent(ev);
//}

//void QSplitterNode::moveSplitter(int pos, int index)
//{
//    qDebug() << this << ": moveSplitter";
//}

//void QSplitterNode::mouseMoveEvent(QMouseEvent *)
//{
//    qDebug() << this << ": mouseMoveEvent";

//}

void QSplitterNode::mousePressEvent(QMouseEvent*)
{
    qDebug() << this << ": mousePressEvent, parent = " << parentWidget();
    //    connect(this->handle(3), SIGNAL(mousePressEvent()), this, SLOT(onHandleMousePressEvent()));
    //    qDebug() << this << ": handle(0) = " << handle(0);
}

//void QSplitterNode::dragEnterEvent(QDragEnterEvent *)
//{
//    qDebug() << this << ": dragEnterEvent";

//}

//void QSplitterNode::onSplitterMoved(int pos, int index)
//{
//    qDebug() << this << ": onSplitterMoved";
//}
