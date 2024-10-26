#ifndef CALCULATOR_FUNCTIONS_H
#define CALCULATOR_FUNCTIONS_H

#include <QString>

int priority(char op);
double applyOp(double a, double b, char op);
bool isOperator(QChar c);
QString evaluateExpression(QString qExpression);

#endif // CALCULATOR_FUNCTIONS_H
