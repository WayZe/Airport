#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "airport.h"
#include "flight.h"
#include "aircraft.h"
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Установка путей к файлам
    airportList.SetPath();
    flightList.SetPath();
    aircraftList.SetPath();

    // Чтение файлов
    airportList.ReadFile();
    aircraftList.ReadFile();
    flightList.ReadFile();

    // Отображение списков из файлов на экран
    airportList.ShowList(ui->lwAirportOutput);
    airportList.ShowList(ui->lwFlightFromName);
    airportList.ShowList(ui->lwFlightToName);
    aircraftList.ShowList(ui->lwFlightAircraft);
    aircraftList.ShowList(ui->lwAircraftOutput);
    flightList.ShowList(ui->lwFlightOutput);

    // Установка масок на поля ввода
    ui->leAirportInput->setValidator(new QRegExpValidator(QRegExp("[A-zА-яЁё]+$")));
    ui->leAirportInput->setValidator(new QRegExpValidator(QRegExp("[A-zА-яЁё]+$")));
    ui->leFlightNumberInput->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->leFlightFromName->setValidator(new QRegExpValidator(QRegExp("[A-zА-яЁё]+$")));
    ui->leFlightToName->setValidator(new QRegExpValidator(QRegExp("[A-zА-яЁё]+$")));
    ui->leFlightAircraft->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->leFlightNumberSearch->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->leFlightFromNameSearch->setValidator(new QRegExpValidator(QRegExp("[A-zА-яЁё]+$")));
    ui->leFlightToNameSearch->setValidator(new QRegExpValidator(QRegExp("[A-zА-яЁё]+$")));
    ui->leFlightAircraftSearch->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->leAircraftNumber->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->leAircraftNumberSearch->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// АЭРОПОРТЫ
// Событие нажатие на кнопку "Добавить"
void MainWindow::on_btnAddAirport_clicked()
{
    QString tmp = ui->leAirportInput->text();
    // Если в списке уже нет введенного аэропорта
    if (airportList.IsAvailable(tmp))
    {
        // Добавление аэропорта в список
        airportList.Add(tmp);
        airportList.WriteFile();
        // Отображение списков с добавленным элементом
        airportList.ShowList(ui->lwAirportOutput);
        airportList.ShowList(ui->lwFlightFromName);
        airportList.ShowList(ui->lwFlightToName);

        ui->leAirportInput->setText("");
    }
    else
    {
        QMessageBox::warning(this, "Некорректное название аэропорта", "Введите другое название");
    }

    ui->leAirportInput->setFocus();
}

// Событие нажатия кнопки "Удалить"
void MainWindow::on_btnDeleteAirport_clicked()
{
    // Удаление выбранного аэропорта из списка
    airportList.Del(ui->lwAirportOutput->currentItem()->text());
    airportList.WriteFile();
    delete ui->lwAirportOutput->takeItem(ui->lwAirportOutput->currentRow());

    // Оображение обновленных списков на экран
    airportList.ShowList(ui->lwFlightFromName);
    airportList.ShowList(ui->lwFlightToName);

    // Блокировка кнопки "Удалить", если список на экране пуст
    if (ui->lwAirportOutput->count() == 0)
        ui->btnDeleteAirport->setEnabled(false);
}

// Событие нажатия кнопки "Поиск"
void MainWindow::on_btnAirportSearch_clicked()
{
    // Вывод списка найденных аэропортов
    airportList.ShowSearchList(ui->lwAirportOutput, ui->leAirportSearch->text());

    ui->leAirportSearch->setText("");
    ui->leAirportSearch->setFocus();
}

// Событие изменения поля ввода аэропортов
void MainWindow::on_leAirportInput_textChanged(const QString &arg1)
{
    // Блокировка кнопки, если поле ввода пусто
    if (arg1 == "")
    {
        ui->btnAddAirport->setDisabled(true);
    }
    else
    {
        ui->btnAddAirport->setDisabled(false);
    }
}

