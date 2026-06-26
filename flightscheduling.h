#ifndef FLIGHTSCHEDULING_H
#define FLIGHTSCHEDULING_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QMessageBox>
#include <QStringList>
#include <QHBoxLayout>
#include <QFile>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class FighterCraft {
public:
    QString id;
    QString type;
    bool isAvailable;

    FighterCraft(const QString& id, const QString& type, bool isAvailable = true)
        : id(id), type(type), isAvailable(isAvailable) {}
};

class Flight {
public:
    QString missionName;
    QString aircraftType;
    QString aircraftModel;
    QString pilotName;
    QDateTime dateTime;

    Flight() = default;

    Flight(const QString& missionName, const QString& aircraftType, const QString& aircraftModel, const QString& pilotName, const QDateTime& dateTime)
        : missionName(missionName), aircraftType(aircraftType), aircraftModel(aircraftModel), pilotName(pilotName), dateTime(dateTime) {}

    // Converts the flight object to a string for file storage
    QString toString() const {
        return missionName + "|" + aircraftType + "|" + aircraftModel + "|" + pilotName + "|" + dateTime.toString(Qt::ISODate);
    }

    // Creates a Flight object from a string
    static Flight fromString(const QString& data) {
        QStringList fields = data.split('|');
        if (fields.size() != 5) {
            throw std::invalid_argument("Invalid flight data format");
        }
        return Flight(fields[0], fields[1], fields[2], fields[3], QDateTime::fromString(fields[4], Qt::ISODate));
    }
};

class FlightSchedulingWindow : public QMainWindow {
    Q_OBJECT

private:
    QTableWidget* flightTable;
    QList<Flight> flightList;

public:
    FlightSchedulingWindow(QWidget *parent = nullptr);

private slots:
    void scheduleFlight();
    void editFlight();
    void deleteFlight();
    void updateTable();

private:
    void saveToFile();
    void loadFromFile();
};

#endif // FLIGHTSCHEDULING_H
