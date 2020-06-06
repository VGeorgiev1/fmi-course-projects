#include "../headers/Availability.h"
#include <iostream>
Availability::Availability(Hotel& h)
	: HotelOperation(h, "availability") {};

void Availability::execute() {
	
	std::string str_date;

	std::getline(std::cin, str_date);

	Date date;

	if(str_date == "") {
		std::time_t rawtime;
		std::tm* timeinfo;

		std::time(&rawtime);
		timeinfo = std::localtime(&rawtime);

		str_date.resize(11);
		std::strftime(&str_date[0], 11, "%Y-%m-%d", timeinfo);

		date = Date(str_date);
	} else {
		date = Date(str_date);
	}

	std::vector<Room> available_rooms_on_date = hotel_.get_unrecorded_rooms();

	std::vector<Record> records = hotel_.get_records();

	std::cout << "Rooms available on " << date << ":" << std::endl;

	for (std::vector<Room>::iterator it = available_rooms_on_date.begin(); it != available_rooms_on_date.end(); ++it) {
		std::cout << it->get_number() << std::endl;
	}
	for (std::vector<Record>::iterator it = records.begin(); it != records.end(); ++it) {
		if (it->get_start_date() > date && it->get_finish_date() < date) {
			std::cout << it->get_room().get_number() << std::endl;
		}
	}


	std::cout << std::endl;

}
