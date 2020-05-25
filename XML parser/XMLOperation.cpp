#include "XMLOperation.h"


XMLOperation::XMLOperation(Node* node, std::string name)
	: Operation(name), parent_node(node) {};

Node* const & XMLOperation::recursive_search(Node* const &n, std::string id) {
    if (n->get_id() == id) {
        return n;
    }

    if (!n->has_children()) {
        return nullptr;
    }

    std::vector<Node* > children = n->get_children();

    for (std::vector<Node*>::iterator it = children.begin(); it != children.end(); ++it) {
        Node* temp = recursive_search((*it), id);

        if (temp != nullptr) {
            return temp;
        }
    }

    return nullptr;
}