#include "window.h"


void window::framebuffer_size_callback(GLFWwindow* window, int w, int h) {
    glViewport(0, 0, w, h);
}

