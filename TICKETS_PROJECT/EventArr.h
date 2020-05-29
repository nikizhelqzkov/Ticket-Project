#ifndef Event_Arr
#define Event_Arr
#include "Event.h"
#include <vector>
/**
 * @brief Класът EventArr  съдържа вктор от събитията на проекта и големината му + методи
 * 
 */
class EventArr
{
private:
    std::vector<Event> data;
    size_t size;

public:
    EventArr();
    EventArr(const std::vector<Event> &, size_t);
    EventArr(const EventArr &);
    ~EventArr();
    void printArr(std::ostream&) const;
    void printArr() const;
    Event &operator[](int i);
    Event operator[](int) const;
    EventArr &addEvent(const Event &);
    bool removeEvent(const Event &);
    int getSize() const;
    std::vector<Event> getData() const;
    void freeseats(std::string, Date);
    void bookings(std::string, Date);
    void boughtTickets(std::string, Date);
    void checkTicket(long unsigned int serialNumber);
    void report(Date, Date);
    EventArr& unbook(std::string name, Date date, int row, int col);
};

#endif