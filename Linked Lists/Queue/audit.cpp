// Мячин Валентин БАС2
/*
Задание 1 (очередь)

создать очередь из 10 целочисленных узлов
значения - случайно
в процессе занесения элементов в очередь выводим на экран "1 элемент очереди = ..."
вывод на экран ВСЕХ элементов очереди сначала без удаления, затем с удалением

*/
#include "stdafx.h"
#include <iostream>
#include <locale>
#include <random>


struct Node {
	int value;
	Node* next;
	Node* prev;
};

void add(Node*&, Node*&, int);
int pop(Node*&);
void print(Node*, Node*);

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(0));
	setlocale(LC_ALL, "rus");

	Node* head = nullptr;
	Node* tail = nullptr;
	int value;
	
	for (int i = 0; i < 10; ++i) {
		value = rand() % 99 - 50;
		add(head, tail, value);
		std::cout << i + 1 << "-й элемент очереди: " << value << std::endl;
	}
	print(head, tail);
	for (int i = 0; i < 10; ++i) {
		std::cout << pop(tail) << ' ';
	}
	std::cout << std::endl;

	std::cin >> value;
	return 0;
}
void add(Node*& head, Node*& tail, int value) {
	Node* new_node = new(Node);
	(*new_node).value = value;
	(*new_node).next = nullptr;
	(*new_node).prev = nullptr;

	if (head == nullptr) {
		head = new_node;
		tail = new_node;
		(*head).next = tail;
		(*tail).prev = head;
	} else {
		(*new_node).next = head;
		(*head).prev = new_node;
		head = new_node;
	}
}
int pop(Node*& tail) {
	int value = (*tail).value;

	Node* copy = tail;
	if ((*tail).prev != nullptr) {
		tail = (*tail).prev;
		(*tail).next = nullptr;
		(*copy).prev = nullptr;
	}
	delete copy;

	return value;
}
void print(Node* head, Node* tail) {
	Node* current = head;
	while (true) {
		std::cout << (*current).value << ' ';
		if (current == tail) { break; }
		current = (*current).next;
		
	}
	std::cout << std::endl;
}
