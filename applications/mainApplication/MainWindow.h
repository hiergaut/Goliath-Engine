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

#include <gui/editor/3dview/QOpenGLWidget_3dView.h>
#include <gui/QOpenGLWidget_Editor.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void loadFile(std::string filename);
    void saveFile(std::string filename);
    void showSystemBrowser();
    void showEditors();

protected:
    void keyPressEvent(QKeyEvent *);
    void focusInEvent(QFocusEvent *);

    void resizeEvent(QResizeEvent *);

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

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;

    QOpenGLWidget_Editor * editor;
//    QOpenGLWidget_3dView * view;
//    QOpenGLWidget_3dView * view2;

//    Model * m_scene;
//    QFileSystemModel * m_model;

//    QSplitterNode * m_splitterRoot;

//    QSplitterNode m_splitterRoot;
//    FormSystemBrowser m_systemBrowser;


//    QSplitterNode * node;
//    QOpenGLWidget_World * openglWidget;

//    QSplitter * splitter;
};

#endif // MAINWINDOW_H
