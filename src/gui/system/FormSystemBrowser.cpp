#include "FormSystemBrowser.h"
#include "ui_FormSystemBrowser.h"

#include <QDebug>
#include <QKeyEvent>
#include <QMetaType>
#include <QSettings>
#include <QVariant>
//#include <engine/Environment.h>
#include <opengl/version.h>
//Q_DECLARE_METATYPE(QList<QString>);
#include <QItemSelectionModel>

namespace {
//QString settingsPath = "openned";
QString opennedDir = "opennedDir";
//QString opennedFile = "opennedFile";
}

FormSystemBrowser::FormSystemBrowser(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::FormSystemBrowser)
    , m_settings("Goliath-Engine", "systemBrowser")
    , m_rootPath(QDir::homePath() + "/")
//    , m_rootPath("/home/gauthier/")
{
    //    qRegisterMetaTypeStreamOperators<QList<QString>>("QList<QString>");
    //    QDir homeDir(m_settings.path);

    ui->setupUi(this);

    ui->splitter_2->setSizes(QList<int>({ 200, width() - 200 }));

    m_model = new QFileSystemModel(this);
    m_model->setNameFilterDisables(false);
    m_model->setRootPath(m_rootPath);
    //        m_model->setFilter(QDir::AllEntries);

    ui->listView_system->setModel(m_model);
    ui->listView_system->setRootIndex(m_model->index(m_rootPath));
    connect(ui->listView_system->selectionModel(), &QItemSelectionModel::selectionChanged, this, &FormSystemBrowser::on_changeSystemSelected);

    ui->listView_current->setModel(m_model);
    ui->listView_current->setRootIndex(m_model->index(m_rootPath));
    connect(ui->listView_current->selectionModel(), &QItemSelectionModel::selectionChanged, this, &FormSystemBrowser::on_changeCurrentSelected);

    m_recent = new QStringListModel(this);
//        updateRecent();
    QStringList paths = m_settings.value(::opennedDir).value<QStringList>();
    m_recent->setStringList(paths);

    ui->listView_recent->setModel(m_recent);
    connect(ui->listView_recent->selectionModel(), &QItemSelectionModel::selectionChanged, this, &FormSystemBrowser::on_changeRecentSelected);

    //    ui->listView_current->selectionModel()->select(ui->listView_recent.cur)

    //    QModelIndex first = m_recent.row
    //    QString initPath = m_recent->stringList().first();
    ui->lineEdit_currentPath->setText(m_rootPath);
    if (m_recent->stringList().size() != 0) {
        //        qDebug() << m_model->index(resourcesPath.c_str());
        //        ui->listView_system->setCurrentIndex(m_model->index(1, 0));
        //        ui->listView_recent->selectionModel()->select(QModelIndex(0, 0, nullptr, nullptr));
        ui->listView_recent->setCurrentIndex(m_recent->index(0, 0));
        //        QModelIndex index = m_recent->stringList().first();
    }

    //    ui->lis

//    connect(ui->listView_recent, &QListView::keyPressEvent,)

//    m_previous = new QStringListModel(this);
//    QStringList previous = m_settings.value(::opennedFile).value<QStringList>();
//    m_previous->setStringList(previous);
}

FormSystemBrowser::~FormSystemBrowser()
{
    delete ui;
    delete m_model;
    delete m_recent;
}


void FormSystemBrowser::openFile()
{

    QString newPath = ui->lineEdit_currentPath->text();
    registerOpennedDir(newPath);


    emit openned(newPath + ui->lineEdit_currentFile->text());
}

void FormSystemBrowser::saveFile()
{
    QFileInfo dir(ui->lineEdit_currentPath->text());
    Q_ASSERT(dir.exists());

    QString filename(ui->lineEdit_currentFile->text());
    Q_ASSERT(!filename.isEmpty());

    QString file(dir.path() + "/" + filename);
    registerOpennedDir(dir.path() + "/");

    emit saved(file);
    //    qDebug() << "saved : " << file;
}

void FormSystemBrowser::importFile()
{
    QString newPath = ui->lineEdit_currentPath->text();
    registerOpennedDir(newPath);

    emit imported(newPath + ui->lineEdit_currentFile->text());
}

void FormSystemBrowser::actionFile()
{
    switch (m_mode) {
    case Mode::OPEN:
        openFile();
        break;

    case Mode::SAVE:
        saveFile();
        break;

    case Mode::IMPORT:
        importFile();
        break;
    }
    //    QSettings& settings = g_env.m_settings;
}

