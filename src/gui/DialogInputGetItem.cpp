#include "DialogInputGetItem.h"
#include "ui_DialogInputGetItem.h"

#include <QDebug>

DialogInputGetItem::DialogInputGetItem(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::DialogInputGetItem)
{
    ui->setupUi(this);
}

DialogInputGetItem::~DialogInputGetItem()
{
    delete ui;
}

void DialogInputGetItem::setModel(QStringListModel* model)
{
    ui->listView_recent->setModel(model);
    //    ui->listView_recent->setCurrentIndex(model.index(0));
    //    ui->listView_recent->selectionModel()->select(model.index(0), QItemSelectionModel::Select);
    //    ui->listView_recent->setCurrentIndex(model.index(0));
    //    connect(model, &QStringListModel::layoutChanged, this, &DialogInputGetItem::on_dataChange);
    //    connect(&model, SIGNAL(dataChanged(QModelIndex&)), this, SLOT(on_dataChange(QModelIndex&)));
}

//void DialogInputGetItem::on_listView_recent_entered(const QModelIndex &index)
//{
//    qDebug() << "entered " << index;

//}

void DialogInputGetItem::on_pushButton_open_clicked()
{
    Q_ASSERT(ui->listView_recent->selectionModel()->selectedIndexes().size() < 2);
    //    if (ui->listView_recent->selectionModel()->selectedIndexes().size() < 2) {

    if (ui->listView_recent->selectionModel()->selectedIndexes().size() == 1) {
        //            QModelIndex& index = ui->listView_recent->selectionModel()->selectedIndexes().first();
        const QModelIndex& index = ui->listView_recent->currentIndex();

        //            qDebug() << "open " << index.data();
        emit openEnv(index);
    } else {
        if (ui->listView_recent->currentIndex().isValid()) {
            emit openEnv(ui->listView_recent->currentIndex());
        }
    }
    //    }
}

void DialogInputGetItem::on_pushButton_recover_clicked()
{
    qDebug() << "recover ";
}

//void DialogInputGetItem::on_dataChange()
//{
////    qDebug() << "data changed" << left;
//    ui->listView_recent->selectionModel()->select(ui->listView_recent->currentIndex(), QItemSelectionModel::Select);

//}

//void DialogInputGetItem::on_listView_recent_pressed(const QModelIndex &index)
//{

//    qDebug() << "pressed";
//}
