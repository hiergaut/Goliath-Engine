#ifndef MAINWINDOWEDITOR_H
#define MAINWINDOWEDITOR_H

#include <QMainWindow>

enum WidgetEditorId {
    VIEW = 1, OUTLINER = 2
};

namespace Ui {
class MainWindowEditor;
}

class MainWindowEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowEditor(QWidget *parent = nullptr);
    ~MainWindowEditor();

    void setEditor(WidgetEditorId id);

    void save(std::ofstream & file);
    void load(std::ifstream & file);

    WidgetEditorId id() const;

protected:
    void keyPressEvent(QKeyEvent *);
    void focusInEvent(QFocusEvent *);

private slots:
    void on_action3D_View_triggered();

    void on_actionOutliner_triggered();

private:
    WidgetEditorId m_id;
    Ui::MainWindowEditor *ui;
};

#endif // MAINWINDOWEDITOR_H
