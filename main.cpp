#include "mainwindow.h"
#include <QApplication>
#include "basics.h"
#include <QFile>
#include <QTextStream>


vector <bool> basics::mon_on = {false,false,false};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
