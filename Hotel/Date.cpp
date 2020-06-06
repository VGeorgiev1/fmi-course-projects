#include "Date.h"
#include <string>
#include <stdexcept>
#include <iostream>


Date::Date() : year(0), month(0), date(0) {};


Date::Date(std::string date_string) {

	int a = date_string[4];

	if (date_string.find('-') == -1) {
		throw std::invalid_argument("Invalid date!");
	}
	int args = 0;

	int start = 0;
	while (args < 3) {
		int finish = date_string.find('-', start);


		std::string arg = date_string.substr(start, finish - start);
		int i_arg = std::stoi(arg);
			
		if (args == 0) {
			if (i_arg <= 0) {
				throw std::invalid_argument("Invalid date!");
			}
			year = i_arg;
		}
		else if (args == 1) {
			if (i_arg <= 0 || i_arg > 12) {
				throw std::invalid_argument("Invalid date!");
			}
			month = i_arg;
		}
		else {
			if (i_arg <= 0 || i_arg > 31) {
				throw std::invalid_argument("Invalid date!");
			}
			date = i_arg;
		}

		args++;

		start = finish + 1;
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
	int year_dates = (year - other.year) * 365;
	int month_date = (month - other.month) * 30;
	int days = (date - other.date) * 1;



	return (year_dates + month_date + days);
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
