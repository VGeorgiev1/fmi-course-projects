#include "Open.h"
#include <fstream>
#include <stdio.h>

Open::Open(Hotel& h)
	: FileOperation(h, "save") {};


void Open::execute() {

	std::string file_name;

	std::cin >> file_name;

	std::ifstream file(file_name, std::ios::in | std::ios::binary);

	if(!file.is_open()) {
		//throw std::No
	}

	this->file_name = file_name;


	std::vector<Room> rooms;

	int rooms_size = 0;

	file.read((char*) &rooms_size, sizeof(int));

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

		hotel_.add_record(Record(start, finish, note, *(hotel_.get_room(rooms_size)), beds_taken, t));
	}

	file.close();

}

