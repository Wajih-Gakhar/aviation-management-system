#ifndef PILOTRECORDMANAGEMENT_H
#define PILOTRECORDMANAGEMENT_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QFormLayout>
#include <QMessageBox>
#include <QList>
#include <QDateEdit>
#include <QFile>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class Pilot {
public:
    QString name;
    QString rank;
    QString certifications;
    bool isAvailable;
    QString currentAssignment;

    Pilot(const QString& name, const QString& rank, const QString& certifications, bool isAvailable)
        : name(name), rank(rank), certifications(certifications), isAvailable(isAvailable), currentAssignment("") {}

    // Constructor for loading data
    Pilot(const QString& name, const QString& rank, const QString& certifications, bool isAvailable, const QString& assignment)
        : name(name), rank(rank), certifications(certifications), isAvailable(isAvailable), currentAssignment(assignment) {}
};

class PilotManagementWindow : public QMainWindow {
    Q_OBJECT

private:
    QTableWidget* pilotTable;
    QList<Pilot> pilotList;

    void saveToFile();
    void loadFromFile();

public:
    PilotManagementWindow(QWidget *parent = nullptr);
    void updateTable();

private slots:
    void addPilot();
    void editPilot();
    void deletePilot();
    void assignPilot();
};

#endif // PILOTRECORDMANAGEMENT_H
