#ifndef AIRCRAFTMANAGEMENT_H
#define AIRCRAFTMANAGEMENT_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QFormLayout>
#include <QMessageBox>

class Aircraft {
public:
    QString id;
    QString type;
    QString model;
    QString maintenanceStatus;
    bool isAvailable;

    Aircraft(const QString& id, const QString& type, const QString& model, const QString& maintenanceStatus, bool isAvailable)
        : id(id), type(type), model(model), maintenanceStatus(maintenanceStatus), isAvailable(isAvailable) {}
};

class AircraftManagementWindow : public QMainWindow {
    Q_OBJECT

private:
    QTableWidget* aircraftTable;
    QList<Aircraft> aircraftList;

    void saveToFile();
    void loadFromFile();

public:
    AircraftManagementWindow(QWidget *parent = nullptr);

private slots:
    void addAircraft();
    void editAircraft();
    void deleteAircraft();
    void updateModelOptions(QComboBox& typeCombo, QComboBox& modelCombo);
    void updateTable();
};

#endif // AIRCRAFTMANAGEMENT_H
