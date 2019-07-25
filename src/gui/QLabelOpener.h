#ifndef QLABELOPENER_H
#define QLABELOPENER_H

#include <QLabel>
//#include <QWidget>

class QLabelOpener : public QLabel
{
    Q_OBJECT
public:
    explicit QLabelOpener(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;

signals:
    void addingNewHSplit(QMouseEvent * ev);
    void addingNewVSplit(QMouseEvent * ev);


public slots:

private:
    QPoint m_posOnClick;
    bool m_pressed = false;
};

#endif // QLABELOPENER_H
