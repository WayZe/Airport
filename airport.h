#ifndef AIRPORT_H
#define AIRPORT_H
#include "QString"
#include "QFile"
#include "QDebug"
#include "QTextEdit"
#include "QListWidget"

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
    void Show(QTextEdit *); //Функция отображения списка на экране
    void Add(QString name); //Функция добавления элементов в список
    void WriteFile();
    void ReadFile();
    void Clear();
    void Del(QString airportName);
    void ShowList(QListWidget*);
    int getLength();
    void SetPath();
    bool IsAvailable(QString);
    void ShowSearchList(QListWidget *lAirport, QString airportName);
};


#endif // AIRPORT_H
