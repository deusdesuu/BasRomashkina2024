// Мячин Валентин БАС 2
#include <iostream>
#include <locale>
#include <ctime>


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
        mas[i] = i  + 1;
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
void CountSortUp(int* A, int n) {
    // Находим максимум
    int max = A[0];
    for (int i = 1; i < n; ++i) { if (A[i] > max) { max = A[i]; }}
    // Инициализируем С
    int* C = new int [max + 1];
    for (int i = 0; i <= max; ++i) C[i] = 0;
    // Заполняем С
    for (int i = 0; i < n; ++i) {
        ++C[A[i]];
    }
    // Перезапись массива А
    int pos = 0;
    for (int i = 0; i < max + 1; ++i) {
        for (int j = 0; j < C[i]; ++j) {
            A[pos] = i;
            ++pos;
        }
    }
}
void CountSortDown(int* A, int n) {
    // Находим максимум
    int max = A[0];
    for (int i = 1; i < n; ++i) { if (A[i] > max) { max = A[i]; }}
    // Инициализируем С
    int* C = new int [max + 1];
    for (int i = 0; i <= max; ++i) C[i] = 0;
    // Заполняем С
    for (int i = 0; i < n; ++i) {
        ++C[A[i]];
    }
    // Перезапись массива А
    int pos = n - 1;
    for (int i = 0; (i < max + 1) && (pos >= 0); ++i) {

        for (int j = 0; j < C[i]; ++j) {
            A[pos] = i;
            --pos;
        }
    }
}
void Sort(int* mas, int n) {
    CountSortUp(mas, n);
}
int main() {
    setlocale(LC_ALL, "rus");

    int n; std::cout << "n = "; std::cin >> n;
    int* mas = new int [n];

    fill_best(mas, n);
    std::cout << "\nИсходный массив в лучшем случае:\n\t"; print(mas, n);
    Sort(mas, n);
    std::cout << "Результат работы сортировки:\n\t"; print(mas, n);

    std::cout << "------------------------------------\n";

    fill_worst(mas, n);
    std::cout << "\nИсходный массив в худшем случае:\n\t"; print(mas, n);
    Sort(mas, n);
    std::cout << "Результат работы сортировки:\n\t"; print(mas, n);

    std::cout << "------------------------------------\n";

    fill_avg(mas, n);
    std::cout << "\nИсходный массив в среднем случае:\n\t"; print(mas, n);
    Sort(mas, n);
    std::cout << "Результат работы сортировки:\n\t"; print(mas, n);

    delete[] mas;
    return 0;
}
/*
Test:

n = 10

Исходный массив в лучшем случае:
	1 2 3 4 5 6 7 8 9 10
Результат работы сортировки:
	10 9 8 7 6 5 4 3 2 1
------------------------------------

Исходный массив в худшем случае:
	10 9 8 7 6 5 4 3 2 1
Результат работы сортировки:
	10 9 8 7 6 5 4 3 2 1
------------------------------------

Исходный массив в среднем случае:
	7 8 2 8 6 6 1 5 7 6
Результат работы сортировки:
	8 8 7 7 6 6 6 5 2 1
 */
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
	3 3 8 9 6 0 7 3 1 9
Результат работы сортировки:
	0 1 3 3 3 6 7 8 9 9
 */
