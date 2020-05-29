#include "EventArr.h"
#include <iostream>
/**
 * @brief Construct a new Event Arr:: Event Arr object
 * 
 */
EventArr::EventArr()
{
    this->data.clear();
    this->size = 0;
}
/**
 * @brief Construct a new Event Arr:: Event Arr object
 * 
 * @param data 
 * @param size 
 */
EventArr::EventArr(const std::vector<Event> &data, size_t size)
{
    this->data = data;
    this->size = data.size();
}
/**
 * @brief Construct a new Event Arr:: Event Arr object
 * 
 * @param other 
 */
EventArr::EventArr(const EventArr &other)
{
    this->data = other.data;
    this->size = other.size;
}
/**
 * @brief Destroy the Event Arr:: Event Arr object
 * 
 */
EventArr::~EventArr()
{
}
/**
 * @brief Отпечатва цялата система от събития, зали, клиенти през файлов поток
 * 
 * @param out 
 */
void EventArr::printArr(std::ostream &out) const
{
    out << this->size << "\n";
    for (int i = 0; i < this->size; i++)
    {
        this->data[i].Print(out);
        // std::cout << this->data[i];
    }
}
/**
 * @brief Отпечатва на конзолата данните за всички събития и места във всяко събитие
 * 
 */
void EventArr::printArr() const
{
    for (int i = 0; i < this->size; i++)
    {
        // std::cout << this->data[i];
        this->data[i].Print(std::cout);
    }
}
/**
 * @brief Оператор [] връщаш оригинала на позиция от вектора(събитие на тази позиция), не е константен
 * 
 * @param i 
 * @return Event& 
 */
Event &EventArr::operator[](int i)
{
    return this->data[i];
}
/**
 * @brief Оператор [] връщащ копие на данните за позиция от вектора(събитие на тази позиция), константен е и не се променя
 * 
 * @param i 
 * @return Event 
 */
Event EventArr::operator[](int i) const
{
    return this->data[i];
}
/**
 * @brief Метод, който добаея събития във вектора от събития.
 * Ако съвпаднат име на събитие и датата, връща че е запазено такова събитие и не добавя още веднъж
 * 
 * @param other 
 * @return EventArr& 
 */
EventArr &EventArr::addEvent(const Event &other)
{
    bool flag = true;
    if (!this->data.empty())
    {

        for (int i = 0; i < this->size; i++)
        {
            if (data[i].getName() == other.getName() && data[i].getDate() == other.getDate())
            {
                std::cout << "ON THIS DATE THAT EVENT IS SAVED\n";
                return *this;
            }
        }
        //this->data.resize(1);
    }
    this->data.push_back(other);
    this->size++;
    return *this;
}
/**
 * @brief Премахва събитие от вектора със събития, ако бъде намерено това събитие по id 
 * 
 * @param other 
 * @return true 
 * @return false 
 */
bool EventArr::removeEvent(const Event &other)
{
    for (int i = 0; i < this->size; i++)
    {
        if (this->data[i].getId() == other.getId())
        {
            this->size--;
            this->data.erase(this->data.begin() + i);
            return true;
        }
    }
    return false;
}
/**
 * @brief Мутатор извеждащ стойността на член-данната size
 * 
 * @return int 
 */
int EventArr::getSize() const
{
    return this->size;
}
/**
 * @brief Мутатор извеждащ стойността на член-данната data
 * 
 * @return std::vector<Event> 
 */
std::vector<Event> EventArr::getData() const
{
    return this->data;
}
/**
 * @brief Метод, чрез който да изведем след проверка в йерахиите за свободните места по зададено име и дата на събитие
 * 
 * @param name 
 * @param date 
 */
void EventArr::freeseats(std::string name, Date date)
{
    std::cout << "\n\nFree seats in " << name << " on " << date << ": \n\n";
    for (int i = 0; i < this->data.size(); i++)
    {
        if (data[i].getName() == name && data[i].getDate() == date)
        {
            data[i].printFreeSeats();
        }
    }
}
/**
 * @brief Метод, чрез който да изведем след проверка в йерахиите за резервираните места по зададено име и дата на събитие
 * 
 */
