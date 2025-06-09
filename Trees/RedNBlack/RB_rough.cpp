/*
	корень - черный
	листья - черные
	у красной вершины - 2 черных потомка
	пути от любого узла к его вершинам должны иметь одинаковое кол-во черных вершин
*/
#include <iostream>
#include <random>


struct Node {
	int value;
	bool color = 0; // 0 - red, 1 - black
	int count = 0;
	Node* left = nullptr;
	Node* right = nullptr;
};
void add(Node*&, int);
void print(Node*);
void check_balance(Node*&, Node*&, Node*&, Node*&, Node*&);
void rotate_left(Node*&, Node*&, Node*&, Node*&);
void rotate_right(Node*&, Node*&, Node*&, Node*&);

void add(Node*& root, int value) {
	Node* new_node = new Node;
	(*new_node).value = value;

	if (root == nullptr) {
		(*new_node).color = 1;
		root = new_node;
		return;
	}
	Node* current = root;
	Node* father = nullptr;
	Node* grand = nullptr;

	while (true) {
		if ((*current).value == value) {
			delete new_node;
			++(*current).count;
			return;
		}
		if ((*current).value < value) {
			if ((*current).right == nullptr) {
				(*current).right = new_node;
				check_balance(grand, father, current, new_node, root);
				return;
			}
			grand = father;
			father = current;
			current = (*current).right;
		}
		else {
			if ((*current).left == nullptr) {
				(*current).left = new_node;
				check_balance(grand, father, current, new_node, root);
				return;
			}
			grand = father;
			father = current;
			current = (*current).left;
		}
	}
}
void print(Node* node) {
	if (node != nullptr) {
		std::cout << (*node).value << '(';
		if ((*node).color) { std::cout << 'b'; }
		else { std::cout << 'r'; }
		std::cout << ") ";
		print((*node).left);
		print((*node).right);
	}
	else {
		std::cout << "\\0 ";
	}
}
void check_balance(Node*& ggrand, Node*& grand, Node*& father, Node*& current, Node*& root) {
	// черный отец (o no)
	if ((*father).color) {
		return;
	}
	Node* uncle;
	if (father == (*grand).left) {
		uncle = (*grand).right;
	}
	else {
		uncle = (*grand).left;
	}
	if (uncle != nullptr && (*uncle).color == 0) {
		(*grand).color = 0;
		(*father).color = 1;
		(*uncle).color = 1;
	}
	else {
		if (uncle == (*grand).right) {
			rotate_right(grand, father, uncle, current);
			if (ggrand == nullptr) {
				root = father;
			}
			else {
				if ((*ggrand).right == grand) {
					((*ggrand).right = father);
				}
				else {
					((*ggrand).left = father);
				}
			}
		}
		else {
			rotate_left(grand, father, uncle, current);
			if (ggrand == nullptr) {
				root = father;
			}
			else {
				if ((*ggrand).right == grand) {
					((*ggrand).right = father);
				}
				else {
					((*ggrand).left = father);
				}
			}
		}
	}
	(*root).color = 1;
}
void rotate_right(Node*& grand, Node*& father, Node*& uncle, Node*& current) {
	Node* buff;
	if (current == (*father).right) {
		(*grand).left = current;
		(*father).right = (*current).left;
		(*current).left = father;
		buff = father;
		father = current;
		current = buff;
	}
	(*grand).color = 0;
	(*father).color = 1;
	(*grand).left = (*father).right;
	(*father).right = grand;
}
void rotate_left(Node*& grand, Node*& father, Node*& uncle, Node*& current) {
	std::cout << "rotating thing\n";
	Node* buff;
	print(grand);
	std::cout << '\n';
	if (current == (*father).left) {
		(*grand).right = current;
		(*father).left = (*current).right;
		(*current).right = father;
		buff = father;
		father = current;
		current = buff;
	}
	print(grand);
	std::cout << '\n';
	(*grand).color = 0;
	(*father).color = 1;
	(*grand).right = (*father).left;
	(*father).left = grand;
}
int main() {
	Node* root = nullptr;
	int value;
	for (int i = 0; i < 15; ++i) {
		value = rand() % 30;
		std::cout << value << std::endl;
		add(root, value);
		print(root);
		std::cout << '\n';
	}
	//print(root);
	std::cout << std::endl;
	return 0;
}
