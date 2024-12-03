// Мячин Валентин БАС2 вариант 9
#include <iostream>
#include <locale>
#include <fstream>


// Сортировка простым обменом
void BubbleSort(int* mas, int n) {
    int tmp;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < n - i; ++j) {
            if (mas[j] > mas[j + 1]) {
                tmp = mas[j];
                mas[j] = mas[j + 1];
                mas[j + 1] = tmp;
            }
        }
    }
}
// Сортировка простыми вставками
void InsertionSort(int* mas, int n) {
    int i;
    int elem;

    for (int j = 1; j < n; ++j) {
        i = j - 1;
        elem = mas[j];
        // Проверяем что mas[i] < elem
        // Для сортировки по возрастанию
        while ((i >= 0) && mas[i] < elem) {
            mas[i + 1] = mas[i];
            --i;
        }

        mas[i + 1] = elem;
    }
}

void print(int* mas, int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << mas[i] << ' ';
    }
    std::cout << std::endl;
}

void fill_random(int* mas, int n) {
    for (int i = 0; i < n; ++i) {
        mas[i] = rand() % 19 - 9;
    }
}

void fill_console(int* mas, int n) {
    for (int i = 0; i < n; ++i) {
        std::cin >> mas[i];
    }
}

void fill_file(int* mas, int n, const char* file) {
    std::ifstream stream;
    stream.open(file);

    if (stream.is_open()) {
        for (int i = 0; i < n; ++i) {
            stream >> mas[i];
        }
        stream.close();
    }
}

void output_file(int* mas, int n, const char* file) {
    std::ofstream stream;
    stream.open(file);

    if (stream.is_open()) {
        for (int i = 0; i < n; ++i) {
            stream << mas[i] << ' ';
        }
        stream << std::endl;
    }

    stream.close();
}

void sort_z1(int* mas, int n) {
    // Находим индексы первого минимального
    // И максимального элементов
    int min = mas[0]; int min_i = 0;
    int max = mas[0]; int max_i = 0;
    for (int i = 1; i < n; ++i) {
        if (mas[i] < min) { min = mas[i]; min_i = i; }
        if (mas[i] > max) { max = mas[i]; max_i = i; }
    }
    // Сортируем max_i - min_i элементов в массива
    // В функцию сортировки передаем указатель на 
    // Элемент после min_i'ого элемента массива
    BubbleSort(mas + min_i + 1, max_i - min_i);
}

int main() {
    setlocale(LC_ALL, "rus");
    std::srand(std::time(nullptr));

    int n; std::cout << "n = "; std::cin >> n;
    int* z1 = new int[n];
    int* z2 = new int[n];
    int* z3 = new int[n];

    const char* f1 = "F1.txt";
    const char* f2 = "F2.txt";
    const char* output = "output.txt";

    // Заполнение из файла
    fill_file(z1, n, "F1.txt");
    fill_file(z2, n, "F2.txt");
    /*
    Резервное заполнение из консоли (т.к. я не понимаю Clion)
    std::cout << "Введите элементы Z1:\n\t"; fill_console(z1, n);
    std::cout << "Введите элементы Z2:\n\t"; fill_console(z2, n);
    */
    std::cout << "---------------------------------------------\n";
    std::cout << "Исходный массив Z1:\n\t"; print(z1, n);
    sort_z1(z1, n);
    std::cout << "Массив Z1 после сортировки:\n\t"; print(z1, n);
    
    std::cout << "---------------------------------------------\n";
    std::cout << "Исходный массив Z2\n\t"; print(z2, n);
    InsertionSort(z2, n);
    std::cout << "Массив Z2 после сортировки:\n\t"; print(z2, n);

    // Заполнение нового массива z3
    for (int i = 0; i < n; ++i) {
        z3[i] = 2 * (z1[i] - z2[i]);
    }
    std::cout << "---------------------------------------------\n";
    std::cout << "Новый массив Z3:\n\t"; print(z3, n);
    // Запись Z3 в файл
    output_file(z3, n, output);

    delete[] z1;
    delete[] z2;
    delete[] z3;
    return 0;
}
/*
Input:
22
-6 1 -5 -999 9 8 7 6 5 4 3 2 1 0 -5 999 -9 6 -7 -8 4 -4
9 -7 -6 -9 3 -6 -2 -6 -6 -1 -7 -5 -5 1 4 -1 -5 8 9 3 -7 -8
*/
/*
Test:

n = 22
---------------------------------------------
Исходный массив Z1:
        -6 1 -5 -999 9 8 7 6 5 4 3 2 1 0 -5 999 -9 6 -7 -8 4 -4
Массив Z1 после сортировки:
        -6 1 -5 -999 -5 0 1 2 3 4 5 6 7 8 9 999 -9 6 -7 -8 4 -4
---------------------------------------------
Исходный массив Z2
        9 -7 -6 -9 3 -6 -2 -6 -6 -1 -7 -5 -5 1 4 -1 -5 8 9 3 -7 -8
Массив Z2 после сортировки:
        9 9 8 4 3 3 1 -1 -1 -2 -5 -5 -5 -6 -6 -6 -6 -7 -7 -7 -8 -9
---------------------------------------------
Новый массив Z3:
        -30 -16 -26 -2006 -16 -6 0 6 8 12 20 22 24 28 30 2010 -6 26 0 -2 24 10
*/
