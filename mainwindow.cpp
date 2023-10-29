#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "AppWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Fire Simulation");

    playPauseButton = new QPushButton(this);

    DecreaseWindButton = new QPushButton(this);
    DecreaseWindButton->setText("-");
    DecreaseWindButton->setMaximumWidth(35);

    IncreaseWindButton = new QPushButton(this);
    IncreaseWindButton->setText("+");
    IncreaseWindButton->setMaximumWidth(35);

    DecreaseIntervalButton = new QPushButton(this);
    DecreaseIntervalButton->setText("-");
    DecreaseIntervalButton->setMaximumWidth(35);

    IncreaseIntervalButton = new QPushButton(this);
    IncreaseIntervalButton->setText("+");
    IncreaseIntervalButton->setMaximumWidth(35);

    DecreaseIntensityButton = new QPushButton(this);
    DecreaseIntensityButton->setText("-");
    DecreaseIntensityButton->setMaximumWidth(35);

    IncreaseIntensityButton = new QPushButton(this);
    IncreaseIntensityButton->setText("+");
    IncreaseIntensityButton->setMaximumWidth(35);

    WindLabel = new QLabel(this);
    WindLabel->setText("Wind:");

    WindSpeedLabel = new QLabel(this);
    WindSpeedLabel->setMinimumWidth(14);
    WindSpeedLabel->setAlignment(Qt::AlignCenter);

    IntervalLabel = new QLabel(this);
    IntervalLabel->setText("Delay:");

    UpdateIntervalLabel = new QLabel(this);
    UpdateIntervalLabel->setMinimumWidth(20);
    UpdateIntervalLabel->setAlignment(Qt::AlignCenter);

    IntensityLabel = new QLabel(this);
    IntensityLabel->setText("Intensity:");

    UpdateIntensityLabel = new QLabel(this);
    UpdateIntensityLabel->setMinimumWidth(20);
    UpdateIntensityLabel->setAlignment(Qt::AlignCenter);

    ui->mainToolBar->setStyleSheet("QToolBar{spacing: 2px;}");

    ui->mainToolBar->addWidget(playPauseButton);

    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(WindLabel);
    ui->mainToolBar->addWidget(DecreaseWindButton);
    ui->mainToolBar->addWidget(WindSpeedLabel);
    ui->mainToolBar->addWidget(IncreaseWindButton);

    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(IntervalLabel);
    ui->mainToolBar->addWidget(DecreaseIntervalButton);
    ui->mainToolBar->addWidget(UpdateIntervalLabel);
    ui->mainToolBar->addWidget(IncreaseIntervalButton);

    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(IntensityLabel);
    ui->mainToolBar->addWidget(DecreaseIntensityButton);
    ui->mainToolBar->addWidget(UpdateIntensityLabel);
    ui->mainToolBar->addWidget(IncreaseIntensityButton);

    appWidget = new AppWidget(centralWidget()->width(), centralWidget()->height());
    setCentralWidget(appWidget);

    connect(playPauseButton, &QPushButton::released, appWidget, &AppWidget::onStartStopPressed);
    connect(DecreaseWindButton, &QPushButton::released, appWidget, &AppWidget::onDecreaseWindPressed);
    connect(IncreaseWindButton, &QPushButton::released, appWidget, &AppWidget::onIncreaseWindPressed);
    connect(DecreaseIntervalButton, &QPushButton::released, appWidget, &AppWidget::onDecreaseIntervalPressed);
    connect(IncreaseIntervalButton, &QPushButton::released, appWidget, &AppWidget::onIncreaseIntervalPressed);
    connect(DecreaseIntensityButton, &QPushButton::released, appWidget, &AppWidget::onDecreaseIntensityPressed);
    connect(IncreaseIntensityButton, &QPushButton::released, appWidget, &AppWidget::onIncreaseIntensityPressed);

    connect(appWidget, &AppWidget::statusUpdated, this, &MainWindow::onStatusUpdated);

    onStatusUpdated();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onStatusUpdated()
{
    playPauseButton->setText(appWidget->playPauseString());
    WindSpeedLabel->setText(appWidget->windSpeed());
    UpdateIntervalLabel->setText(appWidget->updateInterval());
    UpdateIntensityLabel->setText(appWidget->updateIntensity());
}
