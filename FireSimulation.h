#ifndef FIRESIMULATION_FIRESIMULATION_H
#define FIRESIMULATION_FIRESIMULATION_H

#pragma once
#include <qglobal.h>

class FireSimulation {

public:
    FireSimulation(int width, int height);
    ~FireSimulation();

    const uchar* getBrightnessMap();
    int getWidth() const;
    int getHeight() const;
    int getWindSpeed() const;
    void setFireIntensity(int intensity);
    void setIntensityMax(int max);
    int getIntensity() const;
    void decreaseFireHeight();
    void increaseFireHeight();
    void spreadFire();
    void resetFire();
    void decreaseWindSpeed();
    void increaseWindSpeed();
    void resize(int width, int height);
    void setFireWidth(int w, int h);

private:
    int getIdx(int i, int j) const;
    void setPixelColor(int x, int y, uchar brightness_value);

    int width{};
    int height{};
    int aligned_w{};
    int vector_len{};
    int wind_speed{};
    int cur_fire_intensity{};
    int max_fire_intensity{};
    uchar* color_map{};
};
#endif //FIRESIMULATION_FIRESIMULATION_H
