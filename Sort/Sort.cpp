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
