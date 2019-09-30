#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "editor/QOpenGLWidget_World.h"

//#include <QSplitter>
//#include "Gui/TillingWindow/QSplitterNode.h"
//#include "Gui
#include <gui/QSplitterNode.h>
#include <gui/system/FormSystemBrowser.h>

//#include <QFileSystemModel>

#include <gui/editor/3dview/MainWindow3dView.h>
#include <gui/QOpenGLWidget_Editor.h>
#include <engine/scene/Scene.h>
#include "DialogInputGetItem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createStartupSession();

    void loadEnv(std::string filename);
    void saveEnv(std::string filename);
    void showSystemBrowser();
    void showEditors();

//    void loadLastSession();
//    void saveSession();

    void loadLastSession();
    void loadStartupFile();
//    std::list<const MainWindow3dView *> views() const;
    void previousEnvAdd(std::string file);

protected:
    void keyPressEvent(QKeyEvent *);
//    void focusInEvent(QFocusEvent *);

    void resizeEvent(QResizeEvent *);
//    void mouseMoveEvent(QMouseEvent * event);

private slots:
    void on_actionQuit_triggered();
    void on_actionSave_As_triggered();
    void on_actionOpen_triggered();
    void on_actionLoad_Factory_Settings_triggered();
    void on_actionSave_Startup_File_triggered();
    void on_actionNew_triggered();
    void on_actionImport_triggered();

    void on_systemBrowserCanceled();
    void on_systemBrowserLoaded(QString filename);
    void on_systemBrowserSaved(QString file);
    void on_systemBrowserImported(QString file);

    void on_actionSave_triggered();

//    void on_setFps(float fps);

    void on_actionOpen_Recent_triggered();

    void on_dialogOpenPrevious(const QModelIndex & index);

private:
    Ui::MainWindow *ui;

    QOpenGLWidget_Editor * editor;

    std::list<const MainWindow3dView *> * m_views;


//    QStandardItemModel m_fileOpennedModel;

//    MainWindow3dView * view;
//    MainWindow3dView * view2;
//    Scene m_scene;

//    Model * m_scene;
//    QFileSystemModel * m_model;

//    QSplitterNode * m_splitterRoot;

//    QSplitterNode m_splitterRoot;
//    FormSystemBrowser m_systemBrowser;


//    QSplitterNode * node;
//    QOpenGLWidget_World * openglWidget;

//    QSplitter * splitter;
    QSettings m_settings;
    QStringListModel * m_previousEnv;

    DialogInputGetItem m_dialogInput;
    std::string m_startupPath;

//    QString m_currentEnvFile;
};

#endif // MAINWINDOW_H
