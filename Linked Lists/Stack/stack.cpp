// Мячин Валентин БАС2
/*

Задание 2 (стек)

создать стек 1 из n вещественных элементов
n - с клавиатуры
значения - случайно

вывести на экран процесс заполнения стека1 ( на каждый новый элемент)
найдите сумму произведение и ср арифметическое всех элементов стека1
занести их в стек2
вывести на экран значения суммы, произведения и ср арифм
вывести стек2 с удалением

*/
#include "stdafx.h"
#include <iostream>
#include <locale>
#include <random>


struct Node {
	float value;
	Node* next;
};

void add(Node*&, float);
float pop(Node*&);
void print(Node*);
float sum(Node*);
float mul(Node*);
float avg(Node*);

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(0));
	setlocale(LC_ALL, "rus");

	Node* stack1 = nullptr;

	int n;
	std::cout << "n = "; std::cin >> n;
	std::cout << "Процесс заполнения стека1:\n";
	float value;
	for (int i = 0; i < n; ++i) {
		value = static_cast<float>(rand()) / 10000;
		add(stack1, value);
		std::cout << "\t";
		print(stack1);
	}

	float SUM = sum(stack1);
	float MUL = mul(stack1);
	float AVG = avg(stack1);
	
	std::cout << "\nСумма элементов стека: " << SUM << std::endl;
	std::cout << "Произведение элементов стека: " << MUL << std::endl;
	std::cout << "Среднее арифметическое элементов стека: " << AVG << std::endl;

	Node* stack2 = nullptr;
	add(stack2, SUM);
	add(stack2, MUL);
	add(stack2, AVG);

	std::cout << "\nВывод стека2: ";
	while (stack2 != nullptr) {
		std::cout << pop(stack2) << ' ';
	}
	std::cout << std::endl;

	std::cin >> value;
	return 0;
}
void print(Node* node) {
	Node* current = node;
	while (current != nullptr) {
		std::cout << (*current).value << ' ';
		current = (*current).next;
	}
	std::cout << std::endl;
}
void add(Node*& node, float value) {
	Node* new_node = new(Node);
	(*new_node).value = value;
	(*new_node).next = node;
	node = new_node;
}
float pop(Node*& node) {
	float value = (*node).value;
	Node* copy = node;
	node = (*node).next;
	(*copy).next = nullptr;
	delete copy;
	return value;
}
float sum(Node* node) {
	Node* current = node;
	float sum = 0;
	while (current != nullptr) {
		sum += (*current).value;
		current = (*current).next;
	}
	return sum;
}
float mul(Node* node) {
	Node* current = node;
	float mul = 1;
	while (current != nullptr) {
		mul *= (*current).value;
		current = (*current).next;
	}
	return mul;
}
float avg(Node* node) {
	Node* current = node;
	float sum = 0;
	int n = 0;
	while (current != nullptr) {
		sum += (*current).value;
		++n;
		current = (*current).next;
	}
	return sum / n;
}
