#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Banka
{
protected:
    double capacity; // Емкость в литрах

public:
    // Конструктор, принимающий емкость
    Banka(double cap) : capacity(cap) {}

    // Метод для получения описания емкости
    string getDescription() const
    {
        // Convert capacity and filled weight to strings with fixed precision
        string capacityStr = to_string(capacity);
        capacityStr = capacityStr.substr(0, capacityStr.find('.') + 2); // Keep one decimal place

        string weightStr = to_string(getFilledWeight());
        weightStr = weightStr.substr(0, weightStr.find('.') + 3); // Keep two decimal places

        return "Ёмкость с объемом: " + capacityStr + " литров\nВесом: " + weightStr + " кг\n";
    }

    // Метод для получения емкости
    double getCapacity() const
    {
        return capacity;
    }

    // Метод для расчета веса заполненной банки
    double getFilledWeight() const
    {
        const double fillPercentage = 0.95; // 95% заполнение
        const double milkDensity = 1.23; // Удельный вес молока в кг/л
        return capacity * fillPercentage * milkDensity;
    }
};

// Подкласс для емкости 0.5 литра
class Banka0_5L : public Banka
{
public:
    // Конструктор, устанавливающий емкость в 0.5 литра
    Banka0_5L() : Banka(0.5) {}
};

// Подкласс для емкости 1.5 литра
class Banka1_5L : public Banka
{
public:
    // Конструктор, устанавливающий емкость в 1.5 литра
    Banka1_5L() : Banka(1.5) {}
};

// Подкласс для емкости 3 литра
class Banka3L : public Banka
{
public:
    // Конструктор, устанавливающий емкость в 3 литра
    Banka3L() : Banka(3.0) {}
};

int main()
{
    // Создание объектов для каждой емкости
    Banka0_5L smallBanka;
    Banka1_5L mediumBanka;
    Banka3L largeBanka;
    cout << "Размер партии для разлива: 1780 кг\n" << endl;

    // Вывод описания и емкости для каждого объекта
    cout << smallBanka.getDescription() << endl;
    cout << mediumBanka.getDescription() << endl;
    cout << largeBanka.getDescription() << endl;

    return 0;
}