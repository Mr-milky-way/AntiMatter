#pragma once
#include <GLFW/glfw3.h>
#include "../datatypes/datatypes.h"
#include "keycodes.h"


class input {
public:
    GLFWwindow* WindowForInput;
    bool GetKeyDown(KeyCode keycode);
    const char* GetKeyName(KeyCode keycode);

    void DisableCursor();
    void EnableCursor();
    vector2Float GetCursorPos();
    bool GetMouseButtonDown(KeyCode keycode);
};