#ifndef MAINWINDOWPROPERTIES_H
#define MAINWINDOWPROPERTIES_H

#include <QMainWindow>
#include "../TemplateMenuBar.h"

namespace Ui {
class MainWindowProperties;
}

namespace Properties {
    enum e_context {
        MATERIAL,
    };
}

class MainWindowProperties : public QMainWindow, public TemplateMenuBar {
    Q_OBJECT

public:
    explicit MainWindowProperties(QWidget* parent = nullptr);
    ~MainWindowProperties();

    void setContext(Properties::e_context context);

    void setFocusPolicy(Qt::FocusPolicy policy) override;
    QWidget * widget() override;

private slots:
    void on_actionMaterial_triggered();

private:
    Ui::MainWindowProperties* ui;
};

#endif // MAINWINDOWPROPERTIES_H
