#include "../headers/Save.h"
#include <fstream>
#include <stdio.h>

Save::Save(Hotel& h)
	: FileOperation(h, "save") {};

void Save::execute() {
	std::vector<Room> rooms = hotel_.get_rooms();
	std::vector<Record> records = hotel_.get_records();

	std::ofstream file(file_name);

	std::cout << file_name << std::endl;

	if(!file.is_open()) {

		std::cout << "File not opened correctly!" << std::endl;
		return;
	}

	int rooms_size = rooms.size();
	int records_size = records.size();

	file << rooms_size << std::endl;

	//file.write((char*) &rooms_size, sizeof(int));

	for (std::vector<Room>::iterator it = rooms.begin(); it != rooms.end(); ++it) {
		//file.write((char*) &(*it), sizeof(*it));
		file << (*it).get_number() << " "<< (*it).get_beds() << std::endl;
	}

	//file.write((char*)&records_size, sizeof(int));
	file << records_size << std::endl;

	for (std::vector<Record>::iterator it = records.begin(); it != records.end(); ++it) {
		Date start = (*it).get_start_date();
		Date end = (*it).get_finish_date();
		
		file << start << " ";
		file << end << " ";

		//file.write((char*)&(start), sizeof(Date));
		//file.write((char*)&(end), sizeof(Date));
		
		//int note_size = (*it).get_note().size();
		//std::string note = (*it).get_note();

		file << (*it).get_note() << std::endl;

		//file.write((char*)&note_size, sizeof(note_size));

		//file.write(note.c_str(), note_size);

		Record::Type t = (*it).get_type();

		file << (int)t << " ";

		//file.write((char*)&t, sizeof(t));
		
		int room_number = (*it).get_room().get_number();
		int beds_taken = (*it).get_beds_taken();

		file << room_number << " " << beds_taken << std::endl;

		//file.write((char*)&room_number, sizeof(int));

		//file.write((char*)&beds_taken, sizeof(int));

	}

	file.close();

	std::cout << "Successfully saved " << file_name << std::endl;
}

