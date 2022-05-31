#include "mainwindow.h"
#include <QApplication>

#include "graphics_window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyGraphicsView w;
    w.show();
    return a.exec();
}
