#include <iostream>
#include <iomanip>
using namespace std;

class horse {
protected:
    float position;
public:
    horse() : position(0.0f) {}
    virtual void horse_tick() { position += 0.01f; } // ������� ��������
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

        // ���� ��������
        if (position >= maxPos) {
            for (int i = 0; i < numHorses; ++i) {
                if (hArray[i] != this) {
                    float diff = position - hArray[i]->getPosition();
                    if (diff >= 0 && diff < 0.1f) {
                        position += 0.015f; // ��������� ��� ������� �������������
                        return;
                    }
                }
            }
        }

        position += 0.01f; // ������� ��������
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    // ������������� �������
    horse* h0 = new horse();
    horse* h1 = new horse();
    horse* temp[3] = { h0, h1, nullptr };
    comhorse* h2 = new comhorse(temp, 3);
    temp[2] = h2;

    horse* horses[3] = { h0, h1, h2 };

    // ���������
    for (int i = 0; i < 100; ++i) {
        cout << "��� " << i + 1 << ":\n";
        for (int j = 0; j < 3; ++j) {
            horses[j]->horse_tick();
            cout << "  ������ " << j << ": " << fixed << setprecision(3) << horses[j]->getPosition() << endl;
        }
        cout << "--------------------------\n";
    }

    // ������� ������
    for (int i = 0; i < 3; ++i)
        delete horses[i];

    return 0;
}
