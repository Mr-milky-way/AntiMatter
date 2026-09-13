#include <glad/gl.h>
#include "entryPoint.h"
#include "datatypes/datatypes.h"
#include <iostream>
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
        
        while (!WindowManager.WindowShouldClose()) {

            Time.Update();


            glfwPollEvents();
            Update();
            
            Renderer.Render(WindowManager.Window);
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