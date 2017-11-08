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
    cv::Mat im1;
    cv::Mat im2 = this->lastFrame;
    frame.convertTo(im1, CV_64F);
    im1 = im1 / 255.0;
    for (int i = 0; i <= 0; i++) {
        cv::Mat vecs = this->calculate(im1, im2);
        //std::cout << vecs << std::endl;
        cv::Mat similarity = (cv::Mat_<double>(2, 3) << 1.0 + vecs.at<double>(0, 0), -vecs.at<double>(0, 1),
                vecs.at<double>(0, 2), vecs.at<double>(0, 1), 1.0 + vecs.at<double>(0, 0), vecs.at<double>(0, 3));
        //cv::Mat similarity = (cv::Mat_<double>(2, 3) << 1.0, 0.0,
//                vecs.at<double>(0, 0), 0.0, 1.0, vecs.at<double>(0, 1));

        cv::Mat newXY = similarity * (cv::Mat_<double>(3, 1) << this->lastRect.x, this->lastRect.y, 1.0);
        cv::Rect2d newRect(newXY.at<double>(0, 0), newXY.at<double>(0, 1), this->lastRect.width, this->lastRect.height);
        if (!isOutScreen(newRect, this->lastFrame.size())) {
            this->lastRect = newRect;
        }

    }
    this->lastFrame = im1;
    rect = this->lastRect;
    return false;
}

cv::Mat Tracker::calculate(cv::Mat &im1, cv::Mat &im2) {
    cv::Mat Ix, Iy, It;
    cv::Mat It_m1, It_m2;
    cv::Mat Ix_r, Iy_r, It_r;
    cv::Mat Ixx_r, Iyy_r, Ixy_r, Iyx_r;

    // This is derivative of Ix Iy and It
    cv::Mat Ix_kernel = (cv::Mat_<double>(2, 2) << -1, 1, -1, 1);
    cv::Mat Iy_kernel = (cv::Mat_<double>(2, 2) << -1, -1, 1, 1);
    cv::Mat It_kernel = (cv::Mat_<double>(2, 2) << 1, 1, 1, 1);
    cv::Mat r_im1 = im1(this->lastRect), r_im2 = im2(this->lastRect);
    cv::filter2D(r_im2, Ix, -1, Ix_kernel); // dI/dx
    cv::filter2D(r_im2, Iy, -1, Iy_kernel); // dI/dy
    cv::filter2D(r_im1, It_m1, -1, It_kernel);
    cv::filter2D(r_im2, It_m2, -1, It_kernel);
    It = It_m2 - It_m1; // dI/dt
    //-----------
    // This is Ix*x Iy*y Ix*y and Iy*x

    cv::Mat Ixx = cv::Mat::zeros(this->lastRect.size(), CV_64F);
    cv::Mat Iyy = cv::Mat::zeros(this->lastRect.size(), CV_64F);
    cv::Mat Ixy = cv::Mat::zeros(this->lastRect.size(), CV_64F);
    cv::Mat Iyx = cv::Mat::zeros(this->lastRect.size(), CV_64F);
    //
    for (double y = this->lastRect.y; y < Ixx.rows; y++) {
        int row = 0;
        for (double x = this->lastRect.x; x < Ixx.cols; x++) {
            int col = 0;
            Ixx.at<double>(row, col) = Ix.at<double>(row, col) * x;
            Iyy.at<double>(row, col) = Iy.at<double>(row, col) * y;
            Ixy.at<double>(row, col) = Ix.at<double>(row, col) * y;
            Iyx.at<double>(row, col) = Iy.at<double>(row, col) * x;
            col++;
        }
        row++;
    }


    cv::Size s = cv::Size(Ix.cols * Ix.rows, 1);
    cv::resize(Ixx, Ixx_r, s);
    cv::resize(Iyy, Iyy_r, s);
    cv::resize(Ixy, Ixy_r, s);
    cv::resize(Iyx, Iyx_r, s);
    cv::resize(Ix, Ix_r, s);
    cv::resize(Iy, Iy_r, s);
    cv::resize(It, It_r, s);
    cv::Mat A, B, A_pinv;
    cv::vconcat(std::vector<cv::Mat>{Ixx_r + Iyy_r, Ixy_r - Iyx_r, Ix_r, Iy_r}, A);

    cv::invert(A, A_pinv, cv::DECOMP_SVD);
    cv::Mat vecs = It_r * A_pinv;
    return vecs;
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
