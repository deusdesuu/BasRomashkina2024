// Мячин Валентин БАС2
#include <iostream>
#include <locale>

/*
 * Идея:
 * В начале списка будет находиться пустой элемент без значения
 * Со ссылкой на первый элемент списка
 * Т.к. если не использовать такой "нулевой" элемент
 * То придется придумывать как определять что список пуст
 * Также это сильно упрощает написание кода
 */

struct Node {
	int value;
	Node* next = nullptr;
};
void add(Node* node, int value) {
	Node* current = node;
	while ((*current).next != nullptr) {
		current = (*current).next;
	}
	Node* new_node = new(Node);
	(*new_node).value = value;
	(*current).next = new_node;
}
void print(Node* node) {
	/*
	 * Пока указатель на элемент списка ненулевой
	 * Выводим значение элемента и адреса в консоль
	 */
	if ((*node).next == nullptr) {
		std::cout << "Список пуст!" << std::endl;
	}
	else {
		std::cout << "Значение\tАдрес\t\t\tАдрес следующего\n";
		Node* current = (*node).next;
		while (current != nullptr) {
			std::cout << (*current).value << "\t\t" << current << "\t" << (*current).next << '\n';
			current = (*current).next;
		}
		std::cout << std::endl;
	}
}
void delete_first(Node* node) {
	 /*
	 * Если список пустой, то не делаем ничего
	 * (можно сделать raise exception)
	 * Иначе подтягиваем значение и указатель из первого элемента в нулевой
	 * Освобождаем память из под 1-го элемента
	 */
	if ((*node).next == nullptr) {}
	else {
		(*node).value = (*(*node).next).value;
		Node* tmp = (*node).next;
		(*node).next = (*(*node).next).next;
		delete(tmp);
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
	
	//писать delete(node) нет смысла
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
1               0000027247472070        00000272474727F0
2               00000272474727F0        0000027247471A30
3               0000027247471A30        0000027247471A80
4               0000027247471A80        00000272474720C0
5               00000272474720C0        0000000000000000


Список после удаления первого элемента:
Значение        Адрес                   Адрес следующего
2               00000272474727F0        0000027247471A30
3               0000027247471A30        0000027247471A80
4               0000027247471A80        00000272474720C0
5               00000272474720C0        0000000000000000


Список после удаления второго элемента:
Значение        Адрес                   Адрес следующего
3               0000027247471A30        0000027247471A80
4               0000027247471A80        00000272474720C0
5               00000272474720C0        0000000000000000

*/
