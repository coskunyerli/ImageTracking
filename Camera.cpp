//
// Created by coskun  yerli on 29/10/17.
//

#include "Camera.h"

Camera::Camera(unsigned int screenWidth, unsigned int screenHeight, glm::vec3 position, glm::vec3 up, float yaw,
               float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
                              firstPosition(position),
                              MovementSpeed(SPEED),
                              MouseSensitivity(SENSITIVTY), Zoom(ZOOM),
                              screenHeight(screenHeight),
                              screenWidth(screenWidth) {
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

// Constructor with scalar values
Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(
        glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM) {
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(Position, lookAt - Position, Up);
}

void Camera::reset() {
    Position = firstPosition;
    Up = glm::vec3(0.0f, 1.0f, 0.0f);
    Yaw = YAW;
    Pitch = PITCH;
    Zoom = ZOOM;
    updateCameraVectors();
}

// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = MovementSpeed * deltaTime;
    if (direction == UP)
        Position += Up * velocity;
    if (direction == DOWN)
        Position -= Up * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
    if (direction == FORWARD)
        Position += Front * velocity;
    if (direction == BACKWARD)
        Position -= Front * velocity;
    updateCameraVectors();
}


// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch) {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // Update Front, Right and Up Vectors using the updated Eular angles
    updateCameraVectors();
}

// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::ProcessMouseScroll(float yoffset) {
    if (Zoom >= 1.0f && Zoom <= 45.0f)
        Zoom -= yoffset;
    if (Zoom <= 1.0f)
        Zoom = 1.0f;
    if (Zoom >= 45.0f)
        Zoom = 45.0f;
}

void Camera::updateCameraVectors() {
    // Calculate the new Front vector
    //glm::vec3 front;
    //front.x = static_cast<float>(cos(glm::radians(Yaw)) * cos(glm::radians(Pitch)));
    //front.y = static_cast<float>(sin(glm::radians(Pitch)));
    //front.z = static_cast<float>(sin(glm::radians(Yaw)) * cos(glm::radians(Pitch)));
    Front = lookAt - Position;
    Right = glm::normalize(glm::cross(Front,
                                      WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up = glm::normalize(glm::cross(Right, Front));
}

glm::mat4 Camera::getProjection() {
    return glm::perspective(glm::radians(90.0f), (float) this->screenWidth / (float) this->screenHeight, 0.1f,
                            100.0f);
}

void Camera::ProcessRotateObject(Camera_Movement direction, float deltaTime) {

}

void Camera::setLookAt(glm::vec3 lookAt) {
    this->lookAt = lookAt;
}

void Camera::setPosition(glm::vec3 position) {
    this->Position = position;
}

