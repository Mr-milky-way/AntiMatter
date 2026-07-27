#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


glm::mat4 camera::GetViewPerspective() {
    float aspectRatio = (float)WindowManager.width / (float)WindowManager.height;
    return glm::perspective(glm::radians(FOV), aspectRatio, near, far);
}

glm::mat4 camera::GetViewMatrix() {
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void camera::updateVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);

    glm::vec3 worldUp{0.0f, 1.0f, 0.0f};

    glm::mat4 rollMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(roll), cameraFront);

    glm::vec3 rolledWorldUp = glm::vec3(rollMatrix * glm::vec4(worldUp, 0.0f));

    glm::vec3 right = glm::normalize(glm::cross(cameraFront, rolledWorldUp));
    cameraUp = glm::normalize(glm::cross(right, cameraFront));
}

void camera::SetCameraRotation(float x, float y, float z) {
    pitch = x;
    yaw = y;
    roll = z;
    updateVectors();
}


void camera::RotateCamera(float x, float y, float z) {
    pitch += x;
    yaw += y;
    roll += z;
    updateVectors();
}


void camera::SetCameraPostition(float x, float y, float z) {
    cameraPos = glm::vec3{x,y,z};
}

void camera::MoveCamera(float x, float y, float z) {
    glm::vec3 worldUp{0.0f, 1.0f, 0.0f};
    glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));

    cameraPos += cameraRight * x;
    cameraPos += cameraUp * y;
    cameraPos += cameraFront * z;
}