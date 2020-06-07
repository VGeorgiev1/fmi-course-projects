#include "../headers/Checkout.h"
#include "../../OperationException.h"

Checkout::Checkout(Hotel& h)
	: HotelOperation(h, "checkout") {};
void Checkout::execute() {
	int room;

	std::cin >> room;


	if (hotel_.get_check_in_for_room(room) == nullptr) {
		throw OperationException("Room  has not records for it!");
	}

	hotel_.remove_record(room, Record::Type::CHECKIN);
	std::cout << "Room " << room << " is now checkedout!" << std::endl;
}