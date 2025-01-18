#include <iostream>
#include <string>

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

int main() {
    CeramicTile tile;
    WashableWallpaper wallpaper;
    Penoplen penoplen;

    tile.displayInfo();
    cout << endl;
    wallpaper.displayInfo();
    cout << endl;
    penoplen.displayInfo();

    return 0;
}