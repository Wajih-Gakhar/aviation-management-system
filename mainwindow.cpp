#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aircraftmanagement.h"
#include "pilotrecordmanagement.h"
#include "flightscheduling.h"
#include "maintenancelogging.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set the window title
    this->setWindowTitle("Aviation Management System");
    this->resize(1350, 950);

    // Set background image for the main window
    this->setStyleSheet(
        "QMainWindow {"
        "   background-image: url('D:/OneDrive/Desktop/Coding/QT/Aviation_Management_System/Pics/Main.jpg');"
        "   background-repeat: no-repeat;"
        "   background-position: center;"
        "   background-color: black;"
        "}"
        );

    // Set the introduction label
    QLabel *introLabel = new QLabel(this);
    introLabel->setText(
        "<h1><b><i>Welcome to the Aviation Management System of the Pakistan Air Force.</i></b></h1>\n"
        "This system is designed to streamline and enhance aviation operations by automating key tasks such as aircraft management, pilot records, flight scheduling, and maintenance logging.\n"
        "The system ensures efficient data management, faster decision-making, and improved operational readiness.\n"
        "Whether it’s tracking aircraft availability, managing pilot assignments, or monitoring maintenance schedules, this system provides a centralized platform to handle all critical aviation management tasks with accuracy and ease.\n"
        "Explore the tools and features to simplify your workflows and elevate your air force operations to new levels of efficiency."
        );
    introLabel->setAlignment(Qt::AlignCenter);
    introLabel->setWordWrap(true);
    introLabel->setStyleSheet(
        "font-size: 16px;"
        "font-family: Copperplate Gothic Bold, Helvetica, sans-serif;"
        "font-weight: bold;"
        "color: white;"
        "background-color: rgba(0, 0, 0, 0.7);"
        "padding: 20px;"
        "border-radius: 10px;"
        "margin: 10px;"
        );

    // Create a button to show features
    QPushButton *featuresButton = new QPushButton("Main Menu", this);
    featuresButton->setStyleSheet(
        "font-size: 16px;"
        "font-family: Lucida Calligraphy, Helvetica, sans-serif;"
        "color: white;"
        "background-color: #007BFF;"
        "border: none;"
        "border-radius: 10px;"
        "padding: 10px;"
        "margin: 10px;"
        "min-width: 150px;"
        "min-height: 40px;"
        "hover { background-color: #0056b3; }"
        );

    // Set layout for the window
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(introLabel);
    mainLayout->addWidget(featuresButton, 0, Qt::AlignCenter);
    ui->centralwidget->setLayout(mainLayout);

    // Create feature buttons with consistent styling
    QPushButton *aircraftButton = new QPushButton("Aircraft Management System", this);
    QPushButton *pilotButton = new QPushButton("Pilot Record Management System", this);
    QPushButton *flightButton = new QPushButton("Flight Scheduling", this);
    QPushButton *maintenanceButton = new QPushButton("Maintenance Logging", this);

    QString buttonStyle =
        "font-size: 14px;"
        "font-family: Lucida Calligraphy, Helvetica, sans-serif;"
        "color: white;"
        "background-color: #28a745;"
        "border: none;"
        "border-radius: 10px;"
        "padding: 10px;"
        "margin: 5px;"
        "min-width: 200px;"
        "min-height: 40px;"
        "hover { background-color: #218838; }";

    aircraftButton->setStyleSheet(buttonStyle);
    pilotButton->setStyleSheet(buttonStyle);
    flightButton->setStyleSheet(buttonStyle);
    maintenanceButton->setStyleSheet(buttonStyle);

    // Initially hide the feature buttons
    aircraftButton->setVisible(false);
    pilotButton->setVisible(false);
    flightButton->setVisible(false);
    maintenanceButton->setVisible(false);

    // Add feature buttons to the layout
    mainLayout->addWidget(aircraftButton, 0, Qt::AlignCenter);
    mainLayout->addWidget(pilotButton, 0, Qt::AlignCenter);
    mainLayout->addWidget(flightButton, 0, Qt::AlignCenter);
    mainLayout->addWidget(maintenanceButton, 0, Qt::AlignCenter);

    // Function to animate button appearance
    auto fadeSlideInFromBottom = [this](QWidget *button, int offsetIndex, int spacing) {
        int windowHeight = this->height(); // Height of the window
        int windowWidth = this->width();  // Width of the window
        int buttonHeight = button->height(); // Height of the button
        int buttonWidth = button->width(); // Width of the button

        // Adjust size of the button to fit text properly
        button->adjustSize(); // Automatically resize button based on text content
        button->setMinimumWidth(300);  // Set a minimum width to avoid button being too small
        button->setMinimumHeight(40);  // Set a minimum height to ensure text fits

        // Start below the window (off-screen)
        int startX = (windowWidth - buttonWidth) / 2; // Center horizontally
        int startY = windowHeight + 50; // Start below the window (off-screen)

        // Calculate the endY position to align buttons from the bottom upwards
        int endY = windowHeight - (offsetIndex + 1) * (buttonHeight + spacing);

        // Ensure buttons don't overlap or go off-screen by restricting the bottom position
        if (endY < 0) {
            endY = 0; // Prevent buttons from going above the window
        }

        button->setWindowOpacity(0.0); // Start with transparency
        button->setVisible(true); // Make the button visible

        // Fade animation
        QPropertyAnimation *fadeAnimation = new QPropertyAnimation(button, "windowOpacity");
        fadeAnimation->setDuration(1000); // 1 second
        fadeAnimation->setStartValue(0.0);
        fadeAnimation->setEndValue(1.0);

        // Slide animation
        QPropertyAnimation *slideAnimation = new QPropertyAnimation(button, "geometry");
        slideAnimation->setDuration(1000); // 1 second
        slideAnimation->setStartValue(QRect(startX, startY, buttonWidth, buttonHeight));
        slideAnimation->setEndValue(QRect(startX, endY, buttonWidth, buttonHeight));

        // Group animations
        QParallelAnimationGroup *group = new QParallelAnimationGroup;
        group->addAnimation(fadeAnimation);
        group->addAnimation(slideAnimation);
        group->start(QAbstractAnimation::DeleteWhenStopped);
    };

    // Connect the Show Features button to reveal feature buttons with animations
    connect(featuresButton, &QPushButton::clicked, [=]() {
        int spacing = 20; // Spacing between button borders
        fadeSlideInFromBottom(aircraftButton, 3, spacing);        // First button
        fadeSlideInFromBottom(pilotButton, 2, spacing);           // Second button
        fadeSlideInFromBottom(flightButton, 1, spacing);          // Third button
        fadeSlideInFromBottom(maintenanceButton, 0, spacing);    // Fourth button
    });




    // Connect feature buttons to their respective systems
    connect(aircraftButton, &QPushButton::clicked, this, [=]() {
        AircraftManagementWindow *aircraftSystem = new AircraftManagementWindow(this);
        aircraftSystem->show();
    });

    connect(pilotButton, &QPushButton::clicked, this, [=]() {
        PilotManagementWindow *pilotSystem = new PilotManagementWindow(this);
        pilotSystem->show();
    });

    connect(flightButton, &QPushButton::clicked, this, [=]() {
        FlightSchedulingWindow *flightSystem = new FlightSchedulingWindow(this);
        flightSystem->show();
    });

    connect(maintenanceButton, &QPushButton::clicked, this, [=]() {
        MaintenanceLoggingWindow *maintenanceSystem = new MaintenanceLoggingWindow(this);
        maintenanceSystem->show();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
