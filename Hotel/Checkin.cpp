#include "Checkin.h"
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


	Date start(start_date), end(end_date);


	Room* r = hotel_.get_room(room);

	if (idx != note_and_beds.size()) {
		beds = std::stoi(note_and_beds.substr(idx + 1));
	}
	else {
		beds = r->get_beds();
	}


	if (start > end) {
		std::cout << "Start date cannot be after end date!" << std::endl;
		return;
	}
	if (beds > r->get_beds()) {
		std::cout << "This room has fewer beds!" << std::endl;
		return;
	}

	if (r == nullptr) {
		std::cout << "Room not found" << std::endl;
		return;
	}

	if (hotel_.room_is_cheked_in(r->get_number())) {
		std::cout << "Room is cheked in" << std::endl;
		return;
	}

	if (hotel_.is_unavailable_for_period(room, start, end)) {
		std::cout << "Room is unavailable for tha period." << std::endl;
		return;
	}

	
	hotel_.add_record(Record(start, end, note, *r, beds, Record::Type::CHECKIN));
	
}
