/*
	/b/derevo
	root: 1-2n nodes
	page: n-2n nodes
	perfectly balanced tree
	
	if page has k nodes
	then it has k + 1 descendants
*/
#include <iostream>
#include <locale>
#include <random>

struct Page;
struct Node;

struct Page {
	short count; // кол-во вершин на странице
	Node** nodes; // массив под вершины
	Page* p0;
};
struct Node {
	int value;
	Page* child; // правый потомок вершины
	int count; // сколько раз встретился ключ
};
struct BTree {
	Page* root;
	int height;
};
// Инициализируем вершины дерева
void BTree_init(BTree* tree) {

	return;
}

// nodes limit: 62_748_516
int find_height(int nodes) {
	int height = 0;
	int result = 0;
	int last = 0;

	while (nodes > result) {
		++height;
		result = 2 * height;
		last = result * (2 * height + 1);
		for (int i = 0; i < height; ++i) {
			result += last;
			last *= (2 * height + 1);
		}
	}
	return height;
}

int main() {
	setlocale(LC_ALL, "rus");
	srand(time(0));

	int n;
	std::cout << "Введите количество вершин в дереве: ";
	std::cin >> n;

	BTree* tree = new BTree;
	// Устанавливаем значение высоты для дерева
	// В соответствии с тем сколько вершин должно в него поместиться
	(*tree).height = find_height(n);
	// Начальная инициализация дерева
	BTree_init(tree);


	return 0;
}
