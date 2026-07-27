#include <glad/gl.h>
#include "entryPoint.h"
#include "datatypes/datatypes.h"
#include <iostream>
#include <chrono>
#include <GLFW/glfw3.h>
#include "../window/window.h"

namespace AntiMatter {
    Application::Application() {
    }

    Application::~Application() {
    }

    void AntiMatter::Application::Run() {


        if (!WindowManager.InitWindow(640, 480, "AntiMatter")) {
            std::cerr << "Window initialization failed\n";
            return;
        }
        
        Input.WindowForInput = WindowManager.Window;

        glfwSwapInterval(doVsync);

        Audio.initSound();

        OnStart();

        auto lastTime = std::chrono::steady_clock::now();

        while (!WindowManager.WindowShouldClose()) {

            auto currentTime = std::chrono::steady_clock::now();
            std::chrono::duration<float> elapsed = currentTime - lastTime;
            deltaTime = elapsed.count();
            lastTime = currentTime;


            glfwPollEvents();
            Update();
            
            int display_w, display_h;
            glfwGetFramebufferSize(WindowManager.Window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


            OnRender();


            WindowManager.BeginImGuiFrame();
            OnImGuiRender();
            WindowManager.EndImGuiFrame();



            glfwSwapBuffers(WindowManager.Window);


            // Settings
            if (isVsyncOn != doVsync){
                glfwSwapInterval(doVsync);
                isVsyncOn = doVsync;
            }
        }


        BeforeClose();

        WindowManager.WindowCleanUp();
    }
}