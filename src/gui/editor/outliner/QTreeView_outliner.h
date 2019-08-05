#ifndef QTREEVIEW_OUTLINER_H
#define QTREEVIEW_OUTLINER_H

#include <QWidget>
#include <QTreeView>
#include <QStandardItemModel>

class QTreeView_outliner : public QTreeView
{
    Q_OBJECT
public:
    explicit QTreeView_outliner(QWidget *parent = nullptr);


    static void setModelScene(QStandardItemModel *modelScene);

protected:
    void mousePressEvent(QMouseEvent *event) override;

signals:

public slots:
    void on_changingData();


private:
    static QStandardItemModel * m_modelScene;
};

#endif // QTREEVIEW_OUTLINER_H
