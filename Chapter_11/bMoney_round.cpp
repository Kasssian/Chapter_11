#include <iostream>
#include <cmath> // для modfl
using namespace std;

class bMoney {
private:
	long double money;
public:
	bMoney() : money(0.0) {}
	bMoney(long double m) : money(m) {}

	long double getMoney() const { return money; }

	bMoney round() const {
		long double intPart;
		long double fracPart = modfl(money, &intPart);
		if (fracPart >= 0.5)
			return bMoney(intPart + 1);
		return bMoney(intPart);
	}

	// Перегрузка ввода
	friend istream& operator>>(istream& in, bMoney& m) {
		in >> m.money;
		return in;
	}

	// Перегрузка вывода
	friend ostream& operator<<(ostream& out, const bMoney& m) {
		out << m.money;
		return out;
	}
};

int main() {
	setlocale(LC_ALL, "Russian");

	bMoney m1, m2;

	cout << "Введите первую сумму: ";
	cin >> m1;

	cout << "Введите вторую сумму: ";
	cin >> m2;

	cout << "Округление m1: " << m1.round() << endl;
	cout << "Округление m2: " << m2.round() << endl;

	return 0;
}
