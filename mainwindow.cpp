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

    airportList.SetPath();
    flightList.SetPath();
    aircraftList.SetPath();
    airportList.ReadFile();
    aircraftList.ReadFile();
    flightList.ReadFile();
    airportList.ShowList(ui->lwAirportOutput);
    airportList.ShowList(ui->lwFlightFromName);
    airportList.ShowList(ui->lwFlightToName);
    aircraftList.ShowList(ui->lwFlightAircraft);
    aircraftList.ShowList(ui->lwAircraftOutput);
    flightList.ShowList(ui->lwFlightOutput);
    ui->leAirportInput->setFocus();

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
void MainWindow::on_btnDeleteAirport_clicked()
{
    airportList.Del(ui->lwAirportOutput->currentItem()->text());
    airportList.WriteFile();
    delete ui->lwAirportOutput->takeItem(ui->lwAirportOutput->currentRow());
    airportList.ShowList(ui->lwFlightFromName);
    airportList.ShowList(ui->lwFlightToName);
    if (airportList.getLength() == 0)
        ui->btnDeleteAirport->setDisabled(true);
}

void MainWindow::on_btnAddAirport_clicked()
{
    QString tmp = ui->leAirportInput->text();
    if (airportList.IsAvailable(tmp))
    {
        airportList.Add(tmp);
        airportList.WriteFile();
        airportList.ShowList(ui->lwAirportOutput);
        airportList.ShowList(ui->lwFlightFromName);
        airportList.ShowList(ui->lwFlightToName);
        ui->leAirportInput->setText("");
    }
    else
    {
        QMessageBox::warning(this, "Некорректный название", "Введите другое название");
    }
}

void MainWindow::on_btnAirportSearch_clicked()
{
    airportList.ShowSearchList(ui->lwAirportOutput, ui->leAirportSearch->text());
}

void MainWindow::on_leAirportInput_textChanged(const QString &arg1)
{
    if (arg1 == "")
    {
        ui->btnAddAirport->setDisabled(true);
    }
    else
    {
        ui->btnAddAirport->setDisabled(false);
    }
}

void MainWindow::on_leAirportInput_returnPressed()
{
    ui->btnAddAirport->setFocus();
}

