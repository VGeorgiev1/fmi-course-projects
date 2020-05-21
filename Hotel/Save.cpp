#include "Save.h"
#include <fstream>
#include <stdio.h>

Save::Save(Hotel& h)
	: FileOperation(h, "save") {};


void Save::execute() {
	std::vector<Room> rooms = hotel_.get_rooms();
	std::vector<Record> records = hotel_.get_records();


	std::ofstream file(file_name, std::ios::out | std::ios::binary);

	int rooms_size = rooms.size();
	int records_size = records.size();

	file.write((char*) &rooms_size, sizeof(int));

	for (std::vector<Room>::iterator it = rooms.begin(); it != rooms.end(); ++it) {
		file.write((char*) &(*it), sizeof(*it));
	}

	file.write((char*)&records_size, sizeof(int));

	for (std::vector<Record>::iterator it = records.begin(); it != records.end(); ++it) {
		file.write((char*)&((*it).get_start_date()), sizeof(Date));
		file.write((char*)&((*it).get_finish_date()), sizeof(Date));
		
		int note_size = (*it).get_note().size();
		std::string note = (*it).get_note();


		file.write((char*)&note_size, sizeof(note_size));

		file.write(note.c_str(), note_size);

		Record::Type t = (*it).get_type();

		file.write((char*)&t, sizeof(t));
		
		int room_number = (*it).get_room().get_number();
		int beds_taken = (*it).get_beds_taken();

		file.write((char*)&room_number, sizeof(int));

		file.write((char*)&beds_taken, sizeof(int));

	}

	file.close();

	std::cout << "Successfully saved " << file_name;
}

