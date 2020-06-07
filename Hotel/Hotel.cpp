#include "Hotel.h"
#include <limits.h>
#include <iostream>

Room* Hotel::find_room(int number) const {
	for (std::vector<Room*>::const_iterator it = rooms.begin(); it != rooms.end(); ++it) {
		if ((*it)->get_number() == number) {
			return *it;
		}
	}

	return nullptr;
}
Hotel::Hotel() : ready_to_operate(false) {};

void Hotel::set_operatable(bool value) {
	ready_to_operate = value;
}

void Hotel::remove_record(std::vector<Record>::iterator it) {
	records.erase(it);
}

Hotel::~Hotel() {
	for (std::vector<Operation*>::iterator it = operations.begin(); it != operations.end(); ++it) {
		delete *it;
	}
	for (std::vector<Room*>::iterator it = rooms.begin(); it != rooms.end(); ++it) {
		delete *it;
	}
}

void Hotel::remove_record(int number, Record::Type t) {
	for (std::vector<Record>::iterator it = records.begin(); it != records.end(); ++it) {
		if (it->get_room()->get_number() == number && it->get_type() == t) {
			records.erase(it);
			return;
		}
	}
	std::cout << "Room " << number << " has no reacords for itslef" << std::endl;
}

std::vector<Record>& Hotel::get_records() {
	return records;
}

void Hotel::change_room(Room* room_swap, Room* room_to_swap) {
	std::vector<Record>::iterator it = records.begin();
	Date start, end;
	std::string note;
	int beds_taken;


	for (; it != records.end(); ++it) {
		if (it->get_room()->get_number() == room_swap->get_number()) {
			start = it->get_start_date();
			end = it->get_finish_date();
			note = it->get_note();
			beds_taken = it->get_beds_taken();

			records.erase(it);
			
			records.push_back(Record(start, end, note, room_to_swap, beds_taken, Record::Type::CHECKIN));
			break;
		}
	}

}

void Hotel::remove_records() {
	records.clear();
}

void Hotel::remove_rooms() {
	for (std::vector<Room*>::iterator it = rooms.begin(); it != rooms.end(); ++it) {
		delete* it;
	}

	rooms.clear();
}

std::vector<Room*> Hotel::get_unrecorded_rooms() {
	std::vector<Room*> res;

	for (std::vector<Room*>::iterator it = rooms.begin(); it != rooms.end(); ++it) {		
		bool unrecorded = true;
		for (unsigned int j = 0; j < records.size(); j++) {
			if (*it == records[j].get_room()) {
				unrecorded = false;
			}
		}
		if (unrecorded) {
			res.push_back(*it);
		}
	}

	return res;
}

bool Hotel::can_operate() const {
	return ready_to_operate;
}

Record* Hotel::get_check_in_for_room(int room) {
	
	for (std::vector<Record>::iterator it = records.begin(); it != records.end(); ++it) {
		if ((*it).get_room()->get_number() == room && (*it).get_type() == Record::Type::CHECKIN) {
			return &(*it);
		}
	}

	return nullptr;
}

Room* Hotel::get_room(int number) const {
	return find_room(number);
}
void Hotel::add_record(Record r) {
	records.push_back(r);
}

void Hotel::add_room(Room* r) {
	rooms.push_back(r);
}

bool Hotel::is_unavailable_for_period(int room, Date start, Date end) const {

	for (std::vector<Record>::const_iterator it = records.begin(); it != records.end(); ++it) {
		if (it->get_room()->get_number() == room && it->get_type() == Record::Type::UNAVAILABLE) {
			
			if (it->get_start_date() >= start || it->get_finish_date() <= end
				|| (it->get_start_date() <= start && it->get_finish_date() >= end))
			{
				return true;
			}

		}
	}
	
	return false;
}

Room* Hotel::get_most_fitting_room(int requested_beds, Date start, Date end, int room_to_skip) const {
	int min_beds = INT_MAX;
	Room* r = nullptr;

	for (std::vector<Room*>::const_iterator it = rooms.begin(); it != rooms.end(); ++it) {
		int beds = (*it)->get_beds();
		
		if (beds >= requested_beds && beds <= min_beds && !is_unavailable_for_period((*it)->get_number(), start, end)) {
			if (room_to_skip != 0 && room_to_skip == (*it)->get_number()) {
				continue;
			}
			min_beds = beds;
			r = (*it);
		}
	}

	return r;
};


std::vector<Room*>& Hotel::get_rooms() {
	return rooms;
}

void Hotel::add_operation(Operation* op) {
	operations.push_back(op);
}

Operation* Hotel::find_operation(std::string name) {
	for (std::vector<Operation*>::iterator it = operations.begin(); it != operations.end(); ++it) {
		if ((*it)->get_name() == name) {
			return *it;
		}
	}
	return nullptr;
}

bool Hotel::room_is_cheked_in(int room) {
	std::vector<Record> recs;

	for (std::vector<Record>::iterator it = records.begin(); it != records.end(); ++it) {
		if (it->get_room()->get_number() == room && it -> get_type() == Record::Type::CHECKIN) {
			return true;
		}
	}

	return false;
};