// РЕЙСЫ
void MainWindow::on_btnAddFlight_clicked()
{
    Flight flight;
    flight.number  = ui->leFlightNumberInput->text();
    flight.fromName = ui->leFlightFromName->text();
    flight.toName = ui->leFlightToName->text();
    flight.aircraftNumber = ui->leFlightAircraft->text();
    if (flightList.IsAvailable(&flight))
    {
        if (ui->leFlightFromName->text() != ui->leFlightToName->text())
        {
            flightList.Add(&flight);
            flightList.WriteFile();
            flightList.ShowList(ui->lwFlightOutput);
            ui->leFlightNumberInput->setText("");
            ui->leFlightFromName->setText("");
            ui->leFlightToName->setText("");
            ui->leFlightAircraft->setText("");
            //if (!ui->lwFlightOutput->size().isEmpty())
              //  ui->btnDeleteFlight->setEnabled(true);
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
}

void MainWindow::on_btnDeleteFlight_clicked()
{
    flightList.Del(ui->lwFlightOutput->currentItem()->text());
    flightList.WriteFile();
    delete ui->lwFlightOutput->takeItem(ui->lwFlightOutput->currentRow());

    if (flightList.getLength() == 0)
        ui->btnDeleteFlight->setDisabled(true);

    if (ui->lwFlightOutput->count() == 0)
        ui->btnDeleteFlight->setEnabled(false);
}

void MainWindow::on_lwFlightFromName_itemClicked(QListWidgetItem *item)
{
    ui->leFlightFromName->setText(item->text());
}

void MainWindow::on_lwFlightToName_itemClicked(QListWidgetItem *item)
{
    ui->leFlightToName->setText(item->text());
}

void MainWindow::on_lwFlightAircraft_itemClicked(QListWidgetItem *item)
{
    QStringList tmpLst = item->text().split(' ');
    ui->leFlightAircraft->setText(tmpLst[1]);
}

void MainWindow::on_lwFlightOutput_itemClicked(QListWidgetItem *item)
{
    ui->btnDeleteFlight->setDisabled(false);
}

void MainWindow::on_leFlightNumberInput_textChanged(const QString &arg1)
{
    if (arg1 != "" && ui->leFlightFromName->text() != "" && ui->leFlightToName->text() != "" && ui->leFlightAircraft->text() != "")
    {
        ui->btnAddFlight->setDisabled(false);
    }
    else
    {
        ui->btnAddFlight->setDisabled(true);
    }
}

void MainWindow::on_leFlightFromName_textChanged(const QString &arg1)
{
    if (arg1 != "" && ui->leFlightNumberInput->text() != "" && ui->leFlightToName->text() != "" && ui->leFlightAircraft->text() != "")
    {
        ui->btnAddFlight->setDisabled(false);
    }
    else
    {
        ui->btnAddFlight->setDisabled(true);
    }
}

void MainWindow::on_leFlightToName_textChanged(const QString &arg1)
{
    if (arg1 != "" && ui->leFlightFromName->text() != "" && ui->leFlightNumberInput->text() != "" && ui->leFlightAircraft->text() != "")
    {
        ui->btnAddFlight->setDisabled(false);
    }
    else
    {
        ui->btnAddFlight->setDisabled(true);
    }
}

void MainWindow::on_leFlightAircraft_textChanged(const QString &arg1)
{
    if (arg1 != "" && ui->leFlightFromName->text() != "" && ui->leFlightToName->text() != "" && ui->leFlightNumberInput->text() != "")
    {
        ui->btnAddFlight->setDisabled(false);
    }
    else
    {
        ui->btnAddFlight->setDisabled(true);
    }
}

void MainWindow::on_leFlightNumberInput_returnPressed()
{
    ui->leFlightFromName->setFocus();
}

void MainWindow::on_leFlightFromName_returnPressed()
{
    ui->leFlightToName->setFocus();
}

void MainWindow::on_leFlightToName_returnPressed()
{
    ui->leFlightAircraft->setFocus();
}

void MainWindow::on_leFlightAircraft_returnPressed()
{
    ui->btnAddFlight->setFocus();
}

// ВОЗДУШНЫЕ СУДА
void MainWindow::on_btnAddAircraft_clicked()
{
    Aircraft aircraft;
    aircraft.model = ui->leAircraftModel->text();
    aircraft.number = ui->leAircraftNumber->text();
    if(aircraftList.IsAvailable(&aircraft))
    {
        aircraftList.Add(&aircraft);
        aircraftList.WriteFile();
        aircraftList.ShowList(ui->lwAircraftOutput);
        aircraftList.ShowList(ui->lwFlightAircraft);
        ui->leAircraftModel->setText("");
        ui->leAircraftNumber->setText("");
    }
    else
    {
        QMessageBox::warning(this, "Некорректный номер", "Введите другой номер");
    }
}

void MainWindow::on_btnDeleteAircraft_clicked()
{
    aircraftList.Del(ui->lwAircraftOutput->currentItem()->text());
    aircraftList.WriteFile();
    delete ui->lwAircraftOutput->takeItem(ui->lwAircraftOutput->currentRow());
    aircraftList.ShowList(ui->lwFlightAircraft);
    if (aircraftList.getLength() == 0)
        ui->btnDeleteAircraft->setDisabled(true);
}

void MainWindow::on_lwAirportOutput_itemClicked(QListWidgetItem *item)
{
    ui->btnDeleteAirport->setDisabled(false);
}

void MainWindow::on_lwAircraftOutput_itemClicked(QListWidgetItem *item)
{
    ui->btnDeleteAircraft->setDisabled(false);
}

void MainWindow::on_leAircraftModel_textChanged(const QString &arg1)
{
    if (arg1 != "" && ui->leAircraftNumber->text() != "")
    {
        ui->btnAddAircraft->setDisabled(false);
    }
    else
    {
        ui->btnAddAircraft->setDisabled(true);
    }
}

void MainWindow::on_leAircraftNumber_textChanged(const QString &arg1)
{
    if (arg1 != "" && ui->leAircraftNumber->text() != "")
    {
        ui->btnAddAircraft->setDisabled(false);
    }
    else
    {
        ui->btnAddAircraft->setDisabled(true);
    }
}

void MainWindow::on_leAircraftModel_returnPressed()
{
    ui->leAircraftNumber->setFocus();
}

void MainWindow::on_leAircraftNumber_returnPressed()
{
    ui->btnAddAircraft->setFocus();
}

void MainWindow::on_tbMain_currentChanged(int index)
{

}

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

void MainWindow::on_lwFlightFromName_itemActivated(QListWidgetItem *item)
{
    ui->leFlightFromName->setText(item->text());
    ui->lwFlightToName->setFocus();
}

void MainWindow::on_lwFlightToName_itemActivated(QListWidgetItem *item)
{
    ui->leFlightToName->setText(item->text());
    ui->lwFlightAircraft->setFocus();
}

void MainWindow::on_lwFlightAircraft_itemActivated(QListWidgetItem *item)
{
    ui->leFlightAircraft->setText(item->text());
    ui->btnAddFlight->setFocus();
}

void MainWindow::on_btnAddFlightSearch_clicked()
{
    Flight flight;
    flight.number = ui->leFlightNumberSearch->text();
    flight.fromName = ui->leFlightFromNameSearch->text();
    flight.toName = ui->leFlightToNameSearch->text();
    flight.aircraftNumber = ui->leFlightAircraftSearch->text();

    flightList.ShowSearchList(ui->lwFlightOutput, flight);
}

void MainWindow::on_leFlightNumberSearch_returnPressed()
{
    ui->leFlightFromNameSearch->setFocus();
}

void MainWindow::on_leFlightFromNameSearch_returnPressed()
{
    ui->leFlightToNameSearch->setFocus();
}

void MainWindow::on_leFlightToNameSearch_returnPressed()
{
    ui->leFlightAircraftSearch->setFocus();
}

void MainWindow::on_leFlightAircraftSearch_returnPressed()
{
    ui->btnAddFlightSearch->setFocus();
}

void MainWindow::on_btnAddFlightSearch_pressed()
{
    ui->leFlightNumberSearch->setFocus();
    //if (!ui->lwFlightOutput->size().isEmpty())
      //  ui->btnDeleteFlight->setEnabled(true);
}

void MainWindow::on_btnAircraftSearch_clicked()
{
    Aircraft aircraft;
    aircraft.model = ui->leAircraftModelSearch->text();
    aircraft.number = ui->leAircraftNumberSearch->text();

    aircraftList.ShowSearchList(ui->lwAircraftOutput, aircraft);
}

void MainWindow::on_btnAddAircraft_pressed()
{
    ui->leAircraftModel->setFocus();
}

void MainWindow::on_btnAircraftSearch_pressed()
{
    ui->leAircraftModelSearch->setFocus();
}
