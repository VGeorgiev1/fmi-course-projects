#include "../headers/Unavailable.h"
#include "../../OperationException.h"

Unavailable::Unavailable(Hotel& h)
	: HotelOperation(h, "unavailable") {};
void Unavailable::execute() {
	std::string start_date, end_date, note;
	int room;

	std::cin >> room >> start_date >> end_date;
	std::getline(std::cin, note);
	try {
		Date start(start_date), end(end_date);

		if (start > end) {
			throw OperationException("Start date cannot be after end date!");
		}

		Record* record = hotel_.get_check_in_for_room(room);
		Room* r = hotel_.get_room(room);
		if (record == nullptr) {

			if (r == nullptr) {
				throw OperationException("Room is not found!");
			}

			hotel_.add_record(Record(start, end, note, r, r->get_beds(), Record::Type::UNAVAILABLE));
		}

		if ((record->get_start_date() >= start || record->get_finish_date() <= end)
			|| (record->get_start_date() <= start && record->get_finish_date() >= end)) {

			hotel_.remove_record(room, Record::Type::CHECKIN);
			hotel_.add_record(Record(start, end, note, r, r->get_beds(), Record::Type::UNAVAILABLE));
		}

		std::cout << "Room is now  unavailable in " << start << " " << end << std::endl;
	}
	catch (std::invalid_argument err) {
		std::cout << err.what() << std::endl;
		throw OperationException("Ther was a problem parsing date");
	}
}

