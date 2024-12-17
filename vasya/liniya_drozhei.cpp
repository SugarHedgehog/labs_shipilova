#include <iostream>

using namespace std;

// Класс, представляющий поточную линию для производства дрожжей
class YeastLine {
private:
    int packagesPerMinute; // Количество упаковок в минуту
    double minutesWorked;  // Время работы линии в минутах

public:
    // Конструктор класса, инициализирующий производительность и время работы
    YeastLine(int ppm, double mw)
        : packagesPerMinute(ppm), minutesWorked(mw) {}

    // Метод для расчета общего количества произведенных упаковок
    int calculateTotalPackages() const {
        return static_cast<int>(packagesPerMinute * minutesWorked);
    }

    // Метод для преобразования минут в формат "n часов m минут"
    string getFormattedTime() const {
        int hours = static_cast<int>(minutesWorked) / 60;
        int minutes = static_cast<int>(minutesWorked) % 60;
        string result = to_string(hours) + " часов";
        if (minutes > 0) {
            result += " " + to_string(minutes) + " минут";
        }
        return result;
    }

    // Метод для вывода информации о производственной линии
    void displayInfo() const {
        cout << "Количество упаковок в минуту: " << packagesPerMinute << endl;
        cout << "Линия работала: " << getFormattedTime() << endl;
        cout << "Общее количество произведенных упаковок: " 
             << calculateTotalPackages() << endl;
    }
};

int main() {
    // Создаем объекты для каждой из трех линий
    YeastLine line1(8, 300.0);      // Первая линия работает 5 часов (300 минут)
    YeastLine line2(8, 400.0);      // Вторая линия работает 6 часов 40 минут (400 минут)

    // Выводим информацию о каждой линии
    cout << "Линия 1:" << endl;
    line1.displayInfo();
    cout << endl;

    cout << "Линия 2:" << endl;
    line2.displayInfo();
    cout << endl;

    return 0;
}