#include <iostream>
#include <locale>

void print(int* mas, int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << mas[i] << ' ';
    }
    std::cout << std::endl;
}
void fill_best(int* mas, int n) {
    for (int i = 0; i < n; ++i) {
        mas[i] = i + 1;
    }
}
void fill_worst(int* mas, int n) {
    for (int i = 0; i < n; ++i) {
        mas[i] = n - i;
    }
}
void fill_avg(int* mas, int n) {
    std::srand(std::time(nullptr));
    for (int i = 0; i < n; ++i) {
        mas[i] = rand() % 19 - 9;
    }
}
void Merge(int* mas1, int* mas2, int* mas3, int mas1_n, int mas2_n) {
    int a = 0, b = 0, i = 0;
    while (a < mas1_n && b < mas2_n) {
        if (mas1[a] <= mas2[b]) {
            mas3[i++] = mas1[a++];
        }
        else {
            mas3[i++] = mas2[b++];
        }
    }
    while (a < mas1_n) {
        mas3[i++] = mas1[a++];
    }
    while (b < mas2_n) {
        mas3[i++] = mas2[b++];
    }
}
void MergeSort(int* mas, int n) {
    int* mas1 = new int [n];
    int* mas2 = new int [n];
    int k = 1; // Длина серий
    int i;
    int a, b; // Индексы для вспомогательных массивов
    while (k < n)  {
        std::cout << "k = " << k << std::endl;
        i = 0, a = 0, b = 0;
        // Распределяем элементы по вспомогательным массивам
        while (i < n) {
            for (int j = 0; j < k && i < n; ++j, ++i) {
                mas1[a++] = mas[i];
            }
            for (int j = 0; j < k && i < n; ++j, ++i) {
                mas2[b++] = mas[i];
            }
        }
        print(mas1, a);
        print(mas2, b);
        // Сливаем элементы обратно в исходный
        for (int j = 0; j < n / k; ++j) {
            if (a - k >= 0 && b - k >= 0) {
                Merge(mas1 + j * k, mas2 + j * k, mas + 2 * j * k, k, k);
                a -= k;
                b -= k;
            }
            else {
                Merge(mas1 + j * k, mas2 + j * k, mas + 2 * j * k, a, b);
                break;
            }
        }
        print(mas, n);
        std::cout << std::endl;
        k *= 2;
    }

    delete[] mas1;
    delete[] mas2;
}
void Sort(int* mas, int n){
    MergeSort(mas, n);
}

int main() {
    int n;
    std::cout << "n = "; std::cin >> n;
    int* mas = new int[n];

    fill_best(mas, n);
    std::cout << "\nИсходный массив в лучшем случае:\n\t"; print(mas, n);
    Sort(mas, n);
    std::cout << "Результат работы сортировки:\n\t"; print(mas, n);

    fill_worst(mas, n);
    std::cout << "\nИсходный массив в худшем случае:\n\t"; print(mas, n);
    Sort(mas, n);
    std::cout << "Результат работы сортировки:\n\t"; print(mas, n);

    fill_avg(mas, n);
    std::cout << "\nИсходный массив в среднем случае:\n\t"; print(mas, n);
    Sort(mas, n);
    std::cout << "Результат работы сортировки:\n\t"; print(mas, n);

    delete[] mas;
    return 0;
}
