#pragma once
#ifndef SAVE_H
#define SAVE_H

#include "FileOperation.h"
#include <iostream>

class Save : public FileOperation {
public:
	Save(Hotel& h);
	void execute();
};


#endif