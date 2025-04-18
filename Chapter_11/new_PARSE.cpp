#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
using namespace std;

class Token {
public:
	virtual float getNumber() const = 0;
	virtual char getOperator() const = 0;
	virtual ~Token() {}
};

class Operator : public Token {
private:
	char oper;
public:
	Operator(char op) : oper(op) {}
	float getNumber() const override { return 0.0f; } // фиктивная
	char getOperator() const override { return oper; }
};

class Number : public Token {
private:
	float fnum;
public:
	Number(float num) : fnum(num) {}
	float getNumber() const override { return fnum; }
	char getOperator() const override { return 0; } // фиктивная
};

class Stack {
private:
	Token* tokens[100];
	int top;
public:
	Stack() : top(-1) {}
	void push(Token* t) { tokens[++top] = t; }
	Token* pop() { return tokens[top--]; }
	bool empty() const { return top == -1; }

	~Stack() {
		while (!empty()) {
			delete pop();
		}
	}
};

int main() {
	setlocale(LC_ALL, "Russian");
	string input;
	cout << "Введите выражение в ОПЗ (например: 3.14 2.0 + 4.0 *): ";
	getline(cin, input);
	stringstream ss(input);
	string token;

	Stack evalStack;

	while (ss >> token) {
		if (token == "+" || token == "-" || token == "*" || token == "/") {
			if (evalStack.empty()) {
				cerr << "Ошибка: стек пуст перед извлечением операндов\n";
				return 1;
			}
			Token* t2 = evalStack.pop();
			if (evalStack.empty()) {
				cerr << "Ошибка: недостаточно операндов\n";
				delete t2;
				return 1;
			}
			Token* t1 = evalStack.pop();

			float n1 = t1->getNumber();
			float n2 = t2->getNumber();
			float result;

			switch (token[0]) {
			case '+': result = n1 + n2; break;
			case '-': result = n1 - n2; break;
			case '*': result = n1 * n2; break;
			case '/':
				if (n2 == 0) {
					cerr << "Ошибка: деление на ноль\n";
					delete t1; delete t2;
					return 1;
				}
				result = n1 / n2;
				break;
			default:
				cerr << "Неизвестный оператор: " << token << endl;
				delete t1; delete t2;
				return 1;
			}

			delete t1;
			delete t2;
			evalStack.push(new Number(result));
		}
		else {
			try {
				float num = stof(token);
				evalStack.push(new Number(num));
			}
			catch (...) {
				cerr << "Ошибка: недопустимое число: " << token << endl;
				return 1;
			}
		}
	}

	if (evalStack.empty()) {
		cerr << "Ошибка: выражение не содержит результата\n";
		return 1;
	}

	Token* resultToken = evalStack.pop();
	if (!evalStack.empty()) {
		cerr << "Ошибка: лишние операнды в стеке\n";
		delete resultToken;
		return 1;
	}

	cout << "Результат: " << resultToken->getNumber() << endl;
	delete resultToken;
	return 0;
}
