#include "XMLParserException.h"

XMLParserException::XMLParserException(std::string exc)
	: std::logic_error(exc) {};