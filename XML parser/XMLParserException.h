#ifndef XML_PARSER_EXC_H
#define XML_PARSER_EXC_H
#include <stdexcept>
class XMLParserException : public std::logic_error {
public:
	XMLParserException(std::string exc);
};

#endif 