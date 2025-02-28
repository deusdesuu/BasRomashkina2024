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
struct Queue {
	void push(int);
	int pop();
	void print();

	Node* head = nullptr;
	Node* tail = nullptr;
};
int main() {
	setlocale(LC_ALL, "rus");
	srand(time(0));

	Queue queue;

	int n = 10;
	int value;
	
	for (int i = 0; i < n; ++i) {
		value = rand() % 99 - 50;
		std::cout << i + 1 << "-й элемент очереди: " << value << "\n";
		queue.push(value);
	}
	std::cout << "\nВывод элементов без удаления:\n\t";
	queue.print();

	std::cout << "\nВывод элементов с удалением:\n\t";
	for (int i = 0; i < n; ++i) {
		std::cout << queue.pop() << ' ';
	}
	std::cout << std::endl;
	return 0;
}
void Queue::push(int value) {
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
int Queue::pop() {
	if (head == nullptr) { return -1; }
	int result = (*tail).value;
	Node* next = (*tail).next;
	delete tail;
	tail = next;
	return result;
}
void Queue::print() {
	Node* current = tail;
	while (current != nullptr) {
		std::cout << (*current).value << ' ';
		current = (*current).next;
	}
	std::cout << std::endl;
}
/*
 Test:

 1-й элемент очереди: 31
 2-й элемент очереди: -42
 3-й элемент очереди: -7
 4-й элемент очереди: 16
 5-й элемент очереди: -19
 6-й элемент очереди: -32
 7-й элемент очереди: -43
 8-й элемент очереди: 35
 9-й элемент очереди: 40
 10-й элемент очереди: 3
 
 Вывод элементов без удаления:
 		 31 -42 -7 16 -19 -32 -43 35 40 3
 
 Вывод элементов с удалением:
 		 31 -42 -7 16 -19 -32 -43 35 40 3
 */
