#include "Set.h"


Set::Set(Node& h)
	: XMLOperation(h, "set") {};

void Set::execute() {
	std::string id, key, new_value;

	std::cin >> id >> key >> new_value;

	recursive_search(parent_node, id, key, new_value);
}

void Set::recursive_search(Node n, std::string id, std::string key, std::string new_value) {

	Attribute* atr = n.get_attribute(key);

	if(n.get_id() == id && atr != nullptr) {
		atr->set_value(new_value);
        std::cout << "Node " << n.get_name() << ", attribute: " << atr->get_name() << " now has value: " << atr->get_value();
	}

	if(!n.has_children()) {
		return;
	}

	std::vector<Node> children = n.get_children();

	for(std::vector<Node>::iterator it = children.begin(); it != children.end(); ++it) {
		recursive_search(*it, id, key, new_value);
	}

	return;

}
