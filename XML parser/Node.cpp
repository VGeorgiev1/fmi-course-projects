#include "Attribute.h"
#include "Node.h"

Node::Node() {}

Node::Node(std::string name) : name(name) {}

void Node::set_value(std::string value) {
    this->value += value;
}

void Node::set_name(std::string name) {
    this->name = name;
}
std::string Node::get_name() {
    return name;
}

std::string Node::get_value() {
    return value;
}

void Node::set_id(std::string id) {
    this->id = id;
}

std::string Node::get_id() {
    return id;
}

void Node::add_child(Node node) {
    children.push_back(node);
}

bool Node::has_children() {
    return children.size() > 0;
}

std::vector<Node> Node::get_children() {
    return children;
}

void Node::add_attribute(std::string name, std::string value) {
    attibutes.push_back(Attribute(name, value));
}

std::vector<Attribute> Node::get_attributes() {
    return attibutes;
}

Attribute Node::get_attribute(std::string name) {
    std::vector<Attribute>::iterator it;
    for (it = attibutes.begin(); it != attibutes.end(); ++it) {
        if (name.compare(it->get_name())) {
            return *it;
            break;
        }
    }
    std::cout << "Iterator not found!";
}