#include "mainwindow.h"
#include "loginansicht.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginAnsicht l;
    l.show();
    return a.exec();
}
