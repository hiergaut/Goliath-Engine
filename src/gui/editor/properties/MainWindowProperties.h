#ifndef MAINWINDOWPROPERTIES_H
#define MAINWINDOWPROPERTIES_H

#include <QMainWindow>
#include "../TemplateMenuBar.h"

namespace Ui {
class MainWindowProperties;
}

//namespace Properties {
//}

class MainWindowProperties : public QMainWindow, public TemplateMenuBar {
    Q_OBJECT

public:
    enum Type {
        MATERIAL,
        CURVE,
        SURFACE,
//        DEBUG,
        LIGHT,
    } m_context;

    explicit MainWindowProperties(QWidget* parent = nullptr);
    ~MainWindowProperties();

    void save(std::ofstream& file);
    void load(std::ifstream& file);

    void setContext(Type context);

    void setFocusPolicy(Qt::FocusPolicy policy) override;
    QWidget * widget() override;

private slots:
    void on_actionMaterial_triggered();
    void on_actionCurve_triggered();
    void on_actionSurface_triggered();

    void on_actionDebug_triggered();

    void on_actionLight_triggered();

private:
    Ui::MainWindowProperties* ui;
};

#endif // MAINWINDOWPROPERTIES_H
