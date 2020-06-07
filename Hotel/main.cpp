#include "./Operations/Global.h"
#include "./Hotel.h"
#include "OperationException.h"
int main() {
	Hotel hotel;
	
	hotel.add_operation(new Open(hotel));
	hotel.add_operation(new Close(hotel));
	hotel.add_operation(new Saveas(hotel));
	hotel.add_operation(new Save(hotel));
	hotel.add_operation(new Checkin(hotel));
	hotel.add_operation(new Availability(hotel));
	hotel.add_operation(new Checkout(hotel));
	hotel.add_operation(new Report(hotel));
	hotel.add_operation(new Find(hotel));
	hotel.add_operation(new Findem(hotel));
	hotel.add_operation(new Unavailable(hotel));
	hotel.add_operation(new Help(hotel));
	
	//hotel.add_room(new Room(4, 100));
	//hotel.add_room(new Room(5, 200));
	//hotel.add_room(new Room(2, 300));


	while (true) {
		std::string command;

		std::cin >> command;

		if (command == "exit") {
			break;
		}

		if(command != "open" && !hotel.can_operate()) {
			std::cout << "You must open a file first!" << std::endl;
			continue;
		}

		Operation* op = hotel.find_operation(command);
		try {
			if (op != nullptr) {
				op->execute();
			}
		}
		catch (OperationException err) {
			std::cout << err.what() << std::endl;
		}

	}
}