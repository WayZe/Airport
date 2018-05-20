#include "airport.h"
#include "iostream"
#include "QListWidget"
#include "QTextCodec"
#include "QCoreApplication"

void AirportList::SetPath()
{
    airportFilePath = //"/Users/andreymakarov/Langs/Qt/build-Airport-Desktop_Qt_5_10_1_clang_64bit-Debug/airports.txt";
            QCoreApplication::applicationDirPath() + "//airports.txt";
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
                Airport *temp = new Airport; //Выделение памяти под новый элемент структуры
                temp->pNext = NULL;  //Указываем, что изначально по следующему адресу пусто
                temp->name = str.remove(str.size() - 2,2);//Записываем значение в структуру
                qDebug() << temp->name;
                // Если список не пуст
                if (Head!=NULL)
                {
                    temp -> pPrev = Tail; //Указываем адрес на предыдущий элемент в соотв. поле
                    Tail -> pNext = temp; //Указываем адрес следующего за хвостом элемента
                    Tail = temp; //Меняем адрес хвоста
                    length++; // Увелич
                }
                // Если список пустой
                else
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

void AirportList::ShowSearchList(QListWidget *lAirport, QString airportName)
{
    Airport *temp = Head;
    lAirport->clear();
    while (temp != NULL) // Пока не встретим пустое значение
    {
        QString str = temp->name;
        if(str.contains(airportName))
        {
            lAirport->addItem(str);
        }
        temp = temp->pNext; // Смена адреса на адрес следующего элемента
    }
}

AirportList::~AirportList() //Деструктор
{
    while (Head) //Пока по адресу на начало списка что-то есть
    {
        Tail = Head->pNext; //Резервная копия адреса следующего звена списка
        delete Head; //Очистка памяти от первого звена
        Head = Tail; //Смена адреса начала на адрес следующего элемента
    }
}

bool AirportList::IsAvailable(QString name)
{
    Airport *temp = Head; //Выделение памяти под новый элемент структуры

    while (temp != NULL) // Пока не встретим пустое значение
    {
        if (temp->name == name + "\r\n")//Выводим каждое считанное значение на экран
        {
            return false;
        }
        temp = temp->pNext; //Смена адреса на адрес следующего элемента
    }
    return true;
}

void AirportList::Add(QString name)
{
    Airport *temp = new Airport;

    temp->pNext = NULL; //Указываем, что изначально по следующему адресу пусто
    temp->name = name;//Записываем значение в структуру

    if (Head!=NULL) //Если список не пуст
    {
        temp -> pPrev = Tail; // Указываем адрес на предыдущий элемент в соотв. поле
        Tail -> pNext = temp; // Указываем адрес следующего за хвостом элемента
        Tail = temp; // Меняем адрес хвоста
        length++; // Увеличиваем длину списка
    }
    else //Если список пустой
    {
        temp -> pPrev = NULL; //Предыдущий элемент указывает в пустоту
        Head = Tail = temp; //Голова=Хвост=тот элемент, что сейчас добавили
        length++; // Увеличиваем длину списка
    }
}

void AirportList::Show(QTextEdit* outTextEdit)
{
    // Составление выходной строки
    QString str = "";
    Airport *temp = Head; // Временно указываем на адрес первого элемента
    while (temp != NULL) // Пока не встретим пустое значение
    {
        str += temp->name; //Выводим каждое считанное значение на экран
        temp = temp->pNext; //Смена адреса на адрес следующего элемента
    }
    // Вывод строки на экран
    outTextEdit->setText(str);
}

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

void AirportList::Clear() //Деструктор
{
    while (Head) // Пока по адресу на начало списка что-то есть
    {
        Tail = Head->pNext; // Резервная копия адреса следующего звена списка
        delete Head; // Очистка памяти от первого звена
        Head = Tail; // Смена адреса начала на адрес следующего элемента
    }
}

void AirportList::ShowList(QListWidget *lAirport)
{
    Airport *temp = Head;
    lAirport->clear();
    while (temp != NULL) // Пока не встретим пустое значение
    {
        QString str = temp->name;
        lAirport->addItem(str);
        temp = temp->pNext; // Смена адреса на адрес следующего элемента
    }
}

/*ФУНКЦИЯ УДАЛЕНИЯ КОНКРЕТНОГО ЭЛЕМЕНТА ДВУСВЯЗНОГО СПИСКА*/
void AirportList::Del(QString airportName)
{
    int x = 1;
    Airport *tmp = Head;
    while (tmp != NULL) // Пока не встретим пустое значение
    {
//        QString str = tmp->name;
//        int len = str.length();
//        str.remove(len-2, 2);
        qDebug() << tmp->name + " " + airportName;
        if (tmp->name == airportName)
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
        Airport *temp=Head;	//Указываем, что нам нужно начало списка
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
        Airport *temp=Tail;	//Указываем, что нам нужен хвост
        Tail=Tail->pPrev;	//Отодвигаем хвост немного назад
        Tail->pNext=NULL;	//Обозначаем, что впереди за хвостом пусто
        delete temp;	//Очищаем память от бывшего хвоста
        length--;		//Обязательно уменьшаем счетчик элементов
        return;		//И выходим из функции
    }

    //Если же удаляемый элемент лежит где-то в середине списка, то тогда его можно удалить
    Airport *temp=Head,*temp2; //temp-Удаляемый элемент, temp2 нужен, чтобы не потерять данные

        //cout<<count_<<"\n";
    for (int i=0;i<x-1;i++)
        temp=temp->pNext;  //Идем к адресу удаляемого элемента

    temp2=temp;	//Временно запоминаем адрес удаляемого элемента
    temp2->pPrev->pNext=temp->pNext;	//Записываем данные, что следующий за перед сейчас удаляемым элементом - это следующий от удаляемого
    temp2->pNext->pPrev=temp->pPrev; //а предыдущий для следующего - это предыдущий для удаляемого
    delete temp; //теперь смело можно освободить память, удалив адрес на начало удаляемого элемента
    length--; //Обязательно уменьшаем число элементов в списке.
}

int AirportList::getLength()
{
    return length;
}
