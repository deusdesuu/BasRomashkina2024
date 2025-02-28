// Мячин Валентин БАС2
/*
Задание 1 (очередь)

создать очередь из 10 целочисленных узлов
значения - случайно
в процессе занесения элементов в очередь выводим на экран "1 элемент очереди = ..."
вывод на экран ВСЕХ элементов очереди сначала без удаления, затем с удалением

*/
#include <iostream>
#include <locale>
#include <random>


struct Node {
	int value;
	Node* next = nullptr;
};
void print(Node*);
int pop(Node*&);
void push(Node*&, Node*&, int);
void clear(Node*);

int main() {
	setlocale(LC_ALL, "rus");
	srand(time(0));

	Node* head = nullptr;
	Node* tail = nullptr;

	int n = 10;
	int value;
	for (int i = 0; i < n; ++i) {
		value = rand() % 99 - 50;
		std::cout << i + 1 << "-й элемент очереди: " << value << "\n";
		push(head, tail, value);
	}
	std::cout << "\nВывод элементов очереди без удаления:\n\t";
	print(tail);
	std::cout << "\nВывод элементов очереди с удалением\n\t";
	for (int i = 0; i < n; ++i) {
		std::cout << pop(tail) << ' ';
	}
	std::cout << std::endl;

	clear(tail);
	return 0;
}
void print(Node* tail) {
	Node* current = tail;
	while (current != nullptr) {
		std::cout << (*current).value << ' ';
		current = (*current).next;
	}
	std::cout << std::endl;
}
void push(Node*& head, Node*& tail, int value) {
	Node* new_node = new Node;
	(*new_node).value = value;
	if (head == nullptr) {
		head = new_node;
		tail = new_node;
	}
	else {
		(*head).next = new_node;
		head = new_node;
	}
}
int pop(Node*& tail) {
	if (tail == nullptr) { return -1; }
	int result = (*tail).value;
	Node* next = (*tail).next;
	delete tail;
	tail = next;
	return result;
}
void clear(Node* tail) {
	while (tail != nullptr) {
		pop(tail);
	}
}
/*
 * Test:
 * 1-й элемент очереди: -44
 * 2-й элемент очереди: -12
 * 3-й элемент очереди: 8
 * 4-й элемент очереди: -50
 * 5-й элемент очереди: -5
 * 6-й элемент очереди: -31
 * 7-й элемент очереди: 22
 * 8-й элемент очереди: -5
 * 9-й элемент очереди: -43
 * 10-й элемент очереди: 22
 * 
 * Вывод элементов очереди без удаления:
 *         -44 -12 8 -50 -5 -31 22 -5 -43 22
 * 
 * Вывод элементов очереди с удалением
 *         -44 -12 8 -50 -5 -31 22 -5 -43 22
 */
