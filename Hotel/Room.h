#ifndef ROOM_H
#define ROOM_H
#include <string>

class Room {
	int beds;
	int number;
	std::string note;
public:
	Room(int beds, int number);

	int get_number();
	int get_beds();
	bool operator==(const Room& other);
};


#endif // !ROOM_H

