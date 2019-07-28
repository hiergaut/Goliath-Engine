#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "editor/QOpenGLWidget_World.h"

//#include <QSplitter>
//#include "Gui/TillingWindow/QSplitterNode.h"
//#include "Gui
#include <gui/QSplitterNode.h>



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

protected:
    void keyPressEvent(QKeyEvent *);
    void focusInEvent(QFocusEvent *);

private slots:
    void on_actionQuit_triggered();

    void on_actionSave_As_triggered();

    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;

    QSplitterNode * m_splitterRoot;

//    QSplitterNode * node;
//    QOpenGLWidget_World * openglWidget;

//    QSplitter * splitter;
};

#endif // MAINWINDOW_H
