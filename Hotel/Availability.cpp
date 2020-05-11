#include "Availability.h"
#include <iostream>

Availability::Availability(Hotel& h)
	: HotelOperation(h, "availability") {};

void Availability::execute() {
	std::string date;

	std::cin >> date;

	Date d(date);

	std::vector<Room> available_rooms_on_date = hotel_.get_unrecorded_rooms();

	std::vector<Record> records = hotel_.get_records();

	for (std::vector<Record>::iterator it = records.begin(); it != records.end(); ++it) {
		if (it->get_start_date() > d || it->get_finish_date() < d) {
			available_rooms_on_date.push_back(it->get_room());
		}
	}

	std::cout << "Rooms available on " << date << ":";

	for (std::vector<Room>::iterator it = available_rooms_on_date.begin(); it != available_rooms_on_date.end(); ++it) {
		std::cout << it->get_number() << " ";
	}

	std::cout << std::endl;

}
