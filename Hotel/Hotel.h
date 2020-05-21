#ifndef HOTEL_H
#include <vector>
#define HOTEL_H
#include "Room.h"
#include "Record.h"
#include "Operation.h"

class Hotel {
	std::vector<Room> rooms;
	std::vector<Record> records;
	std::vector<Operation*> operations;

	Room* find_room(int number);
public:
	Hotel();

	void remove_record(std::vector<Record>::iterator it);
	void add_room(Room r);

	std::vector<Record>& get_records();
	std::vector<Room> get_unrecorded_rooms();

	Room* get_room(int number);
	void add_record(Record r);

	std::vector<Room> get_rooms();

	void remove_rooms();
	void remove_records();
	
	void add_operation(Operation* op);
	Operation* find_operation(std::string name);

	bool has_record_for_room(int room);
};


#endif