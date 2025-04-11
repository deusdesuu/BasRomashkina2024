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
//поиск с включением (нерекурсивный)
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
// вывод в порядке возрастания (нерекурсивный)
void print_symmetry(Node* root) {
	if (root != nullptr) {
		print_symmetry((*root).left);
		std::cout << (*root).value << ' ';
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
// максимум (нерекурсивный)
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
// минимум (нерекурсивный)
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
// удаление листовой вершины
void del_leaf(Node* parent, Node*& child, bool dir) {
	if (parent != nullptr) {
		if (dir) { (*parent).right = nullptr; }
		else { (*parent).left = nullptr; }
	}
	delete child;
	child = nullptr;
}
// удаление вершины с одним правым потомком
void del_right_child(Node* parent, Node*& child, bool dir) {
	if (parent != nullptr) {
		if (dir) { (*parent).right = (*child).right; }
		else { (*parent).left = (*child).right; }
	}
	(*child).right = nullptr;
	delete child;
	child = nullptr;
}
// удаление вершины с одним левым потомком
void del_left_child(Node* parent, Node*& child, bool dir) {
	if (parent != nullptr) {
		if (dir) { (*parent).right = (*child).left; }
		else { (*parent).left = (*child).left; }
	}
	(*child).left = nullptr;
	delete child;
	child = nullptr;
}
// удаление вершины с двумя потомками
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
    
    // удаляемая вершина слева/справа от своей родительской
	bool dir = 0; // 0 - left, 1 - right;
	
    // определение поддерева из которого удаляем вершину
	int tree_side; // 0 - empty, 1 - left side, 2 - right side, 3 - root
	if (!current) { tree_side = 0; }
	else if ((*current).value == value) { tree_side = 3; }
	else if ((*current).value > value) { tree_side = 1; }
	else if ((*current).value < value) { tree_side = 2; }
    // поиск удаляемой вершины
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
	
	if (current) { // если нашли нужную вершину
		bool f1, f2;
		
		// для удаляемой вершины
		f1 = (*current).left == nullptr; // сущ левый потомок
		f2 = (*current).right == nullptr;// сущ правый потомок
        // пишем в консоль поддерево из которого удаляем
		if (tree_side == 1) { std::cout << "Удаление вершины левого поддерева.\n"; }
		else if (tree_side == 2) { std::cout << "Удаление вершины правого поддерева.\n"; }
		else if (tree_side == 3) { std::cout << "Удаление корня" << std::endl; }
        // если удаляемая лист
		if (f1 && f2) {
			std::cout << "Листовая вершина." << std::endl;
			del_leaf(prv, current, dir);
		}
		// если есть правый потомок
		if (f1 && !f2) {
			std::cout << "С одной правой вершиной." << std::endl;
			del_right_child(prv, current, dir);
		}
		// если есть левый потомок
		if (!f1 && f2) {
			std::cout << "С одной левой вершиной." << std::endl;
			del_left_child(prv, current, dir);
		}
		// если 2 потомка
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
