#include <string>
#include <iostream>
#include <vector>

using namespace std;

class ProductionLine {
private:
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
        return (currentProduction / targetPerShift) * 100.0;
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

// Инициализация статической переменной
int ProductionLine::totalProduction = 0;

int main() {
    const double TOTAL_TARGET = 1240.0;
    const double LINE_TARGET = TOTAL_TARGET / 4.0;

    vector<ProductionLine> lines;
    
    lines.push_back(ProductionLine("№1", LINE_TARGET));
    lines.push_back(ProductionLine("№2", LINE_TARGET));
    lines.push_back(ProductionLine("№3", LINE_TARGET));
    lines.push_back(ProductionLine("№4", LINE_TARGET));

    lines[0].produceTires(150);
    lines[1].produceTires(160);
    lines[2].produceTires(145);
    lines[3].produceTires(155);

    cout << "Статус производственных линий:" << endl;
    for(const auto& line : lines) {
        line.printStatus();
    }

    cout << "\nОбщее количество произведенных покрышек: " 
         << ProductionLine::getTotalProduction() << " из " << TOTAL_TARGET 
         << " (" << (ProductionLine::getTotalProduction() / TOTAL_TARGET * 100.0) 
         << "% от плана)" << endl;

    return 0;
}