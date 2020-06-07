#include "../headers/Checkout.h"

Checkout::Checkout(Hotel& h)
	: HotelOperation(h, "checkout") {};
void Checkout::execute() {
	int room;

	std::cin >> room;


	hotel_.remove_record(room, Record::Type::CHECKIN);

	std::vector<Record>& records = hotel_.get_records();


	for (std::vector<Record>::iterator it = records.begin(); it != records.end(); ++it) {
		if (it->get_room()->get_number() == room && it->get_type() == Record::Type::CHECKIN) {
			hotel_.remove_record(it);
			std::cout << "Record for room " << room << " is removed!" << std::endl;
			return;
		}
	}

	std::cout << "Room " << room << " has not records for it!" << std::endl;
}