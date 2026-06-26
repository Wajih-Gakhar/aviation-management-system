#include "aircraftmanagement.h"
#include <QFile>
#include <QTextStream>
#include <QLabel>
#include <QHeaderView>

AircraftManagementWindow::AircraftManagementWindow(QWidget *parent)
    : QMainWindow(parent) {
    QWidget* centralWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();

    // Set background color
    centralWidget->setStyleSheet("background-color: #f0f0f0;"); // Light grey background

    QLabel* aircraftLabel = new QLabel("<h2><b>Aircraft Management System:</b></h2>");

    // Styling the QLabel to center it, add a border, background color, and padding
    aircraftLabel->setStyleSheet("QLabel {"
                                    "font-size: 20px;"
                                    "color: white;"  // Text color (you can adjust this)
                                    "background-color: #3498DB;"  // Background color (light blue)
                                    "border: 2px solid #2980B9;"  // Border color (darker blue)
                                    "padding: 10px;"  // Padding inside the label
                                    "text-align: center;"  // Center the text inside the label
                                    "border-radius: 8px;"  // Rounded corners for the box
                                    "}");

    aircraftLabel->setAlignment(Qt::AlignCenter);  // Ensure the text is centered
    layout->addWidget(aircraftLabel);

    // Table to display aircraft with custom styles
    aircraftTable = new QTableWidget();
    aircraftTable->setColumnCount(5);
    aircraftTable->setHorizontalHeaderLabels({"ID", "Type", "Model", "Maintenance Status", "Availability"});

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

    // Create button layout (Horizontal Layout for buttons)
    QHBoxLayout* buttonLayout = new QHBoxLayout();

    // Buttons for CRUD operations with custom styles
    QPushButton* addButton = new QPushButton("Add Aircraft");
    QPushButton* editButton = new QPushButton("Edit Aircraft");
    QPushButton* deleteButton = new QPushButton("Delete Aircraft");

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

    // Add buttons to the button layout (horizontal)
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);

    // Set the contents margins to move the buttons slightly up
    buttonLayout->setContentsMargins(0, 0, 0, 20); // Move up by 20 pixels

    // Add the button layout to the main layout (only once)
    layout->addLayout(buttonLayout);

    // Add the button layout to the main layout
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(addButton, &QPushButton::clicked, this, &AircraftManagementWindow::addAircraft);
    connect(editButton, &QPushButton::clicked, this, &AircraftManagementWindow::editAircraft);
    connect(deleteButton, &QPushButton::clicked, this, &AircraftManagementWindow::deleteAircraft);

    setWindowTitle("Aircraft Management");
    resize(1350, 950);

    // Load existing data from file
    loadFromFile();
    updateTable();
}

void AircraftManagementWindow::addAircraft() {
    QDialog dialog(this);
    QFormLayout form(&dialog);

    QLineEdit idEdit;
    QComboBox typeCombo, modelCombo, maintenanceCombo;
    typeCombo.addItems({"Combat Aircraft", "Trainer Aircraft", "Strategic Airlift & Aerial Refueling Aircraft", "Transport Aircraft", "Airborne Early Warning & Control Aircraft", "Electronic Warfare Aircraft", "Unmanned Aerial Vehicles", "Helicopters"});
    maintenanceCombo.addItems({"Operational", "Under Maintenance"});

    form.addRow("ID:", &idEdit);
    form.addRow("Type:", &typeCombo);
    form.addRow("Model:", &modelCombo);
    form.addRow("Maintenance Status:", &maintenanceCombo);

    updateModelOptions(typeCombo, modelCombo);

    connect(&typeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this, &typeCombo, &modelCombo]() {
        updateModelOptions(typeCombo, modelCombo);
    });

    QPushButton okButton("OK"), cancelButton("Cancel");
    QHBoxLayout buttonLayout;
    buttonLayout.addWidget(&okButton);
    buttonLayout.addWidget(&cancelButton);
    form.addRow(&buttonLayout);

    connect(&okButton, &QPushButton::clicked, [&]() {
        if (idEdit.text().isEmpty()) {
            QMessageBox::warning(this, "Input Error", "All fields are required.");
            return;
        }
        aircraftList.append(Aircraft(idEdit.text(), typeCombo.currentText(), modelCombo.currentText(), maintenanceCombo.currentText(), true));
        updateTable();
        saveToFile();  // Save updated list to file
        dialog.accept();
    });
    connect(&cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    dialog.exec();
}

