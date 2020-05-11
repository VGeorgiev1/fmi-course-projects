#include "Hotel.h"


Room* Hotel::find_room(int number) {

	for (unsigned int i = 0; i < rooms.size(); i++) {
		if (rooms[i].get_number() == number) {
			return &rooms[i];
		}
	}
	return nullptr;
}
Hotel::Hotel() {}

void Hotel::remove_record(std::vector<Record>::iterator it) {
	records.erase(it);
}

std::vector<Record>& Hotel::get_records() {
	return records;
}

std::vector<Room> Hotel::get_unrecorded_rooms() {
	std::vector<Room> res;

	for (std::vector<Room>::iterator it = rooms.begin(); it != rooms.end(); ++it) {		
		bool unrecorded = true;
		for (unsigned int j = 0; j < records.size(); j++) {
			if (*it == records[j].get_room()) {
				unrecorded = false;
			}
		}
		res.push_back(*it);
	}

	return res;
}

Room* Hotel::get_room(int number) {
	return find_room(number);
}
void Hotel::add_record(Record r) {
	records.push_back(r);
}
bool Hotel::has_record_for_room(int room) {
	std::vector<Record> recs;

	for (std::vector<Record>::iterator it = records.begin(); it != records.end(); ++it) {
		if (it -> get_room().get_number() == room) {
			return true;
		}
	}

	return false;
};
