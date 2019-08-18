#ifndef QTREEVIEW_OUTLINER_H
#define QTREEVIEW_OUTLINER_H

#include <QWidget>
#include <QTreeView>
#include <QStandardItemModel>
#include "../TemplateMenuBar.h"

class QTreeView_outliner : public QTreeView, public  TemplateMenuBar
{
    Q_OBJECT
public:
    explicit QTreeView_outliner(QWidget *parent = nullptr);


    static void setModelScene(QStandardItemModel *modelScene);

protected:
    void mousePressEvent(QMouseEvent *event) override;

    void setFocusPolicy(Qt::FocusPolicy policy) override;
    QWidget *widget() override;

signals:

public slots:
    void on_changingData();
    void on_click(const QModelIndex & index);


private:
    static QStandardItemModel * m_modelScene;
};

#endif // QTREEVIEW_OUTLINER_H
