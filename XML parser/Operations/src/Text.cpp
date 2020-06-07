#include "../headers/Text.h"


Text::Text(XMLParser& xml)
	: XMLOperation(xml, "text") {};

void Text::execute() {
	std::string id;

	std::cin >> id;

	Node* n = xml.recursive_search(xml.get_parent(), id);

	if (n == nullptr) {
		throw XMLException("Node with this id cannot be found!");
	}

	std::string text = n->get_value();

	if (text.size() == 0) {
		throw XMLException("Node with this id has no text inside");
	}

	std::cout << "Node with id " << id << " and name " << n->get_name() << " has text value: " << n->get_value() << std::endl;
}

