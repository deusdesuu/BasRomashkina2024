// Мячин Валентин БАС-2024-2
/*
	/b/derevo
	root: 1-2n nodes
	page: n-2n nodes
	perfectly balanced tree

	if page has k nodes
	then it has k + 1 descendants
*/
#include <iostream>
#include <fstream>
#include <locale>
#include <random>


struct Page;
struct Node;
struct Node_list;
struct BTree;
int Node_list_add(Node_list*&, int);
void print(Node_list*);
void print(Page*);
void print(BTree*);
void BTree_add(BTree*, int);
void BTree_split(BTree*, Page*);
void BTree_delete(BTree*, int);
void BTree_delete_leaf(BTree*, Page*, Node_list*);

void clear(Page*);
void clear(Node*);
void clear(Node_list*);
void clear(BTree*);
// страница
struct Page {
	short count = 0; // кол-во вершин на странице
	Node_list* nodes = nullptr; // список под вершины
	Page* p0 = nullptr;
	Page* parent = nullptr;
};
// узел с числом
struct Node {
	int value;
	Page* child = nullptr; // правый потомок вершины
	int count = 1; // сколько раз встретился ключ
};
// список для хранения узлов
struct Node_list {
	Node* value = nullptr;
	Node_list* next = nullptr;
};
// дерево
struct BTree {
	Page* root = nullptr;
	int height;
	int node_limit;
};
int Node_list_add(Node_list*& root, int value) {
	/*
		список пуст только когда дерево пусто
	*/
	if (root == nullptr) {
		Node* new_node = new Node;
		(*new_node).value = value;

		Node_list* new_node_list = new Node_list;
		(*new_node_list).value = new_node;

		root = new_node_list;
	}
	else {
		Node_list* current = root;
		// вставка в начало
		if (value < (*(*current).value).value) {
			Node* new_node = new Node;
			(*new_node).value = value;

			Node_list* new_node_list = new Node_list;
			(*new_node_list).value = new_node;

			(*new_node_list).next = current;
			root = new_node_list;
		}
		else {
			/*
				пока справа меньше (для упорядочивания)
				и пока справа не пусто
				идем по списку
			*/
			while (
				((*current).next != nullptr) &&
				((*(*(*current).next).value).value <= value)
				) {
				current = (*current).next;
			}
			/*
				если совпали значения, то просто увеличиваем счетчик
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
	}
	return 1;
}
void print(Node_list* list) {
	Node_list* current = list;
	while (current != nullptr) {
		std::cout << (*(*current).value).value << "(" << (*(*current).value).count << ") ";
		current = (*current).next;
	}
	std::cout << std::endl;
}
void print(Page* page, int level) {
	if ((*page).p0 != nullptr) {
		print((*page).p0, level + 1);
		Node_list* current = (*page).nodes;
		while (current != nullptr) {
			print((*(*current).value).child, level + 1);
			current = (*current).next;
		}
	}
	std::cout << "level: " << level << ", nodes: ";
	print((*page).nodes);
}
void print(BTree* tree) {
	/*
		вызов обратным обходом(?)
		сначала все детишки
		потом вершина
	*/
	std::cout << "B-дерево:\n";
	print((*tree).root, 0);
}
void BTree_add(BTree* tree, int value) {
	if ((*tree).root == nullptr) {
		(*tree).root = new Page;
		(*(*tree).root).count += Node_list_add((*(*tree).root).nodes, value);
		return;
	}
	// идем по дереву до нужной страницы
	Page* current = (*tree).root;
	Node_list* current_node = nullptr;
	while (true) {
		// дошли ли до листа?
		if ((*current).p0 == nullptr) {
			break;
		}
		/*
			идем или в p0 (if)
			или по вершине из списка (else)
		*/
		if (value < (*(*(*current).nodes).value).value) {
			current = (*current).p0;
		}
		else {
			// идем по списку, ищем по какой вершине уйти глубже
			current_node = (*current).nodes;
			while (
				(*current_node).next != nullptr &&
				(*(*(*current_node).next).value).value <= value) {
				current_node = (*current_node).next;
			}
			// если встретили элемент, который уже есть
			if ((*(*current_node).value).value == value) {
				++(*(*current_node).value).count;
				return;
			}
			// спускаемся на уровень ниже
			current = (*(*current_node).value).child;
		}
	}
	// увеличиваем счетчик вершин на странице
	// если их 2 * height + 1, то расщепляем страницу
	(*current).count += Node_list_add((*current).nodes, value);
	if ((*current).count > (*tree).node_limit) {
		BTree_split(tree, current);
	}
}
void BTree_split(BTree* tree, Page* current) {
	Node_list* left = (*current).nodes;
	Node_list* list_current = left;
	Node_list* center = nullptr;
	Node_list* right = nullptr;
	// идем до предцентрального элемента
	for (int i = 0; i < (*tree).height - 1; ++i) {
		list_current = (*list_current).next;
	}
	// фиксируем центральный элемент
	// и часть списка справа от него
	center = (*list_current).next;
	right = (*center).next;
	// делим список пополам
	(*list_current).next = nullptr;
	(*center).next = nullptr;
	/*
		центр поднять на уровень выше
		правый справа от центрального
		левый остается на месте, current не трогаем
	*/
	// делим корень
	if ((*current).parent == nullptr) {
		Page* new_root_page = new Page;
		Page* new_right_page = new Page;
		// привязали правую страницу
		(*new_right_page).count = (*tree).height;
		(*new_right_page).parent = new_root_page;
		(*new_right_page).nodes = right;
		(*new_right_page).p0 = (*(*center).value).child;
		(*(*center).value).child = new_right_page;
		// редактируем левую страницу
		(*current).count = (*tree).height;
		(*current).parent = new_root_page;
		// заполняем новую корневую вершину
		(*new_root_page).count = 1;
		(*new_root_page).p0 = current;
		(*new_root_page).nodes = new Node_list;
		(*new_root_page).nodes = center;
		(*tree).root = new_root_page;
	}
	else {
		/*
			с правой страницей так же как с корнем
			центральную надо поднять наверх
			найти для нее место
			левая остается там же где и была
		*/
		Page* new_right_page = new Page;
		// привязали правую страницу
		(*new_right_page).count = (*tree).height;
		(*new_right_page).parent = (*current).parent;
		(*new_right_page).nodes = right;
		(*new_right_page).p0 = (*(*center).value).child;
		(*(*center).value).child = new_right_page;
		// редактируем левую страницу
		(*current).count = (*tree).height;
		// ищем место для центра в родительской вершине
		Node_list* parent_list = (*(*current).parent).nodes;
		Node_list* assign_to = nullptr;
		while (
			parent_list != nullptr &&
			(*(*parent_list).value).value < (*(*center).value).value
			) {
			assign_to = parent_list;
			parent_list = (*parent_list).next;
		}
		// assign_to == 0 -> центральная вершина становится новым началом списка
		if (assign_to == nullptr) {
			(*center).next = parent_list;
			(*(*current).parent).nodes = center;
		}
		// assign_to != 0 -> привязываем центральную куда-то в список
		else {
			(*center).next = (*assign_to).next;
			(*assign_to).next = center;
		}
		++(*(*current).parent).count;
		// мини рекурсия, если нужно несколько раз делить страницу
		// (если после расщепления страницы в родительской вершине стало (2 * height + 1 вершин) )
		if ((*(*current).parent).count > (*tree).node_limit) {
			BTree_split(tree, (*current).parent);
		}
	}
}
void BTree_delete(BTree* tree, int value) {
    // Ищем вершину в дереве
    Page* current = (*tree).root;
    if (current == 0) {
        return;
    }
    Node_list* current_node = nullptr;
    bool flag = true;
	while (flag) {
		/*
			идем или в p0 (if)
			или по вершине из списка (else)
		*/
		if (value < (*(*(*current).nodes).value).value) {
			current = (*current).p0;
		}
		else {
			// идем по списку, ищем по какой вершине уйти глубже
			current_node = (*current).nodes;
			while (
				(*current_node).next != nullptr &&
				(*(*(*current_node).next).value).value <= value) {
				current_node = (*current_node).next;
			}
			// Если нашли искомый элемент
			if ((*(*current_node).value).value == value) {
                flag = false;
				break;
			}
			// спускаемся на уровень ниже
			current = (*(*current_node).value).child;
		}
	}
	// Если не нашли вершину в дереве
	if (flag) {
        return;
	}
	if ((*current).p0 == 0) {
        BTree_delete_leaf(tree, current, current_node);
	}
}
void BTree_delete_leaf(BTree* tree, Page* page, Node_list* to_delete) {
    /*
    Удаление листа:
        1) (*page).count > (*tree).height:
            - вершина в начале списка - (*page).nodes = (*(*page).nodes).next;
            - вершина в середине / конце списка - (*current).next = (*to_delete).next;
            --(*page).count;
    */
    if ((*page).count > (*tree).height) {
        if (to_delete == (*page).nodes) {
            (*page).nodes = (*(*page).nodes).next;
        }
        else {
            Node_list* current = (*page).nodes;
            while ((*current).next != to_delete) {
                current = (*current).next;
            }
            (*current).next = (*to_delete).next;
        }
        delete to_delete;
        return;
    }

    return;
}
int main() {
	setlocale(LC_ALL, "rus");
	srand(time(0));

	std::ifstream input("text.txt");
	BTree* tree = new BTree;
	// Устанавливаем значение высоты для дерева
	// В соответствии с тем сколько вершин должно в него поместиться
	int n;
	input >> (*tree).height;
	(*tree).node_limit = (*tree).height * 2;
	// Заполнение дерева
	while (input >> n) {
		BTree_add(tree, n);
	}
	// Вывод дерева
	print(tree);
	BTree_delete(tree, 100);
	print(tree);

	// Чистим память
	clear(tree);
	return 0;
}

void clear(Node* node) {
	if ((*node).child != nullptr) {
		clear((*node).child);
	}
	delete node;
}
void clear(Page* page) {
	if ((*page).p0 != nullptr) {
		clear((*page).p0);
	}
	clear((*page).nodes);
	if ((*page).p0 == nullptr) {
		delete (*page).p0;
	}
	delete page;
}
void clear(Node_list* node_list) {
	Node_list* last = nullptr;
	Node_list* current = node_list;
	while (current != nullptr) {
		last = current;
		current = (*current).next;
		clear((*last).value);
		(*last).next = nullptr;
		delete last;
	}
}
void clear(BTree* tree) {
	clear((*tree).root);
	delete tree;
}
/*
Test 1 (10 узлов):
Введите количество вершин в дереве: 10
Введите вершины дерева через пробел:
		0 1 2 3 4 5 6 7 8 9
B-дерево:
level: 1, nodes: 0(1) 1(1)
level: 1, nodes: 3(1) 4(1)
level: 1, nodes: 6(1) 7(1) 8(1) 9(1)
level: 0, nodes: 2(1) 5(1)

Test 2 (19 узлов):
19
13 7 24 16 1 10 14 18 25 3 4 11 15 22 20 21 26 5 6

Введите количество вершин в дереве: 19
Введите вершины дерева через пробел:
		13 7 24 16 1 10 14 18 25 3 4 11 15 22 20 21 26 5 6
B-дерево:
level: 2, nodes: 1(1) 3(1)
level: 2, nodes: 5(1) 6(1)
level: 2, nodes: 10(1) 11(1)
level: 1, nodes: 4(1) 7(1)
level: 2, nodes: 14(1) 15(1) 16(1)
level: 2, nodes: 20(1) 21(1)
level: 2, nodes: 24(1) 25(1) 26(1)
level: 1, nodes: 18(1) 22(1)
level: 0, nodes: 13(1)
*/
