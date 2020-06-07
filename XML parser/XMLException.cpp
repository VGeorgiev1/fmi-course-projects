#include "XMLException.h"

XMLException::XMLException(std::string exc)
	: std::logic_error(exc) {};