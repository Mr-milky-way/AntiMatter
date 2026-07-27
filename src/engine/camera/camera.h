#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "window/window.h"
#pragma once

class camera {
private:

    window WindowManager;
    glm::vec3 cameraPos{0.0f, 0.0f, 0.0f};
    glm::vec3 cameraFront{0.0f, 0.0f, -1.0f}; 
    glm::vec3 cameraUp{0.0f, 1.0f, 0.0f};

    float yaw = -90;
    float pitch = 0;
    float roll = 0;

    void updateVectors();
public:


    float FOV = 70;
    float near = 0.1;
    float far = 100;

    
    void SetCameraRotation(float x, float y, float z);
    void RotateCamera(float x, float y, float z);

    void SetCameraPostition(float x, float y, float z);
    void MoveCamera(float x, float y, float z);

    glm::mat4 GetViewMatrix();

    glm::mat4 GetViewPerspective();
};