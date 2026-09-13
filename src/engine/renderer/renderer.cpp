#include "renderer.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>

void renderer::Render(GLFWwindow* Window) {
    int display_w, display_h;
    glfwGetFramebufferSize(Window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}   