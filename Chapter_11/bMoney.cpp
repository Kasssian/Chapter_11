#include <iostream>
#include <stdexcept>
using namespace std;

class bMoney {
private:
	long double money;
public:
	bMoney() : money(0.0) {}
	bMoney(long double m) : money(m) {}

	long double getMoney() const { return money; }
	// ��������� ��������� � �������
	friend bMoney operator*(long double num, const bMoney& m) {
		return bMoney(num * m.money);
	}
	friend bMoney operator/(long double num, const bMoney& m) {
		if (m.money == 0) throw runtime_error("������� �� ����!");
		return bMoney(num / m.money);
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
	long double num;

	cout << "������� ������ �����: ";
	cin >> m1;

	cout << "������� ������ �����: ";
	cin >> m2;

	cout << "������� �����: ";
	cin >> num;

	try {
		cout << "num * m1 = " << (num * m1) << endl;
		cout << "num / m1 = " << (num / m1) << endl;
	}
	catch (const exception& e) {
		cerr << "������: " << e.what() << endl;
	}

	return 0;
}