void AircraftManagementWindow::editAircraft() {
    int currentRow = aircraftTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Selection Error", "Please select an aircraft to edit.");
        return;
    }

    Aircraft& selectedAircraft = aircraftList[currentRow];

    QDialog dialog(this);
    QFormLayout form(&dialog);

    QLineEdit idEdit(selectedAircraft.id);
    QComboBox typeCombo, modelCombo, maintenanceCombo;
    typeCombo.addItems({"Combat Aircraft", "Trainer Aircraft", "Strategic Airlift & Aerial Refueling Aircraft", "Transport Aircraft", "Airborne Early Warning & Control Aircraft", "Electronic Warfare Aircraft", "Unmanned Aerial Vehicles", "Helicopters"});
    maintenanceCombo.addItems({"Operational", "Under Maintenance"});

    typeCombo.setCurrentText(selectedAircraft.type);
    maintenanceCombo.setCurrentText(selectedAircraft.maintenanceStatus);

    form.addRow("ID:", &idEdit);
    form.addRow("Type:", &typeCombo);
    form.addRow("Model:", &modelCombo);
    form.addRow("Maintenance Status:", &maintenanceCombo);

    updateModelOptions(typeCombo, modelCombo);
    modelCombo.setCurrentText(selectedAircraft.model);

    connect(&typeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this, &typeCombo, &modelCombo]() {
        updateModelOptions(typeCombo, modelCombo);
    });

    QPushButton okButton("OK"), cancelButton("Cancel");
    QHBoxLayout buttonLayout;
    buttonLayout.addWidget(&okButton);
    buttonLayout.addWidget(&cancelButton);
    form.addRow(&buttonLayout);

    connect(&okButton, &QPushButton::clicked, [&]() {
        if (idEdit.text().isEmpty()) {
            QMessageBox::warning(this, "Input Error", "All fields are required.");
            return;
        }
        selectedAircraft.id = idEdit.text();
        selectedAircraft.type = typeCombo.currentText();
        selectedAircraft.model = modelCombo.currentText();
        selectedAircraft.maintenanceStatus = maintenanceCombo.currentText();
        updateTable();
        saveToFile();  // Save updated list to file
        dialog.accept();
    });
    connect(&cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    dialog.exec();
}

void AircraftManagementWindow::deleteAircraft() {
    int currentRow = aircraftTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Selection Error", "Please select an aircraft to delete.");
        return;
    }

    aircraftList.removeAt(currentRow);
    updateTable();
    saveToFile();  // Save updated list to file
}

void AircraftManagementWindow::updateModelOptions(QComboBox& typeCombo, QComboBox& modelCombo) {
    modelCombo.clear();
    if (typeCombo.currentText() == "Combat Aircraft") {
        modelCombo.addItems({"J-10 Vigorous Dragon", "JF-17 Thunder", "F-16 Fighting Falcon", "Mirage III", "Mirage 5", "F-7"});
    } else if (typeCombo.currentText() == "Trainer Aircraft") {
        modelCombo.addItems({"K-8", "T-37 Tweet", "MFI-17 Mushshak"});
    } else if (typeCombo.currentText() == "Strategic Airlift & Aerial Refueling Aircraft") {
        modelCombo.addItems({"Il-78"});
    } else if (typeCombo.currentText() == "Transport Aircraft") {
        modelCombo.addItems({"C-130 Hercules", "Saab 2000", "Y-12", "Airbus A319", "Global 6000", "Citation V", "Gulfstream IV", "Phenom 100"});
    } else if (typeCombo.currentText() == "Airborne Early Warning & Control Aircraft") {
        modelCombo.addItems({"Saab 2000 AEW&C"});
    } else if (typeCombo.currentText() == "Electronic Warfare Aircraft") {
        modelCombo.addItems({"Dassault Falcon 20"});
    } else if (typeCombo.currentText() == "Unmanned Aerial Vehicles") {
        modelCombo.addItems({"Bayraktar Akıncı", "Bayraktar TB2", "Wing Loong II", "Anka", "Burraq", "Shahpar-II", "CH-4 Rainbow", "Falco", "Shahpar", "Jasoos II"});
    } else if (typeCombo.currentText() == "Helicopters") {
        modelCombo.addItems({"Mi-17", "AW139"});
    }
}

void AircraftManagementWindow::updateTable() {
    aircraftTable->setRowCount(aircraftList.size());
    for (int i = 0; i < aircraftList.size(); ++i) {
        const Aircraft& aircraft = aircraftList[i];
        aircraftTable->setItem(i, 0, new QTableWidgetItem(aircraft.id));
        aircraftTable->setItem(i, 1, new QTableWidgetItem(aircraft.type));
        aircraftTable->setItem(i, 2, new QTableWidgetItem(aircraft.model));
        aircraftTable->setItem(i, 3, new QTableWidgetItem(aircraft.maintenanceStatus));
        aircraftTable->setItem(i, 4, new QTableWidgetItem(aircraft.isAvailable ? "Available" : "Unavailable"));
    }
}

void AircraftManagementWindow::saveToFile() {
    QFile file("aircraft_data.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const Aircraft& aircraft : aircraftList) {
            out << aircraft.id << "|"
                << aircraft.type << "|"
                << aircraft.model << "|"
                << aircraft.maintenanceStatus << "|"
                << (aircraft.isAvailable ? "1" : "0") << "\n";
        }
    }
    file.close();
}

void AircraftManagementWindow::loadFromFile() {
    QFile file("aircraft_data.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split("|");
            if (fields.size() == 5) {
                bool isAvailable = fields[4] == "1";
                aircraftList.append(Aircraft(fields[0], fields[1], fields[2], fields[3], isAvailable));
            }
        }
    }
    file.close();
}
