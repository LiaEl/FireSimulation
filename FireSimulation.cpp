//#include <opencv2/opencv.hpp>
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
    this->width = w;
    this->height = h;

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
    setFireIntensity(this->cur_fire_intensity);
}

const uchar* FireSimulation::getAlignedFireVector()
{
    return this->fire_value;
}

int FireSimulation::getWidth() const
{
    return this->width;
}

int FireSimulation::getHeight() const
{
    return this->height;
}

int FireSimulation::getWindSpeed() const
{
    return this->wind_speed;
}

void FireSimulation::setFireIntensity(int intensity)
{
    this->cur_fire_intensity = intensity;
    for (int i = 0; i < this->width; i++) {
        this->fire_value[this->getIdx(i, this->height-1)] = this->cur_fire_intensity;
    }
}

void FireSimulation::setIntensityMax(int max)
{
    this->max_fire_intensity = max;
}

int FireSimulation::getIntensity() const
{
    return this->cur_fire_intensity;
}

void FireSimulation::spreadFire()
{
    std::random_device myRandomDevice;
    unsigned seed = myRandomDevice();
    std::default_random_engine myRandomEngine(seed);

    for (int j = 0; j < (this->height - 1); j++) {
        for (int i = 0; i < this->width; i++) {
            auto decay = myRandomEngine() % 3;
            int new_value = this->fire_value[this->getIdx(i, j+1)] - (decay > 1 ? 1 : 0);
            if (new_value < 0)
                new_value = 0;

            // change pixel direction
            int new_i = i + (myRandomEngine() % 3 - 1);

            // lateral effect (wind)
            if (this->wind_speed > 0 && myRandomEngine() % 2) {
                new_i += this->wind_speed;
            }
            else if (this->wind_speed < 0 && myRandomEngine() % 2) {
                new_i += this->wind_speed;
            }

            this->setIdx(new_i, j, static_cast<uchar>(new_value));
        }
    }
}

void FireSimulation::decreaseWindSpeed()
{
    if (this->wind_speed > -3)
        this->wind_speed--;
}

void FireSimulation::increaseWindSpeed()
{
    if (this->wind_speed < 3)
        this->wind_speed++;
}

void FireSimulation::increaseFireHeight()
{
    if(this->cur_fire_intensity + 10 < this->max_fire_intensity)
    {
        this->setFireIntensity(this->cur_fire_intensity + 10);
    }
    else
    {
        this->setFireIntensity(this->max_fire_intensity);
    }
}

void FireSimulation::decreaseFireHeight()
{
    if(this->cur_fire_intensity - 10 > 0)
    {
        this->setFireIntensity(this->cur_fire_intensity - 10);
    }
    else
    {
        this->setFireIntensity(0);
    }
}