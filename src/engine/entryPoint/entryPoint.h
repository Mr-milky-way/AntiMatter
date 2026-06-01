#include <GLFW/glfw3.h>
#include "input/input.h"
#include "filesystem/filesystem.h"
#include "audio/audio.h"
#include "debug/Debug.h"

#pragma once

namespace AntiMatter {
    class Application {
    public:
        Application();
        virtual ~Application();
        debug Debug;
        input Input;
        filesystem Filesystem;
        audio Audio;
        void Run();


        virtual void OnStart() {}
        virtual void Update() {}
        virtual void OnRender() {}
        virtual void OnImGuiRender() {}


        virtual void BeforeClose() {}

    protected:
        GLFWwindow* Window = nullptr;

        float deltaTime;

        bool doVsync = true;
        bool isVsyncOn = true;
    };
}