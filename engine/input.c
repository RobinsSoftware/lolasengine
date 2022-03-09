/*
Copyright 2022 Robins Software

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

Created by Lola Robins
<lola@robinssoftware.ca>
*/

#include <lolasengine/engine.h>

static bool keys[GLFW_KEY_LAST];
static bool clicks[GLFW_MOUSE_BUTTON_LAST];
static bool buttons[GLFW_GAMEPAD_BUTTON_LAST];

// stores key states
void __glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == -1)
        return; // MacOS FN key registers as -1
    if (action == GLFW_PRESS)
        keys[key] = true;
    else if (action == GLFW_RELEASE)
        keys[key] = false;
}

// stores mouse button states
void __glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS)
        clicks[button] = true;
    else if (action == GLFW_RELEASE)
        clicks[button] = false;
}

bool is_key_pressed(Key key) {
    return keys[key];
}

bool is_mouse_button_pressed(MouseButton button) {
    return clicks[button];
}

bool is_gamepad_button_pressed(GamepadButton button) {
    return buttons[button];
}