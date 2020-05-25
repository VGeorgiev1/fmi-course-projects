#ifndef TEXT_H
#define TEXT_H
#include "XMLOperation.h"

class Text : public XMLOperation {
public:
	Text(Node* h);
	void execute();
};

#endif
