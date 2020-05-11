#include "Attribute.h";

Attribute::Attribute(std::string name, std::string value) : name(name), value(value) {};

std::string Attribute::get_name() {
    return name;
}

std::string Attribute::get_value() {
    return value;
}