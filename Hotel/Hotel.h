#ifndef HOTEL_H
#define HOTEL_H
#include <vector>
#include "Room.h"
#include "Record.h"
#include "Operation.h"


class Hotel {
	std::vector<Room> rooms;
	std::vector<Record> records;
	std::vector<Operation*> operations;
	bool ready_to_operate;
	Room* find_room(int number);
public:
	Hotel();

	void set_operatable(bool value);
	bool can_operate();


	void remove_record(std::vector<Record>::iterator it);
	void add_room(Room r);

	std::vector<Record>& get_records();
	std::vector<Room> get_unrecorded_rooms();

	Room* get_room(int number);
	Room* get_most_fitting_room(int requested_beds, Date start, Date end, int room_to_skip);
	
	bool is_unavailable_for_period(int room, Date start, Date end);

	void add_record(Record r);
	Record* get_check_in_for_room(int room);

	void change_room(Room* room_swap, Room* room_to_swap);

	std::vector<Room> get_rooms();

	void remove_rooms();
	void remove_records();
	
	void add_operation(Operation* op);
	Operation* find_operation(std::string name);

	bool room_is_cheked_in(int room);
};


#endif