// Мячин Валентин БАС-2024-2
// вариант 9
#include <iostream>
#include <fstream>
#include <queue>
#include <locale>
#include <random>

// ввод матрицы смежности
int** input_adjacency(int n, std::ifstream& input) {
	int** mat = new int*[n];
	for (int i = 0; i < n; ++i) {
		mat[i] = new int[n];
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			input >> mat[i][j];
		}
	}
	return mat;
}
void print(int** mat, int a, int b) {
	for (int i = 0; i < a; ++i) {
		for (int j = 0; j < b; ++j) {
			std::cout << mat[i][j] << ' ';
		}
		std::cout << '\n';
	}
	std::cout << std::endl;
}
void print(int** mat, int n) {
	print(mat, n, n);
}
void SHIRINA2(int v, int n, bool* visit, int** mat, std::queue<int> queue) {
	queue.push(v);
	visit[v] = 1;
	while (!queue.empty()) {
		v = queue.front();
		queue.pop();
		std::cout << v + 1 << ' ';
		for (int i = 0; i < n; ++i) {
			if (mat[v][i] && !visit[i]) {
				visit[i] = 1;
				queue.push(i);
			}
		}
	}
}
void SHIRINA(int v, int n, int** mat) {
	bool* visit = new bool[n];
	for (int i = 0; i < n; ++i) {
		visit[i] = 0;
	}
	std::queue<int> queue;
	std::cout << "Обход в глубину для вершины " << v << ": ";
	SHIRINA2(v - 1, n, visit, mat, queue);
	std::cout << std::endl;
}
int main() {
	setlocale(LC_ALL, "rus");
	srand(time(0));

	std::ifstream input1("input_adjacency.txt");
	int n;
	input1 >> n;
	int** mat_adj = input_adjacency(n, input1);
	std::cout << "Матрица смежности:\n";
	print(mat_adj, n, n);

	int v;
	std::cout << "Введите номер вершины, для обхода в ширину: "; std::cin >> v;
	SHIRINA(v, n, mat_adj);

	input1.close();

	return 0;
}
/* матрица смежности
5
0 1 0 1 1
1 0 1 0 1
0 1 0 1 0
1 0 1 0 1
1 1 0 1 0
*/
/* матрица инцидентности
6 5
1 1 1 0 0 0
0 1 0 0 0 1
0 0 0 1 1 1
1 0 0 1 0 0
0 0 1 0 1 0

a 1 4
b 1 2
c 1 5
d 3 4
e 3 5
f 2 3
*/
