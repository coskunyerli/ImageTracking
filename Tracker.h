//
// Created by coskun  yerli on 03/11/17.
//

#ifndef TRACKER_TRACKER_H
#define TRACKER_TRACKER_H


#include <opencv2/core/mat.hpp>

class Tracker {

    void init(cv::Mat &frame, cv::Rect2d rect);

    bool update(cv::Mat &frame, cv::Rect2d &rect);
};


#endif //TRACKER_TRACKER_H
