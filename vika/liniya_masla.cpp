#include <iostream>
#include <vector>

using namespace std;

class productionLine
{
private:
    double productionTarget;           // план в тоннах за смену
    int productionLines;               //количество линий на производстве
    vector<double> lineProductivities; // производительность каждой линии
    double shiftDurationHours;         // продолжительность смены в часах
    double butterUnitWeight;           // вес одного шт масла

public:
    // Конструктор для плана производства
    productionLine(double target, int lines, double shiftDuration, double unitWeight)
        : productionTarget(target), productionLines(lines), shiftDurationHours(shiftDuration), butterUnitWeight(unitWeight)
    {
        lineProductivities.resize(lines);
        for (int i = 0; i < lines; ++i)
        {
            cout << "Введите производительность линии " << i + 1 << " (шт./сек): ";
            cin >> lineProductivities[i];
        }
    }

    // Метод для получения продолжительности смены в секундах
    double getShiftDurationInSeconds() const
    {
        return shiftDurationHours * 3600; // 1 час = 3600 секунд
    }

    // Метод для расчета общего производства в тоннах
    double calculateTotalProductionInTons() const
    {
        return (calculateProductionPerLine() * butterUnitWeight) / 1000.0;
    }

    // Метод для расчета производства на одну линию
    double calculateProductionPerLine() const
    {
        double totalProductivity = 0.0;
        for (double productivity : lineProductivities)
        {
            totalProductivity += productivity;
        }
        return totalProductivity * getShiftDurationInSeconds();
    }

    // Метод для отображения плана производства
    void displayPlan() const
    {
        cout << "Общая цель производства: " << productionTarget << " тонн/смену" << endl;
        cout << "Количество производственных линий: " << productionLines << endl;
        cout << "Продолжительность смены: " << shiftDurationHours << " часов" << endl;
        cout << "Продолжительность смены в секундах: " << getShiftDurationInSeconds() << " секунд" << endl;
        cout << "Вес одной пачки масла: " << butterUnitWeight << " кг" << endl;
        for (int i = 0; i < productionLines; ++i)
        {
            cout << "Производительность линии " << i + 1 << ": " << lineProductivities[i] << " шт./сек" << endl;
        }
        cout << "Общее производство за смену в тоннах: " << calculateTotalProductionInTons() << " тонн" << endl;
    }
};

int main()
{
    // План: 2.7 тонн
    // 3 линии
    // Смена длится 8 часов
    // Вес одной пачки масла 0.2 кг
    productionLine plan(2.7, 3, 8.0, 0.2);
    plan.displayPlan();

    return 0;
}