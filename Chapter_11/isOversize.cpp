#include <iostream>
using namespace std;

class publication {
public:
	virtual bool isOversize() const = 0; // Чисто виртуальная функция
	virtual ~publication() {} // Виртуальный деструктор
};

class book : public publication {
private:
	int pages;
public:
	book(int p) : pages(p) {}
	bool isOversize() const override { return pages > 800; }
};

class tape : public publication {
private:
	float playTime;
public:
	tape(float t) : playTime(t) {}
	bool isOversize() const override { return playTime > 90; }
};

int main() {
	setlocale(LC_ALL, "Russian");
	publication* pub1 = new book(700);
	publication* pub2 = new tape(95);

	if (pub1->isOversize()) {
		cout << "Превышение размера!" << endl;
	}
	else {
		cout << "Книга не превышает размер." << endl;
	}

	if (pub2->isOversize()) {
		cout << "Превышение размера!" << endl;
	}
	else {
		cout << "Кассета в пределах нормы." << endl;
	}

	delete pub1;
	delete pub2;
	return 0;
}
