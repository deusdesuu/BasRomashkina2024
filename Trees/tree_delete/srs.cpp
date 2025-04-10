// Мячин Валентин БАС2
#include <iostream>
#include <fstream>
#include <locale>
#include <random>


struct Node {
	int value;
	Node* left = nullptr;
	Node* right = nullptr;
};
void add(Node*& root, int value) {
	Node* new_node = new Node;
	(*new_node).value = value;

	if (root == nullptr) {
		root = new_node;
	}
	else {
		Node* current = root;
		while (true) {
			if (value == (*current).value) { break; }
			if (value < (*current).value) {
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
void print_symmetry(Node* root) {
	if (root != nullptr) {
		print_symmetry((*root).left);
		std::cout << (*root).value << ' ';
		print_symmetry((*root).right);
	}
}
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
// Идем по дереву вправо
// Пока не встретим nullptr
Node* max(Node*& root) {
	Node* result = 0;
	if (root == nullptr) { return result; }

	Node* current = root;
	while ((*current).right != nullptr) {
		current = (*current).right;
	}
	result = current;
	return result;
}
// Идем по дереву влево
// Пока не встретим nullptr
Node* min(Node*& root) {
	Node* result = 0;
	if (root == nullptr) { return result; }

	Node* current = root;
	while ((*current).left != nullptr) {
		current = (*current).left;
	}
	result = current;
	return result;
}
Node* search(Node*& root, int value) {
	Node* current = root;
	int cur_val = (*current).value;
	while (true) {
		if (cur_val == value) { break; }
		if (cur_val > value) { current = (*current).left; }
		else { current = (*current).right; }
		cur_val = (*current).value;
	}
	return current;
}
void del_leaf(Node* parent, Node*& child, bool dir) {
	if (parent != nullptr) {
		if (dir) { (*parent).right = nullptr; }
		else { (*parent).left = nullptr; }
	}
	delete child;
	child = nullptr;
}
void del_right_child(Node* parent, Node*& child, bool dir) {
	if (parent != nullptr) {
		if (dir) { (*parent).right = (*child).right; }
		else { (*parent).left = (*child).right; }
	}
	(*child).right = nullptr;
	delete child;
	child = nullptr;
}
void del_left_child(Node* parent, Node*& child, bool dir) {
	if (parent != nullptr) {
		if (dir) { (*parent).right = (*child).left; }
		else { (*parent).left = (*child).left; }
	}
	(*child).left = nullptr;
	delete child;
	child = nullptr;
}
void del_two_childs(Node* parent, Node*& child, bool dir) {
	// ищем минимум
	Node* rmin = child;
	Node* min = (*child).right;
	while ((*min).left != nullptr) {
		rmin = min;
		min = (*min).left;
	}
	// меняем удаляемую вершину с минимумом
	if (dir) { (*parent).right = min; }
	else { (*parent).left = min; }
	(*min).left = (*child).left;
	Node* min_right = (*min).right;
	(*min).right = (*child).right;
	// если у минимума было что-то справа, то не теряем
	if (rmin == child) { (*min).right = min_right; }
	else { (*rmin).left = min_right; }
	// удаляем вершину
	(*child).left = nullptr;
	(*child).right = nullptr;
	delete child;
}

void del(Node* root, int value) {
	Node* prv = nullptr;
	Node* current = root;

	bool dir = 0; // 0 - left, 1 - right;

	int tree_side; // 0 - empty, 1 - left side, 2 - right side, 3 - root
	if (!current) { tree_side = 0; }
	else if ((*current).value == value) { tree_side = 3; }
	else if ((*current).value > value) { tree_side = 1; }
	else if ((*current).value < value) { tree_side = 2; }

	while (true) {
		if (!current) {
			std::cout << "Такого узла нет." << std::endl;
			break;
		}
		if ((*current).value == value) { break; }
		else {
			prv = current;
			if ((*current).value > value) {
				current = (*current).left;
				dir = 0;
			}
			else {
				current = (*current).right;
				dir = 1;
			}
		}
	}
	if (current) {
		bool f1, f2;
		f1 = (*current).left == nullptr;
		f2 = (*current).right == nullptr;

		if (tree_side == 1) { std::cout << "Удаление вершины левого поддерева.\n"; }
		else if (tree_side == 2) { std::cout << "Удаление вершины правого поддерева.\n"; }
		else if (tree_side == 3) { std::cout << "Удаление корня" << std::endl; }

		if (f1 && f2) {
			std::cout << "Листовая вершина." << std::endl;
			del_leaf(prv, current, dir);
		}
		if (f1 && !f2) {
			std::cout << "С одной правой вершиной." << std::endl;
			del_right_child(prv, current, dir);
		}
		if (!f1 && f2) {
			std::cout << "С одной левой вершиной." << std::endl;
			del_left_child(prv, current, dir);
		}
		if (!f1 && !f2) {
			std::cout << "С двумя вершинами\n";
			std::cout << "Удален элемент = " << (*current).value << std::endl;
			del_two_childs(prv, current, dir);
		}
	}
}
int main() {
	setlocale(LC_ALL, "rus");
	srand(time(0));

	Node* root = nullptr;

	std::ifstream f("F1.txt");

	int n;
	f >> n;

	int value;
	for (int i = 0; i < n; ++i) {
		f >> value;
		add(root, value);
	}

	std::cout << "Вывод дерева симметричным обходом:\n\t"; print_symmetry(root); std::cout << std::endl;

	std::cout << "Удаляемое значение: "; std::cin >> value;
	del(root, value);
	print_symmetry(root);

	clear(root);
	f.close();
	return 0;
}
/*
Test 1(2 листа):
text:
15
15 10 20 12 18 25 11 13 16 19 24 30 26 33 27

Вывод дерева симметричным обходом:
		10 11 12 13 15 16 18 19 20 24 25 26 27 30 33
Удаляемое значение: 12
Удаление вершины левого поддерева.
С двумя вершинами
Удален элемент = 12
10 11 13 15 16 18 19 20 24 25 26 27 30 33
---------------------------------------------------------------
Test2(левый лист, правый поддерево):
text(добавили 14, 15 к 13, 15 поменяли на 17)
17
17 10 20 12 18 25 11 13 14 15 16 19 24 30 26 33 27

Вывод дерева симметричным обходом:
		10 11 12 13 14 15 16 17 18 19 20 24 25 26 27 30 33
Удаляемое значение: 12
Удаление вершины левого поддерева.
С двумя вершинами
Удален элемент = 12
10 11 13 14 15 16 17 18 19 20 24 25 26 27 30 33
---------------------------------------------------------------
Test3(левый поддерево, правый лист):
text(11, 13 меняем на 9 8 7):
16
15 10 8 9 7 20 12 18 25 16 19 24 30 26 33 27

Вывод дерева симметричным обходом:
		7 8 9 10 12 15 16 18 19 20 24 25 26 27 30 33
Удаляемое значение: 10
Удаление вершины левого поддерева.
С двумя вершинами
Удален элемент = 10
7 8 9 12 15 16 18 19 20 24 25 26 27 30 33
---------------------------------------------------------------
Test4(2 поддерева):
text(добавляем 8 9 7):
18
15 10 8 9 7 20 12 18 25 11 13 16 19 24 30 26 33 27

Вывод дерева симметричным обходом:
		7 8 9 10 11 12 13 15 16 18 19 20 24 25 26 27 30 33
Удаляемое значение: 10
Удаление вершины левого поддерева.
С двумя вершинами
Удален элемент = 10
7 8 9 11 12 13 15 16 18 19 20 24 25 26 27 30 33
*/
