#include "QSplitterNode.h"

#include <QCryptographicHash>
#include <QDebug>
#include <QLayout>
#include <QSettings>
#include <iostream>
#include <sstream>

//#include "FormEditor.h"
#include <QSplitterHandle>

#include <QLabel>
#include <engine/Environment.h>

namespace {
QSizePolicy::Policy singlePolicy(QSizePolicy::Policy::Ignored);
QSizePolicy defaultPolicy(singlePolicy, singlePolicy);
//QList<QSplitterNode> nodes;
//QList<QList<int>> sizes;
QString groupName = "splitterTree0";
}

QSplitterNode::QSplitterNode(QWidget* parent)
    : QSplitter(parent)
//    , m_name(name)
{
    if (parent != nullptr) {
        m_depth = static_cast<QSplitterNode*>(parent)->m_depth + 1;
    } else {
        m_depth = 0;
    }

    connect(this, &QSplitterNode::splitterMoved, this, &QSplitterNode::onSplitterMoved);
    setSizePolicy(::defaultPolicy);
    setOrientation(Qt::Horizontal);
    //    connect(this, SIGNAL(splitterMoved(int, int)), this, SLOT(onSplitterMoved(int, int)));
    //    qDebug() << this << ": handleWidth = " << this->handleWidth();
    //    qDebug() << this << handle(0);
    //    qDebug() << this << ": handle(0) = " << handle(0);
    //    setStyleSheet("background-color: " + 222);
    //    setFocus();

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

QSplitterNode::~QSplitterNode()
{
    if (count() == 1) {
        //        addWidget(new widgetTemplate);
        widget(0)->setParent(nullptr);
        delete widget(0);

    } else {
        //        FormEditor* w = static_cast<FormEditor*>(widget(0));
        //        connect(w, &FormEditor::addingNewHSplit, this, &QSplitterNode::onNewHSplitAdded);
        //        connect(w, &FormEditor::addingNewVSplit, this, &QSplitterNode::onNewVSplitAdded);

        //        qDebug() << this << ": leaf widget " << w;

        for (int i = 0; i < count(); ++i) {
            QSplitterNode* node = static_cast<QSplitterNode*>(widget(i));
            //            node->setName(m_name + QString::number(i));
            //            node->setOrientation(Qt::Vertical);
            //            node->m_depth = m_depth + 1;
            //            node->setup();
            //            node->clear();
            node->setParent(nullptr);
            delete node;
            //            connect(w, &FormEditor::addingNewHSplit, this, &QSplitterNode::onNewHSplitAdded);
        }
    }
    //    m_sizes = sizes();
}

//QSplitterNode::QSplitterNode(const QSplitterNode& node)
//{
//    //    m_name = node.m_name;
////    m_sizes = node.m_sizes;
//}

//QSplitterNode& QSplitterNode::operator=(const QSplitterNode& node)
//{
////    m_sizes = node.m_sizes;
//}

//void QSplitterNode::setup()
//{
//    //    Q_ASSERT(count() > 0);
//    //    for (int i = 0; i < 3; ++i) {
//    //        qDebug() << this << ": handle(" << i << ") = " << handle(i);
//    //    setSizePolicy(defaultPolicy);
//    //    }
//    if (count() == 0) {
//        addWidget(new widgetTemplate);

//    } else {
//        //        FormEditor* w = static_cast<FormEditor*>(widget(0));
//        //        connect(w, &FormEditor::addingNewHSplit, this, &QSplitterNode::onNewHSplitAdded);
//        //        connect(w, &FormEditor::addingNewVSplit, this, &QSplitterNode::onNewVSplitAdded);

//        //        qDebug() << this << ": leaf widget " << w;

//        for (int i = 0; i < count(); ++i) {
//            QSplitterNode* node = static_cast<QSplitterNode*>(widget(i));
//            //            node->setName(m_name + QString::number(i));
//            //            node->setOrientation(Qt::Vertical);
//            node->m_depth = m_depth + 1;
//            node->setup();
//            //            connect(w, &FormEditor::addingNewHSplit, this, &QSplitterNode::onNewHSplitAdded);
//        }
//    }
//    //    m_sizes = sizes();
//}

//void QSplitterNode::clear()
//{
//    if (count() == 1) {
////        addWidget(new widgetTemplate);
//        delete widget(0);

//    } else {
//        //        FormEditor* w = static_cast<FormEditor*>(widget(0));
//        //        connect(w, &FormEditor::addingNewHSplit, this, &QSplitterNode::onNewHSplitAdded);
//        //        connect(w, &FormEditor::addingNewVSplit, this, &QSplitterNode::onNewVSplitAdded);

//        //        qDebug() << this << ": leaf widget " << w;

//        for (int i = 0; i < count(); ++i) {
//            QSplitterNode* node = static_cast<QSplitterNode*>(widget(i));
//            //            node->setName(m_name + QString::number(i));
//            //            node->setOrientation(Qt::Vertical);
////            node->m_depth = m_depth + 1;
////            node->setup();
//            node->clear();
//            delete node;
//            //            connect(w, &FormEditor::addingNewHSplit, this, &QSplitterNode::onNewHSplitAdded);
//        }
//    }
//    //    m_sizes = sizes();
//}

//void QSplitterNode::loadSetting()
//{
//    //    int rand1 = 100 + qrand() % 155;
//    //    int rand2 = 100 + qrand() % 155;
//    //    int rand3 = 100 + qrand() % 155;
//    //    this->setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(rand1).arg(rand2).arg(rand3));

//    QSettings settings("Goliath-Engine", "splitterTree");
//    settings.beginGroup(::groupName);

//    //    m_sizes = settings.value(m_name).value<QList<int>>();
//    //    qDebug() << m_sizes;
//    //    nodes = settings.value("nodes").value<QList<QSplitterNode>>();
//    //    qRegisterMetaTypeStreamOperators<QList<QList<int>>>("QList<QList<int>>");

//    m_sizes = settings.value(m_name).value<QList<int>>();
////    Q_ASSERT(m_sizes.size() != 0);
//    qDebug() << m_name << ": m_sizes = " << m_sizes;
//    if (m_sizes.size() == 0 || (m_sizes.size() == 1 && m_name == "root")) {
//        QSplitterNode* node = new QSplitterNode(this, this->m_name + "0");
////        node->addWidget(new MainWindowEditor);
//        node->addWidget(new widgetTemplate);
////        node->addWidget(new FormEditor);

//        addWidget(node);

//    }

//    //        setSizes(m_sizes);
//    else if (m_sizes.size() == 1) {
//        //        if (m_name == "root") {
//        //            QSplitterNode* node = new QSplitterNode(this, this->m_name + "0");
//        //            node->addWidget(new FormEditor);

//        //            addWidget(node);
//        //        } else {

//        //        qDebug() << "loadSetting: " << m_name << " leaf";
////        addWidget(new FormEditor);
////        addWidget(new MainWindowEditor);
//        addWidget(new widgetTemplate);
//        //        }
//    } else {
//        for (int i = 0; i < m_sizes.size(); ++i) {
//            QSplitterNode* node = new QSplitterNode(this, this->m_name + QString::number(i));
//            //            node->setSizePolicy(::defaultPolicy);
//            //            qDebug() << "loadSetting: " << m_name << " create node " << node->m_name;
//            //            node->setOrientation(Qt::Vertical);
//            //            node->setup();
//            node->loadSetting();
//            //            connect(w, &FormEditor::addingNewHSplit, this, &QSplitterNode::onNewHSplitAdded);
//            addWidget(node);
//        }
//        setSizes(m_sizes);
//        int orientation = settings.value(m_name + "orientation", Qt::Horizontal).value<int>();
//        setOrientation((orientation == 0) ?(Qt::Horizontal) :(Qt::Vertical));
//    }

//    //    qDebug() << m_sizes;

//    //    QList<QList<int>> def;
//    //    ::sizes = settings.value("sizes").value<QList<QList<int>>>();
//    //    qDebug() << ::sizes;

//    //    if (m_sizes.size() == 0) {
//    //        FormEditor* widget;
//    //        widget = new FormEditor(this);
//    //        addWidget(widget);

//    //        //        QSplitterNode * node = new QSplitterNode(this, m_name + QString::number(m_sizes.size()));
//    //    }

//    //    m_nbSons = settings.value(m_name + "m_nbSons", 0).toInt();
//    //    for (int i =0; i <m_nbSons; ++i) {
//    //        QSplitterNode node(this, "root" + QString::number(i));
//    ////        node.setup();
//    //        node.loadSetting();
//    //        m_sons.push_back(node);
//    ////        m_sons.insert(0, node);
//    //    }

//    settings.endGroup();
//}

//void QSplitterNode::saveSetting()
//{
//    QSettings settings("Goliath-Engine", "splitterTree");
//    settings.beginGroup(::groupName);

//    //    QList<QList<int>> sizes;
//    //    settings.setValue("sizes", ::sizes);
//    settings.setValue(m_name, QVariant::fromValue(sizes()));
//    qDebug() << "settings.setValue(" << m_name << ", " << sizes() << ")";

//    if (count() != 1) {
//        int orientation = (this->orientation() == Qt::Horizontal) ?(0) :(1);
//        settings.setValue(m_name + "orientation", QVariant::fromValue(orientation));

//        for (int i = 0; i < count(); ++i) {
//            QSplitterNode* node = static_cast<QSplitterNode*>(widget(i));
//            node->setName(m_name + QString::number(i));
//            //            node->setOrientation(Qt::Vertical);
//            node->saveSetting();
//            //            node->setup();
//            //            connect(w, &FormEditor::addingNewHSplit, this, &QSplitterNode::onNewHSplitAdded);
//        }
//    }

//    settings.endGroup();
//}

//void QSplitterNode::saveEnv()
//{
//    if (count() == 1) {
//        g_env.m_SplitterNodes.push_back(*this);

//    } else {
//        //        qDebug() << "insert map '" << m_name << "'" << sizes();
//        //        g_env.m_sizes[m_name] = sizes();

//        g_env.m_SplitterNodes.push_back(*this);
//        //        qDebug() << &g_env;

//        for (int i = 0; i < count(); ++i) {
//            QSplitterNode* node = static_cast<QSplitterNode*>(widget(i));
//            //            node->setName(m_name + QString::number(i));
//            node->saveEnv();
//        }
//    }
//}

//void QSplitterNode::loadEnv()
//{
//    qDebug() << this << m_sizes << ": loadEnv";
//    //    std::cout << *this << std::endl;
//    //    if (count() == 1) {

//    //    }
//    //    else {

//    //    }

//    //    for (const QSplitterNode & node : g_env.m_SplitterNodes) {

//    //    }

//    //    m_sizes = settings.value(m_name).value<QList<int>>();

//    if (g_env.m_SplitterNodes.size() == 0) { // empty load
//        qDebug() << "empty load";
//        //                QSplitterNode* node = new QSplitterNode(this);
//        //        QSplitterNode * node = &g_env.m_SplitterNodes[iNode++];
//        //                node->addWidget(new MainWindowEditor);
//        //        node->addWidget(new widgetTemplate);

//        //        node->addWidget(new FormEditor);
//        addWidget(new widgetTemplate);

//        //        addWidget(&g_env.m_SplitterNodes[iNode++]);

//    } else if (g_env.m_iSplitterNode == 0) { // root
//        if (count() == 0) {
//            qDebug() << "empty root";
//            addWidget(new widgetTemplate);
//        } else {
//            qDebug() << "root";
//            //            QSplitterNode* node = new QSplitterNode(this);
//            Q_ASSERT(count() == 1);
//            //            this = new QSplitterNode;
//            QSplitterNode* node = static_cast<QSplitterNode*>(widget(0));
//            *node = g_env.m_SplitterNodes[g_env.m_iSplitterNode++];
//            //            QSplitterNode* node = &g_env.m_SplitterNodes[g_env.m_iSplitterNode++];
//            node->setParent(this);
//            //        node.addWidget(this);
//            //            addWidget(node);

//            node->loadEnv();
//        }
//    }
//    //    else if (m_sizes.size() == 0) { //

//    //    }

//    //        setSizes(m_sizes);
//    else if (m_sizes.size() == 1) { // leaf
//        qDebug() << "leaf";
//        //        if (m_name == "root") {
//        //            QSplitterNode* node = new QSplitterNode(this, this->m_name + "0");
//        //            node->addWidget(new FormEditor);

//        //            addWidget(node);
//        //        } else {

//        //        qDebug() << "loadSetting: " << m_name << " leaf";
//        //        addWidget(new FormEditor);
//        //        addWidget(new MainWindowEditor);
//        addWidget(new widgetTemplate);
//        //        }
//    } else {
//        qDebug() << "else";
//        for (int i = 0; i < m_sizes.size(); ++i) {
//            Q_ASSERT(g_env.m_iSplitterNode < g_env.m_SplitterNodes.size());
//            QSplitterNode* node = new QSplitterNode(this);
//            //            QSplitterNode* node = &g_env.m_SplitterNodes[g_env.m_iSplitterNode++];
//            *node = g_env.m_SplitterNodes[g_env.m_iSplitterNode++];
//            //            node->setParent(this);

//            //            node->setSizePolicy(::defaultPolicy);
//            //            qDebug() << "loadSetting: " << m_name << " create node " << node->m_name;
//            //            node->setOrientation(Qt::Vertical);
//            //            node->setup();
//            //            node->loadSetting();
//            node->loadEnv();
//            //            connect(w, &FormEditor::addingNewHSplit, this, &QSplitterNode::onNewHSplitAdded);
//            addWidget(node);
//        }
//        setSizes(m_sizes);
//        //        int orientation = settings.value(m_name + "orientation", Qt::Horizontal).value<int>();
//        //        setOrientation((orientation == 0) ?(Qt::Horizontal) :(Qt::Vertical));
//    }
//}

void QSplitterNode::save(std::ofstream& file) const
{
    //    qDebug() << this;
    //    std::cout << *this << std::endl;
    //    std::cout << count() << sizes().size() << std::endl;
    Q_ASSERT(count() > 0);
    Q_ASSERT(count() == sizes().size());

    size_t size;
    size = count();
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));

    if (size == 1) {
        static_cast<MainWindowEditor*>(widget(0))->save(file);
        //        WidgetEditorId id = static_cast<MainWindowEditor*>(widget(0))->id();
        //        file.write(reinterpret_cast<const char*>(&id), sizeof (id));
        //        qDebug() << "save " << id;
        return;
    }

    bool orientation = this->orientation() == Qt::Horizontal;
    file.write(reinterpret_cast<const char*>(&orientation), sizeof(orientation));

    //    for (const int & size : m_sizes) {
    //        file.write(reinterpret_cast<const char *>(size), sizeof(int));
    //    }
    int t[size];
    for (int i = 0; i < size; ++i) {
        t[i] = sizes()[i];
        //        file.write(reinterpret_cast<const char *>(&val), sizeof(int));
    }
    file.write(reinterpret_cast<const char*>(t), size * sizeof(int));

    for (int i = 0; i < size; ++i) {
        static_cast<QSplitterNode*>(widget(i))->save(file);
    }
}

