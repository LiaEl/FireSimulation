#ifndef FIRESIMULATION_APPWIDGET_H
#define FIRESIMULATION_APPWIDGET_H

#pragma once
#include <QWidget>
#include <QTimer>
#include "FireSimulation.h"

class AppWidget : public QWidget {

Q_OBJECT

public:
    explicit AppWidget(int w, int h, QWidget *parent = nullptr);
    ~AppWidget() override;

    QString playPauseString() const;
    QString windSpeed();
    QString updateInterval() const;
    QString updateIntensity() const;

signals:
    void statusUpdated();

public slots:
    void onTimerUpdate();

    void onStartStopPressed();

    void onIncreaseWindPressed();
    void onDecreaseWindPressed();

    void onIncreaseIntensityPressed();
    void onDecreaseIntensityPressed();

    void onIncreaseIntervalPressed();
    void onDecreaseIntervalPressed();

protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    FireSimulation *simulation;
    int update_interval;
    bool simulation_running;

    QTimer *timer;

    QVector<QRgb> color_table;
};

#endif //FIRESIMULATION_APPWIDGET_H
