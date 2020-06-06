#include "../headers/Open.h"
#include <fstream>
#include <stdio.h>

Open::Open(Hotel& h)
	: FileOperation(h, "open") {};


void Open::execute() {

	std::string file_name;

	std::cout << this->file_name << std::endl;

	std::cin >> file_name;
	
	std::ifstream file(file_name, std::ios::binary);

	FileOperation* save = (FileOperation*)(hotel_.find_operation("save"));
	FileOperation* close = (FileOperation*)(hotel_.find_operation("close"));

	if(save != nullptr && close != nullptr) {
		save->set_file_name(file_name);
		close->set_file_name(file_name);
	}

	set_file_name(file_name);

	if(!file.is_open()) {
		std::ofstream new_file(file_name, std::ios::out | std::ios::binary);
		if(!new_file.is_open()) {
			std::cout << "File " << file_name << " could not be opened or created! " << std::endl;
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
		std::cout << "There was a problem reading the file!" << std::endl;
		return;
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
			std::cout << "There was a problem reading the file!" << std::endl;
			return;
		}

		hotel_.add_room(Room(beds, room_number));
	}

	int records_size = 0;

	
	file >> records_size;
	
	if (!file || records_size < 0) {
		std::cout << "There was a problem reading the file!" << std::endl;
		return;
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

		if (!file || room_number < 0 || beds_taken < 0) {
			std::cout << "There was a problem reading the file!" << std::endl;
			return;
		}

		hotel_.add_record(Record(start_date, finish, note, *(hotel_.get_room(room_number)), beds_taken, (Record::Type)t));
	}

 	file.close();
	hotel_.set_operatable(true);
	std::cout << "File " << file_name << " opened successfully!" << std::endl;

}

bool Open::file_opened() {
	return file_name.size() == 0;
}