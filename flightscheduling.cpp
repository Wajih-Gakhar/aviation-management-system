#include "flightscheduling.h"
#include <QMessageBox>
#include <QLabel>
#include <QHeaderView>

FlightSchedulingWindow::FlightSchedulingWindow(QWidget *parent)
    : QMainWindow(parent){
    QWidget* centralWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();

    // Set background color
    centralWidget->setStyleSheet("background-color: #f0f0f0;"); // Light grey background

    QLabel* flightLabel = new QLabel("<h2><b>Flight Scheduling System:</b></h2>");

    // Styling the QLabel to center it, add a border, background color, and padding
    flightLabel->setStyleSheet("QLabel {"
                                    "font-size: 20px;"
                                    "color: white;"  // Text color (you can adjust this)
                                    "background-color: #3498DB;"  // Background color (light blue)
                                    "border: 2px solid #2980B9;"  // Border color (darker blue)
                                    "padding: 10px;"  // Padding inside the label
                                    "text-align: center;"  // Center the text inside the label
                                    "border-radius: 8px;"  // Rounded corners for the box
                                    "}");

    flightLabel->setAlignment(Qt::AlignCenter);  // Ensure the text is centered
    layout->addWidget(flightLabel);

    flightTable = new QTableWidget();
    flightTable->setColumnCount(5);
    flightTable->setHorizontalHeaderLabels({"Mission Name", "Aircraft Type", "Model", "Pilot Name", "Date & Time"});

    // Styling table headers and rows
    flightTable->setStyleSheet("QTableWidget { border: none; font-size: 14px; }"
                                 "QTableWidget::item { padding: 5px; background-color: #ffffff; }"
                                 "QHeaderView::section { background-color: #4CAF50; color: white; padding: 10px; font-size: 16px; }"
                                 "QTableWidget::item:selected { background-color: #2196F3; color: white; }"
                                 "QTableWidget::horizontalHeader { background-color: #4CAF50; font-weight: bold; }");

    // Set all columns to stretch equally
    for (int i = 0; i < flightTable->columnCount(); ++i) {
        flightTable->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    // Set the table to expand horizontally and vertically in the layout
    flightTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(flightTable);

    // Create button layout (Horizontal Layout for buttons)
    QHBoxLayout* buttonLayout = new QHBoxLayout();

    // Buttons for CRUD operations with custom styles
    QPushButton* scheduleButton = new QPushButton("Schedule Flight");
    QPushButton* editButton = new QPushButton("Edit Flight");
    QPushButton* deleteButton = new QPushButton("Delete Flight");

    // Styling buttons
    scheduleButton->setStyleSheet("QPushButton { "
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

    // Add buttons to the button layout (horizontal)
    buttonLayout->addWidget(scheduleButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);

    // Set the contents margins to move the buttons slightly up
    buttonLayout->setContentsMargins(0, 0, 0, 20); // Move up by 20 pixels

    // Add the button layout to the main layout (only once)
    layout->addLayout(buttonLayout);

    // Add the button layout to the main layout
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(scheduleButton, &QPushButton::clicked, this, &FlightSchedulingWindow::scheduleFlight);
    connect(editButton, &QPushButton::clicked, this, &FlightSchedulingWindow::editFlight);
    connect(deleteButton, &QPushButton::clicked, this, &FlightSchedulingWindow::deleteFlight);

    setWindowTitle("Flight Scheduling");
    resize(1350, 950);

    // Load data from file on startup
    loadFromFile();
}

void FlightSchedulingWindow::scheduleFlight() {
    QDialog dialog(this);
    QFormLayout form(&dialog);

    QLineEdit missionEdit, pilotEdit;
    QComboBox aircraftCombo, modelCombo;
    QDateTimeEdit dateTimeEdit;
    dateTimeEdit.setCalendarPopup(true);

    aircraftCombo.addItems({"Combat Aircraft", "Trainer Aircraft", "Strategic Airlift & Aerial Refueling Aircraft", "Transport Aircraft", "Airborne Early Warning & Control Aircraft", "Electronic Warfare Aircraft", "Unmanned Aerial Vehicles", "Helicopters"});

    connect(&aircraftCombo, &QComboBox::currentTextChanged, [&](const QString& selectedAircraft) {
        modelCombo.clear();
        if (selectedAircraft == "Combat Aircraft") {
            modelCombo.addItems({"J-10 Vigorous Dragon", "JF-17 Thunder", "F-16 Fighting Falcon", "Mirage III", "Mirage 5", "F-7"});
        } else if (selectedAircraft == "Trainer Aircraft") {
            modelCombo.addItems({"K-8", "T-37 Tweet", "MFI-17 Mushshak"});
        } else if (selectedAircraft == "Strategic Airlift & Aerial Refueling Aircraft") {
            modelCombo.addItems({"Il-78"});
        } else if (selectedAircraft == "Transport Aircraft") {
            modelCombo.addItems({"C-130 Hercules", "Saab 2000", "Y-12", "Airbus A319", "Global 6000", "Citation V", "Gulfstream IV", "Phenom 100"});
        } else if (selectedAircraft == "Airborne Early Warning & Control Aircraft") {
            modelCombo.addItems({"Saab 2000 AEW&C"});
        } else if (selectedAircraft == "Electronic Warfare Aircraft") {
            modelCombo.addItems({"Dassault Falcon 20"});
        } else if (selectedAircraft == "Unmanned Aerial Vehicles") {
            modelCombo.addItems({"Bayraktar Akıncı", "Bayraktar TB2", "Wing Loong II", "Anka", "Burraq", "Shahpar-II", "CH-4 Rainbow", "Falco", "Shahpar", "Jasoos II"});
        } else if (selectedAircraft == "Helicopters") {
            modelCombo.addItems({"Mi-17", "AW139"});
        }
    });
    aircraftCombo.setCurrentIndex(0);
    emit aircraftCombo.currentTextChanged(aircraftCombo.currentText());

    form.addRow("Mission Name:", &missionEdit);
    form.addRow("Aircraft Type:", &aircraftCombo);
    form.addRow("Model:", &modelCombo);
    form.addRow("Pilot Name:", &pilotEdit);
    form.addRow("Date and Time:", &dateTimeEdit);

    QPushButton okButton("OK"), cancelButton("Cancel");
    QHBoxLayout buttonLayout;
    buttonLayout.addWidget(&okButton);
    buttonLayout.addWidget(&cancelButton);
    form.addRow(&buttonLayout);

    connect(&okButton, &QPushButton::clicked, [&]() {
        if (missionEdit.text().isEmpty() || aircraftCombo.currentText().isEmpty() || modelCombo.currentText().isEmpty() || pilotEdit.text().isEmpty()) {
            QMessageBox::warning(this, "Input Error", "All fields are required.");
            return;
        }

        Flight newFlight(missionEdit.text(), aircraftCombo.currentText(), modelCombo.currentText(), pilotEdit.text(), dateTimeEdit.dateTime());
        flightList.append(newFlight);

        updateTable();
        saveToFile();
        dialog.accept();
    });
    connect(&cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    dialog.exec();
}

void FlightSchedulingWindow::editFlight() {
    int currentRow = flightTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Selection Error", "Please select a flight to edit.");
        return;
    }

    Flight& selectedFlight = flightList[currentRow];

    QDialog dialog(this);
    QFormLayout form(&dialog);

    QLineEdit missionEdit(selectedFlight.missionName), pilotEdit(selectedFlight.pilotName);
    QComboBox aircraftCombo, modelCombo;
    QDateTimeEdit dateTimeEdit;
    dateTimeEdit.setCalendarPopup(true);
    dateTimeEdit.setDateTime(selectedFlight.dateTime);

    aircraftCombo.addItems({"Combat Aircraft", "Trainer Aircraft", "Strategic Airlift & Aerial Refueling Aircraft", "Transport Aircraft", "Airborne Early Warning & Control Aircraft", "Electronic Warfare Aircraft", "Unmanned Aerial Vehicles", "Helicopters"});
    aircraftCombo.setCurrentText(selectedFlight.aircraftType);

    connect(&aircraftCombo, &QComboBox::currentTextChanged, [&](const QString& selectedAircraft) {
        modelCombo.clear();
        if (selectedAircraft == "Combat Aircraft") {
            modelCombo.addItems({"J-10 Vigorous Dragon", "JF-17 Thunder", "F-16 Fighting Falcon", "Mirage III", "Mirage 5", "F-7"});
        } else if (selectedAircraft == "Trainer Aircraft") {
            modelCombo.addItems({"K-8", "T-37 Tweet", "MFI-17 Mushshak"});
        } else if (selectedAircraft == "Strategic Airlift & Aerial Refueling Aircraft") {
            modelCombo.addItems({"Il-78"});
        } else if (selectedAircraft == "Transport Aircraft") {
            modelCombo.addItems({"C-130 Hercules", "Saab 2000", "Y-12", "Airbus A319", "Global 6000", "Citation V", "Gulfstream IV", "Phenom 100"});
        } else if (selectedAircraft == "Airborne Early Warning & Control Aircraft") {
            modelCombo.addItems({"Saab 2000 AEW&C"});
        } else if (selectedAircraft == "Electronic Warfare Aircraft") {
            modelCombo.addItems({"Dassault Falcon 20"});
        } else if (selectedAircraft == "Unmanned Aerial Vehicles") {
            modelCombo.addItems({"Bayraktar Akıncı", "Bayraktar TB2", "Wing Loong II", "Anka", "Burraq", "Shahpar-II", "CH-4 Rainbow", "Falco", "Shahpar", "Jasoos II"});
        } else if (selectedAircraft == "Helicopters") {
            modelCombo.addItems({"Mi-17", "AW139"});
        }
    });
    emit aircraftCombo.currentTextChanged(selectedFlight.aircraftType);

    form.addRow("Mission Name:", &missionEdit);
    form.addRow("Aircraft Type:", &aircraftCombo);
    form.addRow("Model:", &modelCombo);
    form.addRow("Pilot Name:", &pilotEdit);
    form.addRow("Date and Time:", &dateTimeEdit);

    QPushButton okButton("OK"), cancelButton("Cancel");
    QHBoxLayout buttonLayout;
    buttonLayout.addWidget(&okButton);
    buttonLayout.addWidget(&cancelButton);
    form.addRow(&buttonLayout);

    connect(&okButton, &QPushButton::clicked, [&]() {
        if (missionEdit.text().isEmpty() || aircraftCombo.currentText().isEmpty() || modelCombo.currentText().isEmpty() || pilotEdit.text().isEmpty()) {
            QMessageBox::warning(this, "Input Error", "All fields are required.");
            return;
        }

        selectedFlight.missionName = missionEdit.text();
        selectedFlight.aircraftType = aircraftCombo.currentText();
        selectedFlight.aircraftModel = modelCombo.currentText();
        selectedFlight.pilotName = pilotEdit.text();
        selectedFlight.dateTime = dateTimeEdit.dateTime();

        updateTable();
        saveToFile();
        dialog.accept();
    });
    connect(&cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    dialog.exec();
}

void FlightSchedulingWindow::deleteFlight() {
    int currentRow = flightTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Selection Error", "Please select a flight to delete.");
        return;
    }

    flightList.removeAt(currentRow);
    updateTable();
    saveToFile();
}

void FlightSchedulingWindow::updateTable() {
    flightTable->setRowCount(flightList.size());

    for (int i = 0; i < flightList.size(); ++i) {
        const Flight& flight = flightList[i];
        flightTable->setItem(i, 0, new QTableWidgetItem(flight.missionName));
        flightTable->setItem(i, 1, new QTableWidgetItem(flight.aircraftType));
        flightTable->setItem(i, 2, new QTableWidgetItem(flight.aircraftModel));
        flightTable->setItem(i, 3, new QTableWidgetItem(flight.pilotName));
        flightTable->setItem(i, 4, new QTableWidgetItem(flight.dateTime.toString("dd-MM-yyyy (HH:mm AP)")));
    }
}

void FlightSchedulingWindow::saveToFile() {
    QFile file("flights_data.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to save data to file.");
        return;
    }
    QTextStream out(&file);
    for (const Flight& flight : flightList) {
        out << flight.toString() << "\n";
    }
    file.close();
}

void FlightSchedulingWindow::loadFromFile() {
    QFile file("flights_data.txt");
    if (!file.exists()) return;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to load data from file.");
        return;
    }
    QTextStream in(&file);
    flightList.clear();
    while (!in.atEnd()) {
        QString line = in.readLine();
        try {
            Flight flight = Flight::fromString(line);
            flightList.append(flight);
        } catch (const std::invalid_argument&) {
            QMessageBox::warning(this, "Error", "Corrupted flight data ignored.");
        }
    }
    file.close();
    updateTable();
}
