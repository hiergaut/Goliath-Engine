//#include "MainWindow.h"
#include "TillingWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
    TillingWindow w;
    w.show();

    return a.exec();
}
