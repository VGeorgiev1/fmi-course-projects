#include "Find.h"
#include <iostream>

Find::Find(Hotel& h)
	: HotelOperation(h, "find") {};

void Find::execute() {
	int beds;
	std::string start_date, end_date;

	std::cin >> beds >> start_date >> end_date;

	//todo
}