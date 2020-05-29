#include "Date.h"
#include "Client.h"
#include "Room.h"
#include "Event.h"
#include "EventArr.h"
#include "SortClass.h"
// #include "Date.cpp"
// #include "Client.cpp"
// #include "Room.cpp"
// #include "Event.cpp"
// #include "EventArr.cpp"
//#include "SortClass.cpp"
#include <ctime>
#include <iostream>
#include <cassert>
#include <fstream>
#include <functional>

//g++ main.cpp Date.cpp Client.cpp Room.cpp Event.cpp EventArr.cpp SortClass.cpp
/**
 * @brief Изчиства данни от старо събитие и гопълни с данни
 * 
 * @param event 
 * @param nameOfEvent 
 * @param dateOfEvent 
 * @return Event& 
 */
Event &generate(Event &event, std::string nameOfEvent, Date dateOfEvent)
{
    event.Remove();
    event.setName(nameOfEvent);
    event.setDate(dateOfEvent);
    event.setId(rand() % 100);
    event.setRows(7);
    event.setCols(7);
    return event;
}
/**
 * @brief Чете данни на клиент , пълни ги във матрицата с места и обновява събитието като връща Event&
 * 
 * @param c 
 * @param event 
 * @return Event& 
 */
Event &readTORoom(Client &c, Event &event)
{
    bool f = true;

    std::cout << "\n";
    std::cin.ignore(1, '\n');
    do
    {

        std::vector<std::vector<Client>> temp;
        c.read();
        temp = event.getplaces();
        if (temp[c.getRow() - 1][c.getCol() - 1].getRow() == c.getRow() && temp[c.getRow() - 1][c.getCol() - 1].getCol() == c.getCol())
        {
            std::cout << "THIS PLACE IS BUSY! WRITE NEW SEAT:\n\n";
            f = false;
        }
        else
        {
            f = true;
            temp[c.getRow() - 1][c.getCol() - 1] = c;
            event.setMatrix(temp);
        }
    } while (!f);
    c.print();
    return event;
}
/**
 * @brief Функция, която е в помощ на UI на проекта и командата help
 * @return true 
 * @return false 
 */
bool helpCommander()

{
    bool help = true;
    bool helpFlag = true;
    std::cout << "\n\nWELCOME TO THE HELPING CENTER\n";
    std::cout << "\nThese are the starting commands that you can use:\n\n";
    std::cout << "1)open --> opens file\n2)save --> saves the opened file on his directory\n";
    std::cout << "3)save_as --> saves the opened file on new directory\n4)close -->close opened file\n";
    std::cout << "5)help --> give some information about your valid commands\n\n";
    do
    {
        std::cout << "Write that number if you are: \n";
        std::cout << "1)Moderator\n2)Client\n";
        int helpN;
        std::cin >> helpN;
        if (helpN == 1)
        {
            std::cout << "\nWelcome Mod!\nThese are your using commands:\n";
            std::cout << "1)addevent --> adding new event on EventBox \n2)freeseats --> report of freeseats on an event\n";
            std::cout << "3)bookings --> report of reserved tickets on an event\n";
            std::cout << "4)bought --> report of bought tickets on an event\n";
            std::cout << "5)report --> report of bought tickets from one date to other date\n\n";
            std::cout << "PRESS THE b for back!\n";
            char back;
            bool flagHelp = true;
            do
            {
                std::cin >> back;
                if (back == 'b')
                {
                    help = false;
                }
                else
                {
                    flagHelp = false;
                }
            } while (!flagHelp);
        }
        else if (helpN == 2)
        {
            std::cout << "\nWelcome Client!\nThese are your using commands:\n";
            std::cout << "\n1)ticket --> reserve or buy a ticket with name and date of the event, your seat, your name and some note\n";
            std::cout << "2)unbook --> cancel the reservation\n";
            std::cout << "3)check --> checking your ticket whether is valid and returning information of the ticket\n\n";

            std::cout << "PRESS THE b for back!\n";
            char back;
            bool flagHelp = true;
            do
            {
                std::cin >> back;
                if (back == 'b')
                {
                    help = false;
                }
                else
                {
                    flagHelp = false;
                }
            } while (!flagHelp);
        }
        else
        {
            helpFlag = false;
            std::cout << "Wrong number!\n\n";
        }
    } while (!helpFlag);
    return help;
}
/**
 * @brief Функция, която е в помощ на UI на проекта и командата close

 * @return true 
 * @return false 
 */
