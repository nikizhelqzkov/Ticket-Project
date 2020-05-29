#ifndef ROOM_H
#define ROOM_H
#include <vector>
#include <string>
//#include "Date.h"
#include "Client.h"
/**
 * @brief Класът Room  има за цел да съдържа базовите член-данни на една зала в някое събитие + някои спомагателни методи
 * 
 */
class Room
{
protected:
    int id;
    std::vector<std::vector<Client>> matrix;
    
    int rows;
    int placeOnRow;

public:
    Room();
    Room(int,const std::vector<std::vector<Client>>&,int, int);
    Room(const Room &);
    ~Room();
    void print()const;
    void print(std::ostream&)const;
    int getId()const;
    int getRows()const;
    int getCols()const;
    std::vector<std::vector<Client>>getplaces()const;
    std::vector<std::vector<Client>>getplaces();
    void setId(int);
    void setRows(int rows);
    void setCols(int cols);
    void setMatrix(const std::vector<std::vector<Client>>&);
    Room& operator=(const Room&);
    void remove();
}; 


#endif