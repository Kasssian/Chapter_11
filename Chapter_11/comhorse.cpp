#include <iostream>
#include <iomanip>
using namespace std;

class horse {
protected:
    float position;
public:
    horse() : position(0.0f) {}
    virtual void horse_tick() { position += 0.01f; } // Базовая скорость
    float getPosition() const { return position; }
    virtual ~horse() {}
};

class comhorse : public horse {
private:
    horse** hArray;
    int numHorses;
public:
    comhorse(horse** arr, int n) : hArray(arr), numHorses(n) {}

    void horse_tick() override {
        float maxPos = position;
        for (int i = 0; i < numHorses; ++i) {
            if (hArray[i] != this && hArray[i]->getPosition() > maxPos)
                maxPos = hArray[i]->getPosition();
        }

        // Если лидирует
        if (position >= maxPos) {
            for (int i = 0; i < numHorses; ++i) {
                if (hArray[i] != this) {
                    float diff = position - hArray[i]->getPosition();
                    if (diff >= 0 && diff < 0.1f) {
                        position += 0.015f; // ускорение при близком преследовании
                        return;
                    }
                }
            }
        }

        position += 0.01f; // обычная скорость
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    // Инициализация лошадей
    horse* h0 = new horse();
    horse* h1 = new horse();
    horse* temp[3] = { h0, h1, nullptr };
    comhorse* h2 = new comhorse(temp, 3);
    temp[2] = h2;

    horse* horses[3] = { h0, h1, h2 };

    // Симуляция
    for (int i = 0; i < 100; ++i) {
        cout << "Шаг " << i + 1 << ":\n";
        for (int j = 0; j < 3; ++j) {
            horses[j]->horse_tick();
            cout << "  Лошадь " << j << ": " << fixed << setprecision(3) << horses[j]->getPosition() << endl;
        }
        cout << "--------------------------\n";
    }

    // Очистка памяти
    for (int i = 0; i < 3; ++i)
        delete horses[i];

    return 0;
}
