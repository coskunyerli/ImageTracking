#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>
#include <ctype.h>

using namespace cv;
using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "error " << endl;
        return -1;
    }
    int windowSize = 25;
    cv::Rect2i rect(100, 100, windowSize, windowSize);
    Mat im1Char = imread(argv[1], 0), im2Char = imread(argv[1], 0);
    Mat im1, im2, Ix_m, Iy_m, It_m;
    im1Char.convertTo(im1, CV_32F);
    im2Char.convertTo(im2, CV_32F);
    im1 = im1 / 255.0;
    im2 = im2 / 255.0;

    Mat Ix_kernel = (Mat_<float>(2, 2) << -1, 1, -1, 1);
    Mat Iy_kernel = (Mat_<float>(2, 2) << -1, -1, 1, 1);
    filter2D(im1, Ix_m, -1, Ix_kernel);
    filter2D(im1, Iy_m, -1, Iy_kernel);
    It_m = im1 - im2;
    Mat Ix = Ix_m(rect), Iy = Iy_m(rect), It = -It_m(rect);
    Mat Ix_r, Iy_r, It_r;
    cv::resize(Ix, Ix_r, Size(Ix.cols * Ix.rows, 1));
    cv::resize(Iy, Iy_r, Size(Iy.cols * Iy.rows, 1));
    cv::resize(It, It_r, Size(It.cols * It.rows, 1));
    Mat A, A_pinv;

    cv::vconcat(Ix_r, Iy_r, A);
    invert(A, A_pinv, DECOMP_SVD);

    cout << A_pinv.size() << "  " << It_r.size() << endl;
    Mat vecs = It_r * A_pinv;
    cout << vecs << endl;
    //imshow("vvvvv", im1);
    //imshow("vvvvvcc", Iy_m);
    //waitKey();
    return 0;
}