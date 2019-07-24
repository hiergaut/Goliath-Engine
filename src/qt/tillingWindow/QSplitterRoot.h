#ifndef QSPLITTERROOT_H
#define QSPLITTERROOT_H

//#include <QSplitter>
#include <QSettings>
#include "QSplitterNode.h"

class QSplitterRoot : public QSplitterNode
{
    Q_OBJECT
public:
    explicit QSplitterRoot(QWidget *parent = nullptr);

//    void setup();

signals:

public slots:

private:
    QSettings m_setting;
};

#endif // QSPLITTERROOT_H

