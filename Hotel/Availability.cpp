#include "Availability.h"
#include <iostream>

Availability::Availability(Hotel& h)
	: HotelOperation(h, "availability") {};

void Availability::execute() {
	
	std::string str_date;

	std::getline(std::cin, str_date);

	Date date;

	if(str_date == "") {
		time_t rawtime;
		struct tm * timeinfo;

		time (&rawtime);
		timeinfo = localtime (&rawtime);
		str_date.resize(15);
		strftime (&str_date[0], 15,"%Y-%m-%d",timeinfo);
		date = Date(str_date);
	} else {
		date = Date(str_date);
	}

	std::vector<Room> available_rooms_on_date = hotel_.get_unrecorded_rooms();

	std::vector<Record> records = hotel_.get_records();

	for (std::vector<Record>::iterator it = records.begin(); it != records.end(); ++it) {
		if (it->get_start_date() > date && it->get_finish_date() < date) {
			available_rooms_on_date.push_back(it->get_room());
		}
	}

	std::cout << "Rooms available on " << date << ":";

	for (std::vector<Room>::iterator it = available_rooms_on_date.begin(); it != available_rooms_on_date.end(); ++it) {
		std::cout << it->get_number() << std::endl;
	}

	std::cout << std::endl;

}
