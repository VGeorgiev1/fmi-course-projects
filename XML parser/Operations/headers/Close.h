#ifndef CLOSE_H
#define CLOSE_H

#include "FileOperation.h"
#include <iostream>

class Close : public FileOperation {
public:
	Close(XMLParser& h);
	void execute();
};


#endif