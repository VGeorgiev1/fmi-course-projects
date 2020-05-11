#include "Report.h"

Report::Report(Hotel& h)
	: HotelOperation(h, "report") {};

void Report::execute() {
	std::string date_start, date_end;

	std::cin >> date_start >> date_end;

	Date start(date_start), end(date_end);
	std::vector<Record> records = hotel_.get_records();

	for (std::vector<Record>::iterator it = records.begin(); it != records.end(); ++it) {
		if (it->get_start_date() >= start && it->get_finish_date() <= end) {
			Room room = it->get_room();

			std::cout << room.get_number() << " " << "from: " << it->get_start_date()
				<< " to: " << it->get_finish_date() << "note: " << it->get_note();
		}
	}
}
