#ifndef FIND_H
#define FIND_H
#include "HotelOperation.h";


class Find : public HotelOperation {
public:
	Find(Hotel& h);
	void execute();
};

#endif
