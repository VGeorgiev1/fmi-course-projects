#include "Attribute.h"

Attribute::Attribute(std::string name, std::string value) : name(name), value(value) {};

std::string Attribute::get_name() {
    return name;
}

std::string Attribute::get_value() {
    return value;
}
void set_name(std::string new_name) {
    name = new_name
}
    
void set_value(std::string new_value) {
    value = new_value;
}