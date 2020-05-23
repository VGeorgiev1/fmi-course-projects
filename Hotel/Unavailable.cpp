#include "Unavailable.h"

Unavailable::Unavailable(Hotel& h)
	: HotelOperation(h, "unavailable") {};
void Unavailable::execute() {
	std::string start_date, end_date, note;
	int room;

	std::cin >> room >> start_date >> end_date;
	std::getline(std::cin, note);

	Date start(start_date), end(end_date);

	if (start > end) {
		std::cout << "Start date cannot be after end date!" << std::endl;
	}

	Room* r = hotel_.get_room(room);

	if (r != nullptr) {
		hotel_.add_record(Record(start, end, note, *r, r->get_beds(), Record::Type::UNAVAILABLE));
	}
	else {
		std::cout << "Room not found or already is checkin!";
	}
}

