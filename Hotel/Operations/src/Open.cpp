#include "../headers/Open.h"
#include "../../OperationException.h"
#include <fstream>
#include <stdio.h>

Open::Open(Hotel& h)
	: FileOperation(h, "open") {};


void Open::execute() {

	std::string file_name;

	std::cout << this->file_name << std::endl;

	std::cin >> file_name;
	
	std::ifstream file(file_name);

	FileOperation* save = (FileOperation*)(hotel_.find_operation("save"));
	FileOperation* close = (FileOperation*)(hotel_.find_operation("close"));

	if(save != nullptr && close != nullptr) {
		save->set_file_name(file_name);
		close->set_file_name(file_name);
	}

	set_file_name(file_name);

	if(!file.is_open()) {
		std::ofstream new_file(file_name, std::ios::out);
		if(!new_file.is_open()) {
			throw OperationException("File could not be opened or created!");
			save->set_file_name("");
			close->set_file_name("");
			set_file_name(file_name);
			return;
		}
		int empty_file = 0;
		new_file << 0;
		//new_file.write((char*) &(empty_file), sizeof(int));
		std::cout << "File " << file_name << " successfuly created!" << std::endl;
		hotel_.set_operatable(true);
		return;
	}


	this->file_name = file_name;

	int rooms_size = 0;
	
	file >> rooms_size;

	if (!file) {
		throw OperationException("There was a problem reading the file!");
	}

	if(rooms_size == 0) {
		std::cout << "File " << file_name << " opened successfully!" << std::endl;
		hotel_.set_operatable(true);
		return;
	}

	for (int i = 0; i < rooms_size; i++) {
		int room_number, beds;

		file >> room_number;
		file >> beds;
		
		if (!file) {
			throw OperationException("There was a problem reading the file!");
		}

		hotel_.add_room(new Room(beds, room_number));
	}

	int records_size = 0;

	
	file >> records_size;
	
	if (!file || records_size < 0) {
		throw OperationException("There was a problem reading the file!");
	}



	for (int i = 0; i < records_size; i++) {
		
		std::string note;
		int t;

		std::string start, end;

		file >> start >> end >> note;

		Date start_date(start), finish(end);
		file >> t;

		int room_number = 0, beds_taken = 0;

		file >> room_number >> beds_taken;

		Room* r = hotel_.get_room(room_number);

		if (!file || room_number < 0 || beds_taken < 0 || r == nullptr || beds_taken > r->get_beds()) {
			throw OperationException("There was a problem reading the file!");
		}

		hotel_.add_record(Record(start_date, finish, note, r, beds_taken, (Record::Type)t));
	}

 	file.close();
	hotel_.set_operatable(true);
	std::cout << "File " << file_name << " opened successfully!" << std::endl;

}

bool Open::file_opened() {
	return file_name.size() == 0;
}