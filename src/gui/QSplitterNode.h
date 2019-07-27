#ifndef QSPLITTERNODE_H
#define QSPLITTERNODE_H

#include <QSplitter>
#include <QWidget>
#include <QMouseEvent>
#include <QObject>

#include <ostream>

namespace  {
//    static int iNode;

}


class QSplitterNode : public QSplitter
{
        Q_OBJECT
public:
    explicit QSplitterNode(QWidget * parent = nullptr, QString name = "root");

    QSplitterNode(const QSplitterNode&);
//    QSplitterNode & operator=(const QSplitterNode&);

//    void setup();
//    void loadSetting();
//    void saveSetting();

    void saveEnv();
    void loadEnv();
    void save(std::ofstream & file) const;
    void load(std::ifstream & file);

    friend std::ostream & operator <<(std::ostream & out, const QSplitterNode & node) {
//        out << node.m_name.toStdString() << " ";
        out << "[NODE] nb splits: " << node.m_sizes.size() << std::endl;
        for (int size : node.m_sizes) {
            out << size << ", ";
        }
        return out;
    }

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
//    QString m_name;
//    bool m_leaf;
//    int m_nbSons;

//    QList<QSplitterNode> m_sons;
    QList<int> m_sizes;

};

#endif // QSPLITTERNODE_H
