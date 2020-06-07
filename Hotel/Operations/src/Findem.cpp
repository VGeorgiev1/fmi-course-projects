#include "../headers/Findem.h"
#include <iostream>
#include "../../OperationException.h"

Findem::Findem(Hotel& h)
	: HotelOperation(h, "find!") {};

Room* Findem::create_room(int beds, Date start, Date end, int room_to_miss, int step) {
	
	Room* most_fitting_room = hotel_.get_most_fitting_room(beds, start, end, room_to_miss, false);

	if (most_fitting_room == nullptr) {
		throw OperationException("No rooms with the needed beds were found and no moves were possible to be made!");
	}

	if (hotel_.room_is_cheked_in(most_fitting_room->get_number(), start, end)) {
		Record* r = hotel_.get_check_in_for_room(most_fitting_room->get_number());

		if (most_fitting_room == nullptr && step == 2) {
			throw OperationException("No rooms with the needed beds were found and no moves were possible to be made!");
		}

		Room* room_to_change = create_room(r->get_beds_taken(), r->get_start_date(), r->get_finish_date(), r->get_room()->get_number(), step++);
			
		int room_numb = r->get_room()->get_number();

		if (room_to_change != nullptr) {
			hotel_.change_room(most_fitting_room,room_to_change);
		}
			
		return most_fitting_room;
	}
	return most_fitting_room;
}

void Findem::execute() {
	int beds;
	std::string start_date, end_date;

	std::cin >> beds >> start_date >> end_date;

	Date start(start_date), end(end_date);

	bool found_room = false;

	std::cout << "Rooms available for this period: " << std::endl;

	Room* most_fitting_room = create_room(beds, start, end, 0, 0);
	std::cout << "Room " << most_fitting_room->get_number() << " is free for that period!" << std::endl;


}