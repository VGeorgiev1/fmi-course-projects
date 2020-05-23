#ifndef HELP_H
#define HELP_H

#include "FileOperation.h";
#include <iostream>

class Help : public FileOperation {
public:
	Help(Hotel& h);
	void execute();
};


#endif