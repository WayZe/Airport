#include "flight.h"
#include "airport.h"
#include "QListWidget"
#include "QTextCodec"
#include "QCoreApplication"

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
                    length++;
                }
                // Если список пуст
                else
                {
                    temp -> pPrev = NULL;
                    Head = Tail = temp;
                    length++;
                }
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

void FlightList::Add(Flight *flight)
{
    Flight *temp = new Flight; //Выделение памяти под новый элемент структуры
    temp->pNext = NULL; //Указываем, что изначально по следующему адресу пусто
    temp->number = flight->number;//Записываем значение в структуру
    temp->fromName = flight->fromName;
    temp->toName = flight->toName;
    temp->aircraftNumber = flight->aircraftNumber;

    if (Head!=NULL) //Если список не пуст
    {
        temp -> pPrev = Tail; //Указываем адрес на предыдущий элемент в соотв. поле
        Tail -> pNext = temp; //Указываем адрес следующего за хвостом элемента
        Tail = temp; //Меняем адрес хвоста
        length++;
    }
    else //Если список пустой
    {
        temp -> pPrev = NULL; //Предыдущий элемент указывает в пустоту
        Head = Tail = temp; //Голова=Хвост=тот элемент, что сейчас добавили
        length++;
    }
}

void FlightList::Show(QTextEdit* outTextEdit)
{
    QString str = "";
    //ВЫВОДИМ СПИСОК С НАЧАЛА
    Flight *temp = Head; //Временно указываем на адрес первого элемента
    while (temp != NULL) //Пока не встретим пустое значение
    {
        str += temp->number + " " + temp->fromName + " " + temp->toName + " " + temp->aircraftNumber; //Выводим каждое считанное значение на экран
        temp = temp->pNext; //Смена адреса на адрес следующего элемента
    }
    outTextEdit->setText(str);
}

void FlightList::WriteFile()
{
    QFile file(flightFilePath);

    if (file.open(QIODevice::WriteOnly))
    {
        Flight *temp = Head; //Временно указываем на адрес первого элемента
        QTextStream stream(&file);
        stream.setCodec(QTextCodec::codecForName("UTF-8"));
        while (temp != NULL) //Пока не встретим пустое значение
        {
            stream << temp->number << " " << temp->fromName << " " << temp->toName << " " << temp->aircraftNumber + "\r\n";
            qDebug() << temp->number + temp->fromName + temp->toName + temp->aircraftNumber;
            temp = temp->pNext;
        }
        file.close();
    }
}

void FlightList::ShowList(QListWidget *lFlight)
{
    Flight *temp = Head;
    lFlight->clear();
    while (temp != NULL) //Пока не встретим пустое значение
    {
        QString str = temp->number + " " + temp->fromName + " " + temp->toName + " " + temp->aircraftNumber;
        lFlight->addItem(str);
        temp = temp->pNext; //Смена адреса на адрес следующего элемента
    }
}

void FlightList::ShowSearchList(QListWidget *Flights, Flight flight)
{
    Flight *tmp = Head;
    Flights->clear();
    while (tmp != NULL) // Пока не встретим пустое значение
    {
        if (tmp->number.toLower().contains(flight.number.toLower()) &&
            tmp->fromName.toLower().contains(flight.fromName.toLower()) &&
            tmp->toName.toLower().contains(flight.toName.toLower()) &&
            tmp->aircraftNumber.toLower().contains(flight.aircraftNumber.toLower()))
        {
            Flights->addItem(tmp->number + " " + tmp->fromName + " " + tmp->toName + " " + tmp->aircraftNumber);
        }
        tmp = tmp->pNext; // Смена адреса на адрес следующего элемента
    }
}

/*ФУНКЦИЯ УДАЛЕНИЯ КОНКРЕТНОГО ЭЛЕМЕНТА ДВУСВЯЗНОГО СПИСКА*/
void FlightList::Del(QString flightStr)
{
    int x = 1;
    QStringList tempList = flightStr.split(' ');
    Flight *tmp = Head;
    while (tmp != NULL) // Пока не встретим пустое значение
    {
        if (tmp->number == tempList[0] && tmp->fromName == tempList[1] && tmp->toName == tempList[2] && tmp->aircraftNumber == tempList[3])
        {
            break;
        }
        x++;
        tmp = tmp->pNext; // Смена адреса на адрес следующего элемента
    }

    //Если удаляем первый элемент, то могут быть такие варианты
    //В списке есть только первый, в списке есть несколько элементов
    //Поэтому разбиваем логику выполнения
    if ((x==1) and (Head->pNext))
    { //Если удаляем первый, но есть и другие, то
        Flight *temp=Head;	//Указываем, что нам нужно начало списка
        Head=Head->pNext;	//Сдвигаем начало на следующий за началом элемент
        Head->pPrev=NULL;	//Делаем так, чтоб предыдущий началу элемент был пустым
        delete temp;		//Удаляем удаляемое начало
        length--;		//Обязательно уменьшаем счетчик
        return ;		//И выходим из функции
    }
    else if ((x==1) and (Head==Tail))
    { //Если удаляем первый, но в списке только 1 элемент
        Head->pNext=NULL;	//обнуляем все что нужно
        Head=NULL;
        delete Head;		//Удаляем указатель на начало
        length=0;		//Обязательно обозначаем, что в списке ноль элементов
        return;			//и выходим из функции
    }

    //Также может быть, что удаляемый элемент является последним элементом списка
    if (x == length)
    {
        Flight *temp=Tail;	//Указываем, что нам нужен хвост
        Tail=Tail->pPrev;	//Отодвигаем хвост немного назад
        Tail->pNext=NULL;	//Обозначаем, что впереди за хвостом пусто
        delete temp;	//Очищаем память от бывшего хвоста
        length--;		//Обязательно уменьшаем счетчик элементов
        return;		//И выходим из функции
    }

    //Если же удаляемый элемент лежит где-то в середине списка, то тогда его можно удалить
    Flight *temp=Head,*temp2; //temp-Удаляемый элемент, temp2 нужен, чтобы не потерять данные

    for (int i=0;i<x-1;i++)
        temp=temp->pNext;  //Идем к адресу удаляемого элемента
    temp2=temp;	//Временно запоминаем адрес удаляемого элемента
    temp2->pPrev->pNext=temp->pNext;	//Записываем данные, что следующий за перед сейчас удаляемым элементом - это следующий от удаляемого
    temp2->pNext->pPrev=temp->pPrev; //а предыдущий для следующего - это предыдущий для удаляемого
    delete temp; //теперь смело можно освободить память, удалив адрес на начало удаляемого элемента
    length--; //Обязательно уменьшаем число элементов в списке.
}

int FlightList::getLength()
{
    return length;
}
