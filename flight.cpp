#include "flight.h"

// Установка пути к файлу рейсов
void FlightList::SetPath()
{
    flightFilePath = QCoreApplication::applicationDirPath() + "//flights.txt";
}

// Чтение файла с рейсами
void FlightList::ReadFile()
{
    QFile file(flightFilePath);
    // Если файл существует и открыт для чтения
    if ((file.exists()) && (file.open(QIODevice::ReadOnly)))
    {
        QString str="";
        while(!file.atEnd())
        {
            str = file.readLine();
            if(str != "")
            {
                // Создание структуры рейса
                QStringList flightData = str.split(' ');
                Flight *temp = new Flight;
                temp->pNext = NULL;
                temp->number = flightData.at(0);
                temp->fromName = flightData.at(1);
                temp->toName = flightData.at(2);
                QString tmpStr = flightData.at(3);
                tmpStr = tmpStr.remove(tmpStr.length() - 2, 2);
                temp->aircraftNumber = tmpStr;

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
FlightList::~FlightList()
{
    while (Head)
    {
        Tail = Head->pNext;
        delete Head;
        Head = Tail;
    }
    length = 0;
}

// Проверка наличия добавляемого элемента в списке
bool FlightList::IsAvailable(Flight *tmp)
{
    Flight *temp = Head;
    temp = Head;

    while (temp != NULL) // Пока не встретим пустое значение
    {
        if (temp->number == tmp->number)//Выводим каждое считанное значение на экран
        {
            return false;
        }
        temp = temp->pNext; //Смена адреса на адрес следующего элемента
    }

    return true;
}

// Добавление рейса в список
void FlightList::Add(Flight *flight)
{
    // Создание структуры рейсы
    Flight *temp = new Flight;
    temp->pNext = NULL;
    temp->number = flight->number;
    temp->fromName = flight->fromName;
    temp->toName = flight->toName;
    temp->aircraftNumber = flight->aircraftNumber;

    // Если список не пуст
    if (Head!=NULL)
    {
        temp -> pPrev = Tail;
        Tail -> pNext = temp;
        Tail = temp;
        length++;
    }
    else //Если список пустой
    {
        temp -> pPrev = NULL;
        Head = Tail = temp;
        length++;
    }
}

// Запись списка в файл
void FlightList::WriteFile()
{
    QFile file(flightFilePath);

    if (file.open(QIODevice::WriteOnly))
    {
        Flight *temp = Head;
        QTextStream stream(&file);
        stream.setCodec(QTextCodec::codecForName("UTF-8"));
        while (temp != NULL)
        {
            stream << temp->number << " " << temp->fromName << " " << temp->toName << " " << temp->aircraftNumber + "\r\n";
            temp = temp->pNext;
        }
        file.close();
    }
}

// Вывод списка на экран
void FlightList::ShowList(QListWidget *lFlight)
{
    lFlight->clear();
    Flight *temp = Head;
    while (temp != NULL)
    {
        QString str = temp->number + " " + temp->fromName + " " + temp->toName + " " + temp->aircraftNumber;
        lFlight->addItem(str);
        temp = temp->pNext;
    }
}

// Вывод списка на экран, соответсвующего заданным параметрам поиска
void FlightList::ShowSearchList(QListWidget *Flights, Flight flight)
{
    Flight *tmp = Head;
    Flights->clear();
    while (tmp != NULL)
    {
        if (tmp->number.toLower().contains(flight.number.toLower()) &&
            tmp->fromName.toLower().contains(flight.fromName.toLower()) &&
            tmp->toName.toLower().contains(flight.toName.toLower()) &&
            tmp->aircraftNumber.toLower().contains(flight.aircraftNumber.toLower()))
        {
            Flights->addItem(tmp->number + " " + tmp->fromName + " " + tmp->toName + " " + tmp->aircraftNumber);
        }
        tmp = tmp->pNext;
    }
}

// Удаление элемента списка
void FlightList::Del(QString flightStr)
{
    // Вычисление индекса удаляемого элемента
    int x = 1;
    QStringList tempList = flightStr.split(' ');
    Flight *tmp = Head;
    while (tmp != NULL)
    {
        if (tmp->number == tempList[0] && tmp->fromName == tempList[1] && tmp->toName == tempList[2] && tmp->aircraftNumber == tempList[3])
        {
            break;
        }
        x++;
        tmp = tmp->pNext;
    }

    // Если удаляемый элемент первый и не единственный
    if ((x == 1) && (Head->pNext))
    {
        Flight *temp = Head;
        Head = Head->pNext;
        Head->pPrev = NULL;
        delete temp;
        length--;
        return ;
    }
    // Если элемент первый и единственный
    else if ((x == 1) and (Head == Tail))
    {
        Head->pNext = NULL;
        Head = NULL;
        delete Head;
        length = 0;
        return;
    }

    // Если элемент последний
    if (x == length)
    {
        Flight *temp = Tail;
        Tail = Tail->pPrev;
        Tail->pNext = NULL;
        delete temp;
        length--;
        return;
    }

    // Если элемент в середине
    Flight *temp = Head,*temp2;

    for (int i = 0; i < x-1; i++)
        temp = temp->pNext;
    temp2 = temp;
    temp2->pPrev->pNext = temp->pNext;
    temp2->pNext->pPrev = temp->pPrev;
    delete temp;
    length--;
}
