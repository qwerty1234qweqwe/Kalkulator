#include <iostream>
#include <cmath>
#include <stack>
#include <string>

using namespace std;

int precedence(char op) {
    if (op == '^')
        return 3;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return -1;
}

double precedenceOp(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    case '^': return pow(a, b);
    }
    return 0;
}

double Expression(string expression) {
    stack<double> values;
    stack<char> ops;

    for (int i = 0; i < expression.size(); i++) {
        if (expression[i] == ' ')
            continue;

        if (expression[i] == '(') {
            ops.push(expression[i]);
        }
        else if (isdigit(expression[i])) {
            double val = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                val = val * 10 + (expression[i] - '0');
                i++;
            }
            values.push(val);
            i--;
        }
        else if (expression[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                double val2 = values.top();
                values.pop();

                double val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(precedenceOp(val1, val2, op));
            }
            ops.pop();
        }
        else {
            while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i])) {
                double val2 = values.top();
                values.pop();

                double val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(precedenceOp(val1, val2, op));
            }
            ops.push(expression[i]);
        }
    }

    while (!ops.empty()) {
        double val2 = values.top();
        values.pop();

        double val1 = values.top();
        values.pop();

        char op = ops.top();
        ops.pop();

        values.push(precedenceOp(val1, val2, op));
    }

    return values.top();
}

int main()
{
    setlocale(0, "rus");
    string expression;
    cout << "Введите выражение: ";
    getline(cin, expression);

    double result = Expression(expression);

    cout << "Результат выражения: " << result << endl;
}