void FormSystemBrowser::setMode(Mode mode)
{
    m_mode = mode;
    QStringList filters;

    switch (mode) {
    case Mode::OPEN:
        filters << "*.goliath";
        ui->pushButton_actionFile->setText("Open");
        break;

    case Mode::SAVE:
        filters << "*.goliath";
        ui->pushButton_actionFile->setText("Save");
        break;

    case Mode::IMPORT:
        ui->pushButton_actionFile->setText("Import");
        filters << "*.fbx"
                << "*.obj"
                << "*.smd";
        break;
    }


    m_model->setNameFilters(filters);
//    m_model->layoutChanged();

    ui->listView_current->setFocus();
//    ui->listView_recent->update();
//    ui->listView_current->update();

}

void FormSystemBrowser::registerOpennedDir(QString path)
{
    QStringList paths = m_settings.value(::opennedDir).value<QStringList>();
    if (!paths.contains(path)) {
        paths += path;

    } else {
        int idx = paths.indexOf(path);
        paths.move(idx, 0);
    }

    m_settings.setValue(::opennedDir, QVariant::fromValue(paths));
    //    qDebug() << "save setting " << paths;
//    m_recent->setStringList(paths);
//    pullSettingsRecentModel();
    m_recent->setStringList(paths);

}

//void FormSystemBrowser::setGoliathFilter()
//{
//    QStringList filters;
//    filters << "*.goliath";
//    m_model->setNameFilters(filters);
//}

//void FormSystemBrowser::setAssimpFilter()
//{
//    QStringList filters;
//    filters << "*.fbx" << "*.obj";
//    m_model->setNameFilters(filters);
//}

void FormSystemBrowser::on_changeSystemSelected(const QItemSelection& selected, const QItemSelection& deselected)
{
    //    qDebug() << "on_changeSystemSelected" << selected << deselected;
    Q_ASSERT(selected.indexes().size() == 1);
    QModelIndex index = selected.indexes().first();
    QString filename = m_model->data(index).toString();
    QFileInfo fileInfo(m_rootPath + filename);
    //    qDebug() << "fileInfo : " << fileInfo;
    //    qDebug() << "filename : " << filename;

    if (fileInfo.isDir()) {
        ui->listView_current->setRootIndex(index);
        ui->lineEdit_currentPath->setText(fileInfo.filePath() + "/");

        ui->lineEdit_currentFile->setText("");
        ui->pushButton_actionFile->setEnabled(false);
    }
    //    ui->listView_current->setRootIndex(index);
    //    ui->lineEdit_currentPath->setText(m_model->data(index).toString() + "/");

    //    ui->lineEdit_currentFile->setText("");
    //    ui->pushButton_openFile->setEnabled(false);
}

void FormSystemBrowser::on_changeCurrentSelected(const QItemSelection& selected, const QItemSelection& deselected)
{
    //    qDebug() << "on_changeSystemSelected" << selected << deselected;
    //    if (selected.indexes().size() != 1)
    //        return;
    Q_ASSERT(selected.indexes().size() == 1);
    QModelIndex index = selected.indexes().first();
    updateCurrent(index);
}

void FormSystemBrowser::on_changeRecentSelected(const QItemSelection& selected, const QItemSelection& deselected)
{
    Q_ASSERT(selected.indexes().size() == 1);
    QModelIndex index = selected.indexes().first();

    QModelIndex index2 = m_model->index(m_recent->data(index).toString());
    updateRecent(index2);

}

void FormSystemBrowser::keyPressEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_Return:
        if (ui->pushButton_actionFile->isEnabled()) {
            actionFile();
            //            QString path = ui->lineEdit_currentPath->text();
            //            QString file = ui->lineEdit_currentFile->text();
            //            emit openned(path + file);
        }
        break;

//    case Qt::Key_Shift:
//        if (ui->listView_recent->hasFocus()) {
//            ui->listView_current->setFocus();
//        }
//        else if (ui->listView_current->hasFocus()) {
//            ui->listView_recent->setFocus();
//        }
//        event->accept();
//        break;

