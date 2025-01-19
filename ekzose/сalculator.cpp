#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <stack>
#include <cctype>

using namespace std;

struct Calculation {
    string expression;
    double result;
};

// Определяет приоритет операторов
int getPriority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '(' || op == ')') return 0;
    return -1;
}

// Выполняет операцию между двумя числами
double executeOperation(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) throw runtime_error("Деление на ноль!");
            return a / b;
        default:
            throw runtime_error("Неверная операция!");
    }
}

// Вычисляет значение выражения
double calculateExpression(const string& expr) {
    stack<double> numbers;
    stack<char> operators;
    
    string num;
    for (size_t i = 0; i < expr.length(); i++) {
        if (isspace(expr[i])) continue;
        
        // Обработка открывающей скобки
        if (expr[i] == '(') {
            operators.push(expr[i]);
            continue;
        }
        
        // Обработка закрывающей скобки
        if (expr[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                double b = numbers.top(); numbers.pop();
                double a = numbers.top(); numbers.pop();
                char op = operators.top(); operators.pop();
                numbers.push(executeOperation(a, b, op));
            }
            if (!operators.empty()) operators.pop(); // Удаляем открывающую скобку
            continue;
        }
        
        if (isdigit(expr[i]) || expr[i] == '.') {
            num += expr[i];
            if (i + 1 == expr.length() || (!isdigit(expr[i + 1]) && expr[i + 1] != '.')) {
                numbers.push(stod(num));
                num.clear();
            }
        }
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            while (!operators.empty() && operators.top() != '(' && 
                   getPriority(operators.top()) >= getPriority(expr[i])) {
                double b = numbers.top(); numbers.pop();
                double a = numbers.top(); numbers.pop();
                char op = operators.top(); operators.pop();
                numbers.push(executeOperation(a, b, op));
            }
            operators.push(expr[i]);
        }
    }

    while (!operators.empty()) {
        double b = numbers.top(); numbers.pop();
        double a = numbers.top(); numbers.pop();
        char op = operators.top(); operators.pop();
        numbers.push(executeOperation(a, b, op));
    }

    return numbers.top();
}

void displayHistory(const vector<Calculation>& history) {
    cout << "\nИстория вычислений:\n";
    cout << string(50, '-') << endl;
    for (const auto& calc : history) {
        cout << calc.expression << " = " << calc.result << endl;
    }
    cout << string(50, '-') << endl;
}

void displayMenu() {
    cout << "\nМеню калькулятора:\n";
    cout << "1. Ввести выражение\n";
    cout << "2. Показать историю\n";
    cout << "3. О программе\n";
    cout << "4. Выход\n";
}

void aboutProgram() {
    cout << "\nКалькулятор строковых выражений\n";
    cout << "Программа позволяет вычислять математические выражения, введённые в виде строки.\n";
    cout << "Пример: (2+3)*4 или 5/(1+1)\n";
    cout << "Поддерживаемые операции: +, -, *, / и скобки\n";
}

int main() {
    vector<Calculation> history;
    int choice;

    do {
        displayMenu();
        cout << "Выберите опцию: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                Calculation calc;
                cout << "Введите выражение (например, (3+6)*(8-1)): ";
                getline(cin, calc.expression);

                try {
                    calc.result = calculateExpression(calc.expression);
                    cout << "Результат: " << fixed << setprecision(2) << calc.result << endl;
                    history.push_back(calc);
                }
                catch (const runtime_error& e) {
                    cout << "Ошибка: " << e.what() << endl;
                }
                break;
            }
            case 2:
                displayHistory(history);
                break;
            case 3:
                aboutProgram();
                break;
            case 4:
                cout << "Программа завершена.\n";
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 4);

    return 0;
}