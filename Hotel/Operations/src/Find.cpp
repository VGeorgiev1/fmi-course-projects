#include "../headers/Find.h"
#include "../../OperationException.h"
#include <iostream>

Find::Find(Hotel& h)
	: HotelOperation(h, "find") {};

void Find::execute() {
	int beds;
	std::string start_date, end_date;

	std::cin >> beds >> start_date >> end_date;
	try {
		Date start(start_date), end(end_date);

		Room* r = hotel_.get_most_fitting_room(beds, start, end, 0, true);

		if (r == nullptr) {
			throw OperationException("No available room for this period!");
		};

		std::cout << "Room available for this period: " << r->get_number() << " with " << r->get_beds() << " beds" << std::endl;
	}
	catch (std::invalid_argument err) {
		std::cout << err.what() << std::endl;
		throw OperationException("Ther was a problem parsing date");
	}
}