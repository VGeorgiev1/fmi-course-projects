#ifndef FILE_OPERATION_H
#define FILE_OPERATION_H
#include "Operation.h"
#include "Hotel.h"

class FileOperation : public Operation {
protected:
	Hotel& hotel_;
	std::string file_name = "";
public:
	FileOperation(Hotel& hotel, std::string name);
};

#endif 
