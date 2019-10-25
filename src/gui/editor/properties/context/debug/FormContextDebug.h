#ifndef FORMCONTEXTDEBUG_H
#define FORMCONTEXTDEBUG_H

#include <QWidget>

namespace Ui {
class FormContextDebug;
}

class FormContextDebug : public QWidget
{
    Q_OBJECT

public:
    explicit FormContextDebug(QWidget *parent = nullptr);
    ~FormContextDebug();

private:
    Ui::FormContextDebug *ui;
};

#endif // FORMCONTEXTDEBUG_H
