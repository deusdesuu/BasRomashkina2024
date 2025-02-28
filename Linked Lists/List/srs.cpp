// Мячин Валентин БАС2
#include <iostream>
#include <locale>
#include <random>


/*
 * Первый элемент списка - главный, к которому привязаны все остальные
 */
/*
 * В программе реализованы как обычный вывод в консоль
 * Так и вывод с адресами, как в аудиторной, поэтому в любой момент можно поменять
 */
/*
 * В ТЗ не указано после какого максимального значения удалять элементы
 * Поэтому удалять будем после первого встреченного максимума
 */
struct Node {
	int value;
	Node* next = nullptr;
};
void add(Node*, int); // Добавление элемента в конец
void print(Node*); // Вывод на экран
void print_with_addresses(Node*); // Вывод на экран с адресами
int max(Node*); // Нахождение максимума списка
void del(Node*&); // Удаление элемента списка
void delete_n_after_max(Node*, int, int); // Удаление n элементов после максимума

int main() {
	setlocale(LC_ALL, "rus");
	srand(time(0));

	Node* node = new(Node); // инициализация первого элемента списка
	int n;
	std::cout << "n = "; std::cin >> n;

	for (int i = 0; i < n; ++i) {
		add(node, rand() % 10);
	}
	std::cout << "\nИсходный список:\n";
	print(node);

	int max_value = max(node);

	std::cout << "\nМаксимальный элемент списка: " << max_value << std::endl;
	delete_n_after_max(node, max_value, 3);

	std::cout << "\nСписок после удаление 3-ех элементов после максимального:\n";
	print(node);

	return 0;
}
void add(Node* node, int value) {
	/*
	 * Идем по списку, пока указатель на следующий
	 * Элемент не будет нулевым
	 * Создаем новый элемент с указанным значением
	 * Меняем указатель последнего элемента на следующий
	 * На созданный
	 */
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
		std::cout << "Список пуст!\n" << std::endl;
	}
	else {
		Node* current = (*node).next;
		while (current != nullptr) {
			std::cout << (*current).value << ' ';
			current = (*current).next;
		}
		std::cout << std::endl;
	}
}
void print_with_addresses(Node* node) {
	/*
	 * Пока указатель на элемент списка ненулевой
	 * Выводим значение элемента и адреса в консоль
	 */
	if ((*node).next == nullptr) {
		std::cout << "Список пуст!\n" << std::endl;
	}
	else {
		std::cout << "\nЗначение\tАдрес\t\t\tАдрес следующего\n";
		Node* current = (*node).next;
		while (current != nullptr) {
			std::cout << (*current).value << "\t\t" << current << "\t" << (*current).next << '\n';
			current = (*current).next;
		}
		std::cout << std::endl;
	}
}
void del(Node*& node) {
	/*
	 * Если node - последний элемент списка,
	 * То освобождаем память и меняем указатель на node на nullptr
	 * Иначе подтягиваем переменные следующего элемента в node
	 * И освобождаем память из под следующего элемента
	 */
	if ((*node).next == nullptr) {
		delete node;
		node = nullptr;
	}
	else {
		Node* tmp = (*node).next;
		(*node).value = (*(*node).next).value;
		(*node).next = (*(*node).next).next;
		delete tmp;
	}
}
int max(Node* node) {
	/*
	 * Идем по элементам списка и сравниваем значение элементов с max
	 * Начальное значение max - 0
	 * Поэтому если список пуст / все элементы списка отрицательные
	 * То будет возвращен 0
	 */
	int max = 0;
	if ((*node).next != nullptr) {
		Node* current = (*node).next;
		while (current != nullptr) {
			if ((*current).value > max) {
				max = (*current).value;
			}
			current = (*current).next;
		}
	}
	return max;
}
void delete_n_after_max(Node* node, int max_value, int n) {
	Node* current = (*node).next;
	// Идем по элементам списка до первого максимума
	while (current != nullptr && (*current).value != max_value) {
		current = (*current).next;
	}
	// Удаляем n элементов после максимума
	for (int i = 0; i < n; ++i) {
		if ((*current).next == nullptr) { break; }
		del((*current).next);
	}
}
/*
Test 1:

n = 10

Исходный список:
1 7 4 0 9 4 8 8 2 4

Максимальный элемент списка: 9

Список после удаление 3-ех элементов после максимального:
1 7 4 0 9 2 4
----------------------------------------------------------
Test 2:

n = 5

Исходный список:
8 7 4 9 2

Максимальный элемент списка: 9

Список после удаление 3-ех элементов после максимального:
8 7 4 9
 */
