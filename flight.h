#ifndef FLIGHT_H
#define FLIGHT_H

#include "QString"
#include "QFile"
#include "QDebug"
#include "QTextEdit"
#include "QListWidget"
#include "airport.h"
#include "QTextCodec"
#include "QCoreApplication"

struct Flight
{
    // Данные
    QString number;
    QString fromName;
    QString toName;
    QString aircraftNumber;

    // Служебные поля
    Flight* pNext;
    Flight* pPrev;
};

class FlightList
{
private:
    int number;
    QString flightFilePath = "";
    Flight *Tail; //Указатели на адреса начала списка и его конца
    Flight *Head;
    int length = 0;

public:
    FlightList():Head(NULL),Tail(NULL){}; //Инициализируем адреса как пустые
    ~FlightList(); //Деструктор
    void Add(Flight*); //Функция добавления элементов в список
    void WriteFile();
    void ReadFile();
    void ShowList(QListWidget*);
    void SetPath();
    bool IsAvailable(Flight *tmp);
    void Del(QString flightStr);
    void ShowSearchList(QListWidget *Flights, Flight flight);
};

#endif // FLIGHT_H
