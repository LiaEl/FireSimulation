#include "FireSimulation.h"
#include <string.h>
#include <random>

#define FIRE_ALIGN 4

FireSimulation::FireSimulation(int w, int h) {
    setSize(w, h);
}

FireSimulation::~FireSimulation(){
    delete[] fire_value;
}

void FireSimulation::resetFire() {
    size_t len = static_cast<size_t>(vector_len) * sizeof(uchar);
    memset(fire_value, 0, len);
}

int FireSimulation::getIdx(int i, int j) const {
    return i + aligned_w * j;
}

void FireSimulation::setIdx(int i, int j, uchar value) {
    if (i >= 0 && i < width && j >= 0 && j < height)
        fire_value[getIdx(i, j)] = value;
}

void FireSimulation::setSize(int w, int h) {
    width = w;
    height = h;

    if (w % FIRE_ALIGN)
        aligned_w = w + FIRE_ALIGN - (w % FIRE_ALIGN);
    else
        aligned_w = w;

    vector_len = aligned_w * h;
    fire_value = new uchar[vector_len];
    wind_speed = 0;

    resetFire();
}
void FireSimulation::resize(int w, int h) {
    delete fire_value;
    setSize(w, h);
    setFireIntensity(cur_fire_intensity);
}

const uchar* FireSimulation::getAlignedFireVector()
{
    return fire_value;
}

int FireSimulation::getWidth() const
{
    return width;
}

int FireSimulation::getHeight() const
{
    return height;
}

int FireSimulation::getWindSpeed() const
{
    return wind_speed;
}

void FireSimulation::setFireIntensity(int intensity)
{
    cur_fire_intensity = intensity;
    for (int i = 0; i < width; i++) {
        fire_value[getIdx(i, height-1)] = cur_fire_intensity;
    }
}

void FireSimulation::setIntensityMax(int max)
{
    max_fire_intensity = max;
}

int FireSimulation::getIntensity() const
{
    return cur_fire_intensity;
}

void FireSimulation::spreadFire()
{
    std::random_device myRandomDevice;
    unsigned seed = myRandomDevice();
    std::default_random_engine myRandomEngine(seed);

    for (int j = 0; j < (height - 1); j++) {
        for (int i = 0; i < width; i++) {
            auto decay = myRandomEngine() % 3;
            int new_value = fire_value[getIdx(i, j+1)] - (decay > 1 ? 1 : 0);
            if (new_value < 0)
                new_value = 0;

            // change pixel direction
            int new_i = i + (myRandomEngine() % 3 - 1);

            // lateral effect (wind)
            if (wind_speed > 0 && myRandomEngine() % 2) {
                new_i += wind_speed;
            }
            else if (wind_speed < 0 && myRandomEngine() % 2) {
                new_i += wind_speed;
            }

            setIdx(new_i, j, static_cast<uchar>(new_value));
        }
    }
}

void FireSimulation::decreaseWindSpeed()
{
    if (wind_speed > -3)
        wind_speed--;
}

void FireSimulation::increaseWindSpeed()
{
    if (wind_speed < 3)
        wind_speed++;
}

void FireSimulation::increaseFireHeight()
{
    if(cur_fire_intensity + 10 < max_fire_intensity)
    {
        setFireIntensity(cur_fire_intensity + 10);
    }
    else
    {
        setFireIntensity(max_fire_intensity);
    }
}

void FireSimulation::decreaseFireHeight()
{
    if(cur_fire_intensity - 10 > 0)
    {
        setFireIntensity(cur_fire_intensity - 10);
    }
    else
    {
        setFireIntensity(0);
    }
}