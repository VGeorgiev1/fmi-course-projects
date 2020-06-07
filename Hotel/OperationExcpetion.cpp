#include "OperationException.h"


OperationException::OperationException(std::string exc)
	: std::logic_error(exc) {};