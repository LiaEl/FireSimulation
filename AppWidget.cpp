#include "AppWidget.h"
#include "FireSimulation.h"
#include "colors.h"

#include <QColor>
#include <QPainter>
#include <QResizeEvent>
#include <QDebug>

AppWidget::AppWidget(int w, int h, QWidget *parent) : QWidget(parent)
{

    for(Color color: Colors)
    {
        int r = color.r;
        int g = color.g;
        int b = color.b;
        // append color three times to make fire look higher
        for(int i = 0; i < 3; i++)
        {
            color_table.push_back(QColor(r, g, b).rgb());
        }
    }

    simulation = new FireSimulation(w, h);
    const auto last_color_index = color_table.size() - 1;
    simulation->setIntensityMax(last_color_index);
    simulation->setFireIntensity(last_color_index);
    simulation_running = true;

    update_interval = 20;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &AppWidget::onTimerUpdate);
    timer->start(update_interval);
}

AppWidget::~AppWidget()
{
    delete simulation;
}

QString AppWidget::playPauseString() const
{
    return simulation_running ? QString("Stop") : QString("Start");
}

QString AppWidget::windSpeed()
{
    return QString("%1").arg(simulation->getWindSpeed());
}

QString AppWidget::updateInterval() const
{
    return QString("%1").arg(update_interval);
}

QString AppWidget::updateIntensity() const
{
    return QString("%1").arg(simulation->getIntensity());
}

void AppWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QImage img(simulation->getBrightnessMap(),
               simulation->getWidth(),
               simulation->getHeight(),
               QImage::Format_Indexed8);
    img.setColorTable(color_table);

    QPainter p(this);
    p.drawImage(QPoint(0, 0), img);
}

void AppWidget::onTimerUpdate()
{
    simulation->spreadFire();
    update();
}

void AppWidget::onStartStopPressed()
{
    if (simulation_running)
    {
        timer->stop();
        simulation_running = false;
    } else
    {
        timer->start(update_interval);
        simulation_running = true;
    }
    emit statusUpdated();
    update();
}

void AppWidget::onIncreaseWindPressed()
{
    simulation->increaseWindSpeed();
    emit statusUpdated();
}

void AppWidget::onDecreaseWindPressed()
{
    simulation->decreaseWindSpeed();
    emit statusUpdated();
}

void AppWidget::onDecreaseIntensityPressed()
{
    simulation->decreaseFireHeight();
    emit statusUpdated();
}

void AppWidget::onIncreaseIntensityPressed()
{
    simulation->increaseFireHeight();
    emit statusUpdated();
}

void AppWidget::onIncreaseIntervalPressed()
{
    if (update_interval < 100)
    {
        update_interval += 5;
        timer->setInterval(update_interval);
    }
    emit statusUpdated();
}

void AppWidget::onDecreaseIntervalPressed()
{
    if (update_interval > 5)
    {
        update_interval -= 5;
        timer->setInterval(update_interval);
    }
    emit statusUpdated();
}

void AppWidget::resizeEvent(QResizeEvent *event)
{
    int w = event->size().width();
    int h = event->size().height();
    simulation->resize(w, h);
    emit statusUpdated();
}