// Событие нажатия "Enter" при вводе названия аэропорта для добавления
void MainWindow::on_leAirportInput_returnPressed()
{
    ui->btnAddAirport->setFocus();
}

// Событие выбора элемента списка аэропортов
void MainWindow::on_lwAirportOutput_itemClicked()
{
    ui->btnDeleteAirport->setDisabled(false);
}

// Событие нажатия "Enter" при вводе названия аэропорта для поиска
void MainWindow::on_leAirportSearch_returnPressed()
{
    ui->btnAirportSearch->setFocus();
}

// РЕЙСЫ
// Событие нажатия кнопки "Добавить"
void MainWindow::on_btnAddFlight_clicked()
{
    // Чтение структуры рейса с экрана
    Flight flight;
    flight.number  = ui->leFlightNumberInput->text();
    flight.fromName = ui->leFlightFromName->text();
    flight.toName = ui->leFlightToName->text();
    flight.aircraftNumber = ui->leFlightAircraft->text();

    // Если в списке нету рейса с таким же номером
    if (flightList.IsAvailable(&flight))
    {
        // Если пункт отправления и пункт назначения не равны
        if (ui->leFlightFromName->text() != ui->leFlightToName->text())
        {
            // Добавление рейса в список
            flightList.Add(&flight);
            flightList.WriteFile();

            // Вывод обновленного списка на экран
            flightList.ShowList(ui->lwFlightOutput);

            // Очистка полей ввода
            ui->leFlightNumberInput->setText("");
            ui->leFlightFromName->setText("");
            ui->leFlightToName->setText("");
            ui->leFlightAircraft->setText("");
        }
        else
        {
            QMessageBox::warning(this, "Некорректные названия", "Пункт отправления и пункт назначения должны отличаться.");
        }
    }
    else
    {
        QMessageBox::warning(this, "Некорректный номер", "Введите другой номер рейса.");
    }

    ui->leFlightNumberInput->setFocus();
}

// Событие нажатия кнопки "Удалить"
void MainWindow::on_btnDeleteFlight_clicked()
{
    // Удаление рейса из списка
    flightList.Del(ui->lwFlightOutput->currentItem()->text());
    flightList.WriteFile();
    delete ui->lwFlightOutput->takeItem(ui->lwFlightOutput->currentRow());

    // Если список на экране пуст, то блокировка кнопки "Удалить"
    if (ui->lwFlightOutput->count() == 0)
        ui->btnDeleteFlight->setEnabled(false);
}

// Событие выбора элемента из списка пунктов отправления
void MainWindow::on_lwFlightFromName_itemClicked(QListWidgetItem *item)
{
    ui->leFlightFromName->setText(item->text());
}

// Событие выбора элемента из списка пунктов назначения
void MainWindow::on_lwFlightToName_itemClicked(QListWidgetItem *item)
{
    ui->leFlightToName->setText(item->text());
}

// Событие выбора элемента из списка назначенных судов
void MainWindow::on_lwFlightAircraft_itemClicked(QListWidgetItem *item)
{
    QStringList tmpLst = item->text().split(' ');
    ui->leFlightAircraft->setText(tmpLst[1]);
}

// Событие выбора элемента из списка рейсов
void MainWindow::on_lwFlightOutput_itemClicked(QListWidgetItem *item)
{
    ui->btnDeleteFlight->setDisabled(false);
}


// Событие изменения поля ввода номера рейса
void MainWindow::on_leFlightNumberInput_textChanged(const QString &arg1)
{
    // Блокировка кнопки, если хотя бы одно из полей ввода пусто
    if (arg1 != "" && ui->leFlightFromName->text() != "" && ui->leFlightToName->text() != "" && ui->leFlightAircraft->text() != "")
    {
        ui->btnAddFlight->setDisabled(false);
    }
    else
    {
        ui->btnAddFlight->setDisabled(true);
    }
}

