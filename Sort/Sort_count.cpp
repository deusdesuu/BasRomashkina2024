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
// На больших N наблюдается значительный выйгрыш
// В количестве сравнений и перестановок
// В сравнении с обычным InsertionSort
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
// На больших N наблюдается выйгрыш
// В количестве перестановок
// В сравнении с обычным InsertionSort
void BarrierInsertionSort(int* mas, int N) {
    int* A = new int[N + 1];
    for (int i = 0; i < N; ++i) {
        A[i + 1] = mas[i];
    }
    int C = 0, M = 0;
    M = 2 * N; // копирование массива в 2 стороны
    int j;
    for (int i = 1; i <= N; ++i) {  
        A[0] = A[i]; ++M;
        j = i - 1;
        ++C;
        while (A[j] > A[0]) {
            A[j + 1] = A[j];
            --j;
            ++C;
        }
        A[j + 1] = A[0]; ++M;
    }
    for (int i = 0; i < N; ++i) {
        mas[i] = A[i + 1];
    }
    delete[] A;
    std::cout << "Количество сравнений: " << C << std::endl;
    std::cout << "Количество перестановок: " << M << std::endl;
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
// На больших N наблюдается выйгрыш
// В количестве сравнений
// В сравнении с обычным InsertionSort
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
void ShakerSort(int* M, int num) {
    int left = 0;   // левая граница
    int right = num - 1;// правая граница
    int j, t, k = num - 1;//k-фиксирование индекса посл-его обмена
    int m = 0, c = 0; // m - кол-во перестановок, с - кол-во сравнений

    do {
        for (j = left; j < right; j++) {
            ++c;
            if (M[j] > M[j + 1]) {
                t = M[j];
                M[j] = M[j + 1];
                M[j + 1] = t;
                k = j;
                m += 3;
            }
        }
        right = k;
        for (j = right; j > left; j--) {
            ++c;
            if (M[j - 1] > M[j]) {
                t = M[j];
                M[j] = M[j - 1];
                M[j - 1] = t;
                k = j;
                m+=3;
            }
        }
        left = k;
    } while (left < right);
    std::cout << "Количество сравнений: " << c << std::endl;
    std::cout << "Количество перестановок: " << m << std::endl;
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
