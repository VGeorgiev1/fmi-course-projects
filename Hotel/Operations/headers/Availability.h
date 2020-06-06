#ifndef AVAILABILITY_H
#define AVAILABILITY_H
#include "HotelOperation.h"
#include <ctime>
#include <time.h> 

class Availability : public HotelOperation {
public:
	Availability(Hotel& h);
	void execute();
};

#endif