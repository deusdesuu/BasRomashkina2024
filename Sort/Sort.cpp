/* Сортировка простым обменом
 * T = O(n^2) M = O(n)
 * Проходим массив n - 1 раз:
 * На каждый проход находим максимальный элемент
 * И сдвигаем его в конец массива
 */
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
/* Сортировка простым выбором
 * T = O(n ^ 2) M = O(n)
 * Проходим массив n - 1 раз
 * На каждый проход находим минимальный элемент
 * Меняем местами i и минимальный элемент
 */
void SelectionSort(int* mas, int n) {
    int min;
    int min_i;

    for (int i = 0; i < n - 1; ++i) {
        min = mas[i];
        min_i = i;
        for (int j = i + 1; j < n; ++j) {
            if (mas[j] < min) {
                min = mas[j];
                min_i = j;
            }
        }
        mas[min_i] = mas[i];
        mas[i] = min;
    }
}
/* Сортировка простыми вставками
 * T = O(n ^ 2) M = O(n)
 * Проходим массив n - 1 раз
 * Будем считать что первые j элементов отсортированы
 * Берем j-ый элемент массива
 * Пока элемент слева от j-ого больше него
 * Сдвигаем массив вправо
 * В конце вставляем j-ый элемент
 */
void InsertionSort(int* mas, int n) {
    int i;
    int elem;

    for (int j = 1; j < n; ++j) {
        i = j - 1;
        elem = mas[j];
        while ((i >= 0) && (mas[i] > elem)) {
            mas[i + 1] = mas[i];
            --i;
        }
        mas[i + 1] = elem;
    }
}
/* Сортировка бинарными вставками
 * То же что и в InsertionSort
 * Но позицию, в которую мы будем вставлять
 * Новый элемент
 * Мы ищем бин поиском
 */
int bin_search(int* Arr, int n, int k) {
    int l = 0, r = n - 1;
    int sr;
    while (l <= r) {
        sr = (l + r) / 2;
        if (k == Arr[sr]) { l = sr; break; }
        if (k < Arr[sr]) { l = sr + 1; }
        if (k > Arr[sr]) { r = sr - 1; }
    }
    return l;
}

void bin_InsertionSort(int* Arr, int n) {
    int W, index;
    for (int i = 1; i < n; ++i) {
        if (Arr[i - 1] < Arr[i]) {
            W = Arr[i];
            index = bin_search(Arr, i, W);
            for (int j = i; j > index; --j) {
                Arr[j] = Arr[j - 1];
            }
            Arr[index] = W;
        }
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
void BarrierInsertionSort(int* mas, int n) {
    // Создаем копию массива
    // В котором будет на 1 элемент больше
    int* A = new int[n + 1];
    // Копируем элементы из исходного массива
    for (int i = 0; i < n; ++i) {
        A[i + 1] = mas[i];
    }
    // A1
    int j;
    for (int i = 1; i <= n; ++i) {
        A[0] = A[i];
        j = i - 1;
        // A2
        while (A[j] > A[0]) {
            A[j + 1] = A[j];
            --j;
        }
        A[j + 1] = A[0];
    }
    // Копируем отсортированную часть обратно
    // В исходный массив
    for (int i = 0; i < n; ++i) {
        mas[i] = A[i + 1];
    }
    delete[] A;
}
//Сортировка вставками (Шелла)
void ShellInsertionSort(int* a, int N) {
    int step = N / 2;
    int j, tmp;

    while (step > 0) {
        for (int i = 0; i < N - step; ++i) {
            j = i;
            while ((j >= 0) && (a[j] > a[j + step])) {
                tmp = a[j];
                a[j] = a[j + step];
                a[j + step] = tmp;
                --j;
            }
        }
        step /= 2;
    }
}
