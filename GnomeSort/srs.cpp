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
void fill_best(int* mas, int n) {
    for (int i = 0; i < n; ++i) {
        mas[i] = i + 1;
    }
}
void fill_avg(int* mas, int n) {
    std::srand(std::time(nullptr));
    for (int i = 0; i < n; ++i) {
        mas[i] = rand() % 19 - 9;
    }
}
void GnomeSort(int* ar, int n) {
    int i = 0, tmp;
    int M = 0, C = 0, k = 1;

    while (i < n) {
        ++C; 
        std::cout << k++ << ") i = " << i << ":\n  "; print(ar, n);
        // Если 0 элемент
        // Или удовлетворяет условиям сортировки
        // То увеличиваем индекс
        if (i == 0 || ar[i - 1] <= ar[i]) { 
            ++i;
        }
        // Иначе меняем местами элементы
        // Возвращаемся на прошлый индекс
        else {
            tmp = ar[i];
            ar[i] = ar[i - 1];
            ar[i - 1] = tmp;
            M += 3;
            std::cout << " (обмен " << ar[i] << ' ' << ar[i - 1] << ")\n";
            --i;
        }
    }
    std::cout << "Количество сравнений: " << C << std::endl;
    std::cout << "Количество перемещений: " << M << std::endl;
}
int main() {
    setlocale(LC_ALL, "rus");
    int n; std::cout << "n  = "; std::cin >> n;
    int* mas = new int[n];

    fill_best(mas, n);
    std::cout << "\nИсходный массив в лучшем случае:\n\t"; print(mas, n);
    GnomeSort(mas, n);
    std::cout << "Результат работы сортировки:\n\t"; print(mas, n);

    std::cout << "\n-----------------------------------------------\n";

    fill_worst(mas, n);
    std::cout << "\nИсходный массив в худшем случае:\n\t"; print(mas, n);
    GnomeSort(mas, n);
    std::cout << "Результат работы сортировки:\n\t"; print(mas, n);

    std::cout << "\n-----------------------------------------------\n";

    fill_avg(mas, n);
    std::cout << "\nИсходный массив в среднем случае:\n\t"; print(mas, n);
    GnomeSort(mas, n);
    std::cout << "Результат работы сортировки:\n\t"; print(mas, n);

    delete[] mas;
    return 0;
}
/*
Test 1:

n  = 5

Исходный массив в лучшем случае:
        1 2 3 4 5
1) i = 0:
  1 2 3 4 5
2) i = 1:
  1 2 3 4 5
3) i = 2:
  1 2 3 4 5
4) i = 3:
  1 2 3 4 5
5) i = 4:
  1 2 3 4 5
Количество сравнений: 5
Количество перемещений: 0
Результат работы сортировки:
        1 2 3 4 5

-----------------------------------------------

Исходный массив в худшем случае:
        5 4 3 2 1
1) i = 0:
  5 4 3 2 1
2) i = 1:
  5 4 3 2 1
 (обмен 5 4)
3) i = 0:
  4 5 3 2 1
4) i = 1:
  4 5 3 2 1
5) i = 2:
  4 5 3 2 1
 (обмен 5 3)
6) i = 1:
  4 3 5 2 1
 (обмен 4 3)
7) i = 0:
  3 4 5 2 1
8) i = 1:
  3 4 5 2 1
9) i = 2:
  3 4 5 2 1
10) i = 3:
  3 4 5 2 1
 (обмен 5 2)
11) i = 2:
  3 4 2 5 1
 (обмен 4 2)
12) i = 1:
  3 2 4 5 1
 (обмен 3 2)
13) i = 0:
  2 3 4 5 1
14) i = 1:
  2 3 4 5 1
15) i = 2:
  2 3 4 5 1
16) i = 3:
  2 3 4 5 1
17) i = 4:
  2 3 4 5 1
 (обмен 5 1)
18) i = 3:
  2 3 4 1 5
 (обмен 4 1)
19) i = 2:
  2 3 1 4 5
 (обмен 3 1)
20) i = 1:
  2 1 3 4 5
 (обмен 2 1)
21) i = 0:
  1 2 3 4 5
22) i = 1:
  1 2 3 4 5
23) i = 2:
  1 2 3 4 5
24) i = 3:
  1 2 3 4 5
25) i = 4:
  1 2 3 4 5
Количество сравнений: 25
Количество перемещений: 30
Результат работы сортировки:
        1 2 3 4 5

-----------------------------------------------

Исходный массив в среднем случае:
        5 9 0 -8 7
1) i = 0:
  5 9 0 -8 7
2) i = 1:
  5 9 0 -8 7
3) i = 2:
  5 9 0 -8 7
 (обмен 9 0)
4) i = 1:
  5 0 9 -8 7
 (обмен 5 0)
5) i = 0:
  0 5 9 -8 7
6) i = 1:
  0 5 9 -8 7
7) i = 2:
  0 5 9 -8 7
8) i = 3:
  0 5 9 -8 7
 (обмен 9 -8)
9) i = 2:
  0 5 -8 9 7
 (обмен 5 -8)
10) i = 1:
  0 -8 5 9 7
 (обмен 0 -8)
11) i = 0:
  -8 0 5 9 7
12) i = 1:
  -8 0 5 9 7
13) i = 2:
  -8 0 5 9 7
14) i = 3:
  -8 0 5 9 7
15) i = 4:
  -8 0 5 9 7
 (обмен 9 7)
16) i = 3:
  -8 0 5 7 9
17) i = 4:
  -8 0 5 7 9
Количество сравнений: 17
Количество перемещений: 18
Результат работы сортировки:
        -8 0 5 7 9
*/
/*
Test 2:

n  = 20

Исходный массив в лучшем случае:
        1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
Количество сравнений: 20
Количество перемещений: 0
Результат работы сортировки:
        1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20

-----------------------------------------------

Исходный массив в худшем случае:
        20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
Количество сравнений: 400
Количество перемещений: 570
Результат работы сортировки:
        1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20

-----------------------------------------------

Исходный массив в среднем случае:
        4 7 6 4 -1 -6 -3 -2 -3 -4 8 4 9 7 9 -8 5 6 -4 4
Количество сравнений: 200
Количество перемещений: 270
Результат работы сортировки:
        -8 -6 -4 -4 -3 -3 -2 -1 4 4 4 4 5 6 6 7 7 8 9 9
*/
/*
Test 3:

n  = 50

Исходный массив в лучшем случае:
        1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50
Количество сравнений: 50
Количество перемещений: 0
Результат работы сортировки:
        1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50

-----------------------------------------------

Исходный массив в худшем случае:
        50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34 33 32 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
Количество сравнений: 2500
Количество перемещений: 3675
Результат работы сортировки:
        1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50

-----------------------------------------------

Исходный массив в среднем случае:
        9 -5 9 -7 7 1 -5 3 3 -9 -4 -9 1 -3 -6 -7 6 4 -9 9 0 -4 -1 -7 -4 -3 -9 -9 0 2 3 -2 7 -7 4 9 -8 -8 -8 -4 1 6 -4 -6 -3 3 7 -3 8 -8
Количество сравнений: 1222
Количество перемещений: 1758
Результат работы сортировки:
        -9 -9 -9 -9 -9 -8 -8 -8 -8 -7 -7 -7 -7 -6 -6 -5 -5 -4 -4 -4 -4 -4 -3 -3 -3 -3 -2 -1 0 0 1 1 1 2 3 3 3 3 4 4 6 6 7 7 7 8 9 9 9 9
*/