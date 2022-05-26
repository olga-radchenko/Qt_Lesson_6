#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show(); /* Не смогла решить проблему перевода стандартного контекстного меню для QPlainTextEdit на русский
                 Есть ли возможность сделать это без написания класса-обертки для QPlainTextEdit с педенными пунктами меню ?*/
    return a.exec();
}
