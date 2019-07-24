#ifndef TILLINGWINDOW_H
#define TILLINGWINDOW_H

#include <QMainWindow>

namespace Ui {
class TillingWindow;
}

class TillingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TillingWindow(QWidget *parent = nullptr);
    ~TillingWindow();

private:
    Ui::TillingWindow *ui;
};

#endif // TILLINGWINDOW_H
