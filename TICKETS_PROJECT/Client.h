#ifndef CLIENT_H
#define CLIENT_H

#include "Date.h"
#include <string>
//#include "DataOfRooms.h"
/**
 * @brief Класът Client съдържа данни за едно място в една зала както и за данни при покупка или ресервиране на билет 
 * 
 */
class Client
{
    
private:

    int row;
    int col;
    Date date;
    bool reserve;
    bool buy;
    std::string note;
    std::string name;
    long unsigned int serialNumber;

public:
    Client();
    Client(int, int, Date, std::string, std::string);
    Date getDate() const;
    void setDate(const Date&);
    void read();
    void read(std::istream&);
    void print();
    void print(std::ostream&);
    int getRow() const;
    int getCol() const;
    std::string getName() const;
    std::string getNote() const;
    long unsigned int getTicket() const;
    void setName(std::string);
    bool getReserve() const;
    bool getBuy() const;
    void checkCode();
    Client& remove();

    // bool getRooms(const EventArr &);
};

#endif