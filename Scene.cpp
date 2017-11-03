//
// Created by coskun  yerli on 02/11/17.
//
/*
 * For nor not used camera and light object
 */

#include "Scene.h"

Scene::Scene(uint width, uint height) : isStartTracking(false),
                                        cap(0),
                                        sceneShader("./res/shader/vertexShader.glsl", "res/shader/fragmentShader.glsl"),
                                        rectShader("./res/shader/rectangle.vs.glsl", "res/shader/rectangle.fs.glsl"),
                                        rect({0.0f, 0.0f, 0.0f}), screenHeight(height), screenWidth(width),
                                        camera(screenWidth, screenHeight, {0.0f, 0.0f, 0.0f}) {
    if (sceneShader.hasError()) {
        std::cout << "Error occured compile scene shader" << std::endl;
    }
    if (rectShader.hasError()) {
        std::cout << "Error occured compile rectangle shader" << std::endl;
    }
    camera.setLookAt(glm::vec3(0.0f, 0.0f, 0.0f));
}

bool Scene::draw() {
    sceneShader.setInt("imageTexture", 0);
    //sceneShader.setVec3("lightPos", lightPos);
    //sceneShader.setVec3("viewPos", camera.Position);
    //glm::mat4 projection = camera.getProjection();
    //glm::mat4 view = camera.GetViewMatrix();
    //sceneShader.setMat4("projection", projection);
    // camera/view transformation
    //sceneShader.setMat4("view", view);
    //rectShader.setMat4("projection", projection);
    //rectShader.setMat4("view", view);

    //Render ----
    rect.draw(rectShader, camera);
    //Tracking---
    if (this->isStartTracking) {

        cv::Mat frame, gray;
        this->cap >> frame;
        if (frame.rows == 0 || frame.cols == 0) {
            std::cout << "Frame height or width is zero" << std::endl;
            return false;
        }


        cv::Rect2d newRect;
        cvtColor(frame, gray, CV_RGB2GRAY);
        try {
            tracker->update(frame, newRect);
        } catch (cv::Exception e) {
            cv::error(e);
        }

        this->rect.setModel(newRect, this->screenWidth, this->screenHeight);
        this->model.setTexture(gray.ptr(), gray.cols, gray.rows);
    }

    this->model.draw(sceneShader, camera);
    return true;
}

void Scene::setModel(Model &model) {
    this->model = model;
    cv::Mat gray;
    cap >> firstFrame;
    cap >> firstFrame;
    cap >> firstFrame;
    cvtColor(firstFrame, gray, CV_RGB2GRAY);
    model.setTexture(gray.ptr(), gray.cols, gray.rows);
}

void Scene::setCameraPosition(glm::vec3 position) {
    this->camera.setPosition(position);
}

void Scene::startTracking() {
    if (!this->isStartTracking) {
        tracker->init(firstFrame, this->opencvRect);
        this->isStartTracking = true;
    }

}

void Scene::setRect(cv::Rect2d &rect) {
    if (!this->isStartTracking) {
        this->opencvRect = rect;
        this->rect.setModel(rect, this->screenWidth, this->screenHeight);
    }
}

void Scene::setTracker(cv::Ptr<cv::Tracker> tracker) {
    if (!this->isStartTracking) {
        this->tracker = tracker;
    }
}

void Scene::stopTracking() {
    if (this->isStartTracking) {
        this->isStartTracking = false;
        this->tracker->clear();
    }

}
