#pragma once
#ifndef SAVEAS_H
#define SAVEAS_H

#include "FileOperation.h";
#include <iostream>

class Saveas : public FileOperation {
public:
	Saveas(Hotel& h);
	void execute();
};


#endif