// Мячин Валентин БАС 2
#include <iostream>
#include <locale>


void print(int* mas, int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << mas[i] << ' ';
    }
    std::cout << std::endl;
}
void fill_worst(int* mas, int n) {
    for (int i = 0; i < n; ++i) {
        mas[i] = n - i;
    }
}
void fill_best(int* mas, int n) {
    for (int i = 0; i < n; ++i) {
        mas[i] = i + 1;
    }
}
void fill_avg(int* mas, int n) {
    std::srand(std::time(nullptr));
    for (int i = 0; i < n; ++i) {
        mas[i] = rand() % 10;
    }
}
void fill_console(int* mas, int n) {
    for (int i = 0; i < n; ++i) {
        std::cin >> mas[i];
    }
}
void CountSort(int* A, int* B, int n) {
    // Находим максимум
    int max = A[0];
    for (int i = 1; i < n; ++i) { if (A[i] > max) { max = A[i]; } }
    // Инициализируем С
    int* C = new int[max + 1];
    for (int i = 0; i <= max; ++i) C[i] = 0;
    // Заполняем С
    for (int i = 0; i < n; ++i) {
        ++C[A[i]];
    }
    // C[i] = кол-ву элементов не превосходящих i
    for (int i = 1; i <= n; ++i) {
        C[i] += C[i - 1];
    }
    // Тут происходит магия
    for (int i = n - 1; i >= 0; --i) {
        B[C[A[i]] - 1] = A[i]; 
        --C[A[i]]; // Ничего не делает?
    }
}

int main() {
    setlocale(LC_ALL, "rus");

    int n; std::cout << "n = "; std::cin >> n;
    int* mas = new int[n];
    int* mas2 = new int[n];

    fill_best(mas, n);
    std::cout << "\nИсходный массив в лучшем случае:\n\t"; print(mas, n);
    CountSort(mas, mas2, n);
    std::cout << "Результат работы сортировки:\n\t"; print(mas2, n);

    std::cout << "------------------------------------\n";

    fill_worst(mas, n);
    std::cout << "\nИсходный массив в худшем случае:\n\t"; print(mas, n);
    CountSort(mas, mas2, n);
    std::cout << "Результат работы сортировки:\n\t"; print(mas2, n);

    std::cout << "------------------------------------\n";

    fill_avg(mas, n);
    std::cout << "\nИсходный массив в среднем случае:\n\t"; print(mas, n);
    CountSort(mas, mas2, n);
    std::cout << "Результат работы сортировки:\n\t"; print(mas2, n);

    delete[] mas;
    delete[] mas2;
    return 0;
}
/*
Test:

n = 10

Исходный массив в лучшем случае:
        1 2 3 4 5 6 7 8 9 10
Результат работы сортировки:
        1 2 3 4 5 6 7 8 9 10
------------------------------------

Исходный массив в худшем случае:
        10 9 8 7 6 5 4 3 2 1
Результат работы сортировки:
        1 2 3 4 5 6 7 8 9 10
------------------------------------

Исходный массив в среднем случае:
        0 2 0 2 0 3 0 9 9 1
Результат работы сортировки:
        0 0 0 0 1 2 2 3 9 9
*/
