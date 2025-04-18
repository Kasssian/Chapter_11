#include <iostream>
using namespace std;

class linklist {
private:
    struct Link {
        int data;
        Link* next;
        Link(int d) : data(d), next(nullptr) {}
    };
    Link* first;
public:
    linklist() : first(nullptr) {}
    ~linklist() { /* ������� */ }
    linklist(const linklist& other) : first(nullptr) {
        Link* current = other.first;
        Link* last = nullptr;
        while (current) {
            Link* newLink = new Link(current->data);
            if (!first) first = newLink;
            else last->next = newLink;
            last = newLink;
            current = current->next;
        }
    }
    linklist& operator=(const linklist& other) {
        if (this != &other) {
            // ������� �������� ������
            while (first) {
                Link* temp = first;
                first = first->next;
                delete temp;
            }
            // �����������
            Link* current = other.first;
            Link* last = nullptr;
            while (current) {
                Link* newLink = new Link(current->data);
                if (!first) first = newLink;
                else last->next = newLink;
                last = newLink;
                current = current->next;
            }
        }
        return *this;
    }
};

int main() {
    linklist* list1 = new linklist();
    
    *list1 = linklist();
    linklist* list2 = new linklist(*list1);
    delete list1;

    // ������ list2 ��-�������� ��������, ������ ��� ����� � ��������

    delete list2;
    return 0;
}
