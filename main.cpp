#include "mainwindow.h"

#include <QApplication>
//#include<QtSvg/QGraphicsSvgItem>
//#include<QtSvg/QSvgGenerator>
//#include<QtSvg/QSvgRenderer>
//#include<QtSvg/QSvgWidget>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
