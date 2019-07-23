#ifndef QSPLITTERNODE_H
#define QSPLITTERNODE_H

#include <QSplitter>
#include <QWidget>
#include <QMouseEvent>
#include <QObject>

class QSplitterNode : public QSplitter
{
        Q_OBJECT
public:
    explicit QSplitterNode(QWidget * parent = nullptr, QString name = "root");

    void setup();
    void loadSetting();

protected:
//    void resizeEvent(QResizeEvent *) override;
//    void moveSplitter(int pos, int index);
//    void mouseMoveEvent(QMouseEvent *) override;
    void mousePressEvent(QMouseEvent *) override;

//    void dragEnterEvent(QDragEnterEvent *) override;
//    void setOpaqueResize(bool opaque = true);


public slots:
//    void onSplitterMoved(int pos, int index);
    void onNewHSplitAdded(QMouseEvent * ev);
    void onNewVSplitAdded(QMouseEvent * ev);


//    void onHandleMousePressEvent(QMouseEvent *);

private:
    QString m_name;
//    int m_nbSons;

//    QList<QSplitterNode> m_sons;
    QList<int> m_sizes;
};

#endif // QSPLITTERNODE_H
