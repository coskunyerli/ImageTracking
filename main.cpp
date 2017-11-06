//
// Created by coskun  yerli on 29/10/17.
//
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "Model.h"
#include "Scene.h"
#include <array>
#include <string>
#include <iostream>

void click_callback(GLFWwindow *window, int button, int action, int mods);

void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;
//const std::array<std::string, 4> TRACKINGNAMES = {"MIL", "BOOSTING", "KCF", "TLD"};


Scene *scene;
//char *trackingName;

int main(int argc, char *argv[]) {
    /*
    if (argc != 2) {

        std::cout << "Wrong Usage" << std::endl;
        std::cout << "Example " << std::endl;
        std::cout << "./Visualization MIL" << std::endl;
        std::cout << "Tracking Types < 'MIL' 'BOOSTING' 'KCF' 'TLD' >" << std::endl;
        return -1;
    }


    trackingName = argv[1];
    if (std::find(TRACKINGNAMES.begin(), TRACKINGNAMES.end(), trackingName) == TRACKINGNAMES.end()) {
        std::cout << "Tracking method is not valid" << std::endl;
        return -1;
    }
     */
    // set core profile
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Visualization", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, click_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    // init tracker
    // init scene
    Scene s(SCR_WIDTH, SCR_HEIGHT);
    scene = &s;
    //init model
    Model model(glm::vec3(0.0f, 0.0f, 0.0f));
    // set model to scene
    scene->setModel(model);
    Tracker tracker;

    // render loop
    std::cout << "Select a region and PRESS Enter to start tracking ans PRESS SPACE to stop tracking" << std::endl;
    std::cout << "It is better to choice rectangle as a square" << std::endl;
    while (!glfwWindowShouldClose(window)) {
        // event input
        // -----
        processInput(window);

        // render
        // ------
        //Set shader parameter
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //scene track
        if (!scene->draw()) {
            std::cout << "Error occured while tracking" << std::endl;
            return -1;
        }

        //Swap the buffer
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    } else if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
        scene->startTracking();
    } else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        scene->stopTracking();
    }

}

//get x ,y pos after click and release button
// ----------------------------------------------------------------------
void click_callback(GLFWwindow *window, int button, int action, int mods) {
    static double xPos, yPos;
    static Tracker tracker;
    double xReleasePos, yReleasePos;
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        glfwGetCursorPos(window, &xPos, &yPos);
    } else if (action == GLFW_RELEASE) {
        glfwGetCursorPos(window, &xReleasePos, &yReleasePos);
        cv::Rect2d rect(cv::Point2d((int) xPos, (int) yPos), cv::Point2d((int) xReleasePos, (int) yReleasePos));
        scene->setTracker(rect);
    }
}