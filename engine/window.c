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

#include <stdio.h>
#include <stdlib.h>

#include <lolasengine/engine.h>

#include "internal.h"

// local vars
static GLFWwindow *window;
static GLFWmonitor *monitor;

static string title = "lolasengine";
static int width = 640, height = 480, target_fps = -1;
static bool fullscreen = false, use_native_res = true, resizable = false;

// gets center position (topleft corner pos)
static int window_center_pos(int screen_dim, int dim)
{
    return (screen_dim - dim) / 2;
}

// updates window after dimension changes
static void dimension_update(void)
{
    if (window == NULL)
        return;

    const GLFWvidmode *video_mode = glfwGetVideoMode(monitor);
    GLFWmonitor *primary_monitor = fullscreen ? monitor : NULL;
    int w = fullscreen && use_native_res ? video_mode->width : width;
    int h = fullscreen && use_native_res ? video_mode->height : height;

    glfwSetWindowMonitor(window, primary_monitor, window_center_pos(video_mode->width, w),
                         window_center_pos(video_mode->height, h), w, h, target_fps);

    int red_bits = fullscreen ? video_mode->redBits : GLFW_DONT_CARE;
    int green_bits = fullscreen ? video_mode->greenBits : GLFW_DONT_CARE;
    int blue_bits = fullscreen ? video_mode->blueBits : GLFW_DONT_CARE;

    glfwWindowHint(GLFW_RED_BITS, red_bits);
    glfwWindowHint(GLFW_GREEN_BITS, green_bits);
    glfwWindowHint(GLFW_BLUE_BITS, blue_bits);
}

// free memory after window closes
static void free_memory()
{
    // destroy callbacks
    glfwSetKeyCallback(window, NULL);
    glfwSetMouseButtonCallback(window, NULL);
    glfwSetWindowSizeCallback(window, NULL);
    glfwSetWindowFocusCallback(window, NULL);

    glfwDestroyWindow(window);
    glfwTerminate();

    __free_callback_memory();
}

static void window_focus_callback(GLFWwindow *window, int focused)
{
    event_call(EVENT_WINDOW_FOCUS_CHANGE, EventWindowFocusChange, window, (bool) focused);
}

static void window_size_callback(GLFWwindow *window, int width, int height)
{
    event_call(EVENT_WINDOW_RESIZE, EventWindowResize, window, width, height);
}

int window_launch(void)
{
    glfwSetErrorCallback(__glfw_error_callback);

    event_call(EVENT_WINDOW_PRE_START, NullArgs);

    // glfw init
    if (!glfwInit())
    {
        print_error("Engine cannot enable GLFW.");
        return 1;
    }

    // glfw hints
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, (int)resizable);
    glfwWindowHint(GLFW_REFRESH_RATE, target_fps);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    monitor = glfwGetPrimaryMonitor();

    // size & colour
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

    // create window
    window = glfwCreateWindow(w, h, title, primary_monitor, NULL);

    if (window == NULL)
    {
        print_error("Engine cannot initiialize GLFW window.");
        glfwTerminate();
        return 1;
    }

    // register callbacks
    glfwSetKeyCallback(window, __glfw_key_callback);
    glfwSetMouseButtonCallback(window, __glfw_mouse_button_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetWindowFocusCallback(window, window_focus_callback);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwShowWindow(window);

    event_call(EVENT_WINDOW_START, NullArgs);

    while (!glfwWindowShouldClose(window))
    {
        event_call(EVENT_WINDOW_LOOP, NullArgs);

        glfwPollEvents();

        glClearColor(0.5, 0.5, 0.5, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    event_call(EVENT_WINDOW_STOP, NullArgs);

    free_memory();
    return 0;
}

void window_title(string window_title)
{
    title = window_title;
    if (window != NULL)
        glfwSetWindowTitle(window, title);
}

void window_size(int window_width, int window_height)
{
    width = window_width;
    height = window_height;
    dimension_update();
}

void window_fullscreen(bool window_fullscreen)
{
    fullscreen = window_fullscreen;
    dimension_update();
}

void window_fullscreen_native_resolution(bool window_fullscreen_native_res)
{
    use_native_res = window_fullscreen_native_res;
    dimension_update();
}

void window_resizable(bool window_resizable)
{
    resizable = window_resizable;
    dimension_update();
}