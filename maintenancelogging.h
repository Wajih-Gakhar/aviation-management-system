#ifndef MAINTENANCELOGGING_H
#define MAINTENANCELOGGING_H

#include <QMainWindow>
#include <QApplication>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QDateEdit>
#include <QMessageBox>
#include <QStringList>
#include <QDateTime>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QInputDialog>
#include <QFile>
#include <QTextStream>
#include <QDate>
#include <QString>
#include <QList>

class MaintenanceRecord {
public:
    QDate date;
    QString type;
    QString remarks;

    MaintenanceRecord(const QDate& date = QDate(), const QString& type = "", const QString& remarks = "")
        : date(date), type(type), remarks(remarks) {}

    // Serialize maintenance record to a single line of text
    QString serialize() const {
        return date.toString("dd-MM-yyyy") + "|" + type + "|" + remarks;
    }

    // Deserialize a single line of text to populate this object
    static MaintenanceRecord deserialize(const QString& line) {
        QStringList parts = line.split("|");
        if (parts.size() != 3) return {};
        return MaintenanceRecord(QDate::fromString(parts[0], "dd-MM-yyyy"), parts[1], parts[2]);
    }

    // Equality operator for comparison
    bool operator==(const MaintenanceRecord& other) const {
        return date == other.date && type == other.type && remarks == other.remarks;
    }
};


class Combatcraft {
public:
    QString id;
    QString type;
    QString model;
    bool isAvailable;
    int operationalHours;
    QList<MaintenanceRecord> maintenanceHistory;
    QDate lastMaintenanceDate;

    Combatcraft(const QString& id = "", const QString& type = "", const QString& model = "", bool isAvailable = true, int hours = 0)
        : id(id), type(type), model(model), isAvailable(isAvailable), operationalHours(hours), lastMaintenanceDate(QDate::currentDate()) {}

    bool isMaintenanceDue() const {
        return lastMaintenanceDate.daysTo(QDate::currentDate()) > 30;
    }

    QString serialize() const {
        QStringList lines;
        lines << id << type << model << QString::number(operationalHours) << lastMaintenanceDate.toString("dd-MM-yyyy");
        for (const auto& record : maintenanceHistory) {
            lines << record.serialize();
        }
        lines << "---"; // Separator for maintenance records
        return lines.join("\n");
    }

    static Combatcraft deserialize(QTextStream& stream) {
        QString id = stream.readLine().trimmed();
        if (id.isEmpty()) return {}; // Handle empty lines

        QString type = stream.readLine().trimmed();
        QString model = stream.readLine().trimmed();
        int hours = stream.readLine().trimmed().toInt();
        QDate lastMaintenance = QDate::fromString(stream.readLine().trimmed(), "dd-MM-yyyy");

        Combatcraft aircraft(id, type, model, true, hours);
        aircraft.lastMaintenanceDate = lastMaintenance;

        QString line;
        while (!(line = stream.readLine().trimmed()).isEmpty() && line != "---") {
            MaintenanceRecord record = MaintenanceRecord::deserialize(line);
            if (!record.date.isNull()) {
                aircraft.maintenanceHistory.append(record);
            }
        }
        return aircraft;
    }
};

class MaintenanceLoggingWindow : public QMainWindow {
    Q_OBJECT

private:
    QTableWidget* aircraftTable;
    QTableWidget* maintenanceTable;
    QList<Combatcraft> aircraftList;

public:
    MaintenanceLoggingWindow(QWidget *parent = nullptr);
    ~MaintenanceLoggingWindow();

private slots:
    void addAircraft();
    void editAircraft();
    void deleteAircraft();
    void addMaintenanceRecord();
    void updateTable();
    void logOperationalHours();
    void editMaintenanceRecord();
    void deleteMaintenanceRecord();

private:
    void mapMaintenanceTableRowToRecord(int row, Combatcraft*& aircraft, MaintenanceRecord*& record);

    void saveDataToFile();
    void loadDataFromFile();
};

#endif // MAINTENANCELOGGING_H
