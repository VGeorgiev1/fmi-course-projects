#ifndef OPEN_H
#define OPEN_H

#include "FileOperation.h"
#include <iostream>

class Open : public FileOperation {
public:
	Open(XMLParser& h);
	void execute();
	bool file_opened();
};


#endif