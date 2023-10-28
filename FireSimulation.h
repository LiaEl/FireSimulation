
#ifndef FIRESIMULATION_FIRESIMULATION_H
#define FIRESIMULATION_FIRESIMULATION_H

#pragma once
#include <opencv2/opencv.hpp>

class FireSimulation {

public:
    FireSimulation(int width, int height);

    /**
     *
     */
    void update();

    /**
     *
     * @return
     */
    cv::Mat getFireFrame();

private:
    cv::Mat fireFrame;
    int width{};
    int height{};
};

#endif //FIRESIMULATION_FIRESIMULATION_H
