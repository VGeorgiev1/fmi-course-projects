#pragma once
#include <stdexcept>
class OperationException : public std::logic_error {
public:
	OperationException(std::string exc);
};