#ifndef DELETE_H
#define DELETE_H
#include "XMLOperation.h"

class Delete : public XMLOperation {
public:
	Delete(XMLParser& h);
	void execute();
};

#endif
