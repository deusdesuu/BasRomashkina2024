// Мячин Валентин БАС2
#include <iostream>
#include <locale>
#include <random>


struct SL {
    int value;
    SL* next = nullptr;
};
void print(SL* node) {
    SL* current = node;
    std::cout << "Список L: ";
    while (current != nullptr) {
        std::cout << (*current).value << ' ';
        current = (*current).next;
    }
    std::cout << std::endl;
}
void add_end(SL* node, int value) {
    SL* current = node;
    while ((*current).next != nullptr) {
        current = (*current).next;
    }
    SL* new_node = new(SL);
    (*new_node).value = value;
    (*current).next = new_node;
}
struct SP {
    int value;
    SP* next = nullptr;
};
void add_start(SP* node, int value) {
    SP* new_node = new(SP);
    (*new_node).value = value;
    (*new_node).next = (*node).next;
    (*node).next = new_node;
}
void print(SP* node) {
    SP* current = (*node).next;
    while (current != nullptr) {
        std::cout << (*current).value << ' ';
        current = (*current).next;
    }
    std::cout << std::endl;
}
int sum(SP* node) {
    SP* current = (*node).next;
    int result = 0;
    while (current != nullptr) {
        result += (*current).value;
        current = (*current).next;
    }
    return result;
}
void round(SP* node, int value) {
    SP* current = (*node).next;
    while(current != nullptr && (*current).value != value) {
        current = (*current).next;
    }
    if (current == nullptr) {
        std::cout << "Такого значения нет в списке!" << std::endl;
    }
    else {
        SP* node1 = new(SP);
        SP* node2 = new(SP);
        (*node2).next = (*current).next;
        (*node1).next = node2;
        (*current).next = node1;

        (*node1).value = value;
        (*current).value = -500;
        (*node2).value = -500;
    }
}
int main() {
    srand(time(0));
    setlocale(LC_ALL, "rus");

    int value;
    int n;

    SL* L = new(SL);
    SP* M = new(SP);

    std::cout << "n = "; std::cin >> n;
    // Заполнение L
    std::cout << "\nВведите элементы списка L:\n";
    std::cin >> value;
    (*L).value = value;
    for (int i = 1; i < n; ++i) {
        std::cin >> value;
        add_end(L, value);
    }
    print(L);
    // Заполнение M
    std::cout << "\nВведите элементы списка M:\n";
    for (int i = 0; i < n; ++i) {
        std::cin >> value;
        add_start(M, value);
    }
    std::cout << "Список M: "; print(M);
    // Заполнение Q
    SP* Q = new(SP);
    SP* current_M = (*M).next;
    SL* current_L = L;
    for (int i = 0; i < n; ++i) {
        add_start(Q, (*current_M).value + (*current_L).value);
        current_M = (*current_M).next;
        current_L = (*current_L).next;
    }
    std::cout << "\nСписок Q: "; print(Q);

    (*Q).value = sum(Q);
    std::cout << "Сумма элементов списка Q: " << (*Q).value << std::endl;

    std::cout << "\nВыберите значение элемента, с двух сторон которого вы хотите вставить -500:\n";
    std::cin >> value;
    round(Q, value);
    std::cout << "\nСписок Q: "; print(Q);
    return 0;
}
/*
Test 1:
n = 5

Введите элементы списка L:
1 2 3 4 5
Список L: 1 2 3 4 5

Введите элементы списка M:
5 4 3 2 1
Список M: 1 2 3 4 5

Список Q: 10 8 6 4 2
Сумма элементов списка Q: 30

Выберите значение элемента, с двух сторон которого вы хотите вставить -500:
10

Список Q: -500 10 -500 8 6 4 2
 */
