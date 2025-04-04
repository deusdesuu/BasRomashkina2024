// Мячин Валентин БАС2
#include <iostream>
#include <locale>
#include <random>


struct Node {
	int value;
	Node* left = nullptr;
	Node* right = nullptr;
};
void add(Node*& root, int value) {
	Node* new_node = new Node;
	(*new_node).value = value;

	if (root == nullptr) {
		root = new_node;
	}
	else {
		Node* current = root;
		while (true) {
			if (value == (*current).value) { break; }
			if (value < (*current).value) {
				if ((*current).left == nullptr) { (*current).left = new_node; break; }
				else { current = (*current).left; }
			}
			else {
				if ((*current).right == nullptr) { (*current).right = new_node; break; }
				else { current = (*current).right; }
			}
		}
	}
}
void print_symmetry(Node* root) {
	if (root != nullptr) {
		print_symmetry((*root).left);
		std::cout << (*root).value << ' ';
		print_symmetry((*root).right);
	}
}
void clear(Node*& root) {
	if (root != nullptr) {
		clear((*root).left);
		clear((*root).right);
		(*root).left = nullptr;
		(*root).right = nullptr;
		delete root;
		root = nullptr;
	}
}
// Идем по дереву вправо
// Пока не встретим nullptr
int max(Node*& root) {
	int result = -1;
	if (root == nullptr) { return result; }

	Node* current = root;
	while ((*current).right != nullptr) {
		current = (*current).right;
	}
	result = (*current).value;
	return result;
}
// Идем по дереву влево
// Пока не встретим nullptr
int min(Node*& root) {
	int result = -1;
	if (root == nullptr) { return result; }

	Node* current = root;
	while ((*current).left != nullptr) {
		current = (*current).left;
	}
	result = (*current).value;
	return result;
}
Node* search(Node*& root, int value) {
	Node* current = root;
	int cur_val = (*current).value;
	while (true) {
		if (cur_val == value) { break; }
		if (cur_val > value) { current = (*current).left; }
		else { current = (*current).right; }
		cur_val = (*current).value;
	}
	return current;
}
int next(Node* root, int value) {
	Node* current = root;
	Node* nxt = nullptr;
	while (current != nullptr) {
		if ((*current).value > value) {
			nxt = current;
			current = (*current).left;
		}
		else { current = (*current).right; }
	}
	if (!nxt) {
		std::cout << "Для заданного элемента дерева следующий элемент не найден!" << std::endl;
		return value;
	}
	int result = (*nxt).value;
	return result;
}
int prev(Node* root, int value) {
	Node* current = root;
	Node* prv = nullptr;
	while (current != nullptr) {
		if ((*current).value < value) {
			prv = current;
			current = (*current).right;
		}
		else { current = (*current).left; }
	}
	if (!prv) {
		std::cout << "Для заданного элемента дерева следующий элемент не найден!" << std::endl;
		return value;
	}
	int result = (*prv).value;
	return result;
}
void del_leaf(Node* parent, Node*& child, bool dir) {
    if (parent != nullptr) {
        if (dir) { (*parent).right = nullptr; }
        else { (*parent).left = nullptr; }
    }
    delete child;
    child = nullptr;
}
void del_right_child(Node* parent, Node*& child, bool dir) {
    if (parent != nullptr) {
        if (dir) { (*parent).right = (*child).right; }
        else { (*parent).left = (*child).right; }
    }
    (*child).right = nullptr;
    delete child;
    child = nullptr;
}
void del_left_child(Node* parent, Node*& child, bool dir) {
    if (parent != nullptr) {
        if (dir) { (*parent).right = (*child).left; }
        else { (*parent).left = (*child).left; }
    }
    (*child).left = nullptr;
    delete child;
    child = nullptr;
}
void del_two_childs(Node* parent, Node*& child, bool dir) {}

void del(Node* root, int value) {
    Node* prv = nullptr;
    Node* current = root;

    bool dir = 0; // 0 - left, 1 - right;

    int tree_side; // 0 - empty, 1 - left side, 2 - right side, 3 - root
    if (!current) { tree_side = 0; }
    else if ((*current).value == value) { tree_side = 3; }
    else if ((*current).value > value) { tree_side = 1; }
    else if ((*current).value < value) { tree_side = 2; }

    while (true) {
        if (!current) {
                std::cout << "Такого узла нет." << std::endl;
                break;
        }
        if ((*current).value == value) { break; }
        else {
            prv = current;
            if ((*current).value > value) {
                current = (*current).left;
                dir = 0;
            }
            else {
                current = (*current).right;
                dir = 1;
            }
        }
    }
    if (current) {
        bool f1, f2;
        f1 = (*current).left == nullptr;
        f2 = (*current).right == nullptr;

        if (tree_side == 1) { std::cout << "Удаление вершины левого поддерева.\n"; }
        else if (tree_side == 2) { std::cout << "Удаление вершины правого поддерева.\n"; }
        else if (tree_side == 3) { std::cout << "Удаление корня" << std::endl; }

        if (f1 && f2) {
                std::cout << "Листовая вершина." << std::endl;
                del_leaf(prv, current, dir);
        }
        if (f1 && !f2) {
                std::cout << "С одной правой вершиной." << std::endl;
                del_right_child(prv, current, dir);
        }
        if (!f1 && f2) {
                std::cout << "С одной левой вершиной." << std::endl;
                del_left_child(prv, current, dir);
        }
        if (!f1 && !f2) { del_two_childs(prv, current, dir); }
    }
}
int main() {
	setlocale(LC_ALL, "rus");
	srand(time(0));

	Node* root = nullptr;
	int n;
	std::cout << "n = "; std::cin >> n;

	int value;
	std::cout << "Введите элементы дерева:\n\t";
	for (int i = 0; i < n; ++i) {
		std::cin >> value;
		add(root, value);
	}

	std::cout << "Вывод дерева симметричным обходом:\n\t"; print_symmetry(root); std::cout << std::endl;
    /*
	std::cout << "min = " << min(root) << std::endl;
	std::cout << "max = " << max(root) << std::endl;
	std::cout << "Значение для которого будем искать предыдущее: "; std::cin >> value;
	int prv = prev(root, value);
	std::cout << "prev = " << prv << std::endl;
	*/
    std::cout << "value to delete: "; std::cin >> value;
    del(root, value);
    print_symmetry(root);

	clear(root);
	return 0;
}