//    case Qt::Key_Delete:
//        if (ui->listView_recent->hasFocus()) {
//            Q_ASSERT(ui->listView_recent->selectionModel()->selectedIndexes().size() == 1);
//            QModelIndex & index = ui->listView_recent->selectionModel()->selectedIndexes().first();
//            QVariant data = m_recent->data(index);
//            qDebug() << "data " << data;
//            Q_ASSERT(index.isValid());
//            qDebug() << "delete index " << index;
//            m_recent->removeRow(index.row());
//        }
//        break;
//    case Qt::Key_Down:
//        if (ui->listView_current->hasFocus()) {
//            Q_ASSERT(ui->listView_current->selectionModel()->selectedIndexes().size() == 1);
//            QModelIndex & index = ui->listView_current->selectionModel()->selectedIndexes().first();

//            ui->listView_current->selectionModel()->select(m_recent->index(index.row() + 1), QItemSelectionModel::SelectionFlag::Select);

//        }
//        break;
    }

    event->ignore();
}

void FormSystemBrowser::on_pushButton_actionFile_clicked()
{
    actionFile();
}

void FormSystemBrowser::on_pushButton_cancel_clicked()
{
    emit canceled();
}


//void FormSystemBrowser::pullSettingsRecentModel()
//{
//    QStringList paths = m_settings.value(::settingsPath).value<QStringList>();
//    m_recent->setStringList(paths);
//}

void FormSystemBrowser::updateRecent(const QModelIndex &index)
{
    QFileInfo fileInfo(m_model->filePath(index));
    Q_ASSERT(fileInfo.exists());
//    QString dir = m_recent->data(index).toString();
    //    qDebug() << "recent change" << dir;
//    QFileInfo fileInfo(m_rootPath + dir);
    //    qDebug() << fileInfo;
    Q_ASSERT(fileInfo.isDir());

    QString path(fileInfo.filePath() + "/");

    QModelIndex index2 = m_model->index(path);
    ui->listView_current->setRootIndex(index2);
    ui->lineEdit_currentPath->setText(path);

    ui->lineEdit_currentFile->setText("");
    ui->pushButton_actionFile->setEnabled(false);
    //    QSettings& settings = g_env.m_settings;

}

void FormSystemBrowser::updateCurrent(const QModelIndex& index)
{

    QFileInfo fileInfo(m_model->filePath(index));
    //    qDebug() << fileInfo;
    Q_ASSERT(fileInfo.exists());
    QString path(fileInfo.filePath() + "/");
    //    qDebug() << "path : " << path;

    if (fileInfo.isDir()) {
        ui->listView_current->setRootIndex(index);
        ui->lineEdit_currentPath->setText(path);

        ui->lineEdit_currentFile->setText("");
        ui->pushButton_actionFile->setEnabled(false);
    } else {
        ui->lineEdit_currentFile->setText(m_model->fileName(index));
        ui->pushButton_actionFile->setEnabled(true);
    }
}

void FormSystemBrowser::on_pushButton_parent_clicked()
{
    //    QFileInfo file(m_rootPath + ui->lineEdit_currentPath->text());
    //    ui->lineEdit_currentPath->setText(dir.)
    //    Q_ASSERT(file.exists());
    //    ui->lineEdit_currentPath->setText(file.path());
    //    QString path = ui->lineEdit_currentPath->text();

    std::string path = ui->lineEdit_currentPath->text().toStdString();
    if (path == m_rootPath.toStdString())
        return;
    path = path.substr(0, path.find_last_of('/'));
    path = path.substr(0, path.find_last_of('/'));
    //    file =  file.substr(0, file.find_last_of('/'));
    //    qDebug() << "path : " << path.c_str();
    //    std::string dir = file.substr(0, file.find_last_of('/'));

    //    ui->lineEdit_currentPath->setText((dir + "/").c_str());

    //    ui->listView_current->sele(m_model->index(file.c_str()));
    //    ui->listView_current->setCurrentIndex(m_model->index(file.c_str()));

    QModelIndex index(m_model->index(path.c_str()));
    Q_ASSERT(index.isValid());
    updateCurrent(index);
    //    QItemSelection itemSelection(index, index);
    //    ui->listView_current->setCurrentIndex(index);
    //            str.substr(0, str.find_first_of('|'));
}

void FormSystemBrowser::on_lineEdit_currentFile_textChanged(const QString& arg1)
{
    if (m_mode == Mode::SAVE) {
        //        ui->pushButton_actionFile->setEnabled(true);
        ui->pushButton_actionFile->setEnabled(!ui->lineEdit_currentFile->text().isEmpty());
    }
}
