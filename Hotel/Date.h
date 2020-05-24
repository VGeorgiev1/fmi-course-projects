#ifndef DATE_H
#define DATE_H
#include <string>

class Date {
private:
	int year;
	int month;
	int date;
public:
	Date();
	Date(std::string date_string);

	bool operator <(const Date& other);
	bool operator >(const Date& other);
	bool operator==(const Date& other);
	bool operator!=(const Date& other);
	bool operator <=(const Date& other);
	bool operator >=(const Date& other);
	int operator-(const Date& other);
	friend std::ostream& operator <<(std::ostream& os, const Date& dt);

	int get_year() const;
	int get_month() const;
	int get_date() const;

};


#endif // !1
