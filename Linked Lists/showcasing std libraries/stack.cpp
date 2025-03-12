// Мячин Валентин БАС2
#include <iostream>
#include <locale>
#include <random>
#include <queue>
/*
 * Очередь в стандарте реализована, как
 * Обертка для дека, путем ограничения
 * Доступных к применению операций
 * Который соответствуют операциям очереди(?)
 */
/*
 * Описание функций:
 * - <T> back() - возврат указателя на последний элемент (Node* tail)
 * - bool empty() - пустота очереди (head == tail == nullptr)
 * - <T> front() - возврат указателя на первый элемент (Node* head)
 * - void pop() - удаление первого элемента
 * - void push(const& <T>) - добавление нового элемента в конец
 * int size() - возвращает количество элементов в очереди
 * - операторы ==, !=, >, <, <=, >= сравнивают 2 стека лексикографически
 */
/*
 Пример для оператора >:

template <class T>
bool operator>(std::queue<T> queue1, std::queue<T> queue2) {
 while (!queue1.empty() && queue2.empty()) {
	 if (queue1.front() <= queue2.front()) {
		 return false;
	 }
	 queue1.pop();
	 queue2.pop();
 }
 if (!queue1.empty()) { return true; }
 else { return false; }
}
*/
void print(std::queue<int> queue) {
	while (!queue.empty()) {
		std::cout << queue.front() << ' ';
		queue.pop();
	}
	std::cout << std::endl;
}
int main() {
	setlocale(LC_ALL, "rus");

	std::queue<int> queue; // Инициализация очереди
	int n = 10;
	std::cout << "Проверяем, что очередь пуста (empty): " << queue.empty() << std::endl;
	// Заполнение очереди
	for (int i = 0; i < n; ++i) {
		queue.push(rand() % 99 - 50);
	}
	std::cout << "Очередь после заполнения (push):\n\t"; print(queue);
	std::cout << "Проверяем, что очередь не пуста (empty): " << queue.empty() << std::endl;

	std::cout << "\nfront()\tsize()\tprint()\n";
	for (int i = 0; i < n; ++i) {
		std::cout << queue.front() << '\t' << queue.size() << '\t'; print(queue);
		queue.pop();
	}

	return 0;
}
/*
Test:

Проверяем, что очередь пуста (empty): 1
Очередь после заполнения (push):
		-9 3 47 17 12 32 43 4 -16 -39
Проверяем, что очередь не пуста (empty): 0

front() size()  print()
-9      10      -9 3 47 17 12 32 43 4 -16 -39
3       9       3 47 17 12 32 43 4 -16 -39
47      8       47 17 12 32 43 4 -16 -39
17      7       17 12 32 43 4 -16 -39
12      6       12 32 43 4 -16 -39
32      5       32 43 4 -16 -39
43      4       43 4 -16 -39
4       3       4 -16 -39
-16     2       -16 -39
-39     1       -39
*/
