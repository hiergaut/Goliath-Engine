#ifndef DIALOGINPUTGETITEM_H
#define DIALOGINPUTGETITEM_H

#include <QDialog>
#include <QStringListModel>
#include <QVector>

namespace Ui {
class DialogInputGetItem;
}

class DialogInputGetItem : public QDialog
{
    Q_OBJECT

public:
    explicit DialogInputGetItem(QWidget *parent = nullptr);
    ~DialogInputGetItem();

    void setModel(QStringListModel * model);

signals:
    void openEnv(const QModelIndex & index);

public slots:
//    void on_listView_recent_entered(const QModelIndex &index);
    void on_pushButton_open_clicked();
    void on_pushButton_recover_clicked();

//    void on_dataChange();

//    void on_listView_recent_pressed(const QModelIndex &index);

private:
    Ui::DialogInputGetItem *ui;
};

#endif // DIALOGINPUTGETITEM_H
