#pragma once
#pragma once
#ifndef OPEN_H
#define OPEN_H

#include "FileOperation.h"
#include <iostream>

class Open : public FileOperation {
public:
	Open(Hotel& h);
	void execute();
};


#endif