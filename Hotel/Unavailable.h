#ifndef UNAVAILABLE_H
#define UNAVAILABLE_H

#include "HotelOperation.h"
#include <iostream>

class Unavailable : public HotelOperation {
public:
	Unavailable(Hotel& h);
	void execute();
};


#endif