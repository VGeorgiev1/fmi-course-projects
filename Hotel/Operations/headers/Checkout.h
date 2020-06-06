#ifndef CHECKOUT_H
#define CHECKOUT_H
#include "HotelOperation.h"
#include <iostream>

class Checkout : public HotelOperation {
public:
	Checkout(Hotel& h);
	void execute();
};

#endif
