#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "editor/QOpenGLWidget_World.h"

//#include <QSplitter>
#include <Gui/TillingWindow/QSplitterNode.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();

private:
    Ui::MainWindow *ui;

    QSplitterNode * node;
//    QOpenGLWidget_World * openglWidget;

//    QSplitter * splitter;
};

#endif // MAINWINDOW_H
