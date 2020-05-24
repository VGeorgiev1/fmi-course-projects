#ifndef FINDEM_H
#define FINDEM_H
#include "HotelOperation.h"


class Findem : public HotelOperation {
public:
	Findem(Hotel& h);
	void execute();
	Room* create_room(int beds, Date start, Date end, int room_to_miss, int step);
};

#endif
