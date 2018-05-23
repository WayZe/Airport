#ifndef AIRPORT_H
#define AIRPORT_H
#include "QString"
#include "QFile"
#include "QDebug"
#include "QTextEdit"
#include "QListWidget"
#include "iostream"
#include "QListWidget"
#include "QTextCodec"
#include "QCoreApplication"

struct Airport
{
    // Данные
    QString name;

    // Служебные поля
    Airport* pNext;
    Airport* pPrev;
};

class AirportList
{
private:
    Airport *Tail; //Указатели на адреса начала списка и его конца
    Airport *Head;
    QString airportFilePath = "";
    int length = 0;

public:
    AirportList():Head(NULL),Tail(NULL){}; //Инициализируем адреса как пустые
    ~AirportList(); //Деструктор
    void Add(QString name); //Функция добавления элементов в список
    void WriteFile();
    void ReadFile();
    void Del(QString airportName);
    void ShowList(QListWidget*);
    void SetPath();
    bool IsAvailable(QString);
    void ShowSearchList(QListWidget *lAirport, QString airportName);
};


#endif // AIRPORT_H
