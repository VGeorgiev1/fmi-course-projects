#include "../headers/Report.h"

Report::Report(Hotel& h)
	: HotelOperation(h, "report") {};

void Report::execute() {
	std::string date_start, date_end;

	std::cin >> date_start >> date_end;
	try {
		Date start(date_start), end(date_end);

		std::vector<Record> records = hotel_.get_records();

		for (std::vector<Record>::iterator it = records.begin(); it != records.end(); ++it) {

			if ((it->get_start_date() >= start || it->get_finish_date() <= end)
				|| (it->get_start_date() <= start && it->get_finish_date() >= end)
				&& it->get_type() == Record::Type::CHECKIN) {
				Room* room = it->get_room();

				int start_days = start - it->get_start_date();
				int end_days = end - it->get_finish_date();

				int full_days = (end - start);

				if (start_days < 0 && end_days < 0) {
					std::cout << "Room " << room->get_number() << " will be used for " << full_days + 1 << " days in that period." << std::endl;
					continue;
				}

				if (start_days < 0) {
					full_days += start_days;
				}

				if (end_days > 0) {
					full_days -= end_days;
				}

				std::cout << "Room " << room->get_number() << " will be used for " << full_days + 1 << " days in that period." << std::endl;
			}
		}
	}
	catch (std::invalid_argument err) {
		std::cout << err.what() << std::endl;
		throw OperationException("Ther was a problem parsing date");
	}
}
