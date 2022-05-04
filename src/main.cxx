// qt includes
#include "mainwindow.h"
#include <QApplication>

// ROOT Includes
#include <TApplication.h>
#include <TSystem.h>

int main(int argc, char *argv[])
{
    TApplication rootapp("Test Root", &argc, argv);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
