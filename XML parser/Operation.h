#ifndef OPERATION_H
#define OPERATION_H
#include <string>
#include "Node.h"

class Operation {
	std::string name;
public:
	Operation(std::string _name);
	std::string get_name() const;
	virtual void execute() = 0;
};


#endif