#include "mainwindow.h"
#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Fire Simulation");
    window.setGeometry(100, 100, 640, 480);

    QLabel *fireLabel = new QLabel(&window);
    fireLabel->setText("Fire ");
    fireLabel->setAlignment(Qt::AlignCenter);
    fireLabel->setGeometry(50, 50, 540, 380);
    window.show();

    return app.exec();
}


