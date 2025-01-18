#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <sstream>

using namespace std;

void displayNumbers(const vector<int>& numbers) {
    cout << "Введенные числа: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
}

void findMinMax(const vector<int>& numbers, int& min, int& max) {
    if (!numbers.empty()) {
        min = *min_element(numbers.begin(), numbers.end());
        max = *max_element(numbers.begin(), numbers.end());
    }
}

void displayMenu() {
    cout << "Меню:\n";
    cout << "1. Ввести числа";
    cout << "\t2. Найти минимальное и максимальное значения";
    cout << "\t3. Показать хронологию чисел";
    cout << "\t4. О программе";
    cout << "\t5. Выход\n";
}

void aboutProgram() {
    cout << "Эта программа позволяет вводить числа, находить минимальное и максимальное значения, а также отображать хронологию чисел.\n";
}

int main() {
    vector<int> numbers;
    int choice;
    int min = numeric_limits<int>::max();
    int max = numeric_limits<int>::min();

    do {
        displayMenu();
        cout << "Выберите опцию: ";
        cin >> choice;
        cin.ignore();  // Игнорируем оставшийся символ новой строки

        switch (choice) {
            case 1: {
                string input;
                cout << "Введите числа, разделенные пробелами: ";
                getline(cin, input);
                stringstream ss(input);
                int number;
                while (ss >> number) {
                    numbers.push_back(number);
                }
                break;
            }
            case 2: {
                findMinMax(numbers, min, max);
                cout << "Минимальное значение: " << min << "\nМаксимальное значение: " << max << endl;
                break;
            }
            case 3: {
                displayNumbers(numbers);
                break;
            }
            case 4: {
                aboutProgram();
                break;
            }
            case 5: {
                cout << "Выход из программы.\n";
                break;
            }
            default: {
                cout << "Неверный выбор. Попробуйте снова.\n";
                break;
            }
        }
    } while (choice != 5);

    return 0;
}