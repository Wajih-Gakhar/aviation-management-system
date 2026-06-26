#include "maintenancelogging.h"
#include <QDebug>
#include <QHeaderView>

MaintenanceLoggingWindow::MaintenanceLoggingWindow(QWidget *parent)
    : QMainWindow(parent) {
    QWidget* centralWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();

    // Set background color
    centralWidget->setStyleSheet("background-color: #f0f0f0;"); // Light grey background

    QLabel* maintenanceLabel = new QLabel("<h2><b>Maintenance Logging System:</b></h2>");

    // Styling the QLabel to center it, add a border, background color, and padding
    maintenanceLabel->setStyleSheet("QLabel {"
                                           "font-size: 20px;"
                                           "color: white;"  // Text color (you can adjust this)
                                           "background-color: #3498DB;"  // Background color (light blue)
                                           "border: 2px solid #2980B9;"  // Border color (darker blue)
                                           "padding: 10px;"  // Padding inside the label
                                           "text-align: center;"  // Center the text inside the label
                                           "border-radius: 8px;"  // Rounded corners for the box
                                           "}");

    maintenanceLabel->setAlignment(Qt::AlignCenter);  // Ensure the text is centered
    layout->addWidget(maintenanceLabel);

    // Aircraft table
    aircraftTable = new QTableWidget();
    aircraftTable->setColumnCount(6);
    aircraftTable->setHorizontalHeaderLabels({"Aircraft ID", "Type", "Model", "Last Maintenance", "Maintenance Due", "Operational Hours"});

    // Styling table headers and rows
    aircraftTable->setStyleSheet("QTableWidget { border: none; font-size: 14px; }"
                                 "QTableWidget::item { padding: 5px; background-color: #ffffff; }"
                                 "QHeaderView::section { background-color: #4CAF50; color: white; padding: 10px; font-size: 16px; }"
                                 "QTableWidget::item:selected { background-color: #2196F3; color: white; }"
                                 "QTableWidget::horizontalHeader { background-color: #4CAF50; font-weight: bold; }");

    // Set all columns to stretch equally
    for (int i = 0; i < aircraftTable->columnCount(); ++i) {
        aircraftTable->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    // Set the table to expand horizontally and vertically in the layout
    aircraftTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(aircraftTable);

    // Maintenance table
    maintenanceTable = new QTableWidget();
    maintenanceTable->setColumnCount(4);
    maintenanceTable->setHorizontalHeaderLabels({"Aircraft ID", "Date", "Type", "Remarks"});

    // Styling table headers and rows
    maintenanceTable->setStyleSheet("QTableWidget { border: none; font-size: 14px; }"
                                 "QTableWidget::item { padding: 5px; background-color: #ffffff; }"
                                 "QHeaderView::section { background-color: #4CAF50; color: white; padding: 10px; font-size: 16px; }"
                                 "QTableWidget::item:selected { background-color: #2196F3; color: white; }"
                                 "QTableWidget::horizontalHeader { background-color: #4CAF50; font-weight: bold; }");

    // Set all columns to stretch equally
    for (int i = 0; i < maintenanceTable->columnCount(); ++i) {
        maintenanceTable->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    // Set the table to expand horizontally and vertically in the layout
    maintenanceTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Create the QLabel for the "Maintenance Records" heading
    QLabel* maintenanceRecordsLabel = new QLabel("<h2><b>Maintenance Records:</b></h2>");
    maintenanceRecordsLabel->setStyleSheet(
        "font-family: Engravers MT, Helvetica, sans-serif;"
        "color: purple;"
        );
    maintenanceRecordsLabel->setAlignment(Qt::AlignCenter);  // Ensure the text is centered

    layout->addWidget(maintenanceRecordsLabel);
    layout->addWidget(maintenanceTable);

    // Create button layout (Horizontal Layout for buttons)
    QHBoxLayout* buttonLayout = new QHBoxLayout();

    // Buttons for CRUD operations with custom styles

    QPushButton* addAircraftButton = new QPushButton("Add Aircraft");
    QPushButton* addMaintenanceButton = new QPushButton("Add Maintenance Record");
    QPushButton* logHoursButton = new QPushButton("Log Operational Hours");
    QPushButton* editAircraftButton = new QPushButton("Edit Aircraft");
    QPushButton* deleteAircraftButton = new QPushButton("Delete Aircraft");
    QPushButton* editMaintenanceButton = new QPushButton("Edit Maintenance Record");
    QPushButton* deleteMaintenanceButton = new QPushButton("Delete Maintenance Record");

    // Styling buttons
    addAircraftButton->setStyleSheet("QPushButton { "
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

    addMaintenanceButton->setStyleSheet("QPushButton { "
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

    logHoursButton->setStyleSheet("QPushButton { "
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

    editAircraftButton->setStyleSheet("QPushButton { "
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

    deleteAircraftButton->setStyleSheet("QPushButton { "
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

    editMaintenanceButton->setStyleSheet("QPushButton { "
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

    deleteMaintenanceButton->setStyleSheet("QPushButton { "
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

    // Add buttons to the button layout (horizontal)
    buttonLayout->addWidget(addAircraftButton);
    buttonLayout->addWidget(editAircraftButton);
    buttonLayout->addWidget(deleteAircraftButton);
    buttonLayout->addWidget(addMaintenanceButton);
    buttonLayout->addWidget(editMaintenanceButton);
    buttonLayout->addWidget(deleteMaintenanceButton);
    buttonLayout->addWidget(logHoursButton);

    // Set the contents margins to move the buttons slightly up
    buttonLayout->setContentsMargins(0, 0, 0, 20); // Move up by 20 pixels

    // Add the button layout to the main layout (only once)
    layout->addLayout(buttonLayout);

    // Add the button layout to the main layout
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(addAircraftButton, &QPushButton::clicked, this, &MaintenanceLoggingWindow::addAircraft);
    connect(editAircraftButton, &QPushButton::clicked, this, &MaintenanceLoggingWindow::editAircraft);
    connect(deleteAircraftButton, &QPushButton::clicked, this, &MaintenanceLoggingWindow::deleteAircraft);
    connect(addMaintenanceButton, &QPushButton::clicked, this, &MaintenanceLoggingWindow::addMaintenanceRecord);
    connect(editMaintenanceButton, &QPushButton::clicked, this, &MaintenanceLoggingWindow::editMaintenanceRecord);
    connect(deleteMaintenanceButton, &QPushButton::clicked, this, &MaintenanceLoggingWindow::deleteMaintenanceRecord);
    connect(logHoursButton, &QPushButton::clicked, this, &MaintenanceLoggingWindow::logOperationalHours);

    setWindowTitle("Aircraft Maintenance Logging");
    resize(1350, 950);

    loadDataFromFile();
    updateTable();
}

MaintenanceLoggingWindow::~MaintenanceLoggingWindow() {
    saveDataToFile();
}

void MaintenanceLoggingWindow::addAircraft() {
    QDialog dialog(this);
    QFormLayout form(&dialog);

    QLineEdit idEdit;
    QComboBox typeComboBox, modelComboBox;

    form.addRow("Aircraft ID:", &idEdit);
    form.addRow("Aircraft Type:", &typeComboBox);
    form.addRow("Model:", &modelComboBox);

    typeComboBox.addItems({"Combat Aircraft", "Trainer Aircraft", "Strategic Airlift & Aerial Refueling Aircraft", "Transport Aircraft", "Airborne Early Warning & Control Aircraft", "Electronic Warfare Aircraft", "Unmanned Aerial Vehicles", "Helicopters"});

    connect(&typeComboBox, &QComboBox::currentTextChanged, [&modelComboBox](const QString& type) {
        modelComboBox.clear();
        if (type == "Combat Aircraft") {
            modelComboBox.addItems({"J-10 Vigorous Dragon", "JF-17 Thunder", "F-16 Fighting Falcon", "Mirage III", "Mirage 5", "F-7"});
        } else if (type == "Trainer Aircraft") {
            modelComboBox.addItems({"K-8", "T-37 Tweet", "MFI-17 Mushshak"});
        } else if (type == "Strategic Airlift & Aerial Refueling Aircraft") {
            modelComboBox.addItems({"Il-78"});
        } else if (type == "Transport Aircraft") {
            modelComboBox.addItems({"C-130 Hercules", "Saab 2000", "Y-12", "Airbus A319", "Global 6000", "Citation V", "Gulfstream IV", "Phenom 100"});
        } else if (type == "Airborne Early Warning & Control Aircraft") {
            modelComboBox.addItems({"Saab 2000 AEW&C"});
        } else if (type == "Electronic Warfare Aircraft") {
            modelComboBox.addItems({"Dassault Falcon 20"});
        } else if (type == "Unmanned Aerial Vehicles") {
            modelComboBox.addItems({"Bayraktar Akıncı", "Bayraktar TB2", "Wing Loong II", "Anka", "Burraq", "Shahpar-II", "CH-4 Rainbow", "Falco", "Shahpar", "Jasoos II"});
        } else if (type == "Helicopters") {
            modelComboBox.addItems({"Mi-17", "AW139"});
        }
    });

    typeComboBox.setCurrentIndex(0);
    emit typeComboBox.currentTextChanged(typeComboBox.currentText());

    QPushButton okButton("OK"), cancelButton("Cancel");
    QHBoxLayout buttonLayout;
    buttonLayout.addWidget(&okButton);
    buttonLayout.addWidget(&cancelButton);
    form.addRow(&buttonLayout);

    connect(&okButton, &QPushButton::clicked, [&]() {
        if (idEdit.text().isEmpty() || modelComboBox.currentText().isEmpty()) {
            QMessageBox::warning(this, "Input Error", "All fields are required.");
            return;
        }

        // Check for duplicate Aircraft ID
        for (const Combatcraft& a : aircraftList) {
            if (a.id == idEdit.text()) {
                QMessageBox::warning(this, "Input Error", "Aircraft ID already exists.");
                return;
            }
        }

        aircraftList.append(Combatcraft(idEdit.text(), typeComboBox.currentText(), modelComboBox.currentText()));
        updateTable();
        dialog.accept();
    });

    connect(&cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);
    dialog.exec();
}

void MaintenanceLoggingWindow::editAircraft() {
    int currentRow = aircraftTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Selection Error", "Please select an aircraft to edit.");
        return;
    }

    Combatcraft& selectedAircraft = aircraftList[currentRow];
    QDialog dialog(this);
    QFormLayout form(&dialog);

    QLineEdit idEdit(selectedAircraft.id);
    QComboBox typeComboBox, modelComboBox;

    form.addRow("Aircraft ID:", &idEdit);
    form.addRow("Aircraft Type:", &typeComboBox);
    form.addRow("Model:", &modelComboBox);

    typeComboBox.addItems({"Combat Aircraft", "Trainer Aircraft", "Strategic Airlift & Aerial Refueling Aircraft", "Transport Aircraft", "Airborne Early Warning & Control Aircraft", "Electronic Warfare Aircraft", "Unmanned Aerial Vehicles", "Helicopters"});

    connect(&typeComboBox, &QComboBox::currentTextChanged, [&modelComboBox](const QString& type) {
        modelComboBox.clear();
        if (type == "Combat Aircraft") {
            modelComboBox.addItems({"J-10 Vigorous Dragon", "JF-17 Thunder", "F-16 Fighting Falcon", "Mirage III", "Mirage 5", "F-7"});
        } else if (type == "Trainer Aircraft") {
            modelComboBox.addItems({"K-8", "T-37 Tweet", "MFI-17 Mushshak"});
        } else if (type == "Strategic Airlift & Aerial Refueling Aircraft") {
            modelComboBox.addItems({"Il-78"});
        } else if (type == "Transport Aircraft") {
            modelComboBox.addItems({"C-130 Hercules", "Saab 2000", "Y-12", "Airbus A319", "Global 6000", "Citation V", "Gulfstream IV", "Phenom 100"});
        } else if (type == "Airborne Early Warning & Control Aircraft") {
            modelComboBox.addItems({"Saab 2000 AEW&C"});
        } else if (type == "Electronic Warfare Aircraft") {
            modelComboBox.addItems({"Dassault Falcon 20"});
        } else if (type == "Unmanned Aerial Vehicles") {
            modelComboBox.addItems({"Bayraktar Akıncı", "Bayraktar TB2", "Wing Loong II", "Anka", "Burraq", "Shahpar-II", "CH-4 Rainbow", "Falco", "Shahpar", "Jasoos II"});
        } else if (type == "Helicopters") {
            modelComboBox.addItems({"Mi-17", "AW139"});
        }
    });

    typeComboBox.setCurrentText(selectedAircraft.type);
    modelComboBox.addItem(selectedAircraft.model);

    QPushButton okButton("OK"), cancelButton("Cancel");
    QHBoxLayout buttonLayout;
    buttonLayout.addWidget(&okButton);
    buttonLayout.addWidget(&cancelButton);
    form.addRow(&buttonLayout);

    connect(&okButton, &QPushButton::clicked, [&]() {
        if (idEdit.text().isEmpty() || modelComboBox.currentText().isEmpty()) {
            QMessageBox::warning(this, "Input Error", "All fields are required.");
            return;
        }
        selectedAircraft.id = idEdit.text();
        selectedAircraft.type = typeComboBox.currentText();
        selectedAircraft.model = modelComboBox.currentText();
        updateTable();
        dialog.accept();
    });

    connect(&cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);
    dialog.exec();
}

void MaintenanceLoggingWindow::deleteAircraft() {
    int currentRow = aircraftTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Selection Error", "Please select an aircraft to delete.");
        return;
    }

    aircraftList.removeAt(currentRow);
    updateTable();
}

void MaintenanceLoggingWindow::addMaintenanceRecord() {
    int currentRow = aircraftTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Selection Error", "Please select an aircraft to add a maintenance record.");
        return;
    }

    Combatcraft& selectedAircraft = aircraftList[currentRow];
    QDialog dialog(this);
    QFormLayout form(&dialog);

    QDateEdit dateEdit;
    dateEdit.setCalendarPopup(true);
    dateEdit.setDate(QDate::currentDate());
    QLineEdit typeEdit, remarksEdit;

    form.addRow("Maintenance Date:", &dateEdit);
    form.addRow("Type of Maintenance:", &typeEdit);
    form.addRow("Remarks:", &remarksEdit);

    QPushButton okButton("OK"), cancelButton("Cancel");
    QHBoxLayout buttonLayout;
    buttonLayout.addWidget(&okButton);
    buttonLayout.addWidget(&cancelButton);
    form.addRow(&buttonLayout);

    connect(&okButton, &QPushButton::clicked, [&]() {
        if (typeEdit.text().isEmpty() || remarksEdit.text().isEmpty()) {
            QMessageBox::warning(this, "Input Error", "All fields are required.");
            return;
        }
        selectedAircraft.maintenanceHistory.append(MaintenanceRecord(dateEdit.date(), typeEdit.text(), remarksEdit.text()));
        selectedAircraft.lastMaintenanceDate = dateEdit.date();
        updateTable();
        dialog.accept();
    });

    connect(&cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);
    dialog.exec();
}

void MaintenanceLoggingWindow::editMaintenanceRecord() {
    int currentRow = maintenanceTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Selection Error", "Please select a maintenance record to edit.");
        return;
    }

    Combatcraft* selectedAircraft = nullptr;
    MaintenanceRecord* selectedRecord = nullptr;
    mapMaintenanceTableRowToRecord(currentRow, selectedAircraft, selectedRecord);

    if (!selectedAircraft || !selectedRecord) {
        QMessageBox::warning(this, "Error", "Could not find the selected maintenance record.");
        return;
    }

    QDialog dialog(this);
    QFormLayout form(&dialog);

    QDateEdit dateEdit;
    dateEdit.setCalendarPopup(true);
    dateEdit.setDate(selectedRecord->date);
    QLineEdit typeEdit(selectedRecord->type);
    QLineEdit remarksEdit(selectedRecord->remarks);

    form.addRow("Maintenance Date:", &dateEdit);
    form.addRow("Type of Maintenance:", &typeEdit);
    form.addRow("Remarks:", &remarksEdit);

    QPushButton okButton("OK"), cancelButton("Cancel");
    QHBoxLayout buttonLayout;
    buttonLayout.addWidget(&okButton);
    buttonLayout.addWidget(&cancelButton);
    form.addRow(&buttonLayout);

    connect(&okButton, &QPushButton::clicked, [&]() {
        if (typeEdit.text().isEmpty() || remarksEdit.text().isEmpty()) {
            QMessageBox::warning(this, "Input Error", "All fields are required.");
            return;
        }
        selectedRecord->date = dateEdit.date();
        selectedRecord->type = typeEdit.text();
        selectedRecord->remarks = remarksEdit.text();
        selectedAircraft->lastMaintenanceDate = dateEdit.date();
        updateTable();
        dialog.accept();
    });

    connect(&cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);
    dialog.exec();
}

void MaintenanceLoggingWindow::deleteMaintenanceRecord() {
    int currentRow = maintenanceTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Selection Error", "Please select a maintenance record to delete.");
        return;
    }

    Combatcraft* selectedAircraft = nullptr;
    MaintenanceRecord* selectedRecord = nullptr;
    mapMaintenanceTableRowToRecord(currentRow, selectedAircraft, selectedRecord);

    if (!selectedAircraft || !selectedRecord) {
        QMessageBox::warning(this, "Error", "Could not find the selected maintenance record.");
        return;
    }

    // Ensure correct use of removeOne
    bool removed = false;
    for (int i = 0; i < selectedAircraft->maintenanceHistory.size(); ++i) {
        if (selectedAircraft->maintenanceHistory[i] == *selectedRecord) {
            selectedAircraft->maintenanceHistory.removeAt(i);
            removed = true;
            break;
        }
    }

    if (removed) {
        updateTable();
    } else {
        QMessageBox::warning(this, "Error", "Failed to remove the maintenance record.");
    }
}

void MaintenanceLoggingWindow::logOperationalHours() {
    int currentRow = aircraftTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Selection Error", "Please select an aircraft to log operational hours.");
        return;
    }

    Combatcraft& selectedAircraft = aircraftList[currentRow];
    bool ok;
    int hours = QInputDialog::getInt(this, "Log Operational Hours", "Enter hours:", 0, 0, 1000, 1, &ok);
    if (ok) {
        selectedAircraft.operationalHours += hours;
        updateTable();
    }
}

void MaintenanceLoggingWindow::updateTable() {
    // Aircraft Table
    aircraftTable->setRowCount(0);
    for (const Combatcraft& aircraft : aircraftList) {
        int row = aircraftTable->rowCount();
        aircraftTable->insertRow(row);
        aircraftTable->setItem(row, 0, new QTableWidgetItem(aircraft.id));
        aircraftTable->setItem(row, 1, new QTableWidgetItem(aircraft.type));
        aircraftTable->setItem(row, 2, new QTableWidgetItem(aircraft.model));
        aircraftTable->setItem(row, 3, new QTableWidgetItem(aircraft.lastMaintenanceDate.toString("dd/MM/yyyy")));
        aircraftTable->setItem(row, 4, new QTableWidgetItem(aircraft.isMaintenanceDue() ? "Yes" : "No"));
        aircraftTable->setItem(row, 5, new QTableWidgetItem(QString::number(aircraft.operationalHours)));
    }

    // Maintenance Table
    maintenanceTable->setRowCount(0);
    for (const Combatcraft& aircraft : aircraftList) {
        for (const MaintenanceRecord& record : aircraft.maintenanceHistory) {
            int row = maintenanceTable->rowCount();
            maintenanceTable->insertRow(row);
            maintenanceTable->setItem(row, 0, new QTableWidgetItem(aircraft.id));
            maintenanceTable->setItem(row, 1, new QTableWidgetItem(record.date.toString("dd/MM/yyyy")));
            maintenanceTable->setItem(row, 2, new QTableWidgetItem(record.type));
            maintenanceTable->setItem(row, 3, new QTableWidgetItem(record.remarks));
        }
    }
}

void MaintenanceLoggingWindow::mapMaintenanceTableRowToRecord(int row, Combatcraft *&aircraft, MaintenanceRecord*& record) {
    int recordIndex = 0;
    for (Combatcraft& a : aircraftList) {
        for (int i = 0; i < a.maintenanceHistory.size(); ++i, ++recordIndex) {
            if (recordIndex == row) {
                aircraft = &a;
                record = &a.maintenanceHistory[i];
                return;
            }
        }
    }
    aircraft = nullptr;
    record = nullptr;
}

void MaintenanceLoggingWindow::saveDataToFile() {
    QFile file("maintenance_data.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Unable to open file for saving.";
        return;
    }

    QTextStream out(&file);
    for (const Combatcraft& aircraft : aircraftList) {
        out << aircraft.serialize() << "\n";
    }
    file.close();
}

void MaintenanceLoggingWindow::loadDataFromFile() {
    QFile file("maintenance_data.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Unable to open file for loading.";
        return;
    }

    QTextStream in(&file);
    aircraftList.clear(); // Clear existing list to avoid duplicates
    while (!in.atEnd()) {
        Combatcraft aircraft = Combatcraft::deserialize(in);
        if (!aircraft.id.isEmpty()) {
            aircraftList.append(aircraft);
        }
    }
    file.close();
}
