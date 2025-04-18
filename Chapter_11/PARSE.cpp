#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <iomanip> // для форматированного вывода
using namespace std;

// Абстрактный базовый класс
class Token {
public:
	virtual float getNumber() const = 0;
	virtual char getOperator() const = 0;
	virtual ~Token() {}
};

// Класс числа
class Number : public Token {
private:
	float fnum;
public:
	Number(float n) : fnum(n) {}
	float getNumber() const override { return fnum; }
	char getOperator() const override { return 0; } // фиктивный
};

// Класс оператора
class Operator : public Token {
private:
	char oper;
public:
	Operator(char op) : oper(op) {}
	float getNumber() const override { return 0; } // фиктивный
	char getOperator() const override { return oper; }
};

// Класс стека
class Stack {
private:
	Token* tokens[100];
	int top;
public:
	Stack() : top(-1) {}

	void push(Token* t) {
		if (top < 99) tokens[++top] = t;
		else cerr << "Стек переполнен!" << endl;
	}

	Token* pop() {
		if (top >= 0) return tokens[top--];
		else {
			cerr << "Стек пуст!" << endl;
			return nullptr;
		}
	}

	bool empty() const {
		return top == -1;
	}

	void print() const {
		for (int i = 0; i <= top; ++i) {
			if (tokens[i]->getOperator() != 0)
				cout << "Оператор: " << tokens[i]->getOperator() << endl;
			else
				cout << fixed << setprecision(4)
				<< "Число: " << tokens[i]->getNumber() << endl;
		}
	}

	~Stack() {
		while (!empty()) delete pop();
	}
};

// Парсинг выражения и загрузка в стек
void parseAndPush(const string& input, Stack& s) {
	stringstream ss;
	for (char c : input) {
		if (isdigit(c) || c == '.') {
			ss << c;
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/') {
			if (!ss.str().empty()) {
				float num = stof(ss.str());
				s.push(new Number(num));
				ss.str(""); ss.clear();
			}
			s.push(new Operator(c));
		}
	}

	// Последнее число
	if (!ss.str().empty()) {
		float num = stof(ss.str());
		s.push(new Number(num));
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	string input = "3.14159/2.0+75.25*3.333+6.02";

	cout << "Исходное выражение: " << input << endl;

	Stack s;
	parseAndPush(input, s);

	cout << "\nРезультат разбора и хранения в стеке:\n";
	s.print();

	return 0;
}
