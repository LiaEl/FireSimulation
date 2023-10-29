#include "AppWidget.h"
#include "FireSimulation.h"

#include <QColor>
#include <QPainter>
#include <QResizeEvent>
#include "nlohmann/json.hpp"
#include <QDebug>

using json = nlohmann::json;

AppWidget::AppWidget(int w, int h, QWidget *parent) : QWidget(parent) {
    std::ifstream f("../color.json");
    json data = json::parse(f);
    json colors = data["colors"];

    for(json color: colors)
    {
        int r = color[0];
        int g = color[1];
        int b = color[2];
        color_table.push_back(QColor(r, g, b).rgb()); // three times to make fire looks higher
        color_table.push_back(QColor(r, g, b).rgb());
        color_table.push_back(QColor(r, g, b).rgb());
    }

    this->simulation = new FireSimulation(w, h);
    this->simulation->setIntensityMax(color_table.size() - 1);
    this->simulation->setFireIntensity(color_table.size() - 1);
    this->simulation_created = true;
    this->simulation_running = true;

    update_interval = 20;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &AppWidget::onTimerUpdate);
    timer->start(update_interval);
}

AppWidget::~AppWidget() {
    delete simulation;
}

QString AppWidget::playPauseString() const {
    return simulation_running ? QString("Stop") : QString("Start");
}

QString AppWidget::windSpeed() {
    return QString("%1").arg(simulation->getWindSpeed());
}

QString AppWidget::updateInterval() const {
    return QString("%1").arg(update_interval);
}

QString AppWidget::updateIntensity() const {
    return QString("%1").arg(simulation->getIntensity());
}

void AppWidget::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);

    QImage img(simulation->getAlignedFireVector(),
               simulation->getWidth(),
               simulation->getHeight(),
               QImage::Format_Indexed8);
    img.setColorTable(color_table);

//    cv::Mat img_to_blur = QImageToMat(img, QImage::Format_Indexed8);
//    cv::Mat image_blurred_with_5x5_kernel;
//    GaussianBlur(img_to_blur, image_blurred_with_5x5_kernel, cv::Size(5, 5), 0);
//    QImage* img_blured = matToQImage(image_blurred_with_5x5_kernel, QImage::Format_Indexed8);

    QPainter p(this);
    p.drawImage(QPoint(0, 0), img);
}

//QImage AppWidget::matToQImage(cv::Mat &mat, QImage::Format format)
//{
//    return QImage(mat.data, mat.cols, mat.rows, format);
////    return QImage(mat.data, mat.cols, mat.rows, mat.step, format);
//}
//
//cv::Mat AppWidget::QImageToMat(QImage& img, int format)
//{
////    return cv::Mat(img.height(), img.width(),
////                   format, img.bits(), img.bytesPerLine());
//    return cv::Mat(img.height(), img.width(), format,
//                   const_cast<uchar*>(img.bits()),
//                   img.bytesPerLine()).clone();
//}

void AppWidget::onTimerUpdate() {
    simulation->spreadFire();
    update();
}

void AppWidget::onStartStopPressed() {
    if (simulation_running) {
        timer->stop();
        simulation_running = false;
    } else {
        timer->start(update_interval);
        simulation_running = true;
    }
    emit statusUpdated();
    update();
}

void AppWidget::onIncreaseWindPressed() {
    simulation->increaseWindSpeed();
    emit statusUpdated();
}

void AppWidget::onDecreaseWindPressed() {
    simulation->decreaseWindSpeed();
    emit statusUpdated();
}

void AppWidget::onDecreaseIntensityPressed() {
    simulation->decreaseFireHeight();
    emit statusUpdated();
}

void AppWidget::onIncreaseIntensityPressed() {
    simulation->increaseFireHeight();
    emit statusUpdated();
}

void AppWidget::onIncreaseIntervalPressed() {
    if (update_interval < 100) {
        update_interval += 5;
        timer->setInterval(update_interval);
    }
    emit statusUpdated();
}

void AppWidget::onDecreaseIntervalPressed() {
    if (update_interval > 5) {
        update_interval -= 5;
        timer->setInterval(update_interval);
    }
    emit statusUpdated();
}

void AppWidget::resizeEvent(QResizeEvent *event) {
    int w = event->size().width();
    int h = event->size().height();
    simulation->resize(w, h);
    emit statusUpdated();
}