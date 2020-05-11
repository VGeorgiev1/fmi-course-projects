#include "Checkin.h"
#include <iostream>


Checkin::Checkin(Hotel& h)
	: HotelOperation(h, "checkin") {};

void Checkin::execute() {
	std::string start_date, end_date, note;
	int room, beds;

	std::cin >> room >> start_date >> end_date;
	std::getline(std::cin, note);
	std::cin >> beds;

	Date start(start_date), end(end_date);


	Room* r = hotel_.get_room(room);
	if (start > end) {
		std::cout << "Start date cannot be after end date!" << std::endl;
		return;
	}
	if (beds > r->get_beds()) {
		std::cout << "This room has fewer beds!" << std::endl;
		return;
	}


	if (r != nullptr && !hotel_.has_record_for_room(r->get_number())) {
		hotel_.add_record(Record(start, end, note, *r, beds, Record::Type::CHECKIN));
	}
	else {
		std::cout << "Room not found or already is checkin!";
	}
}
