#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "engine.h"

GLFWwindow *window;
GLFWmonitor *monitor;

char* title = "CactusEngine";
int width = 640, height = 480, target_fps = -1;
bool fullscreen = false, use_native_res = true, resizable = false;

extern int main();
extern int launch_window();

int main() {
    title = "CactusEngine";
    target_fps = -1;
    fullscreen = GLFW_FALSE;

    launch_window();
    
    return 0;
}

int launch_window() {
    // GLFW init
    if(!glfwInit()) {
        printf("[Engine] Cannot initiialize GLFW.");
        return 1;
    }

    // GLFW hints
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, (int) resizable);
    glfwWindowHint(GLFW_REFRESH_RATE, target_fps);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    monitor = glfwGetPrimaryMonitor();

    // Size & Colour
    const GLFWvidmode *video_mode = glfwGetVideoMode(monitor);
    GLFWmonitor *primary_monitor = fullscreen ? monitor : NULL;
    int w = fullscreen && use_native_res ? video_mode->width : width;
    int h = fullscreen && use_native_res ? video_mode->height : height;
    int red_bits = fullscreen ? video_mode->redBits : GLFW_DONT_CARE;
    int green_bits = fullscreen ? video_mode->greenBits : GLFW_DONT_CARE;
    int blue_bits = fullscreen ? video_mode->blueBits : GLFW_DONT_CARE;

    glfwWindowHint(GLFW_RED_BITS, red_bits);
    glfwWindowHint(GLFW_GREEN_BITS, green_bits);
    glfwWindowHint(GLFW_BLUE_BITS, blue_bits);

    // Create window
    window = glfwCreateWindow(w, h, title, primary_monitor, NULL);

    if (window == NULL) {
        printf("[Engine] Cannot initiialize GLFW window.");
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwShowWindow(window);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.5, 0.5, 0.5, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    // Close
    glfwTerminate();
    return 0;
}