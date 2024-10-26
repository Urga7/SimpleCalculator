#include "calculator_functions.h"
#include <stack>
#include <string>
#include <set>

std::set<char> operators = {'+', '-', 'x', '/'};
bool isOperator(QChar c) {
    return operators.find(c.toLatin1()) != operators.end();
}

int priority(char op){
    if(op == 'x' || op == '/')
        return 2;

    if(op == '+' || op == '-')
        return 1;

    return 0;
}

double applyOp(double a, double b, char op) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case 'x': return a * b;
        case '/': return a / b;
        default: return 0.0;
    }
}

QString evaluateExpression(QString qExpression){
    std::string expression = qExpression.toStdString();
    std::stack <double> values;
    std::stack <char> operands;

    for(unsigned short i = 0; i < expression.length(); ++i) {
        if(expression[i] == ' ')
            continue;

        if(expression[i] == '(')
            operands.push(expression[i]);

        else if(isdigit(expression[i])  || expression[i] == '-' && (i == 0 || expression[i - 1] == '(')) {
            short sign = 1;
            if(expression[i] == '-') {
                sign = -1;
                ++i;
            }

            double val = 0.0;
            while(i < expression.length() && isdigit(expression[i])) {
                val = (val * 10) + (expression[i] - '0');
                ++i;
            }

            if(expression [i] == '.') {
                double pow10neg = 10.0;
                ++i;

                while(i < expression.length() && isdigit(expression[i])) {
                    val += (expression[i] - '0') / pow10neg;
                    pow10neg *= 10.0;
                    ++i;
                }
            }

            values.push(val * sign);
            --i;
        }

        else if(expression[i] == ')') {
            while(!operands.empty() && operands.top() != '(') {
                double val2 = values.top();
                values.pop();
                double val1 = values.top();
                values.pop();
                char op = operands.top();
                operands.pop();
                values.push(applyOp(val1, val2, op));
            }

            if(!operands.empty())
                operands.pop();
        }

        else {
            while(!operands.empty() && priority(operands.top()) >= priority(expression[i])) {
                double val2 = values.top();
                values.pop();
                double val1 = values.top();
                values.pop();
                char op = operands.top();
                operands.pop();
                values.push(applyOp(val1, val2, op));
            }

            operands.push(expression[i]);
        }
    }

    while(!operands.empty()){
        double val2 = values.top();
        values.pop();
        double val1 = values.top();
        values.pop();
        char op = operands.top();
        operands.pop();
        values.push(applyOp(val1, val2, op));
    }

    return QString::number(values.top());
}
