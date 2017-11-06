//
// Created by coskun  yerli on 03/11/17.
//

#ifndef TRACKER_TRACKER_H
#define TRACKER_TRACKER_H


#include <opencv2/opencv.hpp>

class Tracker {
public:

    bool init(cv::Mat &frame, cv::Rect2d &rect);

    bool update(cv::Mat &frame, cv::Rect2d &rect);

    cv::Mat calculate(cv::Mat &Ix, cv::Mat &Iy, cv::Mat &It);

    bool isInitialize();

private:
    bool isInit = false;
    cv::Mat lastFrame;
    cv::Rect2d lastRect;
};


#endif //TRACKER_TRACKER_H
