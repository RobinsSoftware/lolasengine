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

#include <GLFW/glfw3.h>

// glfw callbacks
extern void __glfw_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
extern void __glfw_mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
extern void __glfw_error_callback(int err_code, const char *description);

// time util engine start time
extern void __set_start_time();
