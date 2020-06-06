#include "../headers/HotelOperation.h"

HotelOperation::HotelOperation(Hotel& hotel, std::string name)
	: Operation(name), hotel_(hotel) {};

