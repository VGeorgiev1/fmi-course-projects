#ifndef REPORT_H
#define REPORT_H
#include "../../OperationException.h"
#include "HotelOperation.h"
#include <iostream>

class Report : public HotelOperation {
public:
	Report(Hotel& h);
	void execute();
};


#endif