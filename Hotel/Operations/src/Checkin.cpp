#include "../headers/Checkin.h"
#include "../../OperationException.h"
#include <iostream>


Checkin::Checkin(Hotel& h)
	: HotelOperation(h, "checkin") {};

void Checkin::execute() {
	std::string start_date, end_date, note, note_and_beds;
	int room, beds = 0;

	std::cin >> room >> start_date >> end_date;
	std::getline(std::cin, note_and_beds);

	int idx = 1;
	while (idx < note_and_beds.size() && note_and_beds[idx] != ' ') {
		idx++;
	}

	note = note_and_beds.substr(1, idx);

	Room* r = hotel_.get_room(room);

	if (idx != note_and_beds.size()) {
		beds = std::stoi(note_and_beds.substr(idx + 1));
	}
	else {
		beds = r->get_beds();
	}


	if (r == nullptr) {
		throw OperationException("Room cannot be found!");
	}

	if (beds > r->get_beds()) {
		throw OperationException("This room has fewer beds!");
	}

	if (hotel_.get_check_in_for_room(r->get_number()) != nullptr) {
		throw OperationException("Room is cheked in");
	}

	try {

		Date start(start_date), end(end_date);

		if (start > end) {
			throw OperationException("Start date cannot be after end date!");
		}

		if (hotel_.is_unavailable_for_period(room, start, end)) {
			throw OperationException("Room is unavailable for tha period.");
		}

		hotel_.add_record(Record(start, end, note, r, beds, Record::Type::CHECKIN));
		std::cout << "Room with number " << r->get_number() << " is cheked in for the period " << start << " to " << end << std::endl;
	}
	catch (std::invalid_argument err) {
		std::cout << err.what() << std::endl;
		throw OperationException("Ther was a problem parsing date");
	}
}
