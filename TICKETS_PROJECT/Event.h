#ifndef EVENT_H
#define EVENT_H

#include "Room.h"
/**
 * @brief Събитието е наследник на залата и взема негови методи като добавя дата и име на събитието + много методи важни за проекта
 * 
 */
class Event : public Room
{
private:
    std::string name;
    Date eventDate;

public:
    Event();
    Event(const Date &, std::string, int, const std::vector<std::vector<Client>> &, int, int);
    Event(const Event &);
    ~Event();
    Event &operator=(const Event &);
    std::string getName() const;
    Date getDate() const;
    void setName(std::string);
    void setDate(Date);
    void printFreeSeats();
    bool reserveFreeSeats();
    bool bought();
    bool checkCode(long unsigned int);
    Event& unbook(int row, int col);
    void Remove();
    void Print();
    void Print(std::ostream&) const;
};

#endif