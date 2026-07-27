#include <string>
#include <GLFW/glfw3.h>

#pragma once



class window {
public:
    uint32_t width = 640;
    uint32_t height = 480;

    void ChangeWindowName(std::string name);

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};  