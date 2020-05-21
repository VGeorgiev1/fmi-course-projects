#include "Global.h";

int main() {
	Hotel hotel = Hotel();
	
	hotel.add_operation(new Open(hotel));
	hotel.add_operation(new Close(hotel));
	hotel.add_operation(new Saveas(hotel));
	hotel.add_operation(new Exit(hotel));
	hotel.add_operation(new Checkin(hotel));
	hotel.add_operation(new Availability(hotel));
	hotel.add_operation(new Checkout(hotel));
	hotel.add_operation(new Report(hotel));
	hotel.add_operation(new Find(hotel));
	hotel.add_operation(new Unavailable(hotel));


	while (true) {
		std::string command;

		std::cin >> command;

		Operation* op = hotel.find_operation(command);

		op -> execute();
		
	}
}