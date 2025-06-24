// Мячин Валентин БАС-2024-2
#include <iostream>
#include <locale>


void print(int mas[], int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << mas[i] << ' ';
    }
    std::cout << std::endl;
}
void print_indexes(int mas[], int n) {
    int cur = 5;
    while (cur > 0) {
        std::cout << cur << " <- ";
        cur = mas[cur - 1];
    }
    std::cout << '1' << std::endl;
}
int main() {
    setlocale(LC_ALL, "rus");

    const int n = 5;
    int a[n][n];
    int d[n];
    int v[n];
    int prev[n];
    int temp;
    int minindex, min;


    for (int i = 0; i < n; ++i) {
        std::cout << '\t' << i + 1;
    }
    std::cout << '\n';
    for (int i = 0; i < n; ++i) {
        std::cout << i + 1 << ')';
        for (int j = 0; j < n; ++j) {
            std::cout << '\t';
            std::cin >> a[i][j];
        }
        std::cout << '\n';
    }
    // init d with inf
    for (int i = 0; i < n; ++i) {
        d[i] = 10000;
    }
    for (int i = 0; i < n; ++i) {
        v[i] = 1;
    }
    // начальная вершина
    int vert = 0;
    for (int i = 0; i < n; ++i) {
        if (a[vert][i] > 0) {
            d[i] = a[vert][i];
        }
    }
    d[vert] = 0;
    do
    { // поиск новой рабочей вершины d[i] -> min
        minindex = 10000;
        min = 10000;
        for (int i = 0; i < n; i++)
        { // Если вершину ещё не обошли и вес меньше min
            if ((v[i] == 1) && (d[i] < min))
            { // Переприсваиваем значения
                min = d[i];
                minindex = i;
            }
        }// for
        // проверка маршрутов через вершину c minindex
        if (minindex != 10000)
        {
            for (int i = 0; i < n; i++)
            {
                if (a[minindex][i] > 0)
                {
                    // Добавляем найденный минимальный вес к текущему весу вершины
                    temp = min + a[minindex][i];
                    if (temp < d[i]) // и сравниваем с текущим минимальным весом вершины
                    {
                        d[i] = temp;//
                        prev[i] = minindex + 1;
                    }
                }// if
            }// for
            v[minindex] = 0;
        }// if
    } while (minindex < 10000);
    print(d, n);
    print_indexes(prev, n);
    std::cout << "Кратчайший путь из вершины 1 в вершину 5: " << d[4] << std::endl;
    return 0;
}
/*
1   2   3   4   5
-----------------
0   10  0   30  100
10  0   50  0   0
0   50  0   20  10
30  0   20  0   60
100 0   10  60  0
*/

