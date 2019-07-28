#ifndef QSPLITTERNODE_H
#define QSPLITTERNODE_H

#include <QSplitter>
#include <QWidget>
#include <QMouseEvent>
#include <QObject>

#include <ostream>
#include "editor/MainWindowEditor.h"

namespace  {
//    static int iNode;

}
class QWidgetTemplate : public QWidget {
    //    Q_OBJECT
public:
    QWidgetTemplate(QWidget* parent = nullptr)
        : QWidget(parent)
    {
        int rand1 = 100 + qrand() % 155;
        int rand2 = 100 + qrand() % 155;
        int rand3 = 100 + qrand() % 155;
        this->setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(rand1).arg(rand2).arg(rand3));
    }
};


//using widgetTemplate = QWidgetTemplate;
//using widgetTemplate = QWidget;
using widgetTemplate = MainWindowEditor;

class QSplitterNode : public QSplitter
{
        Q_OBJECT
public:
    explicit QSplitterNode(QWidget * parent = nullptr);

    ~QSplitterNode();
//    QSplitterNode(const QSplitterNode&);
//    QSplitterNode &operator=(const QSplitterNode&);

//    void setup();
//    void clear();
//    void loadSetting();
//    void saveSetting();

//    void saveEnv();
//    void loadEnv();
    void save(std::ofstream & file) const;
    void load(std::ifstream & file);

    friend std::ostream & operator <<(std::ostream & out, const QSplitterNode & node);

protected:
//        void resizeEvent(QResizeEvent *) override;
//    void moveSplitter(int pos, int index);
//    void mouseMoveEvent(QMouseEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;

    void focusInEvent(QFocusEvent *) override;
    void keyPressEvent(QKeyEvent *) override;

//    void dragEnterEvent(QDragEnterEvent *) override;
//    void setOpaqueResize(bool opaque = true);


public slots:
    void onSplitterMoved(int pos, int index);
//    void onNewHSplitAdded(QMouseEvent * ev);
//    void onNewVSplitAdded(QMouseEvent * ev);


//    void onHandleMousePressEvent(QMouseEvent *);
public:
//    void setName(const QString &name);

private:
    int m_depth = 0;
//    QString m_name;
//    bool m_leaf;
//    int m_nbSons;

//    QList<QSplitterNode> m_sons;
//    QList<int> m_sizes;

};

#endif // QSPLITTERNODE_H
