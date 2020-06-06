#include "../headers/Unavailable.h"

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

	Record* record = hotel_.get_check_in_for_room(room);
	Room* r = hotel_.get_room(room);
	if (record == nullptr) {

		if (r == nullptr) {
			std::cout << "Room is not found!" << std::endl;
			return;
		}

		hotel_.add_record(Record(start, end, note, *r, r->get_beds(), Record::Type::UNAVAILABLE));
	}

	if ((record->get_start_date() >= start || record->get_finish_date() <= end)
		|| (record->get_start_date() <= start && record->get_finish_date() >= end)) {
		
		hotel_.remove_record(room, Record::Type::CHECKIN);
		hotel_.add_record(Record(start, end, note, *r, r->get_beds(), Record::Type::UNAVAILABLE));
	}

	std::cout << "Room is now  unavailable in " << start << " " << end << std::endl;
}

