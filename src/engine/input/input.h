#include <GLFW/glfw3.h>
#include "../datatypes/datatypes.h"


#pragma once
class input {
public:
    GLFWwindow* WindowForInput;
    bool GetKeyDown(int keycode);
    const char* GetKeyName(int keycode);

    void DisableCursor();
    void EnableCursor();
    vector2Float GetCursorPos();
    bool GetMouseButtonDown(int keycode);
};