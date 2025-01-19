#include <string>
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class ProductionLine {
protected:
    string name;
    double targetPerShift;
    int currentProduction;
    static int totalProduction;

public:
    ProductionLine(const string& lineName, double target) 
        : name(lineName), targetPerShift(target), currentProduction(0) {}

    void produceTires(int amount) {
        currentProduction += amount;
        totalProduction += amount;
    }

    double getProductionRate() const {
        return (totalProduction / targetPerShift) * 100.0;
    }

    void resetProduction() {
        totalProduction -= currentProduction;
        currentProduction = 0;
    }

    string getName() const { return name; }
    double getTarget() const { return targetPerShift; }
    int getCurrentProduction() const { return currentProduction; }

    static int getTotalProduction() {
        return totalProduction;
    }

    void printStatus() const {
        cout << "Линия " << name << ": произведено " << currentProduction << endl;
    }
};

int ProductionLine::totalProduction = 0;

class salaryCalculator : public ProductionLine {
private:
    double tireCost;        // Себестоимость одной шины
    double hourlyRate;      // Почасовая ставка
    double baseBonusRate;   // Процент премии при выполнении плана
    double overBonusRate;   // Процент премии за перевыполнение
    int hoursPerShift;      // Часов в смене
    int workersCount;       // Количество рабочих на линии

public:
    salaryCalculator(const string& lineName, double target, int workers,
                    double tCost, double hRate, double bBonusRate, 
                    double oBonusRate, int hPerShift)
        : ProductionLine(lineName, target), workersCount(workers),
          tireCost(tCost), hourlyRate(hRate), baseBonusRate(bBonusRate),
          overBonusRate(oBonusRate), hoursPerShift(hPerShift) {}

    double calculateBaseSalaryForAll(int totalWorkers) const {
        return totalWorkers * hourlyRate * hoursPerShift;
    }

    double calculateTotalBonus(double target) const {
        double bonus = 0.0;
        if (totalProduction >= target) {
            bonus += target * tireCost * baseBonusRate;
            if (totalProduction > target) {
                int overProduction = totalProduction - target;
                bonus += overProduction * tireCost * overBonusRate;
            }
        }
        return bonus;
    }

    void printStatus() const {
        cout << "Линия " << name << ": произведено " << currentProduction << endl;
    }
};

// Функция для безопасного ввода числовых данных
template<typename T>
T getInput(const string& prompt) {
    T value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Ошибка ввода. Попробуйте снова.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    // Ввод основных параметров
    double totalTarget = getInput<double>("Введите общий план производства: ");
    int workersPerLine = getInput<int>("Введите количество рабочих на одной линии: ");
    int lineCount = getInput<int>("Введите количество линий: ");
    
    // Ввод параметров расчета
    double tireCost = getInput<double>("Введите себестоимость одной шины (руб.): ");
    double hourlyRate = getInput<double>("Введите почасовую ставку (руб.): ");
    double baseBonusRate = getInput<double>("Введите процент премии за выполнение плана (в долях): ");
    double overBonusRate = getInput<double>("Введите процент премии за перевыполнение плана (в долях): ");
    int hoursPerShift = getInput<int>("Введите количество часов в смене: ");
    
    vector<salaryCalculator> lines;
    
    // Создаем линии
    for(int i = 1; i <= lineCount; i++) {
        lines.push_back(salaryCalculator("№" + to_string(i), totalTarget, workersPerLine,
                                       tireCost, hourlyRate, baseBonusRate, 
                                       overBonusRate, hoursPerShift));
    }

    // Ввод производства для каждой линии
    for(int i = 0; i < lineCount; i++) {
        int production = getInput<int>("Введите количество произведенных покрышек для линии №" + 
                                     to_string(i + 1) + ": ");
        lines[i].produceTires(production);
    }

    cout << "\nСтатус производственных линий:" << endl;
    for(const auto& line : lines) {
        line.printStatus();
    }

    cout << "\nОбщее количество произведенных покрышек: " 
         << salaryCalculator::getTotalProduction() << " из " << totalTarget 
         << " (" << (salaryCalculator::getTotalProduction() / totalTarget * 100.0) 
         << "% от плана)" << endl;

    // Расчет всех выплат
    double baseSalary = lines[0].calculateBaseSalaryForAll(workersPerLine * lineCount);
    double totalBonus = lines[0].calculateTotalBonus(totalTarget);
    double totalPayment = baseSalary + totalBonus;

    cout << "\nОбщий расчет для всего производства:" << endl;
    cout << "Базовая зарплата всего персонала: " << baseSalary << " руб." << endl;
    
    if (totalBonus > 0) {
        cout << "Общая премия: " << totalBonus << " руб." << endl;
    } else {
        cout << "План не выполнен, премия не начисляется" << endl;
    }
    
    cout << "Итого к выплате: " << totalPayment << " руб." << endl;

    return 0;
}