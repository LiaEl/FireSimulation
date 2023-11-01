#ifndef FIRESIMULATION_APPWIDGET_H
#define FIRESIMULATION_APPWIDGET_H

#pragma once
#include <QWidget>
#include <QTimer>
#include "FireSimulation.h"
#include <opencv2/opencv.hpp>

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

private:
    FireSimulation *simulation;
    int update_interval;
    bool simulation_running;
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);

    QTimer *timer;

    QVector<QRgb> color_table;
};

#endif //FIRESIMULATION_APPWIDGET_H
