#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "AppWidget.h"

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {

Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    AppWidget *appWidget;

    QPushButton* playPauseButton;

    QPushButton* DecreaseWindButton;
    QPushButton* IncreaseWindButton;

    QPushButton* DecreaseIntervalButton;
    QPushButton* IncreaseIntervalButton;

    QPushButton* DecreaseIntensityButton;
    QPushButton* IncreaseIntensityButton;

    QLabel *WindLabel;
    QLabel *WindSpeedLabel;
    QLabel *IntervalLabel;
    QLabel *IntensityLabel;
    QLabel *UpdateIntervalLabel;
    QLabel *UpdateIntensityLabel;

public slots:
    void onStatusUpdated();
};
#endif // MAINWINDOW_H
