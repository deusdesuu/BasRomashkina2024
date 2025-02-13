// Мячин Валентин БАС2
#include <iostream>
#include <locale>
/*
 * Определяем значение INF
 * Для инициализации начального значения value в Node
 */
/*
 * Как вариант можно сделать список с пустым нулевым элементом
 * Тогда INF не будет нужен
 */
#define INF 2147483647

struct Node {
	int value = INF;
	Node* next = nullptr;
};
void add(Node* node, int value) {
	/*
	 * Если список пустой
	 * То меняем значение первого элемента
	 * Иначе идем до конечного элемента списка
	 * И добавляем элемент в конец
	 */
	if ((*node).value == INF) {
		(*node).value = value;
	} else {
		Node* current = node;
		while ((*current).next != nullptr) {
			current = (*current).next;
		}
		Node* new_node = new(Node);
		(*new_node).value = value;
		(*new_node).next = nullptr;
		(*current).next = new_node;
	}
}
void delete_first(Node* node) {
	/*
	 * Если список пустой, то не делаем ничего
	 * (можно сделать raise exception
	 * Если один элемент, то в значение ставим INF
	 * Если больше, то значение и указатель на следующий элемент подтягиваем
	 * Из второго элемента, освобождаем память из под второго элемента
	 */
	if ((*node).value == INF) {}
	else if ((*node).next == nullptr) { (*node).value = INF; }
	else {
		(*node).value = (*(*node).next).value;
		Node* tmp = (*node).next;
		(*node).next = (*(*node).next).next;
		delete(tmp);
	}
	
}
void print(Node* node) {
	/*
	 * Пока указатель на элемент списка ненулевой
	 * Выводим значение элемента в консоль
	 */
	if ((*node).value != INF) {
		std::cout << "Значение\tАдрес\t\t\tАдрес следующего\n";
		Node* current = node;
		while (current != nullptr) {
			std::cout << (*current).value << "\t\t" << current << "\t" << (*current).next << '\n';
			current = (*current).next;
		}
		std::cout << std::endl;
	}
	else {
		std::cout << "Список пуст!" << std::endl;
	}
}
int main() {
	setlocale(LC_ALL, "rus");

	int n;
	std::cout << "n = "; std::cin >> n;

	Node* node = new(Node);
	std::cout << "Введите " << n << " элементов списка:\n";
	int value;
	for (int i = 0; i < n; ++i) {
		std::cin >> value;
		add(node, value);
	}
	std::cout << "\nИсходный список:\n";
	print(node);

	std::cout << "\nСписок после удаления первого элемента:\n";
	delete_first(node);
	print(node);

	std::cout << "\nСписок после удаления второго элемента:\n";
	delete_first(node);
	print(node);

	//доделать деструктор класса

	return 0;
}
/*
Test:

n = 5
Введите 5 элементов списка:
1 2 3 4 5

Исходный список:
Значение        Адрес                   Адрес следующего
1               0000014618E89070        0000014618E71AD0
2               0000014618E71AD0        0000014618E719E0
3               0000014618E719E0        0000014618E71B20
4               0000014618E71B20        0000014618E725C0
5               0000014618E725C0        0000000000000000


Список после удаления первого элемента:
Значение        Адрес                   Адрес следующего
2               0000014618E89070        0000014618E719E0
3               0000014618E719E0        0000014618E71B20
4               0000014618E71B20        0000014618E725C0
5               0000014618E725C0        0000000000000000


Список после удаления второго элемента:
Значение        Адрес                   Адрес следующего
3               0000014618E89070        0000014618E71B20
4               0000014618E71B20        0000014618E725C0
5               0000014618E725C0        0000000000000000
*/
