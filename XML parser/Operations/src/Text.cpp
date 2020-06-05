#include "../headers/Text.h"


Text::Text(XMLParser& xml)
	: XMLOperation(xml, "text") {};

void Text::execute() {
	std::string id;

	std::cin >> id;

	Node* n = xml.recursive_search(xml.get_parent(), id);

	std::string text = n->get_value();

	if (text.size() == 0) {
		std::cout << "Node with id " << id << " has no text inside." << std::endl;
		return;
	}

	std::cout << "Node with id " << id << " and name " << n->get_name() << " has text value: " << n->get_value() << std::endl;
	return;
}

