#include "FormSystemBrowser.h"
#include "ui_FormSystemBrowser.h"

#include <QDebug>
#include <QKeyEvent>
#include <QMetaType>
#include <QSettings>
#include <QVariant>
#include <engine/Environment.h>
#include <opengl/version.h>
//Q_DECLARE_METATYPE(QList<QString>);

namespace {
QString settingsPath = "systemBrowser/previousGoliathLoad";
}

FormSystemBrowser::FormSystemBrowser(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::FormSystemBrowser)
{
    //    qRegisterMetaTypeStreamOperators<QList<QString>>("QList<QString>");

    ui->setupUi(this);

    ui->splitter_2->setSizes(QList<int>({ 200, width() - 200 }));

    m_model = new QFileSystemModel(this);
    m_model->setRootPath(resourcesPath.c_str());
    //    m_model->setFilter(QDir::AllEntries);

    ui->listView_system->setModel(m_model);
    ui->listView_system->setRootIndex(m_model->index(resourcesPath.c_str()));
    connect(ui->listView_system->selectionModel(), &QItemSelectionModel::selectionChanged, this, &FormSystemBrowser::on_changeSystemSelected);

    ui->listView_current->setModel(m_model);
    ui->listView_current->setRootIndex(m_model->index(resourcesPath.c_str()));
    connect(ui->listView_current->selectionModel(), &QItemSelectionModel::selectionChanged, this, &FormSystemBrowser::on_changeCurrentSelected);

    m_recent = new QStringListModel(this);
    updateRecent();

    ui->listView_recent->setModel(m_recent);
    connect(ui->listView_recent->selectionModel(), &QItemSelectionModel::selectionChanged, this, &FormSystemBrowser::on_changeRecentSelected);

    //    ui->listView_current->selectionModel()->select(ui->listView_recent.cur)

//    QModelIndex first = m_recent.row
//    QString initPath = m_recent->stringList().first();
    if (m_recent->stringList().size() != 0) {
//        qDebug() << m_model->index(resourcesPath.c_str());
//        ui->listView_system->setCurrentIndex(m_model->index(1, 0));
//        ui->listView_recent->selectionModel()->select(QModelIndex(0, 0, nullptr, nullptr));
        ui->listView_recent->setCurrentIndex(m_recent->index(0, 0));
//        QModelIndex index = m_recent->stringList().first();
    }
    //    ui->lis
}

FormSystemBrowser::~FormSystemBrowser()
{
    delete ui;
    delete m_model;
    delete m_recent;
}

void FormSystemBrowser::on_changeSystemSelected(const QItemSelection& selected, const QItemSelection& deselected)
{
    qDebug() << "on_changeSystemSelected" << selected << deselected;
    Q_ASSERT(selected.indexes().size() == 1);
    QModelIndex index = selected.indexes().first();
    QString filename = m_model->data(index).toString();
    QFileInfo fileInfo(resourcesPath.c_str() + filename);
    qDebug() << "fileInfo : " << fileInfo;
    qDebug() << "filename : " << filename;

    if (fileInfo.isDir()) {
        ui->listView_current->setRootIndex(index);
        ui->lineEdit_currentPath->setText(filename + "/");

        ui->lineEdit_currentFile->setText("");
        ui->pushButton_openFile->setEnabled(false);
    }
    //    ui->listView_current->setRootIndex(index);
    //    ui->lineEdit_currentPath->setText(m_model->data(index).toString() + "/");

    //    ui->lineEdit_currentFile->setText("");
    //    ui->pushButton_openFile->setEnabled(false);
}

void FormSystemBrowser::on_changeCurrentSelected(const QItemSelection& selected, const QItemSelection& deselected)
{
    //    qDebug() << "on_changeSystemSelected" << selected << deselected;
    Q_ASSERT(selected.indexes().size() == 1);
    QModelIndex index = selected.indexes().first();

    QString path = ui->lineEdit_currentPath->text();
    QString filename = m_model->data(index).toString();
    QFileInfo fileInfo(resourcesPath.c_str() + path + filename);
    qDebug() << fileInfo;

    if (fileInfo.isDir()) {
        ui->listView_current->setRootIndex(index);
        ui->lineEdit_currentPath->setText(path + filename + "/");

        ui->lineEdit_currentFile->setText("");
        ui->pushButton_openFile->setEnabled(false);
    } else {
        ui->lineEdit_currentFile->setText(filename);
        ui->pushButton_openFile->setEnabled(true);
    }
}

void FormSystemBrowser::on_changeRecentSelected(const QItemSelection& selected, const QItemSelection& deselected)
{
    QModelIndex index = selected.indexes().first();
    QString dir = m_recent->data(index).toString();
    qDebug() << "recent change" << dir;
    QFileInfo fileInfo(resourcesPath.c_str() + dir);
    qDebug() << fileInfo;
    Q_ASSERT(fileInfo.isDir());

    QModelIndex index2 = m_model->index(resourcesPath.c_str() + dir);
    ui->listView_current->setRootIndex(index2);
    ui->lineEdit_currentPath->setText(dir);

    ui->lineEdit_currentFile->setText("");
    ui->pushButton_openFile->setEnabled(false);
}

//void FormSystemBrowser::keyPressEvent(QKeyEvent *event)
//{
//    switch (event->key()) {
//    case Qt::Key_Escape:

//    }

//}

void FormSystemBrowser::on_pushButton_openFile_clicked()
{
    QSettings& settings = g_env.m_settings;
    QStringList paths = settings.value(::settingsPath).value<QStringList>();

    QString newPath = ui->lineEdit_currentPath->text();
    if (!paths.contains(newPath)) {
        paths += newPath;

        settings.setValue(::settingsPath, QVariant::fromValue(paths));
        qDebug() << "save setting " << paths;

        updateRecent();
    }
}

void FormSystemBrowser::on_pushButton_cancel_clicked()
{
    emit canceled();
}

void FormSystemBrowser::updateRecent()
{
    QSettings& settings = g_env.m_settings;
    QStringList paths = settings.value(::settingsPath).value<QStringList>();

    m_recent->setStringList(paths);
}
