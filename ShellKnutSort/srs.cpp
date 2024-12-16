// Мячин Валентин БАС2
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
void ShellInsertionSort3(int* a, int N) {
    int h = 1;
    int j, tmp;
    int M = 0, C = 0;

    while (3 * h < N) {
        for (int i = 0; i < N - h; ++i) {
            j = i;
            ++C;
            while ((j >= 0) && (a[j] > a[j + h])) {
                tmp = a[j];
                a[j] = a[j + h];
                a[j + h] = tmp;
                --j;
                M += 3;
                ++C;
            }
        }
        h = 3 * h + 1;
    }
    std::cout << "Количество сравнений: " << C << std::endl;
    std::cout << "Количество перестановок: " << M << std::endl;
}
void ShellInsertionSort2(int* a, int N) {
    int h = 1;
    int j, tmp;
    int M = 0, C = 0;

    while (2 * h < N) {
        for (int i = 0; i < N - h; ++i) {
            j = i;
            ++C;
            while ((j >= 0) && (a[j] > a[j + h])) {
                tmp = a[j];
                a[j] = a[j + h];
                a[j + h] = tmp;
                --j;
                M += 3;
                ++C;
            }
        }
        h = 2 * h + 1;
    }
    std::cout << "Количество сравнений: " << C << std::endl;
    std::cout << "Количество перестановок: " << M << std::endl;
}

void ShellInsertionSortRoot(int* a, int N) {
    int h = pow((16 * N / acos(-1)), 1.0 / 3);
    int j, tmp;
    int M = 0, C = 0;

    while (N > 0) {
        for (int i = 0; i < N - h; ++i) {
            j = i;
            ++C;
            while ((j >= 0) && (a[j] > a[j + h])) {
                tmp = a[j];
                a[j] = a[j + h];
                a[j + h] = tmp;
                --j;
                M += 3;
                ++C;
            }
        }
        h /= 2;
    }
    std::cout << "Количество сравнений: " << C << std::endl;
    std::cout << "Количество перестановок: " << M << std::endl;
}

int main() {
    setlocale(LC_ALL, "rus");

    int N; std::cout << "N = "; std::cin >> N;
    
    int* mas = new int[N];

    std::cout << "\nФормула приращений h: hk = 3 * hk-1 + 1\n";
    fill_worst(mas, N);
    std::cout << "Исходный массив:\n\t"; print(mas, N);
    ShellInsertionSort3(mas, N);
    std::cout << "Отсортированный массив:\n\t"; print(mas, N);

    std::cout << "\nФормула приращений h: hk = 2 * hk-1 + 1\n";
    fill_worst(mas, N);
    std::cout << "Исходный массив:\n\t"; print(mas, N);
    ShellInsertionSort2(mas, N);
    std::cout << "Отсортированный массив:\n\t"; print(mas, N);

    std::cout << "\nФормула приращений h: h = (16 * N / pi) * (1/3)\n";
    fill_worst(mas, N);
    std::cout << "Исходный массив:\n\t"; print(mas, N);
    ShellInsertionSort2(mas, N);
    std::cout << "Отсортированный массив:\n\t"; print(mas, N);
    return 0;
}
/*
Test:

N = 10

Формула приращений h: hk = 3 * hk-1 + 1
Исходный массив:
        10 9 8 7 6 5 4 3 2 1
Количество сравнений: 54
Количество перестановок: 135
Отсортированный массив:
        1 2 3 4 5 6 7 8 9 10

Формула приращений h: hk = 2 * hk-1 + 1
Исходный массив:
        10 9 8 7 6 5 4 3 2 1
Количество сравнений: 61
Количество перестановок: 135
Отсортированный массив:
        1 2 3 4 5 6 7 8 9 10

Формула приращений h: h = (16 * N / pi) * (1/3)
Исходный массив:
        10 9 8 7 6 5 4 3 2 1
Количество сравнений: 61
Количество перестановок: 135
Отсортированный массив:
        1 2 3 4 5 6 7 8 9 10
*/
