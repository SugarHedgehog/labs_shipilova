#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class YeastLine
{
private:
    int packagesPerMinute; // Количество упаковок в минуту
    double minutesWorked;  // Время работы линии в минутах

public:
    YeastLine(int ppm, double mw)
        : packagesPerMinute(ppm), minutesWorked(mw) {}

    int calculateTotalPackages() const
    {
        return static_cast<int>(packagesPerMinute * minutesWorked);
    }

    string getFormattedTime() const
    {
        int hours = static_cast<int>(minutesWorked) / 60;
        int minutes = static_cast<int>(minutesWorked) % 60;
        return to_string(hours) + " ч " + to_string(minutes) + " мин";
    }

    void printInfo(int lineNumber) const
    {
        cout << "Линия " << lineNumber << ": " << endl;
        cout << "  Упаковок в минуту: " << packagesPerMinute << endl;
        cout << "  Время работы: " << getFormattedTime() << endl;
        cout << "  Всего упаковок: " << calculateTotalPackages() << endl;
    }
};

class ProfitCalculator
{
private:
    double packageWeight;    // Масса пачки в кг
    double costPerPackage;   // Себестоимость одной пачки в рублях
    double planInTons;       // План выпуска продукции в тоннах
    vector<YeastLine> lines; // Вектор для хранения линий
    double profitPercentagePlanMet;
    double profitPercentagePlanUnder;
    double profitPercentagePlanOver;

public:
    ProfitCalculator(double plan, int numberOfLines, double packageWeight, double costPerPackage,
                     double profitMet, double profitUnder, double profitOver)
        : planInTons(plan), packageWeight(packageWeight), costPerPackage(costPerPackage),
          profitPercentagePlanMet(profitMet), profitPercentagePlanUnder(profitUnder),
          profitPercentagePlanOver(profitOver)
    {
        for (int i = 0; i < numberOfLines; ++i)
        {
            int ppm;
            double mw;
            cout << "Введите количество упаковок в минуту для линии " << i + 1 << ": ";
            cin >> ppm;
            cout << "Введите время работы в минутах для линии " << i + 1 << ": ";
            cin >> mw;
            lines.emplace_back(ppm, mw);
        }
    }

    double calculateProfit() const
    {
        int totalPackages = 0;
        for (const auto &line : lines)
        {
            totalPackages += line.calculateTotalPackages();
        }

        double totalWeightInTons = totalPackages * packageWeight / 1000.0;
        double profitPercentage;

        if (totalWeightInTons == planInTons)
        {
            profitPercentage = profitPercentagePlanMet;
        }
        else if (totalWeightInTons < planInTons)
        {
            profitPercentage = profitPercentagePlanUnder;
        }
        else
        {
            profitPercentage = profitPercentagePlanOver;
        }

        double totalCost = totalPackages * costPerPackage;
        return totalCost * profitPercentage;
    }

    void printProductionInfo() const
    {
        cout << endl;
        for (size_t i = 0; i < lines.size(); ++i)
        {
            lines[i].printInfo(i + 1);
            cout << endl;
        }

        cout << endl;
        cout << "Информация о производстве дрожжей:" << endl;
        cout << "План выпуска продукции (тонн): " << planInTons << endl;
        cout << "Масса пачки (кг): " << packageWeight << endl;
        cout << "Себестоимость одной пачки (руб): " << costPerPackage << endl;
        cout << "Процент прибыли при выполнении плана: " << static_cast<int>(profitPercentagePlanMet * 100) << "%" << endl;
        cout << "Процент прибыли при недовыполнении плана: " << static_cast<int>(profitPercentagePlanUnder * 100) << "%" << endl;
        cout << "Процент прибыли при перевыполнении плана: " << static_cast<int>(profitPercentagePlanOver * 100) << "%" << endl;
    }
};

int main()
{
    double planInTons;
    int numberOfLines;
    double packageWeight;
    double costPerPackage;
    double profitMet, profitUnder, profitOver;

    cout << "Введите план выпуска продукции в тоннах: ";
    cin >> planInTons;
    cout << "Введите массу пачки в кг: ";
    cin >> packageWeight;
    cout << "Введите себестоимость одной пачки в рублях: ";
    cin >> costPerPackage;

    // Prompt the user to enter the profit percentages
    cout << "Введите процент прибыли при выполнении плана (в десятичной дроби): ";
    cin >> profitMet;
    cout << "Введите процент прибыли при недовыполнении плана (в десятичной дроби): ";
    cin >> profitUnder;
    cout << "Введите процент прибыли при перевыполнении плана (в десятичной дроби): ";
    cin >> profitOver;

    cout << "Введите количество линий: ";
    cin >> numberOfLines;

    ProfitCalculator calculator(planInTons, numberOfLines, packageWeight, costPerPackage, profitMet, profitUnder, profitOver);

    calculator.printProductionInfo();

    double profit = calculator.calculateProfit();
    cout << "Суточная прибыль: " << fixed << setprecision(2) << profit << " руб." << endl;

    return 0;
}