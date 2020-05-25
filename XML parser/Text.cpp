#include "Text.h"


Text::Text(Node* h)
	: XMLOperation(h, "text") {};

void Text::execute() {
	std::string id;

	std::cin >> id;

	Node* n = recursive_search(parent_node, id);

	std::string text = n->get_value();

	if (text.size() == 0) {
		std::cout << "Node with id " << id << " has no text inside." << std::endl;
		return;
	}

	std::cout << "Node with id " << id << " and name " << n->get_name() << " has text value: " << n->get_value() << std::endl;
	return;
}

