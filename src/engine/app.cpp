#include "app.h"
#include "datatypes/datatypes.h"
#include <iostream>
#include <chrono>
#include <GLFW/glfw3.h>

namespace AntiMatter {
    Application::Application() {
    }

    Application::~Application() {
    }

    void AntiMatter::Application::Run() {

        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            
        }
    
        GLFWwindow* window = glfwCreateWindow(640, 480, "AntiMatter", NULL, NULL);
        if (!window) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            
        }
        glfwMakeContextCurrent(window);
        
        glfwSwapInterval(0); 
        OnStart();

        auto lastTime = std::chrono::steady_clock::now();

        while (!glfwWindowShouldClose(window)) {
            auto currentTime = std::chrono::steady_clock::now();
            std::chrono::duration<float> elapsed = currentTime - lastTime;
            deltaTime = elapsed.count();
            lastTime = currentTime;

            Update();
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
        
            glfwSwapBuffers(window);
        
            glfwPollEvents();
        }
    
        glfwTerminate();
    }
}