#include "aircraft.h"
#include "iostream"
#include "QFile"
#include "QTextStream"
#include "QListWidget"
#include "airport.h"
#include "QTextCodec"
#include "QCoreApplication"

void AircraftList::SetPath()
{
    aircraftFilePath = //"/Users/andreymakarov/Langs/Qt/build-Airport-Desktop_Qt_5_10_1_clang_64bit-Debug/aircrafts.txt";
            QCoreApplication::applicationDirPath() + "//aircrafts.txt";
    qDebug() << QCoreApplication::applicationDirPath();
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
                QStringList flightData = str.split(' ');
                Aircraft *temp = new Aircraft; //Выделение памяти под новый элемент структуры
                temp->pNext = NULL;  //Указываем, что изначально по следующему адресу пусто
                temp->model = flightData.at(0);//Записываем значение в структуру
                QString tmpStr = flightData.at(1);
                qDebug() << tmpStr;
                tmpStr = tmpStr.remove(tmpStr.length() - 2,2);
                temp->number = tmpStr;
                qDebug() << temp->number;
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
        }
        file.close();
    }
}

AircraftList::~AircraftList() //Деструктор
{
    while (Head) //Пока по адресу на начало списка что-то есть
    {
        Tail = Head->pNext; //Резервная копия адреса следующего звена списка
        delete Head; //Очистка памяти от первого звена
        Head = Tail; //Смена адреса начала на адрес следующего элемента
        length = 0;
    }
}

void AircraftList::Show(QTextEdit* outTextEdit)
{
//    //ВЫВОДИМ СПИСОК С КОНЦА
//    //Временный указатель на адрес последнего элемента
//    while (temp!=NULL) //Пока не встретится пустое значение
//    {
//        qDebug() << temp->name << " "; //Выводить значение на экран
//        temp=temp->pPrev; //Указываем, что нужен адрес предыдущего элемента
//    }
//    cout<<"\n";

    QString str = "";
    //ВЫВОДИМ СПИСОК С НАЧАЛА
    Aircraft *temp = Head; //Временно указываем на адрес первого элемента
    while (temp != NULL) //Пока не встретим пустое значение
    {
        str += temp->model + " " + temp->number; //Выводим каждое считанное значение на экран
        temp = temp->pNext; //Смена адреса на адрес следующего элемента
    }
    outTextEdit->setText(str);
}

bool AircraftList::IsAvailable(Aircraft *tmp)
{
    Aircraft *temp = Head; //Выделение памяти под новый элемент структуры

    temp = Head;

    while (temp != NULL) // Пока не встретим пустое значение
    {
        if (temp->number == tmp->number + "\r\n")//Выводим каждое считанное значение на экран
        {
            return false;
        }
        temp = temp->pNext; //Смена адреса на адрес следующего элемента
    }

    return true;
}

