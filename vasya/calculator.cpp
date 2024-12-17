#include <iostream>
#include <bitset>
#include <string>
#include <vector>

using namespace std;

string toBinaryString(int number) {
    string binResult = bitset<32>(number).to_string();
    binResult.erase(0, binResult.find_first_not_of('0'));
    return binResult.empty() ? "0" : binResult;
}

bool isValidBinary(const string& str) {
    for (char ch : str) {
        if (ch != '0' && ch != '1') {
            return false;
        }
    }
    return true;
}

int main() {
    vector<string> binaryNumbers;
    string bin1, bin2;
    char continueInput;

    do {
        // Ввод первого числа в двоичной системе
        do {
            cout << "Введите первое число в двоичной системе: ";
            cin >> bin1;
            if (!isValidBinary(bin1)) {
                cout << "Ошибка: введите только 0 и 1." << endl;
            }
        } while (!isValidBinary(bin1));

        // Ввод второго числа в двоичной системе
        do {
            cout << "Введите второе число в двоичной системе: ";
            cin >> bin2;
            if (!isValidBinary(bin2)) {
                cout << "Ошибка: введите только 0 и 1." << endl;
            }
        } while (!isValidBinary(bin2));

        // Преобразование двоичных строк в целые числа
        int num1 = stoi(bin1, nullptr, 2);
        int num2 = stoi(bin2, nullptr, 2);

        // Проверка и обмен значений, если num1 меньше num2
        if (num1 < num2) {
            int temp = num1;
            num1 = num2;
            num2 = temp;
        }

        // Выполнение всех операций
        int sum = num1 + num2;
        int difference = num1 - num2;
        int product = num1 * num2;
        string quotient = (num2 != 0) ? toBinaryString(num1 / num2) : "Ошибка: деление на ноль";

        // Запись введенных чисел в массив
        binaryNumbers.push_back(bin1);
        binaryNumbers.push_back(bin2);

        // Вывод результатов
        cout << "Сумма в двоичной системе: " << toBinaryString(sum) << endl;
        cout << "Разность в двоичной системе: " << toBinaryString(difference) << endl;
        cout << "Произведение в двоичной системе: " << toBinaryString(product) << endl;
        cout << "Частное в двоичной системе: " << quotient << endl;

        // Спрашиваем, хочет ли пользователь продолжить
        cout << "Хотите продолжить? (y/n): ";
        cin >> continueInput;

    } while (continueInput == 'y' || continueInput == 'Y');

    // Вывод всех введенных чисел после завершения цикла
    cout << "Введенные числа: ";
    for (const auto& bin : binaryNumbers) {
        cout << bin << " ";
    }
    cout << "Введенные числа в десятичной системе: ";
    for (const auto& bin : binaryNumbers) {
        int decimalValue = stoi(bin, nullptr, 2);
        cout << decimalValue << " ";
    }
    cout << endl;

    return 0;
}