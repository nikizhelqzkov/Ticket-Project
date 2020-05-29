#include <iostream>
#include <ctime>
#include "Date.h"
/**
 * @brief Construct a new Date:: Date object
 * 
 * 
 */
Date::Date()
{
	this->day = 1;
	this->month = 1;
	this->year = 1;
}
/**
 * @brief Construct a new Date:: Date object
 * 
 * @param d 
 * @param m 
 * @param y 
 */
Date::Date(unsigned d, unsigned m, unsigned y)
{
	
	if (isValidDate(d, m, y))
	{
		this->day = d;
		this->month = m;
		this->year = y;
	}

	else
	{
		this->day = 1;
		this->month = 1;
		this->year = 2020;
	}
}
/**
 * @brief Construct a new Date:: Date object
 * 
 * @param other 
 */
Date::Date(const Date &other)
{
	this->day = other.day;
	this->month = other.month;
	this->year = other.year;
}
/**
 * @brief Четене от конзола на дата докато тя не е валидна според условията за валидност
 * 
 */
void Date::read()
{
	unsigned short day, month, year;

	do
	{
		std::cout << "Day: ";
		std::cin >> day;
		std::cout << "Month: ";
		std::cin >> month;
		std::cout << "Year: ";
		std::cin >> year;
	} while (!isValidDate(day, month, year));

	this->day = day;
	this->month = month;
	this->year = year;
}
/**
 * @brief Принтиране на член-данните за дата в стандартен тип
 * 
 */
void Date::print() const
{
	std::cout << this->year << '-' << this->month << '-' << this->day;
}
/**
 * @brief Изпращане на член-данните за датата във файл чрез файлов поток
 * 
 * @param out 
 */
void Date::print(std::ostream& out) const
{
	out << this->year << ' ' << this->month << ' ' << this->day;
}
/**
 * @brief Проверка дали има правилен номер на месец(0<месец<=12) и според месеца проверка дали съществува такъв ден като номер при условие дали е високосна годината или не
 *  и връща дали е правилна датата
 * 
 * @param d 
 * @param m 
 * @param y 
 * @return true 
 * @return false 
 */
bool Date::isValidDate(unsigned short d, unsigned short m, unsigned short y)
{
	if (!y)
		return false;

	if (m < 1 || m > 12)
		return false;

	bool leapYear = (y % 4 == 0) && !(y % 100 == 0 && y % 400 != 0);

	unsigned maxDays;
	switch (m)
	{
	case 2:
		maxDays = 28 + leapYear;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		maxDays = 30;
		break;
	default:
		maxDays = 31;
		break;
	}

	return d > 0 && d <= maxDays;
}
/**
 * @briefМутатор извеждащ стойността на член-данната day
 * 
 * @return unsigned 
 */
unsigned Date::getDay() const
{
	return this->day;
}
/**
 * @brief Мутатор с аргумент, който се вкарва в член-данната day
 * 
 * @param newDay 
 */
void Date::setDay(unsigned newDay)
{
	if (isValidDate(newDay, this->month, this->year))
		this->day = newDay;
}
/**
 * @brief Мутатор извеждащ стойността на член-данната month
 * 
 * @return unsigned 
 */
unsigned Date::getMonth() const
{
	return this->month;
}
/**
 * @brief Мутатор с аргумент, който се вкарва в член-данната month
 * 
 * @param newMonth 
 */
void Date::setMonth(unsigned newMonth)
{
	if (isValidDate(this->day, newMonth, this->year))
		this->month = newMonth;
}
/**
 * @brief Мутатор извеждащ стойността на член-данната year
 * 
 * @return unsigned 
 */
unsigned Date::getYear() const
{
	return this->year;
}
/**
 * @brief Мутатор с аргумент, който се вкарва в член-данната year
 * 
 * @param newYear 
 */
void Date::setYear(unsigned newYear)
{
	if (isValidDate(this->day, this->month, newYear))
		this->year = newYear;
}
/**
 * @brief Булева функция проверяваща дали две дати съвпадат
 * 
 * @param other 
 * @return true 
 * @return false 
 */
bool Date::isEqual(const Date &other) const
{
	return this->day == other.day && this->month == other.month && this->year == other.year;
}
/**
 * @brief Булева функция проверяваща дали една дата е преди друга дата
 * 
 * @param other 
 * @return true 
 * @return false 
 */
bool Date::isBefore(const Date &other) const
{
	if (this->year < other.year)
		return true;
	if (this->year > other.year)
		return false;

	if (this->month < other.month)
		return true;
	if (this->month > other.month)
		return false;

	return this->day < other.day;
}
/**
 * @brief Функция която чрез библиотекта ctime и специална структора за време извежда текущата дата 
 * 
 * @return Date& 
 */
Date &Date::getLiveData()
{
	time_t tt;
	struct tm *ti;
	time(&tt);
	ti = localtime(&tt);
	this->month = ti->tm_mon + 1;
	this->year = ti->tm_year + 1900;
	this->day = ti->tm_mday;
	return *this;
}
/**
 * @brief Оператор за присвояване на 2 дати
 * 
 * @param other 
 * @return Date& 
 */
Date &Date::operator=(const Date &other)
{
	this->day = other.day;
	this->month = other.month;
	this->year = other.year;
	return *this;
}
/**
 * @brief Булев оператор проверяващ дали две дати съвпадат
 * 
 * @param other 
 * @return true 
 * @return false 
 */
bool Date::operator==(const Date& other)const{
	return day==other.day && month==other.month && year==other.year;
}
/**
 * @brief Оператор за извеждане на данни в поток
 * 
 * @param out 
 * @param date 
 * @return std::ostream& 
 */
std::ostream &operator<<(std::ostream &out, const Date &date)
{
	// out << date.year << '-' << date.month << '-' << date.day<<" ";
		 out << date.year << ' ' << date.month << ' ' << date.day<<' ';
		 return out;

}
/**
 * @brief Булев оператор извеждащ дали една дата е преди друга дата
 * 
 * @param date 
 * @return true 
 * @return false 
 */
bool Date::operator<(const Date& date)const{
return isBefore(date);
}