#include "../headers/Find.h"
#include "../../OperationException.h"
#include <iostream>

Find::Find(Hotel& h)
	: HotelOperation(h, "find") {};

void Find::execute() {
	int beds;
	std::string start_date, end_date;

	std::cin >> beds >> start_date >> end_date;


	Room* r = hotel_.get_most_fitting_room(beds, start_date, end_date, 0, true);

	std::vector<Room*> rooms = hotel_.get_unrecorded_rooms();

	if (r == nullptr) {
		throw OperationException("No available room for this period!");
		return;
	};

	std::cout << "Room available for this period: " << r->get_number() << " with " << r->get_beds() << " beds" << std::endl;

	

	//for (std::vector<Room>::iterator it = rooms.begin(); it != rooms.end(); ++it) {
	//	if (it->get_beds() <= beds) {
	//		std::cout << it->get_number() << std::endl;
	//	}
	//}

	//std::vector<Record> records = hotel_.get_records(); 

	//for (std::vector<Record>::iterator it = records.begin(); it != records.end(); ++it) {
	//	if (((it->get_start_date() > start_date && it->get_finish_date() > end_date)
	//		|| (it->get_start_date() < start_date && it->get_finish_date() < end_date))
	//		&& it->get_room().get_beds() <= beds)
	//	{
	//		std::cout <<  << it->get_room().get_number() << std::endl;
	//	}
	//}
}