void AircraftList::Add(Aircraft *tmp)
{
    Aircraft *temp = new Aircraft; //Выделение памяти под новый элемент структуры
    temp->pNext = NULL; //Указываем, что изначально по следующему адресу пусто
    temp->model = tmp->model;//Записываем значение в структуру
    temp->number = tmp->number;

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

void AircraftList::WriteFile()
{
    QFile file(aircraftFilePath);

    if (file.open(QIODevice::WriteOnly))
    {
        Aircraft *temp = Head; //Временно указываем на адрес первого элемента
        QTextStream stream(&file);
        stream.setCodec(QTextCodec::codecForName("UTF-8"));
        while (temp != NULL) //Пока не встретим пустое значение
        {
            stream << temp->model << " " << temp->number + "\r\n";
            temp = temp->pNext;
        }
        file.close();
    }
}

void AircraftList::ShowList(QListWidget *lAircraft)
{
    Aircraft *temp = Head;
    lAircraft->clear();
    while (temp != NULL) //Пока не встретим пустое значение
    {
        QString str = temp->model + " " + temp->number;
        lAircraft->addItem(str);
        temp = temp->pNext; //Смена адреса на адрес следующего элемента
    }
}

void AircraftList::Clear() //Деструктор
{
    while (Head) //Пока по адресу на начало списка что-то есть
    {
        Tail = Head->pNext; //Резервная копия адреса следующего звена списка
        delete Head; //Очистка памяти от первого звена
        Head = Tail; //Смена адреса начала на адрес следующего элемента
        length = 0;
    }
}

void AircraftList::ShowSearchList(QListWidget *Aircrafts, Aircraft aircraft)
{
    Aircraft *tmp = Head;
    Aircrafts->clear();
    while (tmp != NULL) // Пока не встретим пустое значение
    {
        if (tmp->model.toLower().contains(aircraft.model.toLower()) && tmp->number.toLower().contains(aircraft.number.toLower()))
        {
            Aircrafts->addItem(tmp->model + " " + tmp->number);
        }
        tmp = tmp->pNext; // Смена адреса на адрес следующего элемента
    }
}

/*ФУНКЦИЯ УДАЛЕНИЯ КОНКРЕТНОГО ЭЛЕМЕНТА ДВУСВЯЗНОГО СПИСКА*/
void AircraftList::Del(QString aircraftStr)
{
    int x = 1;
    QStringList tempList = aircraftStr.split(' ');
    Aircraft *tmp = Head;
    while (tmp != NULL) // Пока не встретим пустое значение
    {
        if (tmp->model.contains(tempList[0]) && tmp->number.contains(tempList[1]))
        {
            break;
        }
        x++;
        tmp = tmp->pNext; // Смена адреса на адрес следующего элемента
    }
    //Если удаляем первый элемент, то могут быть такие варианты
    //В списке есть только первый, в списке есть несколько элементов
    //Поэтому разбиваем логику выполнения
    if ((x==1) and (Head->pNext)){ //Если удаляем первый, но есть и другие, то
        Aircraft *temp=Head;	//Указываем, что нам нужно начало списка
        Head=Head->pNext;	//Сдвигаем начало на следующий за началом элемент
        Head->pPrev=NULL;	//Делаем так, чтоб предыдущий началу элемент был пустым
        delete temp;		//Удаляем удаляемое начало
        length--;		//Обязательно уменьшаем счетчик
        return ;		//И выходим из функции
    } else if ((x==1) and (Head==Tail)){ //Если удаляем первый, но в списке только 1 элемент

        Head->pNext=NULL;	//обнуляем все что нужно
        Head=NULL;
        delete Head;		//Удаляем указатель на начало
        length=0;		//Обязательно обозначаем, что в списке ноль элементов
        return;			//и выходим из функции
    }

    //Также может быть, что удаляемый элемент является последним элементом списка
    if (x == length)
    {
        Aircraft *temp=Tail;	//Указываем, что нам нужен хвост
        Tail=Tail->pPrev;	//Отодвигаем хвост немного назад
        Tail->pNext=NULL;	//Обозначаем, что впереди за хвостом пусто
        delete temp;	//Очищаем память от бывшего хвоста
        length--;		//Обязательно уменьшаем счетчик элементов
        return;		//И выходим из функции
    }

    //Если же удаляемый элемент лежит где-то в середине списка, то тогда его можно удалить
    Aircraft *temp=Head,*temp2; //temp-Удаляемый элемент, temp2 нужен, чтобы не потерять данные

    for (int i=0;i<x-1;i++) temp=temp->pNext;  //Идем к адресу удаляемого элемента

    temp2=temp;	//Временно запоминаем адрес удаляемого элемента
    temp2->pPrev->pNext=temp->pNext;	//Записываем данные, что следующий за перед сейчас удаляемым элементом - это следующий от удаляемого
    temp2->pNext->pPrev=temp->pPrev; //а предыдущий для следующего - это предыдущий для удаляемого
    delete temp; //теперь смело можно освободить память, удалив адрес на начало удаляемого элемента
    length--; //Обязательно уменьшаем число элементов в списке.
}

int AircraftList::getLength()
{
    return length;
}
