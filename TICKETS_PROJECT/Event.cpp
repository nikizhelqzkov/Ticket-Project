#include "Event.h"
#include <iostream>
/**
 * @brief Construct a new Event:: Event object 
 * 
 */
Event::Event() : Room()
{
    eventDate = eventDate.getLiveData();
    this->name = "";
}
/**
 * @brief Construct a new Event:: Event object
 * 
 * @param eventDate 
 * @param name 
 * @param id 
 * @param place 
 * @param rows 
 * @param placeOnRow 
 */
Event::Event(const Date &eventDate, std::string name, int id, const std::vector<std::vector<Client>> &place, int rows, int placeOnRow)
    : Room(id, place, rows, placeOnRow), eventDate(eventDate), name(name) {}
    /**
     * @brief Construct a new Event:: Event object
     * 
     * @param other 
     */
Event::Event(const Event &other) : Room(other), eventDate(other.eventDate), name(other.name) {}
/**
 * @brief Destroy the Event:: Event object
 * 
 */
Event::~Event() {}
/**
 * @brief Оператор за присвояване между 2 събития
 * 
 * @param other 
 * @return Event& 
 */
Event &Event::operator=(const Event &other)
{
    if (this != &other)
    {
        eventDate = other.eventDate;
        name = other.name;
        id = other.id;
        this->matrix = other.matrix;
        rows = other.rows;
        placeOnRow = other.placeOnRow;
    }
    return *this;
}
/**
 * @brief Мутатор извеждащ стойността на член-данната name
 * 
 * @return std::string 
 */
std::string Event::getName() const
{
    return name;
}
/**
 * @brief Мутатор извеждащ стойността на член-данната eventDate
 * 
 * @return Date 
 */
Date Event::getDate() const
{
    return eventDate;
}
/**
 * @brief Мутатор с аргумент, който се вкарва в член-данната name
 * 
 * @param _name 
 */
void Event::setName(std::string _name)
{
    name = _name;
}
/**
 * @brief Мутатор с аргумент, който се вкарва в член-данната eventDate
 * 
 * @param date 
 */
void Event::setDate(Date date)
{
    eventDate = date;
}
/**
 * @brief Извежда данни за свободните места в матрицата от клиенти, като свободно място се брои ако е само резервирано
 * 
 */
void Event::printFreeSeats()
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            if (matrix[i][j].getName() == "FREE" || matrix[i][j].getName() == "" || matrix[i][j].getReserve() == true)
            {
                std::cout << "row: " << i + 1 << ", place: " << j + 1 << " \n";
            }
        }
    }
}
/**
 * @brief Извежда данни за резервираните места в събитието и ако няма такива връща булева стойност false иначе true
 * 
 * @return true 
 * @return false 
 */
bool Event::reserveFreeSeats()
{
    bool flag = false;
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            if (matrix[i][j].getReserve() == true)
            {
                flag = true;
                std::cout << "row: " << i + 1 << ", place: " << j + 1 << " \n";
            }
        }
    }
    return flag;
}
/**
 * @brief Извежда данни за купените билети в събитието и ако няма такива връща булева стойност false иначе true
 * 
 * @return true 
 * @return false 
 */
bool Event::bought()
{
    bool flag = false;
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            if (matrix[i][j].getBuy() == true)
            {
                flag = true;
                std::cout << "row: " << i + 1 << ", place: " << j + 1 << " \n";
            }
        }
    }
    return flag;
}
/**
 * @brief Проверва при подаден номер на билет дали той принадлежи на някое място или не.
 *  Ако съществува извежда данните на билета запазени в обекта клиент на позицията в матрицата
 * 
 * @param serialNumber 
 * @return true 
 * @return false 
 */
bool Event::checkCode(long unsigned int serialNumber)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            if (matrix[i][j].getTicket() == serialNumber)
            {
                std::cout<<"\n\nEvent name: "<<this->name<<"\n";
                matrix[i][j].checkCode();
                return true;
            }
        }
    }
    return false;
}
/**
 * @brief Отменя билет, от матрицата, ако той е бил резервиран
 * 
 * @param row 
 * @param col 
 * @return Event& 
 */
Event &Event::unbook(int row, int col)
{
    if (matrix[row - 1][col - 1].getReserve() == false)
    {
        std::cout << "That ticket is not reserved\n";
        return *this;
    }
    matrix[row - 1][col - 1] = matrix[row - 1][col - 1].remove();
    return *this;
}
/**
 * @brief Ичиства данните на класа Event и баща мu Room 
 * 
 */
void Event::Remove()
{
    Room::remove();
    eventDate = eventDate.getLiveData();
    this->name = "";
}
/**
 * @brief Извежда на конзолата данни на събитието и стартира метод от Room за извеждане на всички негови член данни
 * 
 */
void Event::Print()
{
    std::cout << this->name << ", " << this->eventDate << " , ";
    Room::print();
}
/**
 * @brief Извежда член-данните на Event и след това на Room във файлов поток
 * 
 * @param out 
 */
void Event::Print(std::ostream &out) const
{
    out << this->name << " " << this->eventDate;
    Room::print(out);
}
