#pragma once
#ifndef NEWCHILD_H
#define NEWCHILD_H
#include "XMLOperation.h"

class Newchild : public XMLOperation {
public:
	Newchild(Node* h);
	void execute();

};

#endif