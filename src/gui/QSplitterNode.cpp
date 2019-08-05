#include "QSplitterNode.h"

#include <QCryptographicHash>
#include <QDebug>
#include <QLayout>
#include <QSettings>
#include <iostream>
#include <sstream>

#include <fstream>
//#include "FormEditor.h"
#include <QSplitterHandle>

#include <QLabel>
//#include <engine/Environment.h>

namespace {
QSizePolicy::Policy singlePolicy(QSizePolicy::Policy::Ignored);
QSizePolicy defaultPolicy(singlePolicy, singlePolicy);
//QList<QSplitterNode> nodes;
//QList<QList<int>> sizes;
//QString groupName = "splitterTree0";
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
}

QSplitterNode::~QSplitterNode()
{
    if (count() == 1) {
        //        addWidget(new widgetTemplate);
        //        widget(0)->setParent(nullptr);
        delete widget(0);

    } else {
        for (int i = 0; i < count(); ++i) {
            QSplitterNode* node = static_cast<QSplitterNode*>(widget(i));
            //            node->setParent(nullptr);
            delete node;
            //            connect(w, &FormEditor::addingNewHSplit, this, &QSplitterNode::onNewHSplitAdded);
        }
    }
    //    m_sizes = sizes();
}

void QSplitterNode::save(std::ofstream& file) const
{
    //    qDebug() << this;
    //    std::cout << *this << std::endl;
    //    std::cout << count() << sizes().size() << std::endl;
    Q_ASSERT(count() > 0);
    Q_ASSERT(count() == sizes().size());

    size_t size;

    //    if (m_depth == 0) {
    //        size = 0;
    //        file.write(reinterpret_cast<const char*>(&size), sizeof(size));

    //        static_cast<QSplitterNode*>(widget(0))->save(file);

    //        return;
    //    }
    size = count();
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));

    if (size == 1) {
        //        static_cast<MainWindowEditor*>(widget(0))->save(file);
        MainWindowEditor* win = static_cast<MainWindowEditor*>(widget(0));
//        qDebug() << "[SplitterNode] save mainWindowEditor" << win;
        win->save(file);
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
    //    std::cout << "size = " << size << " " << std::endl;
    //    int sizes[size];
    //    if (size == 0) {
    //        QSplitterNode * node = new QSplitterNode;
    //        addWidget(node);
    //        node->load(file);

    //        return;
    //    }
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
        //        std::cout << "ptr[" << i << "] = " << ptr << " " << std::endl;
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

void QSplitterNode::mousePressEvent(QMouseEvent* ev)
{
//    std::cout << *this;
    //    qDebug() << this << ": depth = " << m_depth << ", parent = " << parentWidget();
    //    qDebug() << rect();
    Q_ASSERT(count() == 1);

    int width = this->width();
    int height = this->height();

    int x = ev->x();
    int y = ev->y();

    int border = 5;

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
        newWidget->setEditor(Editor::id::VIEW);
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
    //    qDebug() << this << ": focusInEvent";
}

void QSplitterNode::keyPressEvent(QKeyEvent* ev)
{
    //    qDebug() << this << ": keyPressEvent" << ev;

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

    if (count() == 1) {

        //        QWidget * widget = widget(0);
        //        QSplitterNode * parent =  static_cast<QSplitterNode*>(this->parent());
        QSplitterNode* son = static_cast<QSplitterNode*>(widget(0));

        //        if (m_depth == 0) {
        ////            this = son;
        //        son->setParent(nullptr);

        setOrientation(son->orientation());
        //        int n = son->count();
        //        for (int i = 0; i < n; ++i) {
        while (son->count() > 0) {
            static_cast<QSplitterNode*>(son->widget(0))->setParent(this);
//            addWidget(static_cast<QSplitterNode*>(son->widget(0)));
            //            son->widget(i)->setParent(this);
            //                addWidget(son->widget(i));
        }
        delete son;
        //        son->setParent(nullptr);
        ////            son->setParent(nullptr);
        //        }
        //        else {
        //            parent->addWidget(son);
        ////            this->setParent(nullptr);
        //        }

        //        delete son;
        //        delete this;
        //        parent->addWidget(son);
        //        setOrientation(son->orientation());

        //        for (int i =0; i <son->count(); ++i) {
        //            QWidget * widget = std::move(son->widget(i));

        //            addWidget(widget);
        //        }

        //        son->setParent(nullptr);
        //        delete son;

        //        Q_ASSERT(son->count() == 1);

        //        son->setParent(nullptr);
        //        addWidget(widget);

        //        Q_ASSERT(count() == 1);
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
    //    if (node.m_depth == 0) {
    ////        Q_ASSERT(node.count() == 1);
    //        out << "(root)" << std::endl;
    //        QSplitterNode* son = static_cast<QSplitterNode*>(node.widget(0));
    //        out << *son;

    //    } else {
    for (int i = 0; i < node.m_depth; ++i) {
        out << "     ";
    }
    if (node.orientation() == Qt::Horizontal) {
        out << "(" << node.width() << ") " << &node << " ";
    } else {
        out << "(" << node.height() << ") " << &node << " ";
    }
    if (node.count() == 1) {
        //                out << "(" << node.widget(0) << ")";
        out << "(widget) " << node.widget(0) << std::endl;
        //        qDebug() << "(" << node.widget(0) << ")";
        //        qDebug() << node;

    } else {
        //            out << "(splitter) " << &node << " ";
        for (int size : node.sizes()) {
            out << "(";
            out << size << " ";
            out << ")";
        }
        //        std::cout << std::endl;
        out << std::endl;

        for (int i = 0; i < node.count(); ++i) {
            QSplitterNode* son = static_cast<QSplitterNode*>(node.widget(i));
            out << *son;
        }
    }
    //    }
    return out;
}
