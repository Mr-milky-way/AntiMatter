#include <engine.h>
#include <iostream>
#include <string>
#include <imgui.h>
#include "reactor/reactor.h"
#include <thread>
#include <glm/gtc/type_ptr.hpp>

camera Camera;
ImVec4 clear_color = ImVec4(0.0f, 0.1f, 0.40f, 1.00f);
static vector2Float lastMousePos = {0.0f, 0.0f};
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
        song = Filesystem.GetFileBuffer("DOESNT MATTER (Instrumental).mp3");
        Audio.CreateSound(
            reinterpret_cast<unsigned char*>(song.data()), 
            song.size(),
            &songSound
        );
    }

    void Update() override {
        if (Input.GetKeyDown(GLFW_KEY_W)) {
            Audio.PlaySound(songSound);
            Camera.MoveCamera(0,0, 1* deltaTime);
        }
        if (Input.GetKeyDown(GLFW_KEY_S)) {
            Audio.StopSound(songSound);
            Camera.SetCameraPostition(0,0,5);
            Camera.SetCameraRotation(0,-90,0);
        }
        if (Input.GetMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
            Input.DisableCursor();
            vector2Float currentMousePos = Input.GetCursorPos();

            float deltaX = currentMousePos.x - lastMousePos.x;
            float deltaY = currentMousePos.y - lastMousePos.y;

            lastMousePos = currentMousePos;

            Camera.RotateCamera(-deltaY * 0.2f, deltaX * 0.2f, 0);

            Debug.Log("DeltaY: " + std::to_string(deltaY));
        }
        if (Input.GetKeyDown(GLFW_KEY_ESCAPE)){
            Input.EnableCursor();
        }
        if (Input.GetKeyDown(GLFW_KEY_Q)) {
            Camera.RotateCamera(0,0,50 * deltaTime);
        }
    }

    void OnRender() override {
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glm::mat4 projection = Camera.GetViewPerspective();
        glLoadMatrixf(glm::value_ptr(projection));

        // 2. Set up your ModelView Matrix using your GLM Camera
        glMatrixMode(GL_MODELVIEW);
        glm::mat4 viewMatrix = Camera.GetViewMatrix();
        glLoadMatrixf(glm::value_ptr(viewMatrix)); 

        // 3. Draw the legacy Quad
        glBegin(GL_QUADS);
            glVertex3f(-0.5f,  0.5f, 0.0f); // Top Left
            glVertex3f(-0.5f, -0.5f, 0.0f); // Bottom Left
            glVertex3f( 0.5f, -0.5f, 0.0f); // Bottom Right
            glVertex3f( 0.5f,  0.5f, 0.0f); // Top Right
        glEnd();
    }

    void OnImGuiRender() override {
        {
            ImGui::Begin("Hello, user!");
            ImGui::Text("Application Stats %.3f ms/frame (%.1f FPS)", (float)deltaTime * 1000, 1/deltaTime);
            ImGui::Checkbox("Vsync on?", &doVsync);
            ImGui::ColorEdit3("Background Color", (float*)&clear_color);
            ImGui::SliderFloat("Label", &Camera.FOV, 30.0f, 180.0f);
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