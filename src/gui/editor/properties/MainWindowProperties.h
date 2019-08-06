#ifndef MAINWINDOWPROPERTIES_H
#define MAINWINDOWPROPERTIES_H

#include <QMainWindow>

namespace Ui {
class MainWindowProperties;
}

namespace Properties {
    enum e_context {
        MATERIAL,
    };
}

class MainWindowProperties : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindowProperties(QWidget* parent = nullptr);
    ~MainWindowProperties();

    void setContext(Properties::e_context context);

private slots:
    void on_actionMaterial_triggered();

private:
    Ui::MainWindowProperties* ui;
};

#endif // MAINWINDOWPROPERTIES_H
