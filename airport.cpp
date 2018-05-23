#include "airport.h"

// Установка пути для аэропортов
void AirportList::SetPath()
{
    airportFilePath = QCoreApplication::applicationDirPath() + "//airports.txt";
}

void AirportList::ReadFile()
{
    QFile file(airportFilePath);
    if ((file.exists()) && (file.open(QIODevice::ReadOnly)))
    {
        QString str="";
        while(!file.atEnd())
        {
            str = file.readLine();
            if (str != "")
            {
                Airport *temp = new Airport;
                temp->pNext = NULL;
                temp->name = str.remove(str.size() - 2,2);
                // Если список не пуст
                if (Head!=NULL)
                {
                    temp -> pPrev = Tail;
                    Tail -> pNext = temp;
                    Tail = temp;
                }
                // Если список пуст
                else
                {
                    temp -> pPrev = NULL;
                    Head = Tail = temp;
                }
                length++;
            }
        }
        file.close();
    }
}

// Вывод списка на экран, соответсвующего заданным параметрам поиска
void AirportList::ShowSearchList(QListWidget *lAirport, QString airportName)
{
    Airport *temp = Head;
    lAirport->clear();
    while (temp != NULL)
    {
        QString str = temp->name;
        if(str.toLower().contains(airportName.toLower()))
        {
            lAirport->addItem(str);
        }
        temp = temp->pNext;
    }
}

// Деструктор
AirportList::~AirportList()
{
    while (Head)
    {
        Tail = Head->pNext;
        delete Head;
        Head = Tail;
    }
}

// Проверка наличия добавляемого элемента в списке
bool AirportList::IsAvailable(QString name)
{
    Airport *temp = Head;
    while (temp != NULL)
    {
        if (temp->name == name)
        {
            return false;
        }
        temp = temp->pNext;
    }
    return true;
}
// Добавление элемента в список
void AirportList::Add(QString name)
{
    Airport *temp = new Airport;

    temp->pNext = NULL;
    temp->name = name;

    // Если список не пуст
    if (Head!=NULL)
    {
        temp -> pPrev = Tail;
        Tail -> pNext = temp;
        Tail = temp;
    }
    // Если список пуст
    else
    {
        temp -> pPrev = NULL;
        Head = Tail = temp;
    }
    length++;
}

// Вывод списка в файл
void AirportList::WriteFile()
{
    QFile file(airportFilePath);
    if (file.open(QIODevice::WriteOnly))
    {
        // Временно указываем на адрес первого элемента
        Airport *temp = Head;
        QTextStream stream(&file);
        stream.setCodec(QTextCodec::codecForName("UTF-8"));
        // Пока не встретим пустое значение
        while (temp != NULL)
        {
            stream << temp->name + "\r\n";
            temp = temp->pNext;
        }
        file.close();
    }
}

// Вывод списка на экран
void AirportList::ShowList(QListWidget *lAirport)
{
    Airport *temp = Head;
    lAirport->clear();
    while (temp != NULL)
    {
        QString str = temp->name;
        lAirport->addItem(str);
        temp = temp->pNext;
    }
}

// Удаление элемента из списка
void AirportList::Del(QString airportName)
{
    // Вычисление индекса удаляемого элемента
    int x = 1;
    Airport *tmp = Head;
    while (tmp != NULL)
    {
        if (tmp->name == airportName)
        {
            break;
        }
        x++;
        tmp = tmp->pNext;
    }

    // Если элемент первый и не единственный
    if ((x==1) and (Head->pNext))
    {
        Airport *temp=Head;
        Head=Head->pNext;
        Head->pPrev=NULL;
        delete temp;
        length--;
        return ;
    }
    // Если элемент первый и единственный
    else if ((x==1) and (Head==Tail))
    {
        Head->pNext=NULL;
        Head=NULL;
        delete Head;
        length=0;
        return;
    }

    // Удаление последнего элемента
    if (x == length)
    {
        Airport *temp=Tail;
        Tail=Tail->pPrev;
        Tail->pNext=NULL;
        delete temp;
        length--;
        return;
    }

    // Удаление элемента из середины
    Airport *temp=Head,*temp2;
    for (int i=0;i<x-1;i++)
    {
        temp=temp->pNext;
    }
    temp2=temp;
    temp2->pPrev->pNext=temp->pNext;
    temp2->pNext->pPrev=temp->pPrev;
    delete temp;
    length--;
}
