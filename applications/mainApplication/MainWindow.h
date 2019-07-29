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

protected:
    void keyPressEvent(QKeyEvent *);
    void focusInEvent(QFocusEvent *);

private slots:
    void on_actionQuit_triggered();
    void on_actionSave_As_triggered();
    void on_actionOpen_triggered();
    void on_actionLoad_Factory_Settings_triggered();
    void on_actionSave_Startup_File_triggered();
    void on_actionNew_triggered();
    void on_actionImport_triggered();

private:
    Ui::MainWindow *ui;

//    QFileSystemModel * m_model;

//    QSplitterNode * m_splitterRoot = nullptr;

//    QSplitterNode m_splitterRoot;
//    FormSystemBrowser m_systemBrowser;


//    QSplitterNode * node;
//    QOpenGLWidget_World * openglWidget;

//    QSplitter * splitter;
};

#endif // MAINWINDOW_H
