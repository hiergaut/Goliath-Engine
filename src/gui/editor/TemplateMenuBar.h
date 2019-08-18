#ifndef TEMPLATEMENUBAR_H
#define TEMPLATEMENUBAR_H

//#include <QWidget>

#include <QMenu>


class TemplateMenuBar
{
public:
//    explicit TemplateMenuBar(QWidget * widget);

//    std::list<QMenu> &menus();

    virtual ~TemplateMenuBar() = default;
    virtual void setFocusPolicy(Qt::FocusPolicy policy) = 0;
//    virtual operator QWidget *() = 0;
    virtual QWidget * widget() = 0;

    std::list<QMenu*> & menus();

//    QWidget *widget();

//private:
protected:
    std::list<QMenu*> m_menus;
//    QWidget * m_widget;
};

#endif // TEMPLATEMENUBAR_H
