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
void InsertionSort(int*& mas, int n) {
    int i;
    int elem;

    int C = 0;
    int M = 0;

    for (int j = 1; j < n; ++j) {
        i = j - 1;
        elem = mas[j]; ++M;
        ++C;
        while ((i >= 0) && mas[i] > elem) {
            mas[i + 1] = mas[i]; ++M;
            --i;
            ++C;
        }

        mas[i + 1] = elem; ++M;
    }
    std::cout << "Количество сравнений в процессе сортировки: " << C << '\n';
    std::cout << "Количество перестановок в процессе сортировки: " << M << std::endl;
}
int bin_search(int* Arr, int n, int k, int& C, int& M) {
    int l = 0, r = n - 1;
    int sr;
    while (l <= r) {
        sr = (l + r) / 2;
        ++C; 
        if (k >= Arr[sr]) { l = sr + 1; }
        else {
            ++C;
            if (k < Arr[sr]) { r = sr - 1; }
        }
    }
    return l;
}
void bin_InsertionSort(int* Arr, int n) {
    int W, index;
    int C = 0, M = 0;
    for (int i = 1; i < n; ++i) {
        ++C;
        if (Arr[i - 1] > Arr[i]) {
            W = Arr[i]; ++M;
            index = bin_search(Arr, i, W, C, M);
            for (int j = i; j > index; --j) {
                Arr[j] = Arr[j - 1];
                ++M;
            }
            Arr[index] = W; ++M;
        }
    }
    std::cout << "Количество сравнений: " << C << std::endl;
    std::cout << "Количество перестановок: " << M << std::endl;
}
void ShellInsertionSort(int* a, int N) {
    int step = N / 2;
    int j, tmp;
    int C = 0, M = 0;

    while (step > 0) {
        for (int i = 0; i < N - step; ++i) {
            j = i;
            ++C;
            while ((j >= 0) && (a[j] > a[j + step])) {
                tmp = a[j];
                a[j] = a[j + step];
                a[j + step] = tmp;
                --j;
                M += 3;
                ++C;
            }
        }
        step /= 2;
    }
    std::cout << "Количество сравнений: " << C << std::endl;
    std::cout << "Количество перестановок: " << M << std::endl;
}

int main() {
    setlocale(LC_ALL, "rus");

    int N; std::cout << "N = "; std::cin >> N;
    
    int* mas = new int[N];

    std::cout << "\nПростые вставки:\n";
    fill_worst(mas, N);
    std::cout << "Исходный массив:\n\t"; print(mas, N);
    InsertionSort(mas, N);
    std::cout << "Отсортированный массив:\n\t"; print(mas, N);

    std::cout << "\nБинарные вставки:\n";
    fill_worst(mas, N);
    std::cout << "Исходный массив:\n\t"; print(mas, N);
    bin_InsertionSort(mas, N);
    std::cout << "Отсортированный массив:\n\t"; print(mas, N);

    std::cout << "\nШелл:\n";
    fill_worst(mas, N);
    std::cout << "Исходный массив:\n\t"; print(mas, N);
    ShellInsertionSort(mas, N);
    std::cout << "Отсортированный массив:\n\t"; print(mas, N);

    return 0;
}
/*
Test:

N = 10

Простые вставки:
Исходный массив:
        10 9 8 7 6 5 4 3 2 1
Количество сравнений в процессе сортировки: 54
Количество перестановок в процессе сортировки: 63
Отсортированный массив:
        1 2 3 4 5 6 7 8 9 10

Бинарные вставки:
Исходный массив:
        10 9 8 7 6 5 4 3 2 1
Количество сравнений: 47
Количество перестановок: 63
Отсортированный массив:
        1 2 3 4 5 6 7 8 9 10

Шелл:
Исходный массив:
        10 9 8 7 6 5 4 3 2 1
Количество сравнений: 39
Количество перестановок: 51
Отсортированный массив:
        1 2 3 4 5 6 7 8 9 10
*/
