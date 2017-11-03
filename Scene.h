//
// Created by coskun  yerli on 02/11/17.
//

#ifndef TRACKER_SCENE_H
#define TRACKER_SCENE_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "Model.h"
#include "Rectangle.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/tracking.hpp>
#include <vector>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_access.hpp>

class Scene {
public:
    Scene(uint width, uint height);
    bool draw();
    void setModel(Model &model);
    void setCameraPosition(glm::vec3 position);
    void setRect(cv::Rect2d &rect);
    void setTracker(cv::Ptr<cv::Tracker> tracker);
    void startTracking();
    void stopTracking();

private:
    uint screenWidth, screenHeight;
    bool isStartTracking;
    cv::VideoCapture cap;
    Rectangle rect;
    cv::Rect2d opencvRect;
    cv::Mat firstFrame;
    cv::Ptr<cv::Tracker> tracker;
    Shader sceneShader;
    Shader rectShader;
    Model model;
    Camera camera;
    //glm::vec3 lightPos;

};


#endif //TRACKER_SCENE_H
