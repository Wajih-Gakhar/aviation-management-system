#include "pilotrecordmanagement.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QPushButton>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QLabel>
#include <QHeaderView>

PilotManagementWindow::PilotManagementWindow(QWidget *parent)
    : QMainWindow(parent) {

    // Setup UI
    QWidget* centralWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();

    // Set background color
    centralWidget->setStyleSheet("background-color: #f0f0f0;"); // Light grey background

    QLabel* pilotLabel = new QLabel("<h2><b>Pilot Record Management System:</b></h2>");

    // Styling the QLabel to center it, add a border, background color, and padding
    pilotLabel->setStyleSheet("QLabel {"
                                    "font-size: 20px;"
                                    "color: white;"  // Text color (you can adjust this)
                                    "background-color: #3498DB;"  // Background color (light blue)
                                    "border: 2px solid #2980B9;"  // Border color (darker blue)
                                    "padding: 10px;"  // Padding inside the label
                                    "text-align: center;"  // Center the text inside the label
                                    "border-radius: 8px;"  // Rounded corners for the box
                                    "}");

    pilotLabel->setAlignment(Qt::AlignCenter);  // Ensure the text is centered
    layout->addWidget(pilotLabel);

    pilotTable = new QTableWidget();
    pilotTable->setColumnCount(5);
    pilotTable->setHorizontalHeaderLabels({"Name", "Rank", "Certifications", "Availability", "Assignment"});

    // Styling table headers and rows
    pilotTable->setStyleSheet("QTableWidget { border: none; font-size: 14px; }"
                                 "QTableWidget::item { padding: 5px; background-color: #ffffff; }"
                                 "QHeaderView::section { background-color: #4CAF50; color: white; padding: 10px; font-size: 16px; }"
                                 "QTableWidget::item:selected { background-color: #2196F3; color: white; }"
                                 "QTableWidget::horizontalHeader { background-color: #4CAF50; font-weight: bold; }");

    // Set all columns to stretch equally
    for (int i = 0; i < pilotTable->columnCount(); ++i) {
        pilotTable->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    // Set the table to expand horizontally and vertically in the layout
    pilotTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(pilotTable);

    // Create button layout (Horizontal Layout for buttons)
    QHBoxLayout* buttonLayout = new QHBoxLayout();

    QPushButton* addButton = new QPushButton("Add Pilot");
    QPushButton* editButton = new QPushButton("Edit Pilot");
    QPushButton* deleteButton = new QPushButton("Delete Pilot");
    QPushButton* assignButton = new QPushButton("Assign Pilot");

    // Styling buttons
    addButton->setStyleSheet("QPushButton { "
                             "background-color: #4CAF50; "
                             "color: white; "
                             "border: none; "
                             "padding: 12px; "
                             "font-size: 14px; "
                             "border-radius: 5px; "
                             "margin-right: 10px; "
                             "} "
                             "QPushButton:hover { "
                             "background-color: #45a049; "
                             "} ");

    editButton->setStyleSheet("QPushButton { "
                              "background-color: #ff9800; "
                              "color: white; "
                              "border: none; "
                              "padding: 12px; "
                              "font-size: 14px; "
                              "border-radius: 5px; "
                              "margin-right: 10px; "
                              "} "
                              "QPushButton:hover { "
                              "background-color: #f57c00; "
                              "} ");

    deleteButton->setStyleSheet("QPushButton { "
                                "background-color: #f44336; "
                                "color: white; "
                                "border: none; "
                                "padding: 12px; "
                                "font-size: 14px; "
                                "border-radius: 5px; "
                                "} "
                                "QPushButton:hover { "
                                "background-color: #e53935; "
                                "} ");

    assignButton->setStyleSheet("QPushButton { "
                                "background-color: #ff9800; "
                                "color: white; "
                                "border: none; "
                                "padding: 12px; "
                                "font-size: 14px; "
                                "border-radius: 5px; "
                                "margin-right: 10px; "
                                "} "
                                "QPushButton:hover { "
                                "background-color: #f57c00; "
                                "} ");

    // Add buttons to the button layout (horizontal)
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(assignButton);

    // Set the contents margins to move the buttons slightly up
    buttonLayout->setContentsMargins(0, 0, 0, 20); // Move up by 20 pixels

    // Ensure the layout is properly added to the central widget
    layout->addLayout(buttonLayout);

    // Add the button layout to the main layout (only once)
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(addButton, &QPushButton::clicked, this, &PilotManagementWindow::addPilot);
    connect(editButton, &QPushButton::clicked, this, &PilotManagementWindow::editPilot);
    connect(deleteButton, &QPushButton::clicked, this, &PilotManagementWindow::deletePilot);
    connect(assignButton, &QPushButton::clicked, this, &PilotManagementWindow::assignPilot);

    setWindowTitle("Pilot Records Management");
    resize(1350, 950);
    // Load saved data
    loadFromFile();
    updateTable();
}

void PilotManagementWindow::addPilot() {
    QDialog dialog(this);
    QFormLayout form(&dialog);

    QLineEdit nameEdit;
    QComboBox rankComboBox;
    rankComboBox.addItems({"PILOT OFFICER", "FLYING OFFICER", "FLIGHT LIEUTENANT", "SQUADRON LEADER",
                           "WING COMMANDER", "GROUP CAPTAIN", "AIR COMMODORE", "AIR VICE MARSHAL", "AIR MARSHAL", "AIR CHIEF MARSHAL", "MARSHAL OF THE AIR FORCE"});

    QComboBox certificationsComboBox;
    certificationsComboBox.addItems({"GENERAL DUTIES (PILOT)", "GENERAL DUTIES (NAVIGATION)", "AIR DEFENCE", "ENGINEERING",
                                     "ADMINISTRATION & SPECIAL DUTY", "INFORMATION TECHNOLOGY", "LOGISTICS", "EDUCATION", "MEDICAL"});

    form.addRow("Name:", &nameEdit);
    form.addRow("Rank:", &rankComboBox);
    form.addRow("Certifications:", &certificationsComboBox);

    QPushButton okButton("OK"), cancelButton("Cancel");
    QHBoxLayout buttonLayout;
    buttonLayout.addWidget(&okButton);
    buttonLayout.addWidget(&cancelButton);
    form.addRow(&buttonLayout);

    connect(&okButton, &QPushButton::clicked, [&]() {
        if (nameEdit.text().isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Name field is required.");
            return;
        }
        Pilot newPilot(nameEdit.text(), rankComboBox.currentText(), certificationsComboBox.currentText(), true);
        pilotList.append(newPilot);
        updateTable();
        saveToFile();  // Save data after adding
        dialog.accept();
    });
    connect(&cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    dialog.exec();
}

void PilotManagementWindow::editPilot() {
    int currentRow = pilotTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Selection Error", "Please select a pilot to edit.");
        return;
    }

    Pilot& selectedPilot = pilotList[currentRow];
    QDialog dialog(this);
    QFormLayout form(&dialog);

    QLineEdit nameEdit(selectedPilot.name);
    QComboBox rankComboBox, certificationsComboBox;
    rankComboBox.addItems({"PILOT OFFICER", "FLYING OFFICER", "FLIGHT LIEUTENANT", "SQUADRON LEADER",
                           "WING COMMANDER", "GROUP CAPTAIN", "AIR COMMODORE", "AIR VICE MARSHAL", "AIR MARSHAL", "AIR CHIEF MARSHAL", "MARSHAL OF THE AIR FORCE"});
    rankComboBox.setCurrentText(selectedPilot.rank);

    certificationsComboBox.addItems({"GENERAL DUTIES (PILOT)", "GENERAL DUTIES (NAVIGATION)", "AIR DEFENCE", "ENGINEERING",
                                     "ADMINISTRATION & SPECIAL DUTY", "INFORMATION TECHNOLOGY", "LOGISTICS", "EDUCATION", "MEDICAL"});
    certificationsComboBox.setCurrentText(selectedPilot.certifications);

    form.addRow("Name:", &nameEdit);
    form.addRow("Rank:", &rankComboBox);
    form.addRow("Certifications:", &certificationsComboBox);

    QPushButton okButton("OK"), cancelButton("Cancel");
    QHBoxLayout buttonLayout;
    buttonLayout.addWidget(&okButton);
    buttonLayout.addWidget(&cancelButton);
    form.addRow(&buttonLayout);

    connect(&okButton, &QPushButton::clicked, [&]() {
        selectedPilot.name = nameEdit.text();
        selectedPilot.rank = rankComboBox.currentText();
        selectedPilot.certifications = certificationsComboBox.currentText();
        updateTable();
        saveToFile();  // Save data after editing
        dialog.accept();
    });
    connect(&cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    dialog.exec();
}

void PilotManagementWindow::deletePilot() {
    int currentRow = pilotTable->currentRow();
    if (currentRow >= 0) {
        pilotList.removeAt(currentRow);
        updateTable();
        saveToFile();  // Save data after deletion
    }
}

void PilotManagementWindow::assignPilot() {
    int currentRow = pilotTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Selection Error", "Please select a pilot to assign.");
        return;
    }

    Pilot& selectedPilot = pilotList[currentRow];

    if (!selectedPilot.isAvailable) {
        QMessageBox::warning(this, "Assignment Error", "Selected pilot is not available.");
        return;
    }

    // Dialog for assigning a pilot
    QDialog dialog(this);
    QFormLayout form(&dialog);

    QLineEdit missionEdit;
    QDateEdit dateEdit;
    dateEdit.setCalendarPopup(true);
    form.addRow("Mission:", &missionEdit);
    form.addRow("Date:", &dateEdit);

    QPushButton okButton("OK"), cancelButton("Cancel");
    QHBoxLayout buttonLayout;
    buttonLayout.addWidget(&okButton);
    buttonLayout.addWidget(&cancelButton);
    form.addRow(&buttonLayout);

    connect(&okButton, &QPushButton::clicked, [&]() {
        if (missionEdit.text().isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Mission name is required.");
            return;
        }
        selectedPilot.currentAssignment = missionEdit.text() + " (" + dateEdit.date().toString("dd-MM-yyyy") + ")";
        selectedPilot.isAvailable = false;

        updateTable();
        saveToFile();
        dialog.accept();
    });
    connect(&cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    dialog.exec();
}

void PilotManagementWindow::updateTable() {
    pilotTable->setRowCount(pilotList.size());
    for (int i = 0; i < pilotList.size(); ++i) {
        const Pilot& pilot = pilotList[i];
        pilotTable->setItem(i, 0, new QTableWidgetItem(pilot.name));
        pilotTable->setItem(i, 1, new QTableWidgetItem(pilot.rank));
        pilotTable->setItem(i, 2, new QTableWidgetItem(pilot.certifications));
        pilotTable->setItem(i, 3, new QTableWidgetItem(pilot.isAvailable ? "Available" : "Unavailable"));
        pilotTable->setItem(i, 4, new QTableWidgetItem(pilot.currentAssignment));
    }
}

// Function to save the data to file
void PilotManagementWindow::saveToFile() {
    QFile file("pilot_data.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const Pilot& pilot : pilotList) {
            out << pilot.name << "|"
                << pilot.rank << "|"
                << pilot.certifications << "|"
                << (pilot.isAvailable ? "1" : "0") << "|"
                << pilot.currentAssignment << "\n";
        }
        file.close();
    }
}

// Function to load the data from file
void PilotManagementWindow::loadFromFile() {
    QFile file("pilot_data.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split("|");
            if (parts.size() == 5) {
                QString name = parts[0];
                QString rank = parts[1];
                QString certifications = parts[2];
                bool isAvailable = (parts[3] == "1");
                QString assignment = parts[4];
                pilotList.append(Pilot(name, rank, certifications, isAvailable, assignment));
            }
        }
        file.close();
    }
}

