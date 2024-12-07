#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Класс, представляющий производственную линию
class productionLine {
protected:
    double productionTarget;           // план в тоннах за смену
    int productionLines;               // количество линий на производстве
    vector<double> lineProductivities; // производительность каждой линии
    double shiftDurationHours;         // продолжительность смены в часах
    double butterUnitWeight;           // вес одного шт масла

public:
    // Конструктор для инициализации плана производства
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

    double getProductionTarget() const
    {
        return productionTarget;
    }
};

// Класс для расчета выплат работникам, наследующийся от productionLine
class WorkerPayment : public productionLine {
private:
    double hourlyRate;      // Часовая ставка
    double costPerUnit;     // Себестоимость пачки масла в рублях
    double targetBonusRate; // Процент бонуса при выполнении плана
    double excessBonusRate; // Процент бонуса при перевыполнении плана

public:
    // Конструктор для инициализации параметров выплат
    WorkerPayment(double target, int lines, double shiftDuration, double unitWeight, double rate, double cost, double targetBonus, double excessBonus)
        : productionLine(target, lines, shiftDuration, unitWeight), hourlyRate(rate), costPerUnit(cost), targetBonusRate(targetBonus), excessBonusRate(excessBonus) {}

    // Метод для расчета бонуса
    double calculateBonus() const
    {
        double totalProduction = calculateTotalProductionInTons();
        double targetProduction = getProductionTarget();
        double bonus = 0.0;

        if (totalProduction >= targetProduction)
        {
            double unitsProduced = calculateProductionPerLine();
            if (totalProduction == targetProduction)
            {
                bonus = unitsProduced * costPerUnit * targetBonusRate;
            }
            else
            {
                double excessProduction = totalProduction - targetProduction;
                double excessUnits = (excessProduction * 1000) / butterUnitWeight;
                bonus = excessUnits * costPerUnit * excessBonusRate;
            }
        }

        return bonus;
    }

    // Метод для расчета общей выплаты
    double calculateTotalPayment() const
    {
        double basePayment = shiftDurationHours * hourlyRate;
        double bonus = calculateBonus();
        return basePayment + bonus;
    }

    // Метод для отображения деталей выплат
    void displayPaymentDetails() const
    {
        displayPlan();
        cout << fixed << setprecision(2); // Set fixed-point notation and precision
        cout << "Бонус за смену: " << calculateBonus() << " руб." << endl;
        cout << "Общая выплата за смену: " << calculateTotalPayment() << " руб." << endl;
    }
};

int main() {
    double targetProduction;
    int numberOfLines;
    double shiftDuration;
    double butterUnitWeight;
    double hourlyRate;
    double costPerUnit;
    double targetBonusRate;
    double excessBonusRate;

    // Prompt the user for input
    cout << "Введите план производства (в тоннах): ";
    cin >> targetProduction;
    
    cout << "Введите количество линий: ";
    cin >> numberOfLines;
    
    cout << "Введите длительность смены (в часах): ";
    cin >> shiftDuration;
    
    cout << "Введите вес одной пачки масла (в кг): ";
    cin >> butterUnitWeight;
    
    cout << "Введите часовую ставку (в рублях): ";
    cin >> hourlyRate;
    
    cout << "Введите себестоимость пачки масла (в рублях): ";
    cin >> costPerUnit;
    
    cout << "Введите процент бонуса при выполнении плана: ";
    cin >> targetBonusRate;
    
    cout << "Введите процент бонуса при перевыполнении плана: ";
    cin >> excessBonusRate;

    // Create an instance of WorkerPayment with user input
    WorkerPayment worker(targetProduction, numberOfLines, shiftDuration, butterUnitWeight, hourlyRate, costPerUnit, targetBonusRate, excessBonusRate);
    
    // Display payment details
    worker.displayPaymentDetails();

    return 0;
}