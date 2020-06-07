#include "../headers/Childn.h"
#include <iostream>

Childn::Childn(XMLParser& xml)
	: XMLOperation(xml, "child") {};


void Childn::execute() {
	std::string id;
    int n;

	std::cin >> id >> n;

    Node* searched_node = xml.recursive_search(xml.get_parent(), id);

    if (searched_node == nullptr) {
        throw XMLException("No node with this id can be found!");
    }

    if(!(searched_node -> has_children())) {
        throw XMLException("The node with this id has no children!");
    }

    std::vector<Node*> children = searched_node->get_children();

    if(children.size() < n) {
        throw XMLException("The node doesnt have that much children!");
    }

    Node* nth_nod = children[n];
    std::cout << "Node " << nth_nod->get_name() << " with id " << nth_nod->get_id() << std::endl;

}