// Событие изменения поля ввода пункта отправления рейса
void MainWindow::on_leFlightFromName_textChanged(const QString &arg1)
{
    // Блокировка кнопки, если хотя бы одно из полей ввода пусто
    if (arg1 != "" && ui->leFlightNumberInput->text() != "" && ui->leFlightToName->text() != "" && ui->leFlightAircraft->text() != "")
    {
        ui->btnAddFlight->setDisabled(false);
    }
    else
    {
        ui->btnAddFlight->setDisabled(true);
    }
}

// Событие изменения поля ввода пункта назначения рейса
void MainWindow::on_leFlightToName_textChanged(const QString &arg1)
{
    // Блокировка кнопки, если хотя бы одно из полей ввода пусто
    if (arg1 != "" && ui->leFlightFromName->text() != "" && ui->leFlightNumberInput->text() != "" && ui->leFlightAircraft->text() != "")
    {
        ui->btnAddFlight->setDisabled(false);
    }
    else
    {
        ui->btnAddFlight->setDisabled(true);
    }
}

// Событие изменения поля ввода судна, назначенного на рейс
void MainWindow::on_leFlightAircraft_textChanged(const QString &arg1)
{
    // Блокировка кнопки, если хотя бы одно из полей ввода пусто
    if (arg1 != "" && ui->leFlightFromName->text() != "" && ui->leFlightToName->text() != "" && ui->leFlightNumberInput->text() != "")
    {
        ui->btnAddFlight->setDisabled(false);
    }
    else
    {
        ui->btnAddFlight->setDisabled(true);
    }
}

// Событие нажатия "Enter" при вводе номера рейса
void MainWindow::on_leFlightNumberInput_returnPressed()
{
    ui->leFlightFromName->setFocus();
}

// Событие нажатия "Enter" при вводе пункта отправления
void MainWindow::on_leFlightFromName_returnPressed()
{
    ui->leFlightToName->setFocus();
}

// Событие нажатия "Enter" при вводе пункта назначения
void MainWindow::on_leFlightToName_returnPressed()
{
    ui->leFlightAircraft->setFocus();
}

// Событие нажатия "Enter" при вводе судна, назначенного на рейс
void MainWindow::on_leFlightAircraft_returnPressed()
{
    ui->btnAddFlight->setFocus();
}

// Событие нажатия кнопки "Поиск"
void MainWindow::on_btnAddFlightSearch_clicked()
{
    // Чтение структуры с экрана
    Flight flight;
    flight.number = ui->leFlightNumberSearch->text();
    flight.fromName = ui->leFlightFromNameSearch->text();
    flight.toName = ui->leFlightToNameSearch->text();
    flight.aircraftNumber = ui->leFlightAircraftSearch->text();

    // Вывод найденных рейсов на экран
    flightList.ShowSearchList(ui->lwFlightOutput, flight);

    ui->leFlightNumberSearch->setFocus();
}

// Событие нажатия "Enter" при вводе номера рейса в поиске
void MainWindow::on_leFlightNumberSearch_returnPressed()
{
    ui->leFlightFromNameSearch->setFocus();
}

// Событие нажатия "Enter" при вводе пункта отправления в поиске
void MainWindow::on_leFlightFromNameSearch_returnPressed()
{
    ui->leFlightToNameSearch->setFocus();
}

// Событие нажатия "Enter" при вводе пункта отправления в поиске
void MainWindow::on_leFlightToNameSearch_returnPressed()
{
    ui->leFlightAircraftSearch->setFocus();
}

// Событие нажатия "Enter" при вводе судна, назначенного на рейс, в поиске
void MainWindow::on_leFlightAircraftSearch_returnPressed()
{
    ui->btnAddFlightSearch->setFocus();
}

