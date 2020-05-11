#ifndef HOTEL_OPERATION_H
#define HOTEL_OPERATION_H
#include "Operation.h"
#include "Hotel.h"

class HotelOperation : public Operation {
protected:
	Hotel& hotel_;
public:
	HotelOperation(Hotel& hotel, std::string name);
};

#endif 
