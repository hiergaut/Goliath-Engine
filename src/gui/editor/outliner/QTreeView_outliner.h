#ifndef QTREEVIEW_OUTLINER_H
#define QTREEVIEW_OUTLINER_H

#include <QWidget>
#include <QTreeView>

class QTreeView_outliner : public QTreeView
{
    Q_OBJECT
public:
    explicit QTreeView_outliner(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;

signals:

public slots:
};

#endif // QTREEVIEW_OUTLINER_H
