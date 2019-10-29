#include "mainwindow.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    int currentExitCode = 0;

    do {
     QCoreApplication a(argc, argv);
     MainWindow w;
     currentExitCode = a.exec();
    } while( currentExitCode == MainWindow::EXIT_CODE_REBOOT );

    return currentExitCode;

}
