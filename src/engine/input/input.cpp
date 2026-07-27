#include "input.h"
#include <GLFW/glfw3.h>

bool input::GetKeyDown(KeyCode keycode) {

    int rawKey = static_cast<int>(keycode);

    int state = glfwGetKey(WindowForInput, rawKey);
    if (state == GLFW_PRESS){
        return true;
    }
    return false;
}

const char* input::GetKeyName(KeyCode keycode) {
    int rawKey = static_cast<int>(keycode);

    const char* name = glfwGetKeyName(rawKey, 0);
    
    if (name) {
        return name;
    }

    switch (rawKey) {
        case GLFW_KEY_SPACE: return "Space";
        case GLFW_KEY_ESCAPE: return "Escape";
        case GLFW_KEY_ENTER: return "Enter";
        case GLFW_KEY_BACKSPACE: return "Backspace";
        case GLFW_KEY_TAB: return "Tab";
        case GLFW_KEY_LEFT_SHIFT:
        case GLFW_KEY_RIGHT_SHIFT: return "Shift";
        case GLFW_KEY_LEFT_CONTROL:
        case GLFW_KEY_RIGHT_CONTROL: return "Ctrl";
        case GLFW_KEY_LEFT_ALT:
        case GLFW_KEY_RIGHT_ALT: return "Alt";
        default: return "Unknown";
    }
}



void input::DisableCursor() {
    glfwSetInputMode(WindowForInput, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(WindowForInput, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
}

void input::EnableCursor() {
    glfwSetInputMode(WindowForInput, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetInputMode(WindowForInput, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
}

vector2Float input::GetCursorPos(){
    vector2Float pos;
    double mouseX, mouseY;
    glfwGetCursorPos(WindowForInput, &mouseX, &mouseY);
    pos.x = static_cast<float>(mouseX);
    pos.y = static_cast<float>(mouseY);
    return pos;
}

bool input::GetMouseButtonDown(KeyCode keycode) {
    int rawKey = static_cast<int>(keycode);
    
    int state = glfwGetMouseButton(WindowForInput, rawKey);
    if (state == GLFW_PRESS){
        return true;
    }
    return false;
}