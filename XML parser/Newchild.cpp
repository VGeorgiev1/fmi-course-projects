#include "Newchild.h"
#include <iostream>


Newchild::Newchild(Node* h)
	: XMLOperation(h, "newchild") {};

void Newchild::execute() {
	std::string id, key;

	std::cin >> id >> key;

	Node* n = recursive_search(parent_node, id);

	n->add_child(new Node());

	return;
}