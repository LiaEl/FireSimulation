#ifndef FIRESIMULATION_FIRESIMULATION_H
#define FIRESIMULATION_FIRESIMULATION_H

#pragma once
#include <qglobal.h>

class FireSimulation {

public:
    FireSimulation(int width, int height);
    ~FireSimulation();

    const uchar* getAlignedFireVector();
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
    void setSize(int w, int h);


private:
    int getIdx(int i, int j) const;
    void setIdx(int i, int j, uchar value);

    int width{};
    int height{};
    int aligned_w{};
    int vector_len{};
    int wind_speed{};
    int cur_fire_intensity{};
    int max_fire_intensity{};
    uchar* fire_value{};
};
#endif //FIRESIMULATION_FIRESIMULATION_H
