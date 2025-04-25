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
// Разница высот поддеревьев для вершины
int height_dif(AVL*& node) { return (*node).h_right - (*node).h_left; }
void fix_balance(AVL*&); // Проверка баланса вершины
void del(AVL*&, int);


struct stack {
	AVL* value;
	stack* next = nullptr;
};
void print(stack*); // вывод стека
void add(stack*&, AVL*); // добавление элемента в стек
void pop(stack*&); // удаление элемента из стека
void clear(stack*&); // очистка стека
void fix_height_del(stack*&, int, AVL*);


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
		while (head != nullptr) {
			// считаем высоты для текущей вершины
			last = (*head).value;
			pop(head);
			int balance = height_dif(last);
			if (abs(balance) == 2) {
                std::cout << "При добавлении вершины " << value << " обнаружен дисбаланс!\n";
                print_forward(root);
            }
			// проверяем баланс вершины, поворачиваем при необходимости
			fix_balance(last);
			if (abs(balance) == 2) {
                std::cout << "Дерево после балансировки:\n";
                print_forward(root); std::cout << '\n' << std::endl;
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
void fix_balance(AVL*& node) {
	int balance = height_dif(node);
	if (balance == 2) {
		if (height_dif((*node).right) == 1) { RR(node); std::cout << "\nВыполняем LL поворот" << std::endl;}
		else { RL(node); std::cout << "\nВыполняем RL поворот" << std::endl;}
	}
	if (balance == -2) {
		if (height_dif((*node).left) == -1) { LL(node); std::cout << "\nВыполняем RR поворот" << std::endl;}
		else { LR(node); std::cout << "\nВыполняем LR поворот" << std::endl;}
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
    std::cout << "Вершина, которую хотим удалить: "; std::cin >> value;
    del(root, value);
    std::cout << "Вывод АВЛ дерева прямым обходом после удаления:\n\t"; print_forward(root); std::cout << std::endl;
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
void del(AVL*& root, int value) {
	AVL* current = root;
	stack* head = nullptr;
	bool flag = 0;
	// поиск вершины в дереве
	// попутно добавляем пройденные вершины в стек
	while (true) {
		if (current == 0) { flag = 1; break; }
		else {
			add(head, current);
			if ((*current).value == value) { break; }
			else if ((*current).value < value) { current = (*current).right; }
			else { current = (*current).left; }
		}
	}
	if (flag) { std::cout << "Такой вершины в дереве нет!" << std::endl; }
	else {
		// 2 потомка удаляемой вершины
		AVL* right = (*current).right;
		AVL* left = (*current).left;
		// Нет потомков или только левый
		if ((*current).right == 0) {
			// Убираем удаляемую вершину со стека
			pop(head);
			(*((*head).value)).left = left;
			delete current;
			current = nullptr;
			--(*(*head).value).h_left;
			// поднимаемся по дереву (по стеку) и балансируем дерево
			fix_height_del(head, value, root);
		}
		// Только правый потомок
		else if ((*current).left == 0) {
			// Убираем удаляемую вершину со стека
			pop(head);
			(*((*head).value)).right = right;
			delete current;
			current = nullptr;
			--(*(*head).value).h_right;
			// поднимаемся по дереву (по стеку) и балансируем дерево
			fix_height_del(head, value, root);
		}
		// 2 потомка
		else {
			// Ищем правый минимум
			// Попутно добавляем пройденный вершины в стек
			// запоминаем вершину, которую собрались удалять
			AVL* to_delete = current;

			current = (*current).right;
			while ((*current).left) {
				add(head, current);
				current = (*current).left;
			}
			// не теряем поддерево вершины, с которой будем менять
			// если вершина сразу справа от удаляемой
			if ((*head).value == to_delete) {
				(*(*head).value).right = (*current).right;
				--(*(*head).value).h_right;
			}
			// если прошли влево
			else {
				(*(*head).value).left = (*current).right;
				--(*(*head).value).h_left;
			}

			// переносим значение правого минимума в удаляемую вершину
			(*to_delete).value = (*current).value;
			// удаляем подменную вершину
			delete current;
			current = nullptr;

			// поднимаемся по дереву (по стеку) и балансируем дерево
			fix_height_del(head, value, root);
		}
	}
	clear(head);
}
void fix_height_del(stack*& head, int value, AVL* root) {
    int height;
    AVL* current;
    while (head != nullptr) {
        // проверяем баланс
        current = (*head).value;
        int balance = height_dif(current);
        if (abs(balance) == 2) {
            std::cout << "При удалении вершины " << value << " обнаружен дисбаланс!\n";
            print_forward(root);
        }
        fix_balance(current);
        if (abs(balance) == 2) {
            std::cout << "Дерево после балансировки:\n";
            print_forward(root); std::cout << '\n' << std::endl;
        }
        pop(head);
        // обновляем высоту для родительской вершины
        if (head == 0) { break; }
        height = max((*current).h_left, (*current).h_right) + 1;
        if (current == (*(*head).value).right) { (*(*head).value).h_right = height; }
        else { (*(*head).value).h_left = height; }
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
