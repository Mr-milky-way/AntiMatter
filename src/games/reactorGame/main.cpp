#include <engine.h>
#include <iostream>
#include <imgui.h>
#include "reactor/reactor.h"
#include <thread>


ImVec4 clear_color = ImVec4(0.0f, 0.1f, 0.40f, 1.00f);

class Sim : public AntiMatter::Application {
public:
    std::vector<char> song;
    Sound songSound;
    Reactor reactor;

    void OnStart() override {
        Debug.Log(TextColor::green + "OnStart() -> Reactor system init" + TextColor::reset);
        reactor.initGrid(100,100,100);
        reactor.Start();

        Filesystem.MountFilePack("common");
        song = Filesystem.GetFileBuffer("ALL MY FELLAS FRIZKY.wav");
        Audio.CreateSound(
            reinterpret_cast<unsigned char*>(song.data()), 
            song.size(),
            &songSound
        );
    }

    void Update() override {
        if (Input.GetKeyDown(GLFW_KEY_W)) {
            Debug.Log(Input.GetKeyName(GLFW_KEY_W));
            Audio.PlaySound(songSound);
        }
        if (Input.GetKeyDown(GLFW_KEY_S)) {
            Debug.Log(Input.GetKeyName(GLFW_KEY_S));
            Audio.StopSound(songSound);
        }
    }

    void OnRender() override {
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    }

    void OnImGuiRender() override {
        {
            ImGui::Begin("Hello, user!");
            ImGui::Text("Application Stats %.3f ms/frame (%.1f FPS)", (float)deltaTime * 1000, 1/deltaTime);
            ImGui::Checkbox("Vsync on?", &doVsync);
            ImGui::ColorEdit3("Background Color", (float*)&clear_color);
            ImGui::End();
        }
    }

    void BeforeClose() override {
        reactor.Stop();
    }

};

int main() {
    Sim game;
    game.Run();
    return 0;
}