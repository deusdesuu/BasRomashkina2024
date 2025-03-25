// Мячин Валентин БАС2
#include <iostream>
#include <locale>
#include <random>


struct Node {
	int value;
	Node* left = nullptr;
	Node* right = nullptr;
};
// Вставка нового узла в дерево
void add(Node*& root, int value) {
	Node* new_node = new Node;
	(*new_node).value = value;

	if (root == nullptr) {
		root = new_node;
	}
	else {
		Node* current = root;
		while (true) {
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
// Вывод дерева прямым обходом
void print_forward(Node* root) {
	if (root != nullptr) {
		std::cout << (*root).value << ' ';
		print_forward((*root).left);
		print_forward((*root).right);
	}
}
// Вывод дерева обратным обходом
void print_backward(Node* root) {
	if (root != nullptr) {
		print_backward((*root).left);
		print_backward((*root).right);
		std::cout << (*root).value << ' ';
	}
}
// Вывод дерева симметричным обходом
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
int main() {
	setlocale(LC_ALL, "rus");
	srand(time(0));

	// Объявление и инициализация корня дерева
	Node* root = nullptr;
	int n;
	std::cout << "n = "; std::cin >> n;
	
	int value;
	std::cout << "Введите элементы дерева:\n\t";
	for (int i = 0; i < n; ++i) {
		std::cin >> value;
		add(root, value);
	}

	std::cout << "Вывод дерева прямым обходом:\n\t"; print_forward(root); std::cout << std::endl;
	std::cout << "Вывод дерева обратным обходом:\n\t"; print_backward(root); std::cout << std::endl;
	std::cout << "Вывод дерева симметричным обходом:\n\t"; print_symmetry(root); std::cout << std::endl;

	clear(root);
	std::cout << "Дерево удалено!" << std::endl;
	return 0;
}
/*
Test 1:

n = 7
Введите элементы дерева:
		9 4 78 1 11 15 14
Вывод дерева прямым обходом:
		9 4 1 78 11 15 14
Вывод дерева обратным обходом:
		1 4 14 15 11 78 9
Вывод дерева симметричным обходом:
		1 4 9 11 14 15 78
Дерево удалено!

--------------------------------------

Test 2:

n = 6
Введите элементы дерева:
		14 5 21 8 54 3
Вывод дерева прямым обходом:
		14 5 3 8 21 54
Вывод дерева обратным обходом:
		3 8 5 54 21 14
Вывод дерева симметричным обходом:
		3 5 8 14 21 54
Дерево удалено!

--------------------------------------

Test 3:

n = 7
Введите элементы дерева:
		10 65 37 12 9 34 102
Вывод дерева прямым обходом:
		10 9 65 37 12 34 102
Вывод дерева обратным обходом:
		9 34 12 37 102 65 10
Вывод дерева симметричным обходом:
		9 10 12 34 37 65 102
Дерево удалено!

*/
