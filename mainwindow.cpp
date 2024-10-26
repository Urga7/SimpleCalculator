#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "calculator_functions.h"

unsigned short brackets = 0;
bool dotLegal = true;

Calculator::Calculator(QWidget *parent) : QMainWindow(parent), ui(new Ui::Calculator) {
    ui->setupUi(this);
    this->setWindowTitle("Calculator");
    this->setStyleSheet("background-color: #282628;");
    ui->Display->setText("0");

    for(qsizetype i = 0; i < 10; ++i) {
        QString buttonName = "num" + QString::number(i);
        QPushButton* button = Calculator::findChild<QPushButton*>(buttonName);
        connect(button, SIGNAL(released()), this, SLOT(numberPressed()));
    }

    connect(ui->add, SIGNAL(released()), this, SLOT(operatorPressed()));
    connect(ui->subtract, SIGNAL(released()), this, SLOT(operatorPressed()));
    connect(ui->multiply, SIGNAL(released()), this, SLOT(operatorPressed()));
    connect(ui->divide, SIGNAL(released()), this, SLOT(operatorPressed()));
    connect(ui->clear, SIGNAL(released()), SLOT(clearPressed()));
    connect(ui->openBracket, SIGNAL(released()), this, SLOT(bracketPressed()));
    connect(ui->closedBracket, SIGNAL(released()), this, SLOT(bracketPressed()));
    connect(ui->dot, SIGNAL(released()), SLOT(dotPressed()));
    connect(ui->equals, SIGNAL(released()), SLOT(equalsPressed()));
}

Calculator::~Calculator() {
    delete ui;
}

void Calculator::numberPressed() {
    QPushButton* button = (QPushButton*) sender();
    QString buttonValue = button->text();
    QString displayValue = ui->Display->text();
    QChar lastChar = '0';

    if(!displayValue.isEmpty())
        lastChar = displayValue[displayValue.size() - 1];

    if(lastChar == ')')
        return;

    if(displayValue == "0" || displayValue == "0.0")
        ui->Display->setText(buttonValue);
    else {
        QString newValue = displayValue + buttonValue;
        ui->Display->setText(newValue);
    }
}

void Calculator::operatorPressed() {
    QPushButton* button = (QPushButton*) sender();
    QChar operatorPressed = button->text()[0];
    QString displayValue = ui->Display->text();

    if(displayValue.isEmpty())
        return;

    QChar lastChar = displayValue[displayValue.size() - 1];
    if(lastChar == '.' || lastChar == '(')
        return;

    if (isOperator(lastChar))
        displayValue[displayValue.size() - 1] = operatorPressed;
    else
        displayValue += operatorPressed;

    ui->Display->setText(displayValue);
    dotLegal = true;
}

void Calculator::clearPressed() {
    ui->Display->setText("");
    dotLegal = true;
    brackets = 0;
}

void Calculator::bracketPressed() {
    QPushButton* button = (QPushButton*) sender();
    QChar bracket = button->text()[0];
    QString displayValue = ui->Display->text();
    QChar lastChar = ' ';

    if(!displayValue.isEmpty())
        lastChar = displayValue[displayValue.size() - 1];

    if(lastChar == '.')
        return;

    if(bracket == '(') {
        if(!isOperator(lastChar) && lastChar != '(' && lastChar != ' ')
            return;

        ++brackets;
    } else {
        if(isOperator(lastChar) || lastChar == '(' || lastChar == ' ' || !brackets)
            return;

        --brackets;
    }

    ui->Display->setText(displayValue + bracket);
    dotLegal = true;
}

void Calculator::dotPressed() {
    QString displayValue = ui->Display->text();
    char lastChar = displayValue.toStdString()[displayValue.size() - 1];

    if(!isdigit(lastChar) || !dotLegal)
        return;

    ui->Display->setText(displayValue + '.');
    dotLegal = false;
}

void Calculator::equalsPressed() {
    if(brackets)
        return;

    QString expression = ui->Display->text();
    if(expression.isEmpty())
        return;

    if(isOperator(expression[expression.size() - 1]))
        return;

    QString result = evaluateExpression(expression);
    ui->Display->setText(result);
    brackets = 0;
    dotLegal = true;
}
