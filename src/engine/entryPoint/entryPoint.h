#include <GLFW/glfw3.h>
#include "input/input.h"
#include "filesystem/filesystem.h"
#include "audio/audio.h"
#include "debug/Debug.h"
#include "window/window.h"
#include "renderer/renderer.h"
#include "time/time.h"

#pragma once

namespace AntiMatter {
    class Application {
    public:
        Application();
        virtual ~Application();
        debug Debug;
        EngineTimer Time;
        input Input;
        filesystem Filesystem;
        audio Audio;
        window WindowManager;
        renderer Renderer;
        
        void Run();


        virtual void OnStart() {}
        virtual void Update() {}
        virtual void OnRender() {}
        virtual void OnImGuiRender() {}


        virtual void BeforeClose() {}

    protected:
        bool doVsync = true;
        bool isVsyncOn = true;
    };
}