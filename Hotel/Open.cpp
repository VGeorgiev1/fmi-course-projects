#include "Open.h"
#include <fstream>
#include <stdio.h>

Open::Open(Hotel& h)
	: FileOperation(h, "open") {};


void Open::execute() {

	std::string file_name;

	std::cout << this->file_name << std::endl;

	std::cin >> file_name;
	
	std::ifstream file(file_name, std::ios::in | std::ios::binary);


	if(!file.is_open()) {
		std::ofstream new_file(file_name, std::ios::out | std::ios::binary);
		if(!new_file.is_open()) {
			std::cout << "File " << file_name << " could not be opened or created! " << std::endl;
			return;
		}
		int empty_file = 0;
		new_file.write((char*) &(empty_file), sizeof(int));
		std::cout << "File " << file_name << " successfuly created!" << std::endl;
		hotel_.set_operatable(true);

		return;
	}

	FileOperation* save = (FileOperation*)(hotel_.find_operation("save"));
	FileOperation* close = (FileOperation*)(hotel_.find_operation("close"));

	if(save != nullptr && close != nullptr) {
		save->set_file_name(file_name);
		close->set_file_name(file_name);
	}

	set_file_name(file_name);

	this->file_name = file_name;


	std::vector<Room> rooms;

	int rooms_size = 0;

	file.read((char*) &rooms_size, sizeof(int));

	if(rooms_size == 0) {
		std::cout << "File " << file_name << " opened successfully!" << std::endl;
		hotel_.set_operatable(true);
		return;
	}

	for (int i = 0; i < rooms_size; i++) {
		Room r;

		file.read((char*) &r, sizeof(Room));

		hotel_.add_room(r);
	}

	int records_size = 0;


	file.read((char*)&records_size, sizeof(int));


	for (int i = 0; i < records_size; i++) {
		Date start, finish;
		std::string note;
		Record::Type t;


		file.read((char*)&start, sizeof(Date));
		file.read((char*)&finish, sizeof(Date));

		int note_size = 0;

		file.read((char*)&note_size, sizeof(int));

		note.resize(note_size);

		file.read((char*)&note[0], note_size);

		file.read((char*)&t, sizeof(t));
		
		int room_number = 0;
		file.read((char*)&room_number, sizeof(int));

		int beds_taken = 0;
		file.read((char*)&beds_taken, sizeof(int));

		hotel_.add_record(Record(start, finish, note, *(hotel_.get_room(room_number)), beds_taken, t));
	}

	file.close();
	hotel_.set_operatable(true);
	std::cout << "File " << file_name << " opened successfully!" << std::endl;

}

bool Open::file_opened() {
	return file_name.size() == 0;
}