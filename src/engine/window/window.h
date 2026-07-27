#pragma once
#include <cstdint>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>


class window {
private:
public:
    uint32_t WindowWidth = 640;
    uint32_t WindowHeight = 480;

    GLFWwindow* Window = nullptr;


    void ChangeWindowName(const char* name);

    bool InitWindow(int width, int height, const char* title);

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    void BeginImGuiFrame();
    void EndImGuiFrame();

    void WindowCleanUp();

    bool WindowShouldClose() {  return glfwWindowShouldClose(Window);   }
};  