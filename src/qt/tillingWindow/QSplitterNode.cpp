#include "QSplitterNode.h"

#include <QCryptographicHash>
#include <QDebug>
#include <QLayout>
#include <QSettings>
#include <iostream>
#include <sstream>

#include "editor/FormEditor.h"
#include <QSplitterHandle>

#include <QLabel>

namespace {
QSizePolicy::Policy singlePolicy(QSizePolicy::Policy::Ignored);
QSizePolicy defaultPolicy(singlePolicy, singlePolicy);
//QList<QSplitterNode> nodes;
//QList<QList<int>> sizes;
QString groupName = "splitterTree0";
}

QSplitterNode::QSplitterNode(QWidget* parent, QString name)
    : QSplitter(parent)
    , m_name(name)
{

    connect(this, &QSplitterNode::splitterMoved, this, &QSplitterNode::onSplitterMoved);
    setSizePolicy(::defaultPolicy);
    setOrientation(Qt::Horizontal);
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
    //    this->setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(rand1).arg(rand2).arg(rand3));

    //        setStyleSheet("background-color: black");
    ///
    ///

    //    setMouseTracking(true);
}

void QSplitterNode::setup()
{
    Q_ASSERT(count() > 0);
    //    for (int i = 0; i < 3; ++i) {
    //        qDebug() << this << ": handle(" << i << ") = " << handle(i);
    //    setSizePolicy(defaultPolicy);
    //    }
    if (count() != 1) {
        //        FormEditor* w = static_cast<FormEditor*>(widget(0));
        //        connect(w, &FormEditor::addingNewHSplit, this, &QSplitterNode::onNewHSplitAdded);
        //        connect(w, &FormEditor::addingNewVSplit, this, &QSplitterNode::onNewVSplitAdded);

        //        qDebug() << this << ": leaf widget " << w;

        for (int i = 0; i < count(); ++i) {
            QSplitterNode* node = static_cast<QSplitterNode*>(widget(i));
            node->setName(m_name + QString::number(i));
            //            node->setOrientation(Qt::Vertical);
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
    settings.beginGroup(::groupName);

    //    m_sizes = settings.value(m_name).value<QList<int>>();
    //    qDebug() << m_sizes;
    //    nodes = settings.value("nodes").value<QList<QSplitterNode>>();
    //    qRegisterMetaTypeStreamOperators<QList<QList<int>>>("QList<QList<int>>");

    m_sizes = settings.value(m_name).value<QList<int>>();
//    Q_ASSERT(m_sizes.size() != 0);
    qDebug() << m_name << ": m_sizes = " << m_sizes;
    if (m_sizes.size() == 0 || (m_sizes.size() == 1 && m_name == "root")) {
        QSplitterNode* node = new QSplitterNode(this, this->m_name + "0");
        node->addWidget(new FormEditor);

        addWidget(node);
    }

    //        setSizes(m_sizes);
    else if (m_sizes.size() == 1) {
        //        if (m_name == "root") {
        //            QSplitterNode* node = new QSplitterNode(this, this->m_name + "0");
        //            node->addWidget(new FormEditor);

        //            addWidget(node);
        //        } else {

        //        qDebug() << "loadSetting: " << m_name << " leaf";
        addWidget(new FormEditor);
        //        }
    } else {
        for (int i = 0; i < m_sizes.size(); ++i) {
            QSplitterNode* node = new QSplitterNode(this, this->m_name + QString::number(i));
            //            node->setSizePolicy(::defaultPolicy);
            //            qDebug() << "loadSetting: " << m_name << " create node " << node->m_name;
            //            node->setOrientation(Qt::Vertical);
            //            node->setup();
            node->loadSetting();
            //            connect(w, &FormEditor::addingNewHSplit, this, &QSplitterNode::onNewHSplitAdded);
            addWidget(node);
        }
        setSizes(m_sizes);
        int orientation = settings.value(m_name + "orientation", Qt::Horizontal).value<int>();
        setOrientation((orientation == 0) ?(Qt::Horizontal) :(Qt::Vertical));
    }

    //    qDebug() << m_sizes;

    //    QList<QList<int>> def;
    //    ::sizes = settings.value("sizes").value<QList<QList<int>>>();
    //    qDebug() << ::sizes;

    //    if (m_sizes.size() == 0) {
    //        FormEditor* widget;
    //        widget = new FormEditor(this);
    //        addWidget(widget);

    //        //        QSplitterNode * node = new QSplitterNode(this, m_name + QString::number(m_sizes.size()));
    //    }

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

void QSplitterNode::saveSetting()
{
    QSettings settings("Goliath-Engine", "splitterTree");
    settings.beginGroup(::groupName);

    //    QList<QList<int>> sizes;
    //    settings.setValue("sizes", ::sizes);
    settings.setValue(m_name, QVariant::fromValue(sizes()));
    qDebug() << "settings.setValue(" << m_name << ", " << sizes() << ")";

    if (count() != 1) {
        int orientation = (this->orientation() == Qt::Horizontal) ?(0) :(1);
        settings.setValue(m_name + "orientation", QVariant::fromValue(orientation));

        for (int i = 0; i < count(); ++i) {
            QSplitterNode* node = static_cast<QSplitterNode*>(widget(i));
            node->setName(m_name + QString::number(i));
            //            node->setOrientation(Qt::Vertical);
            node->saveSetting();
            //            node->setup();
            //            connect(w, &FormEditor::addingNewHSplit, this, &QSplitterNode::onNewHSplitAdded);
        }
    }

    settings.endGroup();
}

//void QSplitterNode::onNewHSplitAdded(QMouseEvent* ev)
//{
//    Q_ASSERT(count() == 1);

//    //    qDebug() << this << "onNewHSplitAdded";
//    QSplitterNode* parent = static_cast<QSplitterNode*>(this->parentWidget());
//    qDebug() << "parent : " << parent;

//    //    widget = new FormEditor(this);

//    if (parent->orientation() == Qt::Horizontal) {
//        qDebug() << "same orientation";

//        QSplitterNode* node = new QSplitterNode(this->parentWidget());
//        FormEditor* widget = new FormEditor(node);

//        //                addWidget(node);
////        parent->addWidget(node);
//        parent->insertWidget(parent->indexOf(this), node);

////        handle(0)->mousePressEvent(ev);
////        handle(0)->scroll(ev->x(), 0);

//    } else {
//        qDebug() << "not same orientation";
//        //        FormEditor * son = static_cast<FormEditor*>(widget(0));
//        //        this = new QSplitterNode(parentWidget());
//        //        this->setOrientation(Qt::Horizontal);

//        setOrientation(Qt::Horizontal);
//        QSplitterNode* node = new QSplitterNode(this);
//        //        node->addWidget(widget(0));
//        widget(0)->setParent(node);
//        //        node->setOrientation(Qt::Horizontal);

//        //        node->addWidget(this);

//        QSplitterNode* node2 = new QSplitterNode(this);
//        FormEditor* widget2 = new FormEditor(node2);
//        addWidget(node2);

////        parent->addWidget(node);

////        node->addWidget(this);
//        //        node->insertWidget(0, this);
////        setParent(node);

//        //        setParent(nullptr);

//        //        FormEditor * nodeForm = new FormEditor(node);
//    }

//    //    addWidget()
//}

//void QSplitterNode::onNewVSplitAdded(QMouseEvent* ev)
//{
//    qDebug() << this << "onNewVSplitAdded";
//}

//void QSplitterNode::resizeEvent(QResizeEvent* ev)
//{
//    QSplitter::resizeEvent(ev);
//    if (count() == 1) {
//        QSplitterNode* parent = static_cast<QSplitterNode*>(this->parentWidget());
////        qDebug() << this << ": resizeEvent " << ev->size().height();
////        qDebug() << orientation();
//        if (parent->orientation() == Qt::Horizontal) {
//            if (ev->size().width() == 0) {
////                setParent(nullptr);
//                delete widget(0);
//            }
//        }
//        else {
//            if (ev->size().height() == 0) {
////                setParent(nullptr);
//                delete widget(0);
//            }

//        }
//    }
//}

//void QSplitterNode::moveSplitter(int pos, int index)
//{
//    qDebug() << this << ": moveSplitter";
//}

//void QSplitterNode::mouseMoveEvent(QMouseEvent *)
//{
//    qDebug() << this << ": mouseMoveEvent";

//}

void QSplitterNode::mousePressEvent(QMouseEvent* ev)
{
    Q_ASSERT(count() == 1);
    //    qDebug() << this << ": mousePressEvent, parent = " << parentWidget();

    qDebug() << m_name << ": " << static_cast<QSplitterNode*>(parentWidget())->m_name << orientation() << count() << size();
    //        qDebug() << m_name << ": "   << orientation() << count() <<  size();
    //    qDebug() << width() << ev;
    int width = this->width();
    int height = this->height();

    int x = ev->x();
    int y = ev->y();

    int border = 10;
    QSplitterNode* parent = static_cast<QSplitterNode*>(this->parentWidget());

    //    qDebug() << this->sizePolicy() << parent->orientation();

    if (x < border || width - border < x || y < border || height - border < y) {
        Qt::Orientation orientation;
        int offset;
        if (x < border || width - border < x) {
            offset = (x < border) ? (0) : (1);
            orientation = Qt::Horizontal;
        } else {
            offset = (y < border) ? (0) : (1);
            orientation = Qt::Vertical;
        }

        //                setCursor(Qt::SplitHCursor);
        //        QWidget* widget = new QWidget;
        //        int rand1 = 100 + qrand() % 155;
        //        int rand2 = 100 + qrand() % 155;
        //        int rand3 = 100 + qrand() % 155;
        //        widget->setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(rand1).arg(rand2).arg(rand3));
        QWidget* widget = new FormEditor;

        if (parent->orientation() == orientation) {
            QSplitterNode* node = new QSplitterNode(parent, parent->m_name + QString::number(parent->count()));
            //            node->setSizePolicy(defaultPolicy);
            //            node->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
            //            node->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));

            node->addWidget(widget);

            parent->insertWidget(parent->indexOf(this) + offset, node);

        } else {
            //            setOrientation(orientation);
            int idx = parent->indexOf(this);
            QSplitterNode* node = new QSplitterNode(parent, parent->m_name + QString::number(parent->count()));
            setParent(node);
            //            node->setSizePolicy(defaultPolicy);
            node->setOrientation(orientation);
            parent->insertWidget(idx, node);

            //            QSplitterNode* node = new QSplitterNode(this, m_name + "0");

            //            node->addWidget(this->widget(0));
            //            this->widget(0)->setParent(node);
            //            node->addWidget(this);

            QSplitterNode* node2 = new QSplitterNode(this, m_name + "1");
            //            node2->setSizePolicy(defaultPolicy);
            //                        node2->addWidget(widget);
            //            node2->insertWidget(offset - 1, widget);
            node2->addWidget(widget);

            //            node->addWidget(node2);
            node->insertWidget(offset, node2);

            //            node->addWidget(this);
        }
    }

    //    connect(this->handle(3), SIGNAL(mousePressEvent()), this, SLOT(onHandleMousePressEvent()));
    //    qDebug() << this << ": handle(0) = " << handle(0);
}

void QSplitterNode::mouseReleaseEvent(QMouseEvent*)
{
    //    setCursor(Qt::ArrowCursor);
}

void QSplitterNode::setName(const QString& name)
{
    m_name = name;
}

//void QSplitterNode::dragEnterEvent(QDragEnterEvent *)
//{
//    qDebug() << this << ": dragEnterEvent";

//}

void QSplitterNode::onSplitterMoved(int pos, int index)
{
    Q_ASSERT(count() != 1);
    //    qDebug() << this << ": onSplitterMoved " << pos << index;
    //    qDebug() << size() << widget(index -1)->size() << widget(index)->size();
    if (orientation() == Qt::Horizontal) {
        if (widget(index - 1)->width() == 0) {
            delete widget(index - 1);
        } else if (widget(index)->width() == 0) {
            delete widget(index);
        }
    } else {
        if (widget(index - 1)->height() == 0) {
            delete widget(index - 1);
        } else if (widget(index)->height() == 0) {
            delete widget(index);
        }
    }
}
