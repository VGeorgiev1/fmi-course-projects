#include "Record.h"

Record::Record(Date start, Date finish, std::string note, Room& r, int beds_taken, Record::Type type)
	: start_date(start), finish_date(finish), note(note), room(r), beds_taken(beds_taken),  type(type) {}

Date Record::get_start_date() {
	return start_date;
}
Date Record::get_finish_date() {
	return finish_date;
}
std::string Record::get_note() {
	return note;
}
Room& Record::get_room() {
	return room;
}

Record& Record::operator=(const Record& other) {

	start_date = other.start_date;
	finish_date = other.finish_date;
	room = other.room;
	type = other.type;

	return *this;
}
