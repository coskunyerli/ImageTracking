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
    cv::Mat frame, gray;
    this->cap >> frame;
    cvtColor(frame, gray, CV_RGB2GRAY);
    if (this->isStartTracking) {


        if (frame.rows == 0 || frame.cols == 0) {
            std::cout << "Frame height or width is zero" << std::endl;
            return false;
        }


        cv::Rect2d newRect;

        try {
            tracker.update(gray, newRect);
        } catch (cv::Exception e) {
            cv::error(e);
        }

        this->rect.setModel(newRect, this->screenWidth, this->screenHeight);

    }
    this->model.setTexture(gray.ptr(), gray.cols, gray.rows);
    this->model.draw(sceneShader, camera);
    return true;
}

void Scene::setModel(Model &model) {
    this->model = model;
}

void Scene::setCameraPosition(glm::vec3 position) {
    this->camera.setPosition(position);
}

void Scene::startTracking() {
    if (!this->isStartTracking) {
        if (this->tracker.isInitialize())
            this->isStartTracking = true;
    }

}

void Scene::setTracker(cv::Rect2d &rect) {
    if (!this->isStartTracking) {
        cv::Mat img, gray;
        cap >> img;
        cv::cvtColor(img, gray, CV_RGB2GRAY);
        this->tracker.init(gray, rect);
        this->rect.setModel(rect, this->screenWidth, this->screenHeight);
    }
}

void Scene::stopTracking() {
    if (this->isStartTracking) {
        this->isStartTracking = false;
        cv::Rect2d r;
        this->rect.setModel(r, this->screenWidth, this->screenHeight);
    }

}
