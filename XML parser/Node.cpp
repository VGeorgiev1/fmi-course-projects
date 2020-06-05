#include "Attribute.h"
#include "Node.h"

Node::Node() :name(""), value(""), id("") {}

Node::Node(std::string name) : name(name), value(""), id("") {}

void Node::set_value(std::string value) {
    this->value += value;
}

void Node::set_name(std::string name) {
    this->name = name;
}
std::string& Node::get_name() {
    return name;
}

std::string& Node::get_value() {
    return value;
}

void Node::set_id(std::string id) {
    this->id = id;
}

std::string& Node::get_id() {
    return id;
}

void Node::add_child(Node* node) {
    children.push_back(node);
}

bool Node::has_children() {
    return children.size() > 0;
}

std::vector<Node*> Node::get_children() {
    return children;
}

void Node::add_attribute(std::string name, std::string value) {
    attibutes.push_back(Attribute(name, value));
}

std::vector<Attribute> Node::get_attributes() {
    return attibutes;
}

Attribute* Node::get_attribute(std::string name) {
    for (std::vector<Attribute>::iterator it = attibutes.begin(); it != attibutes.end(); ++it) {
        if (name == it->get_name()) {
            return &(*it);
            break;
        }
    }
    return nullptr;
}

bool Node::remove_attribute(std::string name) {
    for (std::vector<Attribute>::iterator it = attibutes.begin(); it != attibutes.end(); ++it) {
        if (name == it->get_name()) {
            attibutes.erase(it);
            return true;
            break;
        }
    }
    return false;
};