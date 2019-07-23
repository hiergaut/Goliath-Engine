#ifndef FORMEDITOR_H
#define FORMEDITOR_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class FormEditor;
}

class FormEditor : public QWidget
{
    Q_OBJECT

public:
    explicit FormEditor(QWidget *parent = nullptr);
    ~FormEditor();

signals:
    void addingNewHSplit(QMouseEvent * ev);
    void addingNewVSplit(QMouseEvent * ev);


//public slots:
//    void onNewHSplitAdded(QMouseEvent * ev);
//    void onNewVSplitAdded(QMouseEvent * ev);

private:
    Ui::FormEditor *ui;
};

#endif // FORMEDITOR_H
