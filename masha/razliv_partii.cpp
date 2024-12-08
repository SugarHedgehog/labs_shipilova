#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>

using namespace std;

class Banka
{
protected:
    double capacity; // Емкость в литрах

public:
    Banka(double cap) : capacity(cap) {}

    string getDescription() const
    {
        string capacityStr = to_string(capacity);
        capacityStr = capacityStr.substr(0, capacityStr.find('.') + 2); // Keep one decimal place

        string weightStr = to_string(getFilledWeight());
        weightStr = weightStr.substr(0, weightStr.find('.') + 3); // Keep two decimal places

        return "Ёмкость с объемом: " + capacityStr + " литров\nВесом: " + weightStr + " кг\n";
    }

    double getCapacity() const
    {
        return capacity;
    }

    double getFilledWeight() const
    {
        const double fillPercentage = 0.95; // 95% заполнение
        const double milkDensity = 1.23;    // Удельный вес молока в кг/л
        return capacity * fillPercentage * milkDensity;
    }
};

class Razliv
{
private:
    double standardMass; // Стандартная масса партии в кг
    double deviation;    // Отклонение в процентах
    double largeBankaCapacity;
    double smallBankaCapacity;

public:
    Razliv(double stdMass, double dev, double largeCap, double smallCap)
        : standardMass(stdMass), deviation(dev), largeBankaCapacity(largeCap), smallBankaCapacity(smallCap) {}

    void calculateContainers()
    {
        double actualMass = standardMass * (1 + deviation / 100);
        cout << "\nРеальная масса партии в кг.: " << actualMass << "\n"
             << endl;

        // Use large containers for excess
        Banka largeBanka(largeBankaCapacity);
        int numLargeBankas = static_cast<int>(floor(actualMass / largeBanka.getFilledWeight()));
        double weightInLargeBanka = numLargeBankas * largeBanka.getFilledWeight();
        double weightInSmallBanka = actualMass - weightInLargeBanka;

        // Use small containers for remaining excess
        Banka smallBanka(smallBankaCapacity);
        int numSmallBankas = static_cast<int>(ceil(weightInSmallBanka / smallBanka.getFilledWeight()));

        cout << "В большую банку вмещается " << largeBanka.getFilledWeight() << " кг." << endl;
        cout << "В маленькую банку вмещается " << smallBanka.getFilledWeight() << " кг." << endl;

        cout << fixed << setprecision(2);
        cout << "Необходимо использовать " << numLargeBankas << " "
             << " банок объёмом " << largeBanka.getCapacity() << " л. и "
             << numSmallBankas << " банок объёмом " << smallBanka.getCapacity() << " л." << endl;
        cout << "В большие вместилось " << weightInLargeBanka << " кг. сгущёнки" << endl;
        cout << "В маленькие вместилось " << weightInSmallBanka << " кг. сгущёнки" << endl;
    }
};

int main()
{
    double standardMass;
    cout << "Введите стандартную массу партии в кг.: ";
    cin >> standardMass;

    srand(static_cast<unsigned int>(time(0)));

    double minInt, maxInt;
    cout << "Введите минимальное значение для отклонения в процентах: ";
    cin >> minInt;
    cout << "Введите максимальное значение для отклонения в процентах: ";
    cin >> maxInt;

    int scaledMin = minInt * 10;
    int scaledMax = maxInt * 10;

    double deviation = (scaledMin + rand() % (scaledMax - scaledMin + 1)) / 10.0;

    double largeBankaCapacity, smallBankaCapacity;
    cout << "Введите объём большой банки в литрах: ";
    cin >> largeBankaCapacity;
    cout << "Введите объём маленькой банки в литрах: ";
    cin >> smallBankaCapacity;

    cout << "\nПроцент отклонения от стандартной массы партии: " << deviation << "%" << endl;

    Razliv razliv(standardMass, deviation, largeBankaCapacity, smallBankaCapacity);
    razliv.calculateContainers();

    return 0;
}