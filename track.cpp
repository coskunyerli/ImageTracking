//
// Created by coskun  yerli on 03/11/17.
//


#include "Tracker.h"

bool isOutScreen(cv::Rect2d &rect, cv::Size size);

bool Tracker::init(cv::Mat &frame, cv::Rect2d &rect) {
    if (rect.area() > 0.0) {
        if (isOutScreen(rect, frame.size())) {
            std::cout << "Rectangle is out of screen! Please choose another" << std::endl;
            return false;
        } else {
            frame.convertTo(this->lastFrame, CV_64F);
            this->lastFrame = this->lastFrame / 255.0;
            this->lastRect = rect;
            this->isInit = true;
        }

    } else {
        std::cout << "Area of rectangle is zero" << std::endl;
        return false;
    }
    return true;

}

bool Tracker::update(cv::Mat &frame, CV_OUT cv::Rect2d &rect) {
    cv::Mat im1, Ix_m, Iy_m, It_m, It_m1, It_m2;
    cv::Mat im2 = this->lastFrame;
    frame.convertTo(im1, CV_64F);
    im1 = im1 / 255.0;
    cv::Mat Ix_kernel = (cv::Mat_<double>(2, 2) << -1, 1, -1, 1);
    cv::Mat Iy_kernel = (cv::Mat_<double>(2, 2) << -1, -1, 1, 1);
    cv::Mat It_kernel = (cv::Mat_<double>(2, 2) << 1, 1, 1, 1);
    cv::Mat r_im1 = im1(this->lastRect), r_im2 = im2(this->lastRect);
    cv::filter2D(r_im2, Ix_m, -1, Ix_kernel); // dI/dx
    cv::filter2D(r_im2, Iy_m, -1, Iy_kernel); // dI/dy
    cv::filter2D(r_im1, It_m1, -1, It_kernel);
    cv::filter2D(r_im2, It_m2, -1, It_kernel);
    It_m = It_m2 - It_m1; // dI/dt
    for (int i = 0; i <= 0; i++) {
        cv::Mat vecs = this->calculate(Ix_m, Iy_m, It_m);
        double nvecX = this->lastRect.x + vecs.at<double>(0, 0), nvecY = this->lastRect.y + vecs.at<double>(0, 1);
        cv::Rect2d newRect(nvecX, nvecY, this->lastRect.width, this->lastRect.height);
        if (!isOutScreen(newRect, this->lastFrame.size())) {
            this->lastRect = newRect;
        }


    }
    this->lastFrame = im1;
    rect = this->lastRect;
    return false;
}

cv::Mat Tracker::calculate(cv::Mat &Ix, cv::Mat &Iy, cv::Mat &It) {
    cv::Mat Ix_r, Iy_r, It_r;
    cv::resize(Ix, Ix_r, cv::Size(Ix.cols * Ix.rows, 1));
    cv::resize(Iy, Iy_r, cv::Size(Iy.cols * Iy.rows, 1));
    cv::resize(It, It_r, cv::Size(It.cols * It.rows, 1));
    cv::Mat A, A_pinv;
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
