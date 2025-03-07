// Мячин Валентин БАС2
#include <iostream>
#include <locale>
#include <random>


struct Node {
    int value;
    Node* next = nullptr;
    Node* prev = nullptr;
};
void print(Node*& head, Node*& tail);
void push_back(Node*& head, Node*& tail, int);
void push_front(Node*& head, Node*& tail, int);
void pop_front(Node*& head, Node*& tail);

int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(0));

    Node* head = nullptr;
    Node* tail = nullptr;

    int n;
    std::cout << "n = "; std::cin >> n;

    int i = 0;
    int value;
    for (;(i < n) && (i < 5); ++i) {
        value = rand() % 99 - 50;
        push_front(head, tail, value);
        std::cout << "(добавили " << value << ") "; print(head, tail);
    }
    std::cout << "\nСписок после добавления первых 5 (или меньше) элементов в начало:\n\t";
    print(head, tail);
    for(; (i < n); ++i) {
        value = rand() % 99 - 50;
        push_back(head, tail, value);
        std::cout << "(добавили " << value << ") "; print(head, tail);
    }
    std::cout << "\nСписок после добавления оставшихся элементов в конец списка:\n\t";
    print(head, tail);

    int k;
    std::cout << "\nk = "; std::cin >> k;
    for (i = 0; i < k; ++i) {
        pop_front(head, tail);
        print(head, tail);
    }
    std::cout << "Список после удаления " << k << " элементов:\n\t"; print(head, tail);

    return 0;
}

void print(Node*& head, Node*& tail) {
    Node* current = head;
    while (current != nullptr) {
        std::cout << (*current).value << ' ';
        current = (*current).next;
    }
    std::cout << std::endl;
}
void push_back(Node*& head, Node*& tail, int value) {
    Node* new_node = new Node;
    (*new_node).value = value;
    if (head == nullptr) {
        head = new_node;
        tail = new_node;
    }
    else {
        (*new_node).prev = tail;
        (*tail).next = new_node;
    }
    tail = new_node;
}
void push_front(Node*& head, Node*& tail, int value) {

    Node* new_node = new Node;
    (*new_node).value = value;
    if (head == nullptr) {
        head = new_node;
        tail = new_node;
    }
    else {
        (*new_node).next = head;
        (*head).prev = new_node;
        head = new_node;
    }
}
void pop_front(Node*& head, Node*& tail) {
    if (head != nullptr) {
        Node* cpy = head;
        head = (*head).next;
        (*head).prev = nullptr;
        delete cpy;
        cpy = nullptr;
    }
}
