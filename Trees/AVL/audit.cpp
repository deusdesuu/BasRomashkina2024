// Мячин Валентин БАС2
#include <iostream>
#include <locale>
#include <random>
#include <fstream>


int max(int a, int b) {
	if (a > b) { return a; }
	else { return b; }
}
struct AVL {
	int value;

	int h_left = 0;
	int h_right = 0;
	AVL* left = nullptr;
	AVL* right = nullptr;
};
void print_symmetry(AVL*); // вывод дерева симметричным обходом
void clear(AVL*&); // освобождение памяти дерева
int height(AVL*&); // рекурсивный поиск высоты дерева
void add(AVL*&, int); // поиск с включением (нерек)

struct stack {
	AVL* value;
	stack* next = nullptr;
};
void print(stack*); // вывод стека
void add(stack*&, AVL*); // добавление элемента в стек
void pop(stack*&); // удаление элемента из стека


// вывод в порядке возрастания (нерекурсивный)
void print_symmetry(AVL* root) {
	if (root != nullptr) {
		print_symmetry((*root).left);
		std::cout << (*root).value << ' ' <<
			"(" << (*root).h_left << ' ' << (*root).h_right << ") ";
		print_symmetry((*root).right);
	}
}
// освобождение память (рекурсивное)
void clear(AVL*& root) {
	if (root != nullptr) {
		clear((*root).left);
		clear((*root).right);
		(*root).left = nullptr;
		(*root).right = nullptr;
		delete root;
		root = nullptr;
	}
}
int height(AVL*& node) {
	int result;
	if (node == 0) { result = 0; }
	else {
		int l = height((*node).left);
		int r = height((*node).right);
		if (l > r) { result = l; }
		else { result = r; }
		++result;
	}
	return result;
}
void add(AVL*& root, int value) {
	AVL* new_node = new AVL;
	(*new_node).value = value;

	stack* head = nullptr;
	// поиск с включением,
	// дополнительно посещенные вершины добавляем в стек
	if (root == 0) { root = new_node; }
	else {
		AVL* current = root;
		
		while (true) {
			add(head, current);
			if ((*current).value == value) { break; }
			else if ((*current).value > value) {
				if ((*current).left == 0) {
					(*current).left = new_node;
					break;
				}
				else {
					current = (*current).left; 
				}
			}
			if ((*current).value < value) {
				if ((*current).right == 0) {
					(*current).right = new_node;
					break;
				}
				else {
					current = (*current).right; 
				}
			}
		}
	}
	add(head, new_node);
	// пересчитываем высоты по пути добавления новой вершины
	AVL* last;
	AVL* current;
	int height;
	while (head != nullptr) {
		// считаем высоты для текущей вершины
		last = (*head).value;
		pop(head);
		height = max((*last).h_left, (*last).h_right) + 1;
		// обновляем высоту для родительской вершины
		if (head == nullptr) { break; }
		current = (*head).value;
		// обновляем значение высоты
		if (last == (*current).right) { (*current).h_right = height; }
		else { (*current).h_left = height; }
	}
}

void print(stack* head) {
	stack* current = head;
	while (current != nullptr) {
		std::cout << (*(*current).value).value << ' ';
		current = (*current).next;
	}
	std::cout << std::endl;
}
void add(stack*& head, AVL* value) {
	stack* new_node = new stack;
	(*new_node).value = value;
	if (head == 0) { head = new_node; }
	else {
		(*new_node).next = head;
		head = new_node;
	}
}
void pop(stack*& head) {
	stack* cpy = head;
	head = (*head).next;
	delete cpy;
	cpy = nullptr;
}
int main() {
	setlocale(LC_ALL, "rus");
	srand(time(0));


	AVL* root = nullptr;

	std::ifstream f("text.txt");

	int n;
	f >> n;

	int value;
	for (int i = 0; i < n; ++i) {
		f >> value;
		add(root, value);
	}

	std::cout << "Вывод дерева симметричным обходом:\n\t"; print_symmetry(root); std::cout << std::endl;

	clear(root);
	f.close();

	return 0;
}
