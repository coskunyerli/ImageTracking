#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "Model.h"
#include "Rectangle.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/tracking.hpp>

#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_access.hpp>

#include <iostream>

//TODO draw circle and get image
//TODO run tdl tracker
//TODO Implement own tracker

using namespace cv;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

void click_callback(GLFWwindow *window, int button, int action, int mods);

void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

// camera
Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 0.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// lighting

glm::vec3 lightPos(camera.Position);

bool startTracking = false;
VideoCapture cap(0);
Rectangle *rectPtr;
Mat firstFrame;
Ptr<Tracker> tracker;


int main() {
    // open the default camera
    // glfw: initialize and configure
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
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Visualization", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, click_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("res/shader/vertexShader.glsl", "res/shader/fragmentShader.glsl");
    if (ourShader.hasError()) {
        std::cout << "Error occured compile shader" << std::endl;
        return -1;
    }
    Shader shader("res/shader/rectangle.vs.glsl", "res/shader/rectangle.fs.glsl");
    if (shader.hasError()) {
        std::cout << "Error occured compile shader" << std::endl;
        return -1;
    }
    Model scene(glm::vec3(0.0f, 0.0f, 0.0f));
    Rectangle rect({0.0f, 0.0f, 0.0f});
    rectPtr = &rect;
    camera.setLookAt(glm::vec3(0.0f, 0.0f, 0.0f));
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------


    // render loop

    // -----------
    //Rectangle rectangle(glm::vec3(0.0f, 0.0f, 1.0f));

    //initialize Tracker
    Mat img;
    cap >> firstFrame;
    cvtColor(firstFrame, img, CV_RGB2GRAY);

    scene.setTexture(img.ptr(), img.cols, img.rows);
    tracker = Tracker::create("MIL");
    std::cout << "Select a region and PRESS Enter to start tracking" << std::endl;
    while (!glfwWindowShouldClose(window)) {

        //imshow("edges", frame);

        // per-frame time logic
        // --------------------
        float currentFrame = (float) glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        //Set shader parameter
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ourShader.setInt("imageTexture", 0);
        ourShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        ourShader.setVec3("lightPos", lightPos);
        ourShader.setVec3("viewPos", camera.Position);
        glm::mat4 projection = camera.getProjection();
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        // camera/view transformation
        ourShader.setMat4("view", view);

        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        {
        }

        //Render ----
        rect.draw(shader, camera);
        //Tracking---
        if (startTracking) {

            Mat frame;
            cap >> frame;
            if (frame.rows == 0 || frame.cols == 0) {
                std::cout << "Frame height or width is zero" << std::endl;
                return -1;
            }

            Rect2d newRect;
            tracker->update(frame, newRect);
            rectPtr->setModel(newRect, SCR_WIDTH, SCR_HEIGHT);
            cvtColor(frame, frame, CV_RGB2GRAY);
            scene.setTexture(frame.ptr(), frame.cols, frame.rows);
        }

        scene.draw(ourShader, camera);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    } else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        camera.ProcessKeyboard(UP, deltaTime);
    } else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        camera.ProcessKeyboard(DOWN, deltaTime);
    } else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    } else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    } else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        camera.reset();
    } else if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
        startTracking = true;
    }

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    //camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll((float) yoffset);
}

void click_callback(GLFWwindow *window, int button, int action, int mods) {
    static double xPos, yPos;
    double xReleasePos, yReleasePos;
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        glfwGetCursorPos(window, &xPos, &yPos);
    } else if (action == GLFW_RELEASE) {
        if (!startTracking) {
            glfwGetCursorPos(window, &xReleasePos, &yReleasePos);

            cv::Rect2d rect(Point2d(xPos, yPos), Point2d(xReleasePos, yReleasePos));
            rectPtr->setModel(rect, SCR_WIDTH, SCR_HEIGHT);
            tracker->init(firstFrame, rect);
        }

    }
}