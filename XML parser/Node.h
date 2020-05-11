#ifndef NODE_H
#define NODE_H
#include <string>
#include "Attribute.h"
#include <vector>
#include <iostream>

class Node {
private:
    std::string id;
    std::string value = "";
    std::string name;
    std::vector<Attribute> attibutes;
    std::vector<Node> children;
public:
    Node();
    Node(std::string name);
    std::string get_name();
    std::string get_value();
    std::string get_id();
    void set_id(std::string id);
    void set_value(std::string value);
    void set_name(std::string name);
    void add_child(Node node);
    bool has_children();
    std::vector<Node> get_children();
    void add_attribute(std::string name, std::string value);
    std::vector<Attribute> get_attributes();
    Attribute get_attribute(std::string name);
};

#endif