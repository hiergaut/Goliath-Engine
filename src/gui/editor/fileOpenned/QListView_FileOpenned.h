#ifndef QLISTVIEW_FILEOPENNED_H
#define QLISTVIEW_FILEOPENNED_H

#include <QWidget>
#include <QListView>

#include <QStandardItemModel>

class QListView_FileOpenned : public QListView
{
    Q_OBJECT
public:
    explicit QListView_FileOpenned(QWidget *parent = nullptr);


    static void setModelFileOpenned(QStandardItemModel *modelFileOpenned);

protected:
    void keyPressEvent(QKeyEvent * ev);


signals:

public slots:

private:
    static QStandardItemModel * m_modelFileOpenned;
};

#endif // QLISTVIEW_FILEOPENNED_H
