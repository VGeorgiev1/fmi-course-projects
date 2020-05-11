#ifndef CHECKIN_H
#define CHECKIN_H
#include "HotelOperation.h";


class Checkin : public HotelOperation {
public:
	Checkin(Hotel& h);
	void execute();
};

#endif
