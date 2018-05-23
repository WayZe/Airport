#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "QString"
#include "QTextEdit"
#include "QListWidget"
#include "airport.h"
#include "iostream"
#include "QFile"
#include "QTextStream"
#include "QListWidget"
#include "QTextCodec"
#include "QCoreApplication"

struct Aircraft
{
    // Данные
    QString model;
    QString number;

    // Служебные поля
    Aircraft* pNext;
    Aircraft* pPrev;
};

class AircraftList
{
private:
    Aircraft *Tail; //Указатели на адреса начала списка и его конца
    Aircraft *Head;
    QString aircraftFilePath = "";
    int length = 0;

public:
    AircraftList():Head(NULL),Tail(NULL){}; //Инициализируем адреса как пустые
    ~AircraftList(); //Деструктор
    void Add(Aircraft*); //Функция добавления элементов в список
    void WriteFile();
    void ReadFile();
    void ShowList(QListWidget*);
    void Del(QString aircraftStr);
    void SetPath();
    bool IsAvailable(Aircraft *);
    void ShowSearchList(QListWidget *Flights, Aircraft aircraft);
};


#endif // AIRCRAFT_H