// ВОЗДУШНЫЕ СУДА
// Событие нажатия кнопки
void MainWindow::on_btnAddAircraft_clicked()
{
    // Чтение структуры судна с экрана
    Aircraft aircraft;
    aircraft.model = ui->leAircraftModel->text();
    aircraft.number = ui->leAircraftNumber->text();

    // Если в списке нету судна с таким же номером
    if(aircraftList.IsAvailable(&aircraft))
    {
        // Добавление судна в список
        aircraftList.Add(&aircraft);
        aircraftList.WriteFile();

        // Обновление списков на экране
        aircraftList.ShowList(ui->lwAircraftOutput);
        aircraftList.ShowList(ui->lwFlightAircraft);

        // Очистка полей ввода
        ui->leAircraftModel->setText("");
        ui->leAircraftNumber->setText("");
    }
    else
    {
        QMessageBox::warning(this, "Некорректный номер", "Введите другой номер");
    }
}

// Событие нажатия кнопки "Удалить"
void MainWindow::on_btnDeleteAircraft_clicked()
{
    // Удаление судна из списка
    aircraftList.Del(ui->lwAircraftOutput->currentItem()->text());
    aircraftList.WriteFile();
    delete ui->lwAircraftOutput->takeItem(ui->lwAircraftOutput->currentRow());

    // Вывод обновленного списка на экран
    aircraftList.ShowList(ui->lwFlightAircraft);

    // Блокировка кнопки "Удалить", если список на экране пуст
    if (ui->lwAircraftOutput->count() == 0)
        ui->btnDeleteAircraft->setEnabled(false);
}

// Событие выбора судна из списка на экране
void MainWindow::on_lwAircraftOutput_itemClicked(QListWidgetItem *item)
{
    ui->btnDeleteAircraft->setDisabled(false);
}

// Событие изменение текста в поле ввода модели судна
void MainWindow::on_leAircraftModel_textChanged(const QString &arg1)
{
    // Блокировка кнопки "Удалить", если есть пустые поля ввода
    if (arg1 != "" && ui->leAircraftNumber->text() != "")
    {
        ui->btnAddAircraft->setDisabled(false);
    }
    else
    {
        ui->btnAddAircraft->setDisabled(true);
    }
}

// Событие изменение текста в поле ввода номера судна
void MainWindow::on_leAircraftNumber_textChanged(const QString &arg1)
{
    // Блокировка кнопки "Удалить", если есть пустые поля ввода
    if (arg1 != "" && ui->leAircraftNumber->text() != "")
    {
        ui->btnAddAircraft->setDisabled(false);
    }
    else
    {
        ui->btnAddAircraft->setDisabled(true);
    }
}

// Событие нажатия кнопки "Enter" при вводе модели судна
void MainWindow::on_leAircraftModel_returnPressed()
{
    ui->leAircraftNumber->setFocus();
}

// Событие нажатия кнопки "Enter" при вводе номера судна
void MainWindow::on_leAircraftNumber_returnPressed()
{
    ui->btnAddAircraft->setFocus();
}

// Событие нажатия кнопки "Поиск"
void MainWindow::on_btnAircraftSearch_clicked()
{
    // Чтение структуры судна для поиска с экрана
    Aircraft aircraft;
    aircraft.model = ui->leAircraftModelSearch->text();
    aircraft.number = ui->leAircraftNumberSearch->text();

    // Вывод найденных судов на экран
    aircraftList.ShowSearchList(ui->lwAircraftOutput, aircraft);

    ui->leAircraftModelSearch->setFocus();
}

// Событие нажание "Enter" при вводе модели в поиске
void MainWindow::on_leAircraftModelSearch_returnPressed()
{
    ui->leAircraftNumberSearch->setFocus();
}

// Событие нажание "Enter" при вводе номера судна в поиске
void MainWindow::on_leAircraftNumberSearch_returnPressed()
{
    ui->btnAircraftSearch->setFocus();
}

// Установка фокуса на первое поле ввода при выборе другой вкладки
void MainWindow::on_tbMain_tabBarClicked(int index)
{
    switch (index)
    {
    case 0:
        ui->leAirportInput->setFocus();
        break;
    case 1:
        ui->leFlightNumberInput->setFocus();
        break;
    case 2:
        ui->leAircraftModel->setFocus();
        break;
    }
}


