#include <string>
#include "Room.h"

Room::Room(int beds, int number) : beds(beds), number(number) {}

Room::Room() : beds(0), number(0) {};

int Room::get_number() {
	return number;
}
int Room::get_beds() {
	return beds;
}
bool Room::operator==(const Room& other) {
	if (number == other.number) return true;

	return false;
}