void QSplitterNode::load(std::ifstream& file)
{

    size_t size;
    Q_ASSERT(!file.eof());
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    std::cout << "size = " << size << " " << std::endl;
    //    int sizes[size];
    //    m_sizes = std::vector<int>(size);
    if (size == 1) {
        //        WidgetEditorId id;
        //        file.read(reinterpret_cast<char*>(&id), sizeof (id));
        MainWindowEditor* w = new MainWindowEditor;
        w->load(file);
        //        w->setEditor(id);
        addWidget(w);
        //        qDebug() << "load " << id;
        return;
    }

    bool orientation = this->orientation() == Qt::Horizontal;
    file.read(reinterpret_cast<char*>(&orientation), sizeof(orientation));
    setOrientation(orientation ? Qt::Horizontal : Qt::Vertical);
    //    m_sizes = QList<int>(size);
    //    m_sizes.clear();
    QList<int> localSizes;
    //    int * sizes = m_sizes.data();
    int ptr;
    for (int i = 0; i < size; ++i) {
        Q_ASSERT(!file.eof());
        file.read(reinterpret_cast<char*>(&ptr), sizeof(int));
        if (file.bad()) {
            perror("error reading ptr");
        }
        std::cout << "ptr[" << i << "] = " << ptr << " " << std::endl;
        //        m_sizes.push_back(*ptr);
        localSizes.push_back(ptr);
    }
    //    std::cout << std::endl;

    for (int i = 0; i < size; ++i) {
        QSplitterNode* node = new QSplitterNode(this);
        node->m_depth = m_depth + 1;
        node->load(file);

        addWidget(node);
    }
    //    std::cout << std::endl;
    //    qDebug() << this << localSizes << count();
    //    Q_ASSERT(size == count());
    Q_ASSERT(count() == sizes().size());
    setSizes(localSizes);
    //    m_sizes = std::list<int>(sizes);
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
    qDebug() << this << ": depth = " << m_depth << ", parent = " << parentWidget();
    Q_ASSERT(count() == 1);

    //    if (m_depth == 0) {
    //        QWidget * w = widget(0);
    //        w->setParent(nullptr);

    //        QSplitterNode * node = new QSplitterNode(this);
    //        node->addWidget(w);
    //        node->setParent(this);
    //        node->mousePressEvent(ev);
    //        return;
    //    }

    //    qDebug() << m_name << ": " << static_cast<QSplitterNode*>(parentWidget())->m_name << orientation() << count() << size();
    //        qDebug() << m_name << ": "   << orientation() << count() <<  size();
    //    qDebug() << width() << ev;
    int width = this->width();
    int height = this->height();

    int x = ev->x();
    int y = ev->y();

    int border = 10;

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
        MainWindowEditor* newWidget = new MainWindowEditor;
        newWidget->setEditor(VIEW);
        //        QWidget* newWidget = new widgetTemplate;

        QSplitterNode* parent = static_cast<QSplitterNode*>(this->parentWidget());
        if (parent->orientation() == orientation) {
            QSplitterNode* node = new QSplitterNode(parent);
            //            node->setSizePolicy(defaultPolicy);
            //            node->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
            //            node->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));

            node->addWidget(newWidget);

            int length = (orientation == Qt::Horizontal) ? (width) : (height);
            //            QList<int> s = parent->sizes();
            parent->insertWidget(parent->indexOf(this) + offset, node);

            //            int length;
            //            if (orientation == Qt::Horizontal) {
            //                length = width / parent->count();
            //            } else {
            //                length = height / parent->count();
            //            }
            //            for (int i = 0; i < parent->count(); ++i) {
            //                sizes.push_back(length);
            //            }
            QList<int> s = parent->sizes();
            s[parent->indexOf(this)] = length / 2;
            s[parent->indexOf(this) - (1 - 2 * offset)] = length / 2;
            parent->setSizes(s);

        } else {
            QWidget* w = widget(0);
            w->setParent(nullptr);

            setOrientation(orientation);

            QSplitterNode* node = new QSplitterNode(this);
            node->addWidget(w);
            w->setParent(node);

            QSplitterNode* node2 = new QSplitterNode(this);
            node2->addWidget(newWidget);

            addWidget(node);
            addWidget(node2);
            //            QList<int> sizes;
            //            int middle = height / 2;
            setSizes(QList<int>({ height / 2, height - height / 2 }));
            //            setOrientation(orientation);
            //            int idx = parent->indexOf(this);
            //            QSplitterNode* node = new QSplitterNode(parent);
            //            setParent(node);
            //            m_depth = node->m_depth +1;
            //            //            node->setSizePolicy(defaultPolicy);
            //            node->setOrientation(orientation);
            //            parent->insertWidget(idx, node);

            //            //            QSplitterNode* node = new QSplitterNode(this, m_name + "0");

            //            //            node->addWidget(this->widget(0));
            //            //            this->widget(0)->setParent(node);
            //            //            node->addWidget(this);

            //            QSplitterNode* node2 = new QSplitterNode(this);
            //            //            node2->setSizePolicy(defaultPolicy);
            //            //                        node2->addWidget(widget);
            //            //            node2->insertWidget(offset - 1, widget);
            //            node2->addWidget(widget);

            //            //            node->addWidget(node2);
            //            node->insertWidget(offset, node2);

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

void QSplitterNode::focusInEvent(QFocusEvent*)
{
    qDebug() << this << ": focusInEvent";
}

void QSplitterNode::keyPressEvent(QKeyEvent* ev)
{
    qDebug() << this << ": keyPressEvent" << ev;

    //    ev->ignore();
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

//void QSplitterNode::setName(const QString& name)
//{
//    m_name = name;
//}

std::ostream& operator<<(std::ostream& out, const QSplitterNode& node)
{
    //    std::cout << node.sizes().size() << node.count() << std::endl;
    Q_ASSERT(node.sizes().size() == node.count());
    //        out << node.m_name.toStdString() << " ";
    //    out << "[NODE] nb splits: " << node.m_sizes.size() << std::endl;
    for (int i = 0; i < node.m_depth; ++i) {
        out << "     ";
    }
    if (node.count() == 1) {
        //                out << "(" << node.widget(0) << ")";
        out << "(widget)" << std::endl;
        //        qDebug() << "(" << node.widget(0) << ")";
        //        qDebug() << node;

    } else {
        for (int size : node.sizes()) {
            out << "(";
            out << size << " ";
            out << ")";
        }
        std::cout << std::endl;

        for (int i = 0; i < node.count(); ++i) {
            QSplitterNode* son = static_cast<QSplitterNode*>(node.widget(i));
            out << *son;
        }
    }
    return out;
}
