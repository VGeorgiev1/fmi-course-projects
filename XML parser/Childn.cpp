#include "Childn.h"
#include <iostream>


Childn::Childn(Node* h)
	: XMLOperation(h, "child") {};


void Childn::execute() {
	std::string id;
    int n;

	std::cin >> id >> n;

    Node* searched_node = recursive_search(parent_node, id);

    if(!(searched_node -> has_children())) {
        std::cout << "The node with this id has no children!" << std::endl;
    }

    std::vector<Node*> children = searched_node->get_children();

    if(children.size() < n) {
        std::cout << "The node doesnt have that much children!" << std::endl;
    }

    Node* nth_nod = children[n];
    std::cout << "Node " << nth_nod->get_name() << " with id " << nth_nod->get_id() << std::endl;

}
