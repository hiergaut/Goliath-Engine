#ifndef MAINWINDOWEDITOR_H
#define MAINWINDOWEDITOR_H

#include <QMainWindow>

namespace Editor {
enum id {
    ZERO = 0,
    VIEW,
    OUTLINER,
//    FILE_OPENNED,
};
}


namespace Ui {
class MainWindowEditor;
}

class MainWindowEditor : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindowEditor(QWidget* parent = nullptr);
    ~MainWindowEditor();

    void setEditor(Editor::id id);

    void save(std::ofstream& file);
    void load(std::ifstream& file);

    QString text();
//    Editor::id id() const;

protected:
    void keyPressEvent(QKeyEvent*);
    void focusInEvent(QFocusEvent*);

private slots:
    void on_action3D_View_triggered();

    void on_actionOutliner_triggered();

//    void on_actionFile_Openned_triggered();

private:
    Editor::id m_id = Editor::id::ZERO;
    Ui::MainWindowEditor* ui;

    QWidget * m_centralWidget = nullptr;

public:
    QWidget * centralWidget();
};

#endif // MAINWINDOWEDITOR_H
