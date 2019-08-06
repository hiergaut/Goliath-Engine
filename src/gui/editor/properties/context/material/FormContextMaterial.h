#ifndef FORMCONTEXTMATERIAL_H
#define FORMCONTEXTMATERIAL_H

#include <QWidget>

namespace Ui {
class FormContextMaterial;
}

class FormContextMaterial : public QWidget
{
    Q_OBJECT

public:
    explicit FormContextMaterial(QWidget *parent = nullptr);
    ~FormContextMaterial();

private:
    Ui::FormContextMaterial *ui;
};

#endif // FORMCONTEXTMATERIAL_H
