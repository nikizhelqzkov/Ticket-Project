#include "Room.h"
#include <iostream>
#include <cassert>
/**
 * @brief Валидация на матрицата съдържаща клиенти -> вектор от вектори.
 * Има връзка между стойностите на член-данните rows и columns и вектора от вектори 
 * @param rows 
 * @param cols 
 * @param m 
 * @return true 
 * @return false 
 */
bool isItOkMatrix(int rows, int cols, std::vector<std::vector<Client>> m)
{
    if (rows != m.size())
        return false;
    else
    {
        for (int i = 0; i < rows; i++)
        {
            if (m[i].size() != cols)
            {
                return false;
            }
        }
        return true;
    }
}
/**
 * @brief Construct a new Room:: Room object
 * 
 */
Room::Room()
{
    this->id = 0;
    this->rows = 0;
    this->placeOnRow = 0;
}
/**
 * @brief Construct a new Room:: Room object
 * 
 * @param id 
 * @param place 
 * @param rows 
 * @param placeOnRow 
 */
Room::Room( int id, const std::vector<std::vector<Client>> &place, /*std::string name,*/ int rows, int placeOnRow)
    :  id(id)
{
    this->setRows(rows);
    this->setCols(placeOnRow);
    assert(isItOkMatrix(this->rows, this->placeOnRow, place));
    this->matrix = place;
}
/**
 * @brief Destroy the Room:: Room object
 * 
 */
Room::~Room()
{
}
/**
 * @brief Construct a new Room:: Room object
 * 
 * @param other 
 */
Room::Room(const Room &other) :  id(other.id),rows(other.rows),
                                placeOnRow(other.placeOnRow), matrix(other.matrix)
{
}
/**
 * @brief Принтира на конзолата стойностите на член-данните на класа
 * 
 */
void Room::print() const
{
    std::cout <<  "Number: " << this->id << ", Rows: " << this->rows << ", Columns: " << this->placeOnRow << "\n\n";
    for (auto vec : this->matrix)
    {
        for (auto x : vec)
        {
            x.print();
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}
/**
 * @brief Извежда през поток към файл стойнсотите на член-данните на класа
 * 
 * @param out 
 */
void Room::print(std::ostream& out) const
{
    out <<this->id<<" "<< this->rows << " " << this->placeOnRow << "\n";
    for (auto vec : this->matrix)
    {
        for (auto x : vec)
        {
            x.print(out);
            out << "\n";
        }
        
    }
}
/**
 * @brief Мутатор извеждащ стойността на член-данната id
 * 
 * @return int 
 */
int Room::getId() const
{
    return this->id;
}
/**
 * @brief Мутатор извеждащ стойността на член-данната rows
 * 
 * @return int 
 */
int Room::getRows() const
{
    return this->rows;
}
/**
 * @brief Мутатор извеждащ стойността на член-данната matrix 
 * 
 * @return std::vector<std::vector<Client>> 
 */
std::vector<std::vector<Client>> Room::getplaces() const
{
    return this->matrix;
}
/**
 * @brief Мутатор извеждащ стойността на член-данната matrix, но не е константен
 * 
 * @return std::vector<std::vector<Client>> 
 */
std::vector<std::vector<Client>> Room::getplaces()
{
    return this->matrix;
}
/**
 * @brief Мутатор извеждащ стойността на член-данната placeOnRow 
 * 
 * @return int 
 */
int Room::getCols() const
{
    return this->placeOnRow;
}
/**
 * @brief Мутатор с аргумент, който се вкарва в член-данната id
 * 
 * @param id 
 */
void Room::setId(int id)
{
    this->id = id;
}
/**
 * @brief Мутатор с аргумент, който се вкарва в член-данната matrix
 * 
 * @param other 
 */
void Room::setMatrix(const std::vector<std::vector<Client>> &other)
{
    assert(isItOkMatrix(this->rows, this->placeOnRow, other));
    this->matrix = other;
}
/**
 * @briefМутатор с аргумент, който се вкарва в член-данната rows
 * 
 * @param rows 
 */
void Room::setRows(int rows)
{
    assert(rows > 0);
   
    this->rows = rows;
}
/**
 * @brief Мутатор с аргумент, който се вкарва в член-данната placeOnRow
 * 
 * @param cols 
 */
void Room::setCols(int cols)
{
    assert(cols > 0);
    this->placeOnRow = cols;
}
/**
 * @brief оператор за извеждане в поток на член-данните на класа
 * 
 * @param out 
 * @param room 
 * @return std::ostream& 
 */
std::ostream &operator<<(std::ostream &out, const Room &room)
{
    out << "Number: " << room.getId() << ", Rows: " << room.getRows() << ", Columns: " << room.getCols() << "\n\n";
    for (auto vec : room.getplaces())
    {
        for (auto x : vec)
        {
            x.print();
        }
        out << "\n";
    }
    return out;
}
/**
 * @brief Оператор за присвояване между 2 зали
 * 
 * @param other 
 * @return Room& 
 */
Room &Room::operator=(const Room &other)
{
    if (this != &other)
    {
        id = other.id;
        this->matrix = other.matrix;
        rows = other.rows;
        placeOnRow = other.placeOnRow;
    }
    return *this;
}
/**
 * @brief Изчистване на данните на една зала
 * 
 */
void Room::remove()
{
    this->id = 0;
    this->rows = 0;
    this->placeOnRow = 0;
}