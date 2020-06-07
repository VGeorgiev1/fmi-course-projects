#ifndef XML_EXC_H
#define XML_EXC_H
#include <stdexcept>
class XMLException : public std::logic_error {
public:
	XMLException(std::string exc);
};

#endif 

