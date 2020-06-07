#ifndef SAVE_H
#define SAVE_H

#include "FileOperation.h"
#include "XMLOperation.h"
#include <iostream>

class Save : public FileOperation {
public:
	Save(XMLParser& h);
	void execute();
};


#endif