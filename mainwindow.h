#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class Calculator;
}
QT_END_NAMESPACE

class Calculator : public QMainWindow {
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;

private slots:
    void numberPressed();
    void operatorPressed();
    void clearPressed();
    void bracketPressed();
    void dotPressed();
    void equalsPressed();
};

#endif // MAINWINDOW_H
