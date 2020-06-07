#ifndef ROOM_H
#define ROOM_H
#include <string>

class Room {
	int beds;
	int number;
public:
	Room(int beds, int number);
	Room();

	int get_number() const;
	int get_beds() const;
	bool operator==(const Room& other);
};


#endif // !ROOM_H

