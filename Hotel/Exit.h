#ifndef EXIT_H
#define EXIT_H

#include "FileOperation.h"
#include <iostream>

class Exit : public FileOperation {
public:
	Exit(Hotel& h);
	void execute();
};


#endif
