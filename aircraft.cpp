#include "aircraft.h"

void AircraftList::SetPath()
{
    aircraftFilePath = QCoreApplication::applicationDirPath() + "//aircrafts.txt";
}

void AircraftList::ReadFile()
{
    QFile file(aircraftFilePath);
    if ((file.exists()) && (file.open(QIODevice::ReadOnly)))
    {
        QString str="";
        while(!file.atEnd())
        {
            str = file.readLine();
            if (str != "")
            {
                // Создание структуры судна
                QStringList flightData = str.split(' ');
                Aircraft *temp = new Aircraft;
                temp->pNext = NULL;
                temp->model = flightData.at(0);
                QString tmpStr = flightData.at(1);
                tmpStr = tmpStr.remove(tmpStr.length() - 2,2);
                temp->number = tmpStr;
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

// Деструктор
AircraftList::~AircraftList()
{
    while (Head)
    {
        Tail = Head->pNext;
        delete Head;
        Head = Tail;
        length = 0;
    }
}

// Проверка наличия добавляемого элемента в списке
bool AircraftList::IsAvailable(Aircraft *tmp)
{
    Aircraft *temp = Head;
    temp = Head;
    while (temp != NULL)
    {
        qDebug() << temp->number + " " + tmp->number;
        if (temp->number.toLower() == tmp->number.toLower())
        {
            return false;
        }
        temp = temp->pNext;
    }
    return true;
}

// Добавление элемента в список
void AircraftList::Add(Aircraft *tmp)
{
    Aircraft *temp = new Aircraft;
    temp->pNext = NULL;
    temp->model = tmp->model;
    temp->number = tmp->number;
    // Если список не пуст
    if (Head!=NULL)
    {
        temp -> pPrev = Tail;
        Tail -> pNext = temp;
        Tail = temp;
    }
    // Если список пустой
    else
    {
        temp -> pPrev = NULL;
        Head = Tail = temp;
    }
    length++;
}

// Запись списка в файл
void AircraftList::WriteFile()
{
    QFile file(aircraftFilePath);

    if (file.open(QIODevice::WriteOnly))
    {
        Aircraft *temp = Head;
        QTextStream stream(&file);
        stream.setCodec(QTextCodec::codecForName("UTF-8"));
        while (temp != NULL)
        {
            stream << temp->model << " " << temp->number + "\r\n";
            temp = temp->pNext;
        }
        file.close();
    }
}

// Вывод списка на экран
void AircraftList::ShowList(QListWidget *lAircraft)
{
    Aircraft *temp = Head;
    lAircraft->clear();
    while (temp != NULL)
    {
        QString str = temp->model + " " + temp->number;
        lAircraft->addItem(str);
        temp = temp->pNext;
    }
}

// Вывод списка на экран, соответсвующего заданным параметрам поиска
void AircraftList::ShowSearchList(QListWidget *Aircrafts, Aircraft aircraft)
{
    Aircraft *tmp = Head;
    Aircrafts->clear();
    while (tmp != NULL)
    {
        if (tmp->model.toLower().contains(aircraft.model.toLower()) && tmp->number.toLower().contains(aircraft.number.toLower()))
        {
            Aircrafts->addItem(tmp->model + " " + tmp->number);
        }
        tmp = tmp->pNext;
    }
}

// Удаление элемента из списка
void AircraftList::Del(QString aircraftStr)
{
    // Вычисление индекса удаляемого элемента
    int x = 1;
    QStringList tempList = aircraftStr.split(' ');
    Aircraft *tmp = Head;
    while (tmp != NULL)
    {
        if (tmp->model.contains(tempList[0]) && tmp->number.contains(tempList[1]))
        {
            break;
        }
        x++;
        tmp = tmp->pNext;
    }

    // Если элемент первый и не единственный
    if ((x==1) and (Head->pNext))
    {
        Aircraft *temp=Head;
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
        length = 0;
        return;
    }

    // Если элемент последний
    if (x == length)
    {
        Aircraft *temp=Tail;
        Tail=Tail->pPrev;
        Tail->pNext=NULL;
        delete temp;
        length--;
        return;
    }

    // Если элемент находится в середине
    Aircraft *temp=Head,*temp2;
    for (int i = 0;i < x-1; i++)
    {
        temp=temp->pNext;
    }
    temp2=temp;
    temp2->pPrev->pNext=temp->pNext;
    temp2->pNext->pPrev=temp->pPrev;
    delete temp;
    length--;
}
