#ifndef ATTR_H
#define ATTR_H
#include <string>

class Attribute {
private:
    std::string name;
    std::string value;
public:
    Attribute(std::string name, std::string value);
    std::string get_name();
    std::string get_value();
};


#endif
