/*
	/b/derevo
	root: 1-2n nodes
	page: n-2n nodes
	perfectly balanced tree

	if page has k nodes
	then it has k + 1 descendants
*/
#include <iostream>
#include <locale>
#include <random>

struct Page;
struct Node;
struct Node_list;

// страница
struct Page {
	short count; // кол-во вершин на странице
	Node_list* nodes = nullptr; // массив под вершины
	Page* p0;
};
// узел с числом
struct Node {
	int value;
	Page* child = nullptr; // правый потомок вершины
	int count = 1; // сколько раз встретился ключ
};
// список для хранения узлов
struct Node_list {
	Node* value;
	Node_list* next = nullptr;
};
/*
	список пуст только когда дерево пусто

*/
int Node_list_add(Node_list*& root, int value) {
	if (root == nullptr) {
		Node* new_node = new Node;
		(*new_node).value = value;

		Node_list* new_node_list = new Node_list;
		(*new_node_list).value = new_node;

		root = new_node_list;
	}
	else {
		Node_list* current = root;
		/*
			пока справа меньше (для упорядочивания)
			и пока справа не пусто
			идем
		*/
		while (
			((*current).next != nullptr) && 
			((*(*(*current).next).value).value <= value)
			)  {
			current = (*current).next;
		}
		/*
			если совпали значение, то просто увеличиваем счетчик
			встреченной вершины
		*/
		if ((*(*current).value).value == value) {
			++(*(*current).value).count;
			return 0; // чтобы дальше увеличить счетчик вершин на странице
		}
		/*
			создаем новую вершину
			и помещаем ее в список в порядке возрастания
		*/
		else {
			Node* new_node = new Node;
			(*new_node).value = value;

			Node_list* new_node_list = new Node_list;
			(*new_node_list).value = new_node;

			(*new_node_list).next = (*current).next;
			(*current).next = new_node_list;
		}
	}
	return 1;
}

struct BTree {
	Page* root;
	int height;
	int node_limit;
};
void BTree_add(BTree tree, int value) {

}
// Инициализируем вершины дерева
void BTree_init(BTree* tree) {

	return;
}

// nodes limit: 62_748_516
int find_height(int nodes) {
	int height = 0;
	int result = 0;
	int last = 0;

	while (nodes > result) {
		++height;
		result = 2 * height;
		last = result * (2 * height + 1);
		for (int i = 0; i < height; ++i) {
			result += last;
			last *= (2 * height + 1);
		}
	}
	return height;
}

int main() {
	setlocale(LC_ALL, "rus");
	srand(time(0));

	int n;
	std::cout << "Введите количество вершин в дереве: ";
	std::cin >> n;

	BTree* tree = new BTree;
	// Устанавливаем значение высоты для дерева
	// В соответствии с тем сколько вершин должно в него поместиться
	(*tree).height = find_height(n);
	(*tree).node_limit = (*tree).height * 2;
	// Начальная инициализация дерева
	BTree_init(tree);


	return 0;
}
