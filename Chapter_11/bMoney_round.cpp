#include <iostream>
#include <cmath> // ��� modfl
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

	// ���������� �����
	friend istream& operator>>(istream& in, bMoney& m) {
		in >> m.money;
		return in;
	}

	// ���������� ������
	friend ostream& operator<<(ostream& out, const bMoney& m) {
		out << m.money;
		return out;
	}
};

int main() {
	setlocale(LC_ALL, "Russian");

	bMoney m1, m2;

	cout << "������� ������ �����: ";
	cin >> m1;

	cout << "������� ������ �����: ";
	cin >> m2;

	cout << "���������� m1: " << m1.round() << endl;
	cout << "���������� m2: " << m2.round() << endl;

	return 0;
}
