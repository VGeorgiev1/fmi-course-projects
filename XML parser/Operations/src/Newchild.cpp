#include "../headers/Newchild.h"
#include <iostream>


Newchild::Newchild(XMLParser& xml)
	: XMLOperation(xml, "newchild") {};

void Newchild::execute() {
	std::string id;

	std::cin >> id;

	Node* n = xml.recursive_search(xml.get_parent(), id);

	if (n == nullptr) {
		throw XMLException("Node with this id cannot be found!");
	}

	n->add_child(new Node());

	std::cout << "Node with id " << id << " was added" << std::endl;
}