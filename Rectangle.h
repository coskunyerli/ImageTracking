//
// Created by coskun  yerli on 29/10/17.
//

#ifndef VISUALIZATION_RECTANGLE_H
#define VISUALIZATION_RECTANGLE_H

#include <opencv2/core/types.hpp>
#include "glad/glad.h"
#include "Shader.h"
#include "Camera.h"

class Rectangle {
public:
    Rectangle(glm::vec3 position);

    void draw(Shader &shader, Camera &camera);

    void remove();
    double vertices[24] = {
            1.0001f, -1.0001f, 0.5f,
            -1.0001f, -1.0001f, 0.5f,

            -1.0001f, -1.0001f, 0.5f,
            -1.0001f, 1.0001f, 0.5f,

            -1.0001f, 1.0001f, 0.5f,
            1.0001f, 1.0001f, 0.5f,

            1.0001f, 1.0001f, 0.5f,
            1.0001f, -1.0001f, 0.5f
    };
    void setModel(glm::mat4 model);
    void setModel(cv::Rect2d &rect,int SWidth,int SHeight);


private:
    glm::mat4 model;
    glm::vec3 position;
    unsigned int VBO, VAO;
};


#endif //VISUALIZATION_RECTANGLE_H
