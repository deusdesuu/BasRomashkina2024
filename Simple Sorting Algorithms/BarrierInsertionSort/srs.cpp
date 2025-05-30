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
// Сортировка простыми вставками
// С барьерным элементом
/* T = O(n^2)   M = O(n)
 * Сохраняем рассматриваемый элемент массива
 * В 0 позиции, таким образом при прохождении
 * Массива мы не уйдем за его пределы
 *
 * Пока элемент справа больше элемента слева
 * Двигаем элементы
 * Иначе вставляем элемент из 0 позиции
 * На место правого
 */
void BarrierInsertionSort(int* mas, int N) {
    // Создаем копию массива
    // В котором будет на 1 элемент больше
    int* A = new int[N + 1];
    // Копируем элементы из исходного массива
    for (int i = 0; i < N; ++i) {
        A[i + 1] = mas[i];
    }
    // A1
    int j;
    for (int i = 1; i <= N; ++i) {  
        A[0] = A[i];
        //std::cout << "\nПроход " << i << ":\n"; print(A, N + 1);
        j = i - 1;
        // A2
        while (A[j] > A[0]) {
            A[j + 1] = A[j];
            --j;
            //print(A, N + 1);
        }
        A[j + 1] = A[0];
        //print(A, N + 1);
    }
    // Копируем отсортированную часть обратно
    // В исходный массив
    for (int i = 0; i < N; ++i) {
        mas[i] = A[i + 1];
    }
    delete[] A;
}

int main() {
    setlocale(LC_ALL, "rus");

    int N; std::cout << "N = "; std::cin >> N;
    
    int* mas = new int[N];

    fill_worst(mas, N);

    std::cout << "Исходный массив:\n\t"; print(mas, N);
    
    BarrierInsertionSort(mas, N);

    std::cout << "Отсортированный массив:\n\t"; print(mas, N);

    return 0;
}
/*
Test:
N = 8
Исходный массив:
        8 7 6 5 4 3 2 1
Отсортированный массив:
        1 2 3 4 5 6 7 8
*/
/*
Разбор:
Исходный массив:
        8 7 6 5 4 3 2 1

Создаем массив с барьерным:
? 8 7 6 5 4 3 2 1

Проход 1:
8 8 7 6 5 4 3 2 1

Проход 2:
7 8 7 6 5 4 3 2 1
7 8 8 6 5 4 3 2 1
7 7 8 6 5 4 3 2 1

Проход 3:
6 7 8 6 5 4 3 2 1
6 7 8 8 5 4 3 2 1
6 7 7 8 5 4 3 2 1
6 6 7 8 5 4 3 2 1

Проход 4:
5 6 7 8 5 4 3 2 1
5 6 7 8 8 4 3 2 1
5 6 7 7 8 4 3 2 1
5 6 6 7 8 4 3 2 1
5 5 6 7 8 4 3 2 1

Проход 5:
4 5 6 7 8 4 3 2 1
4 5 6 7 8 8 3 2 1
4 5 6 7 7 8 3 2 1
4 5 6 6 7 8 3 2 1
4 5 5 6 7 8 3 2 1
4 4 5 6 7 8 3 2 1

Проход 6:
3 4 5 6 7 8 3 2 1
3 4 5 6 7 8 8 2 1
3 4 5 6 7 7 8 2 1
3 4 5 6 6 7 8 2 1
3 4 5 5 6 7 8 2 1
3 4 4 5 6 7 8 2 1
3 3 4 5 6 7 8 2 1

Проход 7:
2 3 4 5 6 7 8 2 1
2 3 4 5 6 7 8 8 1
2 3 4 5 6 7 7 8 1
2 3 4 5 6 6 7 8 1
2 3 4 5 5 6 7 8 1
2 3 4 4 5 6 7 8 1
2 3 3 4 5 6 7 8 1
2 2 3 4 5 6 7 8 1

Проход 8:
1 2 3 4 5 6 7 8 1
1 2 3 4 5 6 7 8 8
1 2 3 4 5 6 7 7 8
1 2 3 4 5 6 6 7 8
1 2 3 4 5 5 6 7 8
1 2 3 4 4 5 6 7 8
1 2 3 3 4 5 6 7 8
1 2 2 3 4 5 6 7 8
1 1 2 3 4 5 6 7 8

Результат работы сортировки:
    1 2 3 4 5 6 7 8
*/
