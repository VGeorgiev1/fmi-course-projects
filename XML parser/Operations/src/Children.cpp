#include "../headers/Children.h"
#include <iostream>

Children::Children(XMLParser& xml)
    : XMLOperation(xml, "children") {};


void Children::execute() {
    std::string id;

    std::cin >> id;

    Node* searched_node = xml.recursive_search(xml.get_parent(), id);

    if (searched_node == nullptr) {
        throw XMLException("No node with this id can be found!");
    }

    if (!(searched_node->has_children())) {
        throw XMLException("The node with this id has no children!");
    }

    std::vector<Node*> children = searched_node->get_children();

    for (std::vector<Node*>::iterator it = children.begin(); it != children.end(); ++it) {
        std::vector<Attribute> attrs = (*it)->get_attributes();
        std::cout << (*it)->get_name() << ": " << std::endl;

        for (std::vector<Attribute>::iterator at = attrs.begin(); at != attrs.end(); ++at) {
            std::cout << "Attribute " << at->get_name() << ", value: " << at->get_value() << std::endl;
        }

        
    }

}
