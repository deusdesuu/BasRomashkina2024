// Мячин Валентин БАС2
#include <iostream>
#include <locale>
#include <random>
#include <string>


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
// Очередь для вывода дерева в ширину
struct Q {
	Node* value = nullptr;
	Q* next = nullptr;
};
void q_add(Q*& head, Node* value) {
	Q* new_node = new Q;
	(*new_node).value = value;
	
	if (head == nullptr) { head = new_node; }
	else {
		Q* current = head;
		while ((*current).next != nullptr) {
			current = (*current).next;
		}
		(*current).next = new_node;
	}
}
Node* q_pop(Q*& head) {
	Node* result = (*head).value;
	Q* tmp = (*head).next;
	(*head).next = nullptr;
	delete head;
	head = tmp;
	return result;
}
// Функция для определения глубины дерева
int depth(Node* root) {
	if (!root) {
		return 0;
	}
	int l = depth((*root).left);
	int r = depth((*root).right);
	if (l >= r) { return l + 1; }
	else { return r + 1; }
}
// Вывод дерева в ширину
/*
Помещаем корень дерева в очередь
Идем по очереди
Для каждой встреченной вершины добавляем в очередь
Ее левую и правую вершину

Магию с пробелами для вывода я делал перебором
Я ее не понимаю (на то она и магия)
*/
void print_wide(Node* root) {
	Q* q = nullptr;
	q_add(q, root);

	int d = depth(root);
	int pow2 = 1;
	int index = 0;

	std::string gap = "";
	for (int i = 0; i < pow(2, d); ++i) { std::cout << " "; }
	while (d > 0) {
		Node* tmp = q_pop(q);

		if (tmp) { std::cout << (*tmp).value; }
		else { std::cout << ' '; }
		std::cout << gap + gap;

		++index;
		if (index == pow2) {
			pow2 *= 2;
			index = 0;
			--d;
			std::cout << std::endl;
			gap = "";
			for (int i = 0; i < pow(2, d); ++i) { gap += " "; }
			std::cout << gap;
		}
		/*
		Добавляем узлы в очередь
		Для пустых узлов тоже, чтобы не ломать вывод
		*/
		if (tmp) {
			q_add(q, (*tmp).left);
			q_add(q, (*tmp).right);
		}
		else {
			q_add(q, nullptr);
			q_add(q, nullptr);
		}



	}
	std::cout << std::endl;
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
	std::cout << "Красивый вывод в ширину:\n";
	print_wide(root);
	clear(root);
	std::cout << "Дерево удалено!" << std::endl;
	return 0;
}
/*
Test 1:
n = 7
Введите элементы дерева:
		10 65 37 12 9 34 102
Вывод дерева прямым обходом:
		10 9 65 37 12 34 102
Вывод дерева обратным обходом:
		9 34 12 37 102 65 10
Вывод дерева симметричным обходом:
		9 10 12 34 37 65 102
Красивый вывод в ширину:
                                10
                9                                65
                                          37                102
                                        12
                                               34
Дерево удалено!

-----------------------------------------------------------------------

Test 2:

n = 5
Введите элементы дерева:
		4 2 1 3 5
Вывод дерева прямым обходом:
		4 2 1 3 5
Вывод дерева обратным обходом:
		1 3 2 5 4
Вывод дерева симметричным обходом:
		1 2 3 4 5
Красивый вывод в ширину:
        4
    2        5
  1    3

Дерево удалено!
*/
