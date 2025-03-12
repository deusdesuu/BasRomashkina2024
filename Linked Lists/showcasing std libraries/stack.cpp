// Мячин Валентин БАС2
#include <iostream>
#include <locale>
#include <random>
#include <stack>
/*
 * Очередь в стандарте реализована, как
 * Обертка для дека, путем ограничения
 * Доступных к применению операций
 * Который соответствуют операциям очереди(?)
 */
/*
 * Описание функций:
 * - <T> top() - возврат указателя на вершину стека (Node* head)
 * - bool empty() - пустота очереди (head == tail == nullptr)
 * - void pop() - удаление первого элемента
 * - void push(const& <T>) - добавление нового элемента на вершину стека
 * - int size() - возвращает количество элементов в стеке
 * - операторы ==, !=, >, <, <=, >= сравнивают 2 стека лексикографически
 */
/*
 Пример для оператора >:

 template <class T>
bool operator>(std::stack<T> stack1, std::stack<T> stack2) {
	while (!stack1.empty() && stack2.empty()) {
		if (stack1.top() <= stack2.top()) {
			return false;
		}
		stack1.pop();
		stack2.pop();
	}
	if (!stack1.empty()) { return true; }
	else { return false; }
}
 */
void print(std::stack<int> stack) {
	while (!stack.empty()) {
		std::cout << stack.top() << ' ';
		stack.pop();
	}
	std::cout << std::endl;
}
int main() {
	setlocale(LC_ALL, "rus");
	srand(time(0));

	std::stack<int> stack; // Инициализация стека
	int n = 10;
	std::cout << "Проверяем, что стек пуст(empty): " << stack.empty() << std::endl;
	// Заполнение стека
	for (int i = 0; i < n; ++i) {
		stack.push(rand() % 99 - 50);
	}
	std::cout << "Стек после заполнения (push):\n\t"; print(stack);
	std::cout << "Проверяем, что стек не пуст (empty): " << stack.empty() << std::endl;

	std::cout << "\ntop()\tsize()\tprint()\n";
	for (int i = 0; i < n; ++i) {
		std::cout << stack.top() << '\t' << stack.size() << '\t'; print(stack);
		stack.pop();
	}
	return 0;
}
/*
Test:

Проверяем, что стек пуст(empty): 1
Стек после заполнения (push):
		30 -43 31 -25 -26 26 -37 29 -38 7
Проверяем, что стек не пуст (empty): 0

top()   size()  print()
30      10      30 -43 31 -25 -26 26 -37 29 -38 7
-43     9       -43 31 -25 -26 26 -37 29 -38 7
31      8       31 -25 -26 26 -37 29 -38 7
-25     7       -25 -26 26 -37 29 -38 7
-26     6       -26 26 -37 29 -38 7
26      5       26 -37 29 -38 7
-37     4       -37 29 -38 7
29      3       29 -38 7
-38     2       -38 7
7       1       7
*/
