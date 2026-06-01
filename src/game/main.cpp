#include "../engine/app.h"
#include <iostream>

class Sim : public AntiMatter::Application {
public:
    void OnStart() override {
        std::cout << "Game Starting" << std::endl;
    }

    void Update() override {
        std::cout << 1/deltaTime << std::endl;
    }

    void OnRender() override {
        
    }
};

int main() {
    Sim game;
    game.Run();
    return 0;
}