#include "Date.h"
#include <string>
#include <stdexcept>
#include <iostream>


Date::Date() : year(0), month(0), date(0) {};

int Date::monthsDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

Date::Date(std::string date_string) {

	if (date_string.find('-') == -1) {
		throw std::invalid_argument("Invalid date!");
	}
	int args = 0;

	int start = 0;

	int finish = date_string.find('-', start);


	std::string y = date_string.substr(start, finish - start);
	year = std::stoi(y);

	if (year <= 0) {
		throw std::invalid_argument("Invalid date!");
	}
	start = finish + 1;
	finish = date_string.find('-', start);

	std::string m = date_string.substr(start, finish - start);
	month = std::stoi(m);
	if (month <= 0 || month > 12) {
		throw std::invalid_argument("Invalid date!");
	}
	start = finish + 1;


	std::string d = date_string.substr(start, finish - start);
	date = std::stoi(d);


	if (date <= 0 || date > monthsDays[month]) {
		throw std::invalid_argument("Invalid date!");
	}
}

bool Date::operator <(const Date& other) {
	if (other.get_year() > year || other.get_month() > month || other.get_date() > date) {
		return true;
	}
	return false;
}
bool Date::operator >(const Date& other) {
	return !(*this < other || *this == other);
}
bool Date::operator==(const Date& other) {
	if (other.get_year() == year && other.get_month() == month && other.get_date() == date) {
		return true;
	}
	return false;
}
int Date::operator-(const Date& other) {
	int date_n1 = year*365 + date;
	int date_n2 = other.year * 365 + other.date;

	for (int i = 0; i < month - 1; i++) {
		date_n1 += monthsDays[i];
	}

	for (int i = 0; i < other.month - 1; i++) {
		date_n2 += monthsDays[i];
	}

	return date_n1 - date_n2;
}
bool Date::operator!=(const Date& other) {
	return !(*this == other);
}
bool Date::operator <=(const Date& other) {
	if (*this < other) {
		return true;
	}
	return *this == other;
}
bool Date::operator >=(const Date& other) {
	return !(*this <= other) || *this == other;
}

int Date::get_year() const {
	return year;
}

int Date::get_month() const {
	return month;
}

int Date::get_date() const {
	return date;
}

std::ostream& operator<<(std::ostream& os, const Date& dt)
{
	os << dt.year << "-" << dt.month << "-" << dt.date;

	return os;
}
