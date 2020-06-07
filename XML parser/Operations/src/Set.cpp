#include "../headers/Set.h"


Set::Set(XMLParser& xml)
	: XMLOperation(xml, "set") {};

void Set::execute() {
	std::string id, key, new_value;

	std::cin >> id >> key >> new_value;

	Node* n = xml.recursive_search(xml.get_parent(), id);

	if (n == nullptr) {
		throw XMLException("No node with this id can be found!");
	}

	Attribute* atr = n->get_attribute(key);

	if (atr == nullptr) {
		n->add_attribute(key, new_value);
		std::cout << "Node now has attribute " << key << " with value " << new_value<< std::endl;
		return;
	}

	atr->set_value(new_value);
	std::cout << "Node " << n->get_name() << ", attribute: " << atr->get_name() << " now has value: " << atr->get_value() << std::endl;
	return;
	
}