bool closeCommander()
{
    bool close = true;
    std::cout << "\n\nYOU CLOSED THE FILE!!!!\n";
    std::cout << "NOW WE WILL RETURN BACK TO THE START MENU!!!\n\n\n";
    close = false;
    return close;
}
/**
 * @brief Четене на данните за вектора от събития и връщайки EventArr&
 * 
 * @param studio 
 * @param c 
 * @return EventArr& 
 */
EventArr &read(EventArr &studio, Client &c)
{

    std::cout << "Enter the event name: ";
    std::string name;

    std::getline(std::cin, name);

    std::cout << "\nEnter the day, month and year of a event: ";
    unsigned int day, m, y;
    std::cin >> day >> m >> y;
    Date date(day, m, y);
    bool isItHave = false;
    for (size_t i = 0; i < studio.getSize(); i++)
    {

        if (studio[i].getName() == name && studio[i].getDate() == date)
        {
            isItHave = true;
            c.setDate(date);
            studio[i] = readTORoom(c, studio[i]);
        }
    }
    if (!isItHave)
    {
        std::cout << "The event on that date is missing!\n";
    }
    return studio;
}
/**
 * @brief Функция, която е в помощ на UI на проекта и командата unbook
 * 
 * 
 * @param studio 
 * @return EventArr& 
 */
EventArr &unbook(EventArr &studio)
{
    std::string nameCLose;
    std::cout << "Name of event: ";
    std::getline(std::cin, nameCLose);
    std::cout << "\n Enter the day, month and year of a event: ";
    unsigned int Day, month, year;
    std::cin >> Day >> month >> year;
    Date dateClose(Day, month, year);
    std::cout << "Enter your row and seat of a row: ";
    int row, col;
    std::cin >> row >> col;
    studio = studio.unbook(nameCLose, dateClose, row, col);
    std::cout << "\n";
    return studio;
}
/**
 * @brief Функция, която е в помощ на UI на проекта и командата check
 * 
 * 
 * @param studio 
 */
void checkTicket(EventArr &studio)
{
    long unsigned int tN;
    std::cout << "Your ticket number: ";
    std::cout << "\n";
    std::cin >> tN;
    studio.checkTicket(tN);
    std::cout << "\n\n";
}
/**
 * @brief Функция, която е в помощ на UI на проекта и командата report
 * 
 * 
 * @param st 
 */
void reportFromTo(EventArr st)
{

    std::cout << "\n\nWELCOME TO THE REPORT MODE!\nWrite the date from: ";
    int day, month, year;
    std::cin >> day >> month >> year;
    std::cout << "\nWrite the date to: ";
    int day2, month2, year2;
    std::cin >> day2 >> month2 >> year2;
    Date from(day, month, year);
    Date to(day2, month2, year2);
    /**
     * @brief Използваме статичния клас SortClass и ламда функцията(статичния метод)sort
     * функцията сорт използва логиката за работа на std::sort от библиоткета algorithm
     * Сравнява по две дати от събитията във вектора от събития и сортира в ред от най-ранна към по-късни дати
     */
    SortClass::sort(st, st.getSize(), [](Event a, Event b) { return b.getDate() < a.getDate(); });
    st.report(from, to);
}
/**
 * @brief Мейн функцията на проекта, в която са нужните обекти от класовете, различни променливи и UI  на проекта
 * 
 * @return int 
 */
