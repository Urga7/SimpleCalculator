#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/imgs/calculator.ico"));
    Calculator calc;
    calc.show();
    return a.exec();
}
