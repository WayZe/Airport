#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "airport.h"
#include "flight.h"
#include "aircraft.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnDeleteAirport_clicked();

    void on_btnAddAirport_clicked();

    void on_btnAddFlight_clicked();

    void on_btnDeleteFlight_clicked();

    void on_btnAddAircraft_clicked();

    void on_btnDeleteAircraft_clicked();

    void on_lwFlightFromName_itemClicked(QListWidgetItem *item);

    void on_lwFlightToName_itemClicked(QListWidgetItem *item);

    void on_lwFlightAircraft_itemClicked(QListWidgetItem *item);

    void on_lwFlightOutput_itemClicked(QListWidgetItem *item);

    void on_lwAirportOutput_itemClicked(QListWidgetItem *item);

    void on_lwAircraftOutput_itemClicked(QListWidgetItem *item);

    void on_leAirportInput_textChanged(const QString &arg1);

    void on_leAircraftModel_textChanged(const QString &arg1);

    void on_leAircraftNumber_textChanged(const QString &arg1);

    void on_leFlightNumberInput_textChanged(const QString &arg1);

    void on_leFlightFromName_textChanged(const QString &arg1);

    void on_leFlightToName_textChanged(const QString &arg1);

    void on_leFlightAircraft_textChanged(const QString &arg1);

    void on_leAirportInput_returnPressed();

    void on_leAircraftModel_returnPressed();

    void on_leAircraftNumber_returnPressed();

    void on_leFlightNumberInput_returnPressed();

    void on_leFlightFromName_returnPressed();

    void on_leFlightToName_returnPressed();

    void on_leFlightAircraft_returnPressed();

    void on_tbMain_currentChanged(int index);

    void on_tbMain_tabBarClicked(int index);

    void on_lwFlightFromName_itemActivated(QListWidgetItem *item);

    void on_lwFlightToName_itemActivated(QListWidgetItem *item);

    void on_lwFlightAircraft_itemActivated(QListWidgetItem *item);

    void on_btnAirportSearch_clicked();

    void on_btnAddFlightSearch_clicked();

    void on_leFlightNumberSearch_returnPressed();

    void on_leFlightFromNameSearch_returnPressed();

    void on_leFlightToNameSearch_returnPressed();

    void on_leFlightAircraftSearch_returnPressed();

    void on_btnAddFlightSearch_pressed();

    void on_btnAircraftSearch_clicked();

    void on_btnAddAircraft_pressed();

    void on_btnAircraftSearch_pressed();

private:
    Ui::MainWindow *ui;
    AirportList airportList;
    FlightList flightList;
    AircraftList aircraftList;
    bool isEnabledShowAirportButton = false;
    bool isEnabledShowFlightButton = false;
    bool isEnabledShowAircraftButton = false;
};

#endif // MAINWINDOW_H
