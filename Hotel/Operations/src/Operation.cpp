#include <string>
#include "../headers/Operation.h"


Operation::Operation(std::string _name) : name(_name) {};

std::string Operation::get_name() const {
	return name;
}