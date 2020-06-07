#ifndef OPERATION_EXC_H
#define OPERATION_EXC_H


#include <stdexcept>
class OperationException : public std::logic_error {
public:
	OperationException(std::string exc);
};
#endif