int main()
{
    /**
 * @brief Извеждане на Текуща дата и задействане на функцията за произволно число
 * 
 */
    std::cout << "Live Date: ";
    srand(time(0));
    Date z1;
    z1.getLiveData();
    z1.print();
    std::cout << std::endl;
    std::string a;
    bool open = false;
    bool help = false;
    bool save = false;
    bool save_as = false;
    bool close = false;
    bool exit = false;
    /**
     * @brief Начало на UI
     * 
     */
    std::cout << "WELCOME TO THE TICKET CENTER!" << std::endl;
    /**
     * @brief Необходими променливи
     * 
     */
    EventArr st;
    bool canOpen = true;
    std::string fileName;
    bool closeC = true;
    bool isOpen = false;
    /**
     * @brief Основното меню е в do while конструкция, за да може лесно да се връща потребителя назад
     * 
     */
    do
    {
        open = false;
        help = false;
        save = false;
        save_as = false;
        close = false;
        exit = false;
        /**
         * @brief Показване на командите, от основното меню
         * 
         */
        std::cout << "Write one of the commands: " << std::endl
                  << "1)open" << std::endl
                  << "2)help" << std::endl
                  << "3)save" << std::endl
                  << "4)save_as" << std::endl
                  << "5)close" << std::endl
                  << "6)exit" << std::endl;

        std::cin >> a;

        if (a == "open" || a == "Open" || a == "OPEN" || a == "1")
        {
            /**
            * @brief Construct a new if object
            * Потребителя е влезнал в open.
            * Ако преди е бил влезнал и не е затворил с командата close, няма да може да отвори отворен файл
            * Трбява да избере име на файла, от който чете и след това ще се разбере дали той съществува и може да се чете от него.
            * След като извлече данните от четенето ще може да работи със системата
            * 
            */
            if (canOpen == false)
            {
                std::cout << "\n\n YOU CAN NOT OPEN AGAIN THE FILE! YOU CAN SAVE IT OR CLOSE IT!!!\n\n\n";
            }
            else if (canOpen == true)
            {
                closeC = true;
                int num;
                std::cout << "WRITE NAME OF THE FILE FOR READING: ";

                std::cin >> fileName;
                int size;
                std::ifstream in(fileName);
                if (!in.is_open())
                {
                    std::cout << "That file is missing\n\n\n";

                    in.close();
                }
                else
                {
                    /**
                     * @brief Успешно четене и начало на четенето от файл
                     * 
                     */
                    isOpen = true;
                    open = true;
                    canOpen = false;
                    in >> size;

                    for (size_t i = 0; i < size; i++)
                    {

                        std::string NameOfEvent;
                        in >> NameOfEvent;

                        int dayOfEvent, monthOfEvent, yearOfEvent, id, rows, cols;
                        in >> yearOfEvent >> monthOfEvent >> dayOfEvent;
                        in >> id >> rows >> cols;
                        Date dateOfEvent;
                        dateOfEvent.setDay(dayOfEvent);
                        dateOfEvent.setMonth(monthOfEvent);
                        dateOfEvent.setYear(yearOfEvent);
                        Event s;
                        s.setName(NameOfEvent);
                        s.setDate(dateOfEvent);
                        s.setId(id);
                        s.setRows(rows);
                        s.setCols(cols);
                        std::vector<std::vector<Client>> temp(rows, std::vector<Client>(cols));
                        for (size_t j = 0; j < rows; j++)
                        {
                            for (size_t k = 0; k < cols; k++)
                            {
                                Client cl;
                                cl.read(in);
                                temp[j][k] = cl;
                            }
                        }
                        s.setMatrix(temp);
                        st.addEvent(s);
                    }
                    in.close();
                    std::cout << "YOUR FILE IS OPEN!\n";
                    /**
                     * @brief Навлиане в основните методи на платформата след като е отворен файла.
                     * Преди това има следните възможности:
                     * - За напускане на командата open и така връщане към основното меню;
                     * - За отваряне на help и четене на основните методи на проекта.
                     * - Продължение към методите
                     */
                    std::cout << "NOW YOU CAN USE SEVERAL MODS! --> IT HAS DIFFERENT MODS FOR MODERATOR AND CLIENT\n\n";
                    std::cout << "Do you want help for methods? y or n: ";
                    char h;
                    std::cin >> h;
                    if (h == 'y')
                    {
                        bool he;
                        he = helpCommander();
                    }

                    char modOrCLient;
                    bool mOC = false;
                    do
                    {
                        /**
                         * @brief Избор дали да се отворят методите за Модератор или да се отворят методите за Клиент
                         * 
                         */
                        std::cout << "You are moderator or client? --> write m for moderator and c for client and b for back:\n";
                        std::cin >> modOrCLient;
                        if (modOrCLient == 'm')
                        {
                            mOC = true;
                            bool m = false;
                            /**
                             * @brief Знае се, че вече сме Модератори
                             * Вижда се на конзолата какво можем да ползваме и си избираме
                             * 
                             */
                            do
                            {
                                std::cout << "\nWelcome Mod!\nThese are your using commands:\n";
                                std::string mV;
                                std::cout << "1)addevent --> adding new event on EventBox \n";
                                std::cout << "2)freeseats --> report of freeseats on an event\n";
                                std::cout << "3)bookings --> report of reserved tickets on an event\n";
                                std::cout << "4)bought --> report of bought tickets on an event\n";
                                std::cout << "5)report --> report of bought tickets from one date to other date\n";
                                std::cout << "6)back\n";
                                std::cout << "WRITE THE NAME OF COMMAND OR THE NUMBER: \n";
                                std::cin >> mV;
                                if (mV == "1" || mV == "addevent" || mV == "Addevent" || mV == "ADDEVENT" || mV == "AddEvent")
                                {
                                    /**
                                     * @brief Създаване на събитие
                                     * 
                                     */
                                    m = true;
                                    mOC = false;

                                    std::cout << "\n";
                                    std::cin.ignore(1, '\n');
                                    std::cout << "\n";

                                    std::vector<std::vector<Client>> v(7, std::vector<Client>(7));
                                    for (int i = 0; i < v.size(); i++)
                                    {
                                        for (int j = 0; j < v[i].size(); j++)
                                        {
                                            v[i][j].setName("FREE");
                                        }
                                    }
                                    std::cout << "Write the name of event: ";
                                    std::string nameOfEvent;
                                    std::getline(std::cin, nameOfEvent);
                                    std::cout << "\n";
                                    std::cout << "Enter the date: ";
                                    int dayOfEvent2, monthOfEvent2, yearOfEvent2;
                                    std::cin >> dayOfEvent2 >> monthOfEvent2 >> yearOfEvent2;
                                    Date dateOfEvent2;
                                    dateOfEvent2.setDay(dayOfEvent2);
                                    dateOfEvent2.setMonth(monthOfEvent2);
                                    dateOfEvent2.setYear(yearOfEvent2);

                                    Event event;
                                    event = generate(event, nameOfEvent, dateOfEvent2);
                                    event.setMatrix(v);

                                    st = st.addEvent(event);

                                    for (int i = 0; i < v.size(); i++)
                                    {
                                        for (int j = 0; j < v[i].size(); j++)
                                        {
                                            v[i][j].setName("FREE");
                                            v[i][j].remove();
                                        }
                                    }
                                }
                                else if (mV == "2" || mV == "freeseats" || mV == "Freeseats" || mV == "FREESEATS" || mV == "FreeSeats")
                                {
                                    /**
                                     * @brief Информация за свободните места
                                     * 
                                     */
                                    std::cin.ignore(1, '\n');
                                    std::cout << "Enter the name of event for freeseats: ";
                                    std::string freeSeats;
                                    std::getline(std::cin, freeSeats);
                                    std::cout << "\n";
                                    int dF, mF, yF;
                                    std::cout << "Enter the date of an event: ";
                                    std::cin >> dF >> mF >> yF;
                                    Date DF(dF, mF, yF);
                                    std::cin.ignore(1, '\n');
                                    st.freeseats(freeSeats, DF);
                                    std::cout << "\n";
                                }
                                else if (mV == "3" || mV == "bookings" || mV == "Bookings" || mV == "BOOKINGS")
                                {
                                    /**
                                     * @brief Информация за резервираните места
                                     * 
                                     */
                                    std::cin.ignore(1, '\n');
                                    std::cout << "Enter the name of event for bookings: ";
                                    std::string bookings;
                                    std::getline(std::cin, bookings);
                                    std::cout << "\n";
                                    int dB, mB, yB;
                                    std::cout << "Enter the date of an event: ";
                                    std::cin >> dB >> mB >> yB;
                                    Date DB(dB, mB, yB);
                                    std::cin.ignore(1, '\n');
                                    st.bookings(bookings, DB);
                                }
                                else if (mV == "4" || mV == "bought" || mV == "Bought" || mV == "BOUGHT")
                                {
                                    /**
                                     * @brief Информация за купените билети
                                     * 
                                     */
                                    std::cin.ignore(1, '\n');
                                    std::cout << "Enter the name of event for report: ";
                                    std::string bT;
                                    std::getline(std::cin, bT);
                                    std::cout << "\n";
                                    int dR, mR, yR;
                                    std::cout << "Enter the date of an event: ";
                                    std::cin >> dR >> mR >> yR;
                                    Date DR(dR, mR, yR);
                                    std::cin.ignore(1, '\n');
                                    st.boughtTickets(bT, DR);
                                }
                                else if (mV == "5" || mV == "report" || mV == "Report" || mV == "REPORT")
                                {
                                    /**
                                     * @brief Construct a new report From To object
                                     * Отчет за купените билети от една дата до друга дата
                                     */
                                    reportFromTo(st);
                                }
                                else if (mV == "6" || mV == "back" || mV == "Back" || mV == "BACK")
                                {
                                    /**
                                     * @brief Напускане на режим Модератори стъпка назад
                                     * 
                                     */
                                    m = true;
                                    mOC = false;
                                }
                                else
                                {
                                    std::cout << "\nUNVALID COMMAND!!! WRITE AGAIN!!!\n";
                                    m = false;
                                }

                            } while (!m);
                        }
                        else if (modOrCLient == 'c')
                        {
                            /**
                             * @brief Знае се, че вече сме Клиенти
                             * Вижда се на конзолата какво можем да ползваме и си избираме
                             * 
                             */
                            mOC = true;
                            bool cl = false;
                            do
                            {
                                std::cout << "\nWelcome Client!\nThese are your using commands:\n";
                                std::string cV;

                                std::cout << "\n1)ticket --> reserve or buy a ticket with name and date of the event, your seat, your name and some note\n";
                                std::cout << "2)unbook --> cancel the reservation\n";
                                std::cout << "3)check --> checking your ticket whether is valid and returning information of the ticket\n\n";
                                std::cout << "4)back\n";
                                std::cout << "WRITE THE NAME OF COMMAND OR THE NUMBER: \n";
                                std::cin >> cV;
                                if (cV == "1" || cV == "ticket" || cV == "Ticket" || cV == "TICKET")
                                {
                                    /**
                                     * @brief Според името на събитието и датата можем да:
                                     * - Купим билет за събитието
                                     * - Резервираме място за събитието
                                     */
                                    cl = true;
                                    mOC = false;

                                    std::cout << "\n";
                                    std::cin.ignore(1, '\n');
                                    std::cout << "\n";
                                    std::vector<std::vector<Client>> v(7, std::vector<Client>(7));
                                    for (int i = 0; i < v.size(); i++)
                                    {
                                        for (int j = 0; j < v[i].size(); j++)
                                        {
                                            v[i][j].setName("FREE");
                                        }
                                    }

                                    Client c;

                                    st = read(st, c);
                                }
                                else if (cV == "2" || cV == "unbook" || cV == "Unbook" || cV == "UNBOOK")
                                {
                                    /**
                                     * @brief Отменяме резервация подавайки:
                                     * - Име на събитие
                                     * - Дата на събитието
                                     * - Ред и място в реда, където ни е било резервирно
                                     */
                                    std::cin.ignore(1, '\n');
                                    st = unbook(st);
                                }
                                else if (cV == "3" || cV == "check" || cV == "Check" || cV == "CHECK")
                                {
                                    /**
                                     * @brief Информация за билета ни дали е валиден и информацията в него
                                     * 
                                     */
                                    std::cin.ignore(1, '\n');
                                    checkTicket(st);
                                }
                                else if (cV == "4" || cV == "back" || cV == "Back" || cV == "BACK")
                                {
                                    /**
                                     * @brief Напускане на режим Client и  стъпка назад
                                     * 
                                     */
                                    cl = true;
                                    mOC = false;
                                }
                                else
                                {
                                    std::cout << "\nUNVALID COMMAND!!! WRITE AGAIN!!!\n";
                                    cl = false;
                                }

                            } while (!cl);
                        }
                        else if (modOrCLient == 'b')
                        {
                            /**
                             * @brief Напускане на основното меню с последно запитване преди да го напуснем дали сме сигурни в това решение
                             * 
                             */
                            bool t = true;
                            do
                            {
                                std::cout << "ARE YOU SURE THAT YOU WANT TO LEAVE\n";
                                std::cout << "(IF PRESS y you will have chance to save your new updates but if you not save and press again open you will lost your saves)\n";
                                std::cout << "y/n: ";
                                char YN;
                                std::cin >> YN;
                                if (YN == 'y' || YN == 'Y')
                                {
                                    mOC = true;
                                    t = true;
                                }
                                else if (YN == 'n' || YN == 'N')
                                {

                                    t = true;
                                }
                                else if (YN != 'y' && YN != 'Y' && YN != 'n' && YN != 'N')
                                {
                                    std::cout << "INVALID COMMAND!!!\n";
                                    t = false;
                                }
                            } while (!t);
                        }
                        else if (modOrCLient != 'c' && modOrCLient != 'm')
                        {
                            std::cout << "Write again your decision: \n";
                        }
                    } while (!mOC);

                    open = false;
                }
            }
        }
        else if (a == "help" || a == "Help" || a == "HELP" || a == "2")
        {
            /**
             * @brief Отваря помощния център, където да разберем за методите в проекта
             * 
             */
            help = helpCommander();
        }
        else if (a == "save" || a == "Save" || a == "SAVE" || a == "3")
        {
            /**
             * @brief Construct a new if object
             * Запазва данните на системата във файла, който е бил отворен в open
             * Ако не е бил отворен файл или е бил затвоен, извежда, че не може да запише празен файл
             */
            if (closeC == false || isOpen == false)
            {
                std::cout << "\n\nYOU CAN NOT SAVE THE EMPTY FILE!!!!\n\n";
            }
            else
            {
                save = true;
                std::cout << "YOUR FILE IS SAVED ON " << fileName << " !!! \n\n";
                std::ofstream out(fileName);
                st.printArr(out);
                out.close();
                canOpen = false;
                save = false;
            }
        }
        else if (a == "save_as" || a == "Save_as" || a == "SAVE_AS" || a == "Save_As" || a == "4")
        {

            /**
             * @brief Construct a new if object
             * Запазва данните на системата във файл, който е написан от потребителя
             * Ако не е бил отворен файл или е бил затвоен, извежда, че не може да запише празен файл
             */
            if (closeC == false || isOpen == false)
            {
                std::cout << "\n\nYOU CAN NOT SAVE THE EMPTY FILE!!!!\n\n";
            }
            else
            {
                save_as = false;
                std::cout << "WRITE NAME OF THE FILE FOR SAVING: ";
                std::string fileName2;
                std::cin >> fileName2;
                std::ofstream out(fileName2);
                st.printArr(out);
                out.close();
                std::cout << "YOUR FILE IS SAVED ON " << fileName2 << " !!! \n\n";
                fileName = fileName2;

                canOpen = false;
            }
        }
        else if (a == "close" || a == "Close" || a == "CLOSE" || a == "5")
        {
            /**
             * @brief Construct a new if object
             * Затваря отворения файл и отклюва възможността за отваряне на файл. Ако не са запазени данните преди затваряне , те се изгубват
             */
            if (isOpen == false)
            {
                std::cout << "\n\nYOU CAN NOT CLOSE THE EMPTY FILE!!!!\n\n";
            }
            else
            {
                close = closeCommander();
                closeC = false;
                canOpen = true;
                isOpen = false;
                EventArr t;
                st = t;
            }
        }
        else if (a == "exit" || a == "Exit" || a == "EXIT" || a == "6")
        {
            /**
             * @brief Спиране на приложението
             * 
             */
            exit = true;
            std::cout << "GOOD BYE !!!\n";
            return 0;
        }
        else
        {
            std::cout << "WRITE AGAIN CORRECT COMMAND\n\n\n";
        }
    } while (!open && !help && !save && !save_as && !close && !exit);
    return 0;
}