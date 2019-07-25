#ifndef MAINWINDOWEDITOR_H
#define MAINWINDOWEDITOR_H

#include <QMainWindow>

namespace Ui {
class MainWindowEditor;
}

class MainWindowEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowEditor(QWidget *parent = nullptr);
    ~MainWindowEditor();

protected:
    void keyPressEvent(QKeyEvent *);
    void focusInEvent(QFocusEvent *);

private:
    Ui::MainWindowEditor *ui;
};

#endif // MAINWINDOWEDITOR_H
