#ifndef DELETE_H
#define DELETE_H
#include "XMLOperation.h"

class Delete : public XMLOperation {
public:
	Delete(Node* h);
	void execute();
};

#endif
