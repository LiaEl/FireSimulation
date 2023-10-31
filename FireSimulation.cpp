#include "FireSimulation.h"
#include <string.h>
#include <random>

#define FIRE_ALIGN 4

FireSimulation::FireSimulation(int w, int h)
{
    setFireWidth(w, h);
}

FireSimulation::~FireSimulation()
{
    delete[] color_map;
}

void FireSimulation::resetFire()
{
    size_t len = static_cast<size_t>(vector_len) * sizeof(uchar);
    memset(color_map, 0, len);
}

int FireSimulation::getIdx(int x, int y) const
{
    return x + aligned_w * y;
}

void FireSimulation::setPixelColor(int x, int y, uchar color)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
        color_map[getIdx(x, y)] = color;
}

void FireSimulation::setFireWidth(int w, int h)
{
    width = w;
    height = h;

    if (w % FIRE_ALIGN)
        aligned_w = w + FIRE_ALIGN - (w % FIRE_ALIGN);
    else
        aligned_w = w;

    vector_len = aligned_w * h;
    color_map = new uchar[vector_len];
    wind_speed = 0;

    resetFire();
}
void FireSimulation::resize(int w, int h)
{
    delete color_map;
    setFireWidth(w, h);
    setFireIntensity(cur_fire_intensity);
}

const uchar* FireSimulation::getBrightnessMap()
{
    return color_map;
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
    // in fact, we don't have "intensity" value, but we set the color with what fire start propagating
    cur_fire_intensity = intensity;
    for (int i = 0; i < width; i++)
    {
        color_map[getIdx(i, height - 1)] = cur_fire_intensity;
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

    for (int y = 0; y < (height - 1); y++)
    {
        for (int x = 0; x < width; x++)
        {
            auto decay = myRandomEngine() % 3;
            int new_value = color_map[getIdx(x, y + 1)] - (decay > 1 ? 1 : 0);
            if (new_value < 0)
                new_value = 0;

            int new_x = x + (myRandomEngine() % 3 - 1);

            if (myRandomEngine() % 3)
            {
                new_x += wind_speed;
            }

            setPixelColor(new_x, y, static_cast<uchar>(new_value));
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