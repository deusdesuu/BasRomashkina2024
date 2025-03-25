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
Test:

n = 5
Введите элементы дерева:
		4 2 1 3 5
Вывод дерева прямым обходом:
		4 2 1 3 5
Вывод дерева обратным обходом:
		1 3 2 5 4
Вывод дерева симметричным обходом:
		1 2 3 4 5
Дерево удалено!
*/
