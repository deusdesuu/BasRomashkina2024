// Нерекурсивное АВЛ дерево (кроме вывода и удаления)
// Мячин Валентин БАС2
#include <iostream>
#include <locale>
#include <fstream>


// шаблонная функция нахождения максимума
template <class T> T max(T a, T b) { return (a > b) ? a : b; }


struct AVL {
	int value;

	int h_left = 0;
	int h_right = 0;
	AVL* left = nullptr;
	AVL* right = nullptr;
};
void print_symmetry(AVL*); // вывод дерева симметричным обходом
void print_forward(AVL*); // вывод прямым обходом
void clear(AVL*&); // освобождение памяти дерева
void add(AVL*&, int); // поиск с включением (нерек)
void LL(AVL*&); // перевес лево-лево
void RR(AVL*&); // перевес право-право
void LR(AVL*&); // перевес лево-право
void RL(AVL*&); // перевес право-лево
int balance(AVL*& node) { return (*node).h_right - (*node).h_left; }


struct stack {
	AVL* value;
	stack* next = nullptr;
};
void print(stack*); // вывод стека
void add(stack*&, AVL*); // добавление элемента в стек
void pop(stack*&); // удаление элемента из стека
void clear(stack*&); // очистка стека


void add(AVL*& root, int value) {
	AVL* new_node = new AVL;
	(*new_node).value = value;

	stack* head = nullptr;
	// флаг для проверки случаев, когда мы добавляем вершину, которая уже есть в дереве
	// (чтобы не было утечек памяти)
	bool flag = 0;
	// поиск с включением,
	// дополнительно посещаемые вершины добавляем в стек
	if (root == 0) { root = new_node; }
	else {
		AVL* current = root;

		while (true) {
			add(head, current);
			if ((*current).value == value) { flag = 1; break; }
			else if ((*current).value > value) {
				if ((*current).left == 0) {
					(*current).left = new_node;
					break;
				}
				else {
					current = (*current).left;
				}
			}
			else {
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
	// Если добавляемая вершина уже есть в дереве
	// Чистим стек и удаляем вершину (повторку)
	if (flag) {
		clear(head);
		delete new_node;
		new_node = nullptr;
	}
	else {
		add(head, new_node);
		// пересчитываем высоты по пути добавления новой вершины
		AVL* last;
		AVL* current;
		int height; // высота дерева
		int bal; // разница высот правого и левого поддерева
		while (head != nullptr) {
			// считаем высоты для текущей вершины
			last = (*head).value;
			pop(head);
			// проверяем баланс вершины, поворачиваем при необходимости
			bal = balance(last);
			if (bal > 1) {
				if (balance((*last).right) == 1) { RR(last); }
				else { RL(last); }
			}
			if (bal < -1) {
				if (balance((*last).left) == -1) { LL(last); }
				else { LR(last); }
			}
			// обновляем высоту для родительской вершины
			height = max((*last).h_left, (*last).h_right) + 1;
			if (head == nullptr) { break; }
			current = (*head).value;
			// обновляем значение высоты
			if (last == (*current).right) { (*current).h_right = height; }
			else { (*current).h_left = height; }
		}
	}
}
/*
	Внутри RR и LL:
		- меняем местами вершины
		- обновляем высоты
	Путанница с указателями:
		- создаем новую вершину х
		  и копируем в нее node
		- в конце копируем в node вершину у
		- удаляем у
		*иначе не выходит
*/
// Однократный поворот влево (если перевес право-право)
void RR(AVL*& node) {
	AVL* x = new AVL;
	(*x).value = (*node).value;
	(*x).h_left = (*node).h_left;
	(*x).h_right = (*node).h_right;
	(*x).left = (*node).left;
	(*x).right = (*node).right;

	AVL* y = (*x).right;

	(*x).right = (*y).left;
	(*x).h_right = (*y).h_left;

	(*y).left = x;
	(*y).h_left = max((*x).h_left, (*x).h_right) + 1;

	(*node).value = (*y).value;
	(*node).h_left = (*y).h_left;
	(*node).h_right = (*y).h_right;
	(*node).left = (*y).left;
	(*node).right = (*y).right;

	delete y;
}
// Однократный поворот вправо (если перевес слева)
void LL(AVL*& node) {
	AVL* x = new AVL;
	(*x).value = (*node).value;
	(*x).h_left = (*node).h_left;
	(*x).h_right = (*node).h_right;
	(*x).left = (*node).left;
	(*x).right = (*node).right;

	AVL* y = (*x).left;

	(*x).left = (*y).right;
	(*x).h_left = (*y).h_right;

	(*y).right = x;
	(*y).h_right = max((*x).h_left, (*x).h_right) + 1;
	
	(*node).value = (*y).value;
	(*node).h_left = (*y).h_left;
	(*node).h_right = (*y).h_right;
	(*node).left = (*y).left;
	(*node).right = (*y).right;
	
	delete y;
}
// Перевес лево-право
void LR(AVL*& node) {
	RR((*node).left);
	LL(node);
}
// Перевес право-лево
void RL(AVL*& node) {
	LL((*node).right);
	RR(node);
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

	std::cout << "Вывод АВЛ дерева прямым обходом:\n\t"; print_forward(root); std::cout << std::endl;

	clear(root);
	f.close();

	return 0;
}
// вывод в порядке возрастания (нерекурсивный)
void print_symmetry(AVL* root) {
	if (root != nullptr) {
		print_symmetry((*root).left);
		std::cout << (*root).value << ' ' <<
			"(" << (*root).h_left << ' ' << (*root).h_right << ") ";
		print_symmetry((*root).right);
	}
}
// прямой обход
void print_forward(AVL* root) {
	if (root != nullptr) {
		print_forward((*root).left);
		print_forward((*root).right);
		std::cout << (*root).value << ' ' <<
			"(" << (*root).h_left << ' ' << (*root).h_right << ") ";
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
// вывод стека в консоль
void print(stack* head) {
	stack* current = head;
	while (current != nullptr) {
		std::cout << (*(*current).value).value << ' ';
		current = (*current).next;
	}
	std::cout << std::endl;
}
// добавление элемента в стек
void add(stack*& head, AVL* value) {
	stack* new_node = new stack;
	(*new_node).value = value;
	if (head == 0) { head = new_node; }
	else {
		(*new_node).next = head;
		head = new_node;
	}
}
// удаление элемента из стека
void pop(stack*& head) {
	stack* cpy = head;
	head = (*head).next;
	delete cpy;
	cpy = nullptr;
}
// удаление стека
void clear(stack*& head) {
	stack* current = head;
	stack* next = nullptr;
	while (current != nullptr) {
		next = (*current).next;
		delete current;
		current = next;
	}
}
/*
Test 1(LL):
Дерево:
9
12 8 17 4 10 15 2 6 1

Вывод АВЛ дерева прямым обходом:
		1 (0 0) 2 (1 0) 6 (0 0) 10 (0 0) 8 (1 1) 4 (2 2) 15 (0 0) 17 (1 0) 12 (3 2)
------------------------------------------------------------------------------------
Test 2(RL x2):
Дерево:
13
15 10 20 12 18 25 11 13 16 19 30 26 33

Вывод АВЛ дерева прямым обходом:
		10 (0 0) 13 (0 0) 12 (0 1) 11 (1 2) 16 (0 0) 19 (0 0) 18 (1 1) 25 (0 0) 33 (0 0) 30 (0 1) 26 (1 2) 20 (2 3) 15 (3 4)
------------------------------------------------------------------------------------
Test 3(RR):
Дерево:
6
60 50 70 40 80 90

Вывод АВЛ дерева прямым обходом:
		40 (0 0) 50 (1 0) 70 (0 0) 90 (0 0) 80 (1 1) 60 (2 2)
------------------------------------------------------------------------------------
Test 4(LR):
Дерево:
6
60 50 70 40 80 45

Вывод АВЛ дерева прямым обходом:
		40 (0 0) 50 (0 0) 45 (1 1) 80 (0 0) 70 (0 1) 60 (2 2)
*/
