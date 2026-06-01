#include <glad/glad.h>
#include "entryPoint.h"
#include "datatypes/datatypes.h"
#include <iostream>
#include <chrono>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

namespace AntiMatter {
    Application::Application() {
    }

    Application::~Application() {
    }

    void AntiMatter::Application::Run() {

        //GLFW init
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return;
        }
    
        Window = glfwCreateWindow(640, 480, "AntiMatter", NULL, NULL);
        if (!Window) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }
        Input.WindowForInput = Window;
        glfwMakeContextCurrent(Window);
        


        //GLAD init
        if (!gladLoadGL()) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return;
        }
        glViewport(0, 0, 640, 480);


        glfwSwapInterval(doVsync);

        Audio.initSound();

        OnStart();

        //setup ImGUI
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(Window, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        auto lastTime = std::chrono::steady_clock::now();

        while (!glfwWindowShouldClose(Window)) {
            auto currentTime = std::chrono::steady_clock::now();
            std::chrono::duration<float> elapsed = currentTime - lastTime;
            deltaTime = elapsed.count();
            lastTime = currentTime;

            Update();
            glfwPollEvents();
            
            int display_w, display_h;
            glfwGetFramebufferSize(Window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            OnRender(); // for OpenGL



            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            OnImGuiRender(); //ImGui Logic
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());



            glfwSwapBuffers(Window);


            //Settings
            if (isVsyncOn != doVsync){
                glfwSwapInterval(doVsync);
                isVsyncOn = doVsync;
            }
        }


        BeforeClose();
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwTerminate();
    }
}