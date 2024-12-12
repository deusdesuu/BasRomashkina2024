// Мячин Валентин БАС2
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

void SelectionSort(int*& mas, int n) {
    int min;
    int min_i;

    int C = 0;
    int M = 0;

    std::cout << "Процесс сортировки массива:\n";
    for (int i = 0; i < n - 1; ++i) {
        min = mas[i]; // 1st swap
        min_i = i;
        for (int j = i + 1; j < n; ++j) {
            if (mas[j] < min) {
                min = mas[j];
                ++M;
                min_i = j;
            }
            ++C;
        }
        mas[min_i] = mas[i]; // 2nd swap
        mas[i] = min; // 3rd swap

        std::cout << "Шаг " << i + 1 << ": ";
        print(mas, n);

        M += 3;
    }
    std::cout << "Количество сравнений в процессе сортировки: " << C << '\n';
    std::cout << "Количество перестановок в процессе сортировки: " << M << std::endl;
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
        std::cout << "Шаг " << j << ": ";
        print(mas, n);
    }
    std::cout << "Количество сравнений в процессе сортировки: " << C << '\n';
    std::cout << "Количество перестановок в процессе сортировки: " << M << std::endl;
}

void ShellInsertionSort(int* a, int N) {
    int step = N / 2;
    int j, tmp;
    int C = 0, M = 0;

    while (step > 0) {
        for (int i = 0; i < N - step; ++i) {
            j = i;
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

void Sort(int*& mas, int n) {
    InsertionSort(mas, n);
}

int main() {
    setlocale(LC_ALL, "rus");

    int n;
    std::cout << "n = "; std::cin >> n;
    int* mas = new int [n];

    std::cout << "Исходный массив в лучшем случае:\n\t";
    fill_best(mas, n);
    print(mas, n);
    Sort(mas, n);
    std::cout << "Результат работы сортировки:\n\t";
    print(mas, n);

    std::cout << "\nИсходный массив в худшем случае:\n\t";
    fill_worst(mas, n);
    print(mas, n);
    Sort(mas, n);
    std::cout << "Результат работы сортировки:\n\t";
    print(mas, n);

    std::cout << "\nИсходный массив в среднем случае:\n\t";
    fill_avg(mas, n);
    print(mas, n);
    Sort(mas, n);
    std::cout << "Результат работы сортировки:\n\t";
    print(mas, n);

    delete[] mas;
    return 0;
}
