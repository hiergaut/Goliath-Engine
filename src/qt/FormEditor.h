#ifndef FORMEDITOR_H
#define FORMEDITOR_H

#include <QWidget>

namespace Ui {
class FormEditor;
}

class FormEditor : public QWidget
{
    Q_OBJECT

public:
    explicit FormEditor(QWidget *parent = nullptr);
    ~FormEditor();

private:
    Ui::FormEditor *ui;
};

#endif // FORMEDITOR_H
