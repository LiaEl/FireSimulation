#include <opencv2/opencv.hpp>
#include "FireSimulation.h"

FireSimulation::FireSimulation(int width, int height): width(width), height(height)
{
        fireFrame = cv::Mat(height, width, CV_8UC3, cv::Scalar(0, 0, 0));
}

void FireSimulation::update()
{
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int intensity = 255 - (y * 255 / height);
            cv::Vec3b &pixel = fireFrame.at<cv::Vec3b>(y, x);
            pixel[0] = 0;
            pixel[1] = intensity;
            pixel[2] = intensity;

            if (rand() % 100 < 5) {
                int flicker = rand() % 100;
                pixel[1] += flicker;
                pixel[2] += flicker;
            }
        }
    }
}

cv::Mat FireSimulation::getFireFrame()
{
    return fireFrame;
}