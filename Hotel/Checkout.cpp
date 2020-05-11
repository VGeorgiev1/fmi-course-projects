#include "Checkout.h"

Checkout::Checkout(Hotel& h)
	: HotelOperation(h, "checkout") {};
void Checkout::execute() {
	int room;

	std::cin >> room;

	std::vector<Record>& records = hotel_.get_records();

	for (std::vector<Record>::iterator it = records.begin(); it != records.end(); ++it) {
		if (it->get_room().get_number() == room) {
			hotel_.remove_record(it);
			break;
		}
	}
}