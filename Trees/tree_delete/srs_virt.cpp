// Мячин Валентин БАС2
#include <iostream>
#include <fstream>
#include <locale>
#include <random>


struct Node {
	int key;
	Node* left = nullptr;
	Node* right = nullptr;
};
//поиск с включением (нерекурсивный)
void add(Node*& root, int value) {
	Node* new_node = new Node;
	(*new_node).key = value;

	if (root == nullptr) {
		root = new_node;
	}
	else {
		Node* current = root;
		while (true) {
			if (value == (*current).key) { break; }
			if (value < (*current).key) {
				if ((*current).left == nullptr) { (*current).left = new_node; break; }
				else { current = (*current).left; }
			}
			else {
				if ((*current).right == nullptr) { (*current).right = new_node; break; }
				else { current = (*current).right; }
			}
		}
	}
}
// Рекурсивное добавление
void add_rec(Node*& node, int value) {
	// Добавление корня
	if (node == 0) {
		Node* new_node = new Node;
		(*new_node).key = value;
		node = new_node;
	}
	// вправо
	else if ((*node).key < value) {
		// если справа пусто, то добавляем
		if ((*node).right == 0) {
			Node* new_node = new Node;
			(*new_node).key = value;
			(*node).right = new_node;
		}
		// непусто - идем дальше
		else { add((*node).right, value); }
	}
	// влево
	else if ((*node).key > value) {
		// если слева пусто, то добавляем
		if ((*node).left == 0) {
			Node* new_node = new Node;
			(*new_node).key = value;
			(*node).left = new_node;
		}
		// непусто - идем дальше
		else { add((*node).left, value); }
	}
}
// вывод в порядке возрастания (нерекурсивный)
void print_symmetry(Node* root) {
	if (root != nullptr) {
		print_symmetry((*root).left);
		std::cout << (*root).key << ' ';
		print_symmetry((*root).right);
	}
}
// освобождение память (рекурсивное)
void clear(Node*& root) {
	if (root != nullptr) {
		clear((*root).left);
		clear((*root).right);
		(*root).left = nullptr;
		(*root).right = nullptr;
		delete root;
		root = nullptr;
	}
}
void del_lmax(Node*& r, Node*& p) {
	// Идем к максимальной вершине левого поддерева
	if ((*r).right != 0) { del_lmax((*r).right, p); }
	// Значение найденного максимума переносим в удаляемую
	// Меняем найденный максимум на то что у него было слева
	else {
		(*p).key = (*r).key;
		r = (*r).left;
	}
}
void del_rmin(Node*& r, Node*& p) {
	// Идем к минимальной вершине правого поддерева
	if ((*r).left != 0) { del_rmin((*r).left, p); }
	// Значение найденного максимума переносим в удаляемую
	// Меняем найденный максимум на то что у него было справа
	else {
		(*p).key = (*r).key;
		r = (*r).right;
	}
}
// Изначальный способ - левый максимум
// flag: 0 - lmax, 1 - rmin
void deletee(int x, Node*& p) {
	// Пока не нашли искомую вершину - идем по дереву в ее поисках
	if (p == 0) { std::cout << "Такой вершины в дереве нет!" << std::endl; }
	else if (x < (*p).key) { deletee(x, (*p).left); }
	else if (x > (*p).key) { deletee(x, (*p).right); }
	// Нашли
	else {
		// Если у искомой вершины....
		// Только левое поддерево - поттягиваем левую вершину на место удаляемой
		if ((*p).right == 0) { p = (*p).left; }
		// Только правое поддерево - поттягиваем правую вершину на место удаляемой
		else if ((*p).left == 0) { p = (*p).right; }
		// Оба поддерева - выбираем по флагу нужную функцию удаления
		else {
			std::cout << "Выберите способ выбора вершины для замены удаляемой\n";
			std::cout << "\t0. Левая максимальная\n";
			std::cout << "\t1. Правая минимальная\n";

			bool flag;
			std::cin >> flag;

			if (flag) { del_rmin((*p).right, p); }
			else { del_lmax((*p).left, p); }
		}
	}
}
int main() {
	setlocale(LC_ALL, "rus");
	srand(time(0));

	Node* root = nullptr;

	std::ifstream f("text.txt");

	int n;
	f >> n;

	int value;
	for (int i = 0; i < n; ++i) {
		f >> value;
		add(root, value);
	}

	std::cout << "Вывод дерева симметричным обходом:\n\t"; print_symmetry(root); std::cout << std::endl;

	std::cout << "Удаляемое значение: "; std::cin >> value;
	

	deletee(value, root);
	print_symmetry(root);

	clear(root);
	f.close();
	return 0;
}
/*
Дерево:
18
15 10 8 9 7 20 12 18 25 11 13 16 19 24 30 26 33 27
*/
/*
Test 1:

Вывод дерева симметричным обходом:
		7 8 9 10 11 12 13 15 16 18 19 20 24 25 26 27 30 33
Удаляемое значение: 15
Выберите способ выбора вершины для замены удаляемой
		0. Левая максимальная
		1. Правая минимальная
0
7 8 9 10 11 12 13 16 18 19 20 24 25 26 27 30 33
-----------------------------------------------------------------
Test 2:

Вывод дерева симметричным обходом:
		7 8 9 10 11 12 13 15 16 18 19 20 24 25 26 27 30 33
Удаляемое значение: 27
Выберите способ выбора вершины для замены удаляемой
		0. Левая максимальная
		1. Правая минимальная
1
7 8 9 10 11 12 13 15 16 18 19 20 24 25 26 30 33
-----------------------------------------------------------------
Test 3:

Вывод дерева симметричным обходом:
		7 8 9 10 11 12 13 15 16 18 19 20 24 25 26 27 30 33
Удаляемое значение: 33
7 8 9 10 11 12 13 15 16 18 19 20 24 25 26 27 30
*/
