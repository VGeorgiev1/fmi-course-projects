#include "../headers/Set.h"


Set::Set(XMLParser& xml)
	: XMLOperation(xml, "set") {};

void Set::execute() {
	std::string id, key, new_value;

	std::cin >> id >> key >> new_value;

	Node* n = xml.recursive_search(xml.get_parent(), id);

	Attribute* atr = n->get_attribute(key);

	if (atr != nullptr) {
		atr->set_value(new_value);
		std::cout << "Node " << n->get_name() << ", attribute: " << atr->get_name() << " now has value: " << atr->get_value() << std::endl;
		return;
	}

	n->add_attribute(key, new_value);
	return;
}

