#include "Childn.h"
#include <iostream>


Childn::Childn(Node& h)
	: XMLOperation(h, "child") {};

Node* Childn::recursive_search(Node* n, std::string id) {

    if(n -> get_id() == id) {
        return n;
    }

    if(!n -> has_children()) {
        return nullptr;
    }

    std::vector<Node> children = n -> get_children();

    Node* found = nullptr;

	for(std::vector<Node>::iterator it = children.begin(); it != children.end(); ++it) {
        Node* temp = recursive_search(&(*it) , id);

        if(temp != nullptr) {
            found = temp;
            break;
        }
	}

    return found;
}

void Childn::execute() {
	std::string id;
    int n;

	std::cin >> id >> n;

    Node* searched_node = recursive_search(&parent_node, id);

    if(!(searched_node -> has_children())) {
        std::cout << "The node with this id has no children!" << std::endl;
    }

    std::vector<Node> children = searched_node->get_children();

    if(children.size() < n) {
        std::cout << "The node doesnt have that much children!" << std::endl;
    }

    Node nth_nod = children[n];
    std::cout << "Node " << nth_nod.get_name() << " " << nth_nod.get_id() << std::endl;

}
