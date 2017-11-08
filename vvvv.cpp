//
// Created by coskun  yerli on 03/11/17.
//


#include "Tracker.h"

bool isOutScreen(cv::Rect2d &rect, cv::Size size);

void Tracker::init(cv::Mat &frame, cv::Rect2d rect) {
    frame.convertTo(this->lastFrame, CV_32F);
    this->lastFrame = this->lastFrame / 255.0;
    this->lastRect = rect;
    this->isInit = true;

}

bool Tracker::update(cv::Mat &frame, CV_OUT cv::Rect2d &rect) {
    cv::Mat im1, im2, Ix_m, Iy_m, It_m;
    frame.convertTo(im1, CV_32F);
    im1 = im1 / 255.0;
    cv::Mat Ix_kernel = (cv::Mat_<float>(2, 2) << -1, 1, -1, 1);
    cv::Mat Iy_kernel = (cv::Mat_<float>(2, 2) << -1, -1, 1, 1);
    cv::filter2D(im1, Ix_m, -1, Ix_kernel);
    cv::filter2D(im1, Iy_m, -1, Iy_kernel);
    It_m = im1 - im2;
    for (int i = 0; i <= 30; i++) {
        cv::Mat Ix = Ix_m(this->lastRect), Iy = Iy_m(this->lastRect), It = -It_m(this->lastRect);
        cv::Mat vecs = this->calculate(Ix, Iy, It);
        this->lastFrame = im1;
        //cv::Mat similarity = (cv::Mat_<float>(2, 3) << vecs.at<float>(0, 0), vecs.at<float>(0, 1), vecs.at<float>(0, 2),
        //        -vecs.at<float>(0, 1), vecs.at<float>(0, 0), vecs.at<float>(0, 3));
        //std::cout << similarity << std::endl;
        //cv::Mat newXY = similarity * (cv::Mat_<float>(3, 1) << this->lastRect.x, this->lastRect.y, 1.0f);
        float nvecX = this->lastRect.x + vecs.at<float>(0, 0), nvecY = this->lastRect.y + vecs.at<float>(1, 0);
        cv::Rect2d newRect(nvecX, nvecY, this->lastRect.width, this->lastRect.height);
        if (!isOutScreen(newRect, this->lastFrame.size())) {
            this->lastRect = newRect;
        }
        rect = this->lastRect;


    }
    return false;
}

cv::Mat Tracker::calculate(cv::Mat &Ix, cv::Mat &Iy, cv::Mat &It) {
    /*
    cv::Mat Ixx = cv::Mat::zeros(this->lastRect.size(), CV_32F);
    cv::Mat Iyy = cv::Mat::zeros(this->lastRect.size(), CV_32F);
    cv::Mat Ixy = cv::Mat::zeros(this->lastRect.size(), CV_32F);
    cv::Mat Iyx = cv::Mat::zeros(this->lastRect.size(), CV_32F);
    for (int y = (int) this->lastRect.y; y < this->lastRect.br().y; y++) {
        for (int x = (int) this->lastRect.x; x < this->lastRect.br().x; x++) {
            Ixx.at<float>(x, y) = Ix_m.at<float>(x, y) * x;
            Iyy.at<float>(x, y) = Iy_m.at<float>(x, y) * y;
            Ixy.at<float>(x, y) = Ix_m.at<float>(x, y) * y;
            Iyx.at<float>(x, y) = Iy_m.at<float>(x, y) * -x;
        }
    }


    cv::Mat Ix_r, Iy_r, It_r, Ixx_r, Iyy_r, Ixy_r, Iyx_r;

    cv::resize(Ixx, Ixx_r, cv::Size(Ixx.cols * Ixx.rows, 1));
    cv::resize(Iyy, Iyy_r, cv::Size(Iyy.cols * Iyy.rows, 1));
    cv::resize(Ixy, Ixy_r, cv::Size(Ixy.cols * Ixy.rows, 1));
    cv::resize(Iyx, Iyx_r, cv::Size(Iyx.cols * Iyx.rows, 1));
     */
    cv::Mat Ix_r, Iy_r, It_r;
    //cv::Mat Ix = Ix_m(this->lastRect), Iy = Iy_m(this->lastRect), It = -It_m(this->lastRect);
    cv::resize(Ix, Ix_r, cv::Size(Ix.cols * Ix.rows, 1));
    cv::resize(Iy, Iy_r, cv::Size(Iy.cols * Iy.rows, 1));
    cv::resize(It, It_r, cv::Size(It.cols * It.rows, 1));
    cv::Mat A, A_pinv;
    //cv::vconcat(Ixx_r + Iyy_r, Ixy_r + Iyx_r, A);
    //cv::vconcat(A, Ix_r, A);
    //cv::vconcat(A, Iy_r, A);
    cv::vconcat(Ix_r, Iy_r, A);
    cv::invert(A, A_pinv, cv::DECOMP_SVD);

    cv::Mat vecs = It_r * A_pinv;
    return vecs;
    //outVec = vecs;
}

bool Tracker::isInitialize() {
    return this->isInit;
}

bool isOutScreen(cv::Rect2d &rect, cv::Size size) {
    if (rect.x < 0.0 || rect.y < 0.0 || rect.br().x < 0.0 || rect.br().y < 0.0)
        return true;
    else if (rect.x > size.width || rect.y > size.height || rect.br().x > size.width || rect.br().y > size.height)
        return true;
    return false;
}
