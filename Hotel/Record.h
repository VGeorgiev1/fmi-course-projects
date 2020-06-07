#ifndef RECORD_H
#define RECORD_H

#include "Date.h"
#include "Room.h"


class Record {
public:
	enum class Type {CHECKIN, UNAVAILABLE};
private:
	Date start_date;
	Date finish_date;
	int beds_taken;
	std::string note;
	Room* room;
	Type type;
public:

	Record(Date start, Date finish, std::string note, Room* r, int beds_taken, Record::Type type);

	Date get_start_date() const;
	Date get_finish_date() const;
	Room* get_room() const;
	const std::string& get_note() const;
	Type get_type() const;
	int get_beds_taken() const;

	Record& operator=(const Record& other);
};
#endif 