void EventArr::bookings(std::string name, Date date)
{
    bool res1 = false;
    bool res2 = false;
    bool res3 = false;
    if (name == "")
    {
        std::cout << "\n\nReserve seats on " << date << ": \n\n";
        for (int i = 0; i < this->data.size(); i++)
        {
            if (data[i].getDate() == date)
            {

                std::cout << "Event " << data[i].getName() << ":\n";
                res1 = data[i].reserveFreeSeats();
            }
        }
    }
    else if (date.getYear() == 1)
    {
        std::cout << "\n\nReserve seats in " << name << ": \n\n";
        for (int i = 0; i < this->data.size(); i++)
        {
            if (data[i].getName() == name)
            {

                std::cout << "Event on :" << data[i].getDate() << ":\n";
                res2 = data[i].reserveFreeSeats();
            }
        }
    }
    else
    {
        std::cout << "\n\nReserve seats in " << name << " on " << date << ": \n\n";
        for (int i = 0; i < this->data.size(); i++)
        {
            if (data[i].getName() == name && data[i].getDate() == date)
            {

                res3 = data[i].reserveFreeSeats();
            }
        }
    }
    if (!res1 && !res2 && !res3)
    {
        std::cout << "No reserved tickets !!!\n";
    }
}
/**
 * @brief Метод, чрез който да изведем след проверка в йерахиите за купените билети по зададено име и дата на събитие
 * 
 * @param name 
 * @param date 
 */
void EventArr::boughtTickets(std::string name, Date date)
{
    bool res1 = false;
    bool res2 = false;
    bool res3 = false;
    if (name == "")
    {
        std::cout << "\n\nBought seats on " << date << ": \n\n";
        for (int i = 0; i < this->data.size(); i++)
        {
            if (data[i].getDate() == date)
            {

                std::cout << "Event " << data[i].getName() << ":\n";
                res1 = data[i].bought();
            }
        }
    }
    else if (date.getYear() == 1)
    {
        std::cout << "\n\nBought seats in " << name << ": \n\n";
        for (int i = 0; i < this->data.size(); i++)
        {
            if (data[i].getName() == name)
            {

                std::cout << "Event on :" << data[i].getDate() << ":\n";
                res2 = data[i].bought();
            }
        }
    }
    else
    {
        std::cout << "\n\nBought seats in " << name << " on " << date << ": \n\n";
        for (int i = 0; i < this->data.size(); i++)
        {
            if (data[i].getName() == name && data[i].getDate() == date)
            {

                res3 = data[i].bought();
            }
        }
    }
    if (!res1 && !res2 && !res3)
    {
        std::cout << "No bought tickets !!!\n";
    }
}
/**
 * @brief Метод, чрез който по номер на билет извежда данните за мястото му в събитието, съсържащо номера му , ако изобщо го има и е валиден билета
 * 
 * @param serialNumber 
 */
void EventArr::checkTicket(long unsigned int serialNumber)
{
    bool flag = false;
    bool valid = false;
    for (int i = 0; i < this->data.size(); i++)
    {
        flag = false;
        flag = data[i].checkCode(serialNumber);
        if (flag)
        {
            valid = true;
        }
    }
    if (!valid)
    {
        std::cout << "THAT TICKET NUMBER IS NOT VALID!!!\n";
    }
}
/**
 * @brief Отменя резервация по дадено име и дата на събитие и ред и място в реда ,където му е било запазено
 * Ако няма резервиран такъв билет, се съобщава за грешка
 * 
 * @param name 
 * @param date 
 * @param row 
 * @param col 
 * @return EventArr& 
 */
EventArr &EventArr::unbook(std::string name, Date date, int row, int col)
{
    bool flag = false;
    for (size_t i = 0; i < this->data.size(); i++)
    {
        std::cout << "here 1\n";
        if (this->data[i].getName() == name && this->data[i].getDate() == date)
        {
            flag = true;
            data[i] = data[i].unbook(row, col);
        }
    }
    if (!flag)
    {
        std::cout << "Your reservation is not on this date or in this event\n";
    }
    return *this;
}
/**
 * @brief Отчет за купените билети според събитията при зададени начална дата и крайна дата, през които да бъдат разгледани отчетите
 * 
 * @param from 
 * @param to 
 */
void EventArr::report(Date from, Date to)
{
    bool hasBought;
    std::cout << "\n";
    for (auto e : this->data)
    {
        if (from < e.getDate() && e.getDate() < to)
        {

            std::cout << "Event -> " << e.getName() << " , Date: " << e.getDate() << "\n";

            hasBought = e.bought();
            if (!hasBought)
            {
                std::cout << "NO BOUGHT TICKETS!!! \n";
            }
            else
            {
                std::cout << "\n";
            }
            std::cout << "\n";
        }
    }
}