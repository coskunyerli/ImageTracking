//
// Created by coskun  yerli on 29/10/17.
//

#include "Rectangle.h"

Rectangle::Rectangle(glm::vec3 position) : position(position) {
    model = glm::translate(model, this->position);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 3 * sizeof(double), (void *) 0);
    glEnableVertexAttribArray(0);
    // normal coord attribute
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Rectangle::draw(Shader &shader, Camera &camera) {


    // pass projection matrix to shader (note that in this case it could change every frame)

    // render boxes
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // calculate the model matrix for each object and pass it to shader before drawing
    shader.use();
    shader.setMat4("model", model);


    glDrawArrays(GL_LINES, 0, sizeof(this->vertices) / sizeof(double));
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

void Rectangle::remove() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}


void Rectangle::setModel(glm::mat4 model) {
    this->model = model;
}

void Rectangle::setModel(cv::Rect2d &rect, int SWidth, int SHeight) {
    double xc = (rect.x + rect.br().x) / 2, yc = (rect.y + rect.br().y) / 2;
    double d_sx = rect.width / SWidth; //scale ratio in x
    double d_sy = rect.height / SHeight; // scale ratio in y

    int x = SWidth / 2, y = SHeight / 2;
    double d_tx =(xc - x) / SWidth, d_ty = (y - yc) / SHeight;

    glm::mat4 model;
    model = glm::translate(model, {2 * d_tx, 2 * d_ty, 0.0f});
    model = glm::scale(model, {d_sx, d_sy, 1.0f});
    this->setModel(model);

// cv::Rect rect(Point(xPos, yPos), Point(xReleasePos, yReleasePos));
}
