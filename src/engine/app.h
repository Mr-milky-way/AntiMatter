#pragma once

namespace AntiMatter {
    class Application {
    public:
        Application();
        virtual ~Application();

        void Run();
        float deltaTime;

        virtual void OnStart() {}
        virtual void Update() {}
        virtual void OnRender() {}
    };
}