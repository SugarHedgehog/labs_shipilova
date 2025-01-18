#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class RepairMaterial {
protected:
    string name;
    double length; // в метрах
    double width;  // в метрах
    double area;   // в квадратных метрах

public:
    RepairMaterial(string n, double l, double w) : name(n), length(l), width(w) {
        area = length * width;
    }

    virtual void displayInfo() const {
        cout << "Материал: " << name << endl;
        cout << "Размеры: " << length << "м x " << width << "м" << endl;
        cout << "Площадь: " << area << " квадратных метров" << endl;
    }

    double getArea() const {
        return area;
    }
};

class CeramicTile : public RepairMaterial {
public:
    CeramicTile() : RepairMaterial("Керамическая плитка", 0.15, 0.15) {}
};

class WashableWallpaper : public RepairMaterial {
public:
    WashableWallpaper() : RepairMaterial("Моющиеся обои", 10.0, 0.6) {}
};

class Penoplen : public RepairMaterial {
public:
    Penoplen() : RepairMaterial("Пеноплен", 10.0, 1.5) {}
};

class MaterialCalculator {
private:
    double roomLength;
    double roomWidth;
    double roomHeight;
    double tilePrice;
    double wallpaperPrice;
    double penoplenPrice;

public:
    MaterialCalculator(double l, double w, double h, double tp, double wp, double pp)
        : roomLength(l), roomWidth(w), roomHeight(h), tilePrice(tp), wallpaperPrice(wp), penoplenPrice(pp) {}

    void calculateMaterials() {
        double wallArea = 2 * (roomLength * roomHeight + roomWidth * roomHeight);
        cout << "Площадь стен: " << wallArea << " квадратных метров" << endl;

        if (wallArea < 31) {
            CeramicTile tile;
            double numTiles = ceil(wallArea / tile.getArea());
            double cost = numTiles * tilePrice;
            cout << "Используется керамическая плитка. Количество: " << numTiles << ", Стоимость: " << cost << " руб." << endl;
        } else if (wallArea == 31) {
            WashableWallpaper wallpaper;
            double numRolls = ceil(wallArea / wallpaper.getArea());
            double cost = numRolls * wallpaperPrice;
            cout << "Используются моющиеся обои. Количество: " << numRolls << ", Стоимость: " << cost << " руб." << endl;
        } else {
            Penoplen penoplen;
            double numSheets = ceil(wallArea / penoplen.getArea());
            double cost = numSheets * penoplenPrice;
            cout << "Используется пеноплен. Количество: " << numSheets << ", Стоимость: " << cost << " руб." << endl;
        }
    }
};

int main() {
    double roomLength, roomWidth, roomHeight;
    double tilePrice, wallpaperPrice, penoplenPrice;

    cout << "Введите длину помещения: ";
    cin >> roomLength;
    cout << "Введите ширину помещения: ";
    cin >> roomWidth;
    cout << "Введите высоту помещения: ";
    cin >> roomHeight;

    cout << "Введите цену за плитку: ";
    cin >> tilePrice;
    cout << "Введите цену за рулон обоев: ";
    cin >> wallpaperPrice;
    cout << "Введите цену за лист пеноплена: ";
    cin >> penoplenPrice;

    MaterialCalculator calculator(roomLength, roomWidth, roomHeight, tilePrice, wallpaperPrice, penoplenPrice);
    calculator.calculateMaterials();

    return 0;
}