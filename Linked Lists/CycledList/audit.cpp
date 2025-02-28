// Мячин Валентин БАС2
#include <iostream>
#include <locale>
#include <random>


struct Node {
	char* fname;
	int id;
	int value1;
	int value2;
	Node* next = nullptr;
};
int len(Node* node) {
	int result = (*node).value1;
	return result;
}
void print(Node* node) {
	Node* current = (*node).next;
	std::cout << "\n\tФамилия\t\tid\tvalue1\tvalue2\n";
	int k = 1;
	while ((*current).id != 0) {
		std::cout << k << ")\t" << (*current).fname << "\t\t" << (*current).id << "\t" << (*current).value1 << "\t" << (*current).value2 << "\n";
		current = (*current).next;
		++k;
	}
	std::cout << std::endl;
}
void print_twice(Node* node) {
	Node* current = (*node).next;
	std::cout << "\n\tФамилия\t\tid\tvalue1\tvalue2\n";
	int k = 1;
	int n = len(node);
	for (int i = 0; i <= 2 * n; ++i) {
		if ((*current).id != 0) {
			std::cout << k << ")\t" << (*current).fname << "\t\t" << (*current).id << "\t" << (*current).value1 << "\t" << (*current).value2 << "\n";
			++k;
		}
		current = (*current).next;
	}
	std::cout << std::endl;
}
void print_even(Node* node) {
	Node* current = (*(*node).next).next;
	std::cout << "\n\tФамилия\t\tid\tvalue1\tvalue2\n";
	int k = 1;
	int n = len(node);
	for (int i = 1; i < n; i += 2) {
		std::cout << k << ")\t" << (*current).fname << "\t\t" << (*current).id << "\t" << (*current).value1 << "\t" << (*current).value2 << "\n";
		++k;
		current = (*(*current).next).next;
	}
	std::cout << std::endl;
}
void add(Node* node, char* fname) {
	++(*node).value1;
	Node* new_node = new(Node);
	(*new_node).fname = fname;
	(*new_node).id = (*node).value1;
	(*new_node).value1 = rand() % 99 - 50;
	(*new_node).value2 = rand() % 99 - 50;
	(*new_node).next = (*node).next;
	(*node).next = new_node;
}
int main() {
	setlocale(LC_ALL, "rus");
	srand(time(0));

	Node* head = new(Node);
	(*head).value1 = 0;
	(*head).next = head;
	(*head).id = 0;

	int n;
	std::cout << "n = "; std::cin >> n;

	for (int i = 0; i < n; ++i) {
		char* fname = new char[20];
		std::cout << "Введите фамилию:"; std::cin >> fname;
		add(head, fname);
		print(head);
	}
	std::cout << "\nВывод списка 2 раза по кругу:\n";
	print_twice(head);
	std::cout << "\nВывод четных элементов списка:\n";
	print_even(head);
	std::cin >> n;
	return 0;
}
/*
Test:

n = 5
Введите фамилию:Ivanov

		Фамилия         id      value1  value2
1)      Ivanov          1       16      -28

Введите фамилию:Petrov

		Фамилия         id      value1  value2
1)      Petrov          2       -44     -37
2)      Ivanov          1       16      -28

Введите фамилию:Sidorov

		Фамилия         id      value1  value2
1)      Sidorov         3       -25     -39
2)      Petrov          2       -44     -37
3)      Ivanov          1       16      -28

Введите фамилию:Levin

		Фамилия         id      value1  value2
1)      Levin           4       28      22
2)      Sidorov         3       -25     -39
3)      Petrov          2       -44     -37
4)      Ivanov          1       16      -28

Введите фамилию:Kazakov

		Фамилия         id      value1  value2
1)      Kazakov         5       2       -50
2)      Levin           4       28      22
3)      Sidorov         3       -25     -39
4)      Petrov          2       -44     -37
5)      Ivanov          1       16      -28


Вывод списка 2 раза по кругу:

		Фамилия         id      value1  value2
1)      Kazakov         5       2       -50
2)      Levin           4       28      22
3)      Sidorov         3       -25     -39
4)      Petrov          2       -44     -37
5)      Ivanov          1       16      -28
6)      Kazakov         5       2       -50
7)      Levin           4       28      22
8)      Sidorov         3       -25     -39
9)      Petrov          2       -44     -37
10)     Ivanov          1       16      -28


Вывод четных элементов списка:

		Фамилия         id      value1  value2
1)      Levin           4       28      22
2)      Petrov          2       -44     -37
*/
