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

#ifndef LOLASENGINE_H
#define LOLASENGINE_H

// silence deprecation warnings for mac glfw
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#include <stdbool.h>
#include <stdint.h>

#include <GLFW/glfw3.h>

#ifdef __cplusplus
extern "C"
{
#endif

    // +------------------------------------------------------------+
    // |  * input enums                                             |
    // +------------------------------------------------------------+

    typedef char *string;

    typedef enum Key
    {
        SPACE = GLFW_KEY_SPACE,
        APOSTROPHE = GLFW_KEY_APOSTROPHE,
        COMMA = GLFW_KEY_COMMA,
        MINUS = GLFW_KEY_MINUS,
        PERIOD = GLFW_KEY_PERIOD,
        SLASH = GLFW_KEY_SLASH,
        N0 = GLFW_KEY_0,
        N1 = GLFW_KEY_1,
        N2 = GLFW_KEY_2,
        N3 = GLFW_KEY_3,
        N4 = GLFW_KEY_4,
        N5 = GLFW_KEY_5,
        N6 = GLFW_KEY_6,
        N7 = GLFW_KEY_7,
        N8 = GLFW_KEY_8,
        N9 = GLFW_KEY_9,
        SEMICOLON = GLFW_KEY_SEMICOLON,
        EQUAL = GLFW_KEY_EQUAL,
        A = GLFW_KEY_A,
        B = GLFW_KEY_B,
        C = GLFW_KEY_C,
        D = GLFW_KEY_D,
        E = GLFW_KEY_E,
        F = GLFW_KEY_F,
        G = GLFW_KEY_G,
        H = GLFW_KEY_H,
        I = GLFW_KEY_I,
        J = GLFW_KEY_J,
        K = GLFW_KEY_K,
        L = GLFW_KEY_L,
        M = GLFW_KEY_M,
        N = GLFW_KEY_N,
        O = GLFW_KEY_O,
        P = GLFW_KEY_P,
        Q = GLFW_KEY_Q,
        R = GLFW_KEY_R,
        S = GLFW_KEY_S,
        T = GLFW_KEY_T,
        U = GLFW_KEY_U,
        V = GLFW_KEY_V,
        W = GLFW_KEY_W,
        X = GLFW_KEY_X,
        Y = GLFW_KEY_Y,
        Z = GLFW_KEY_Z,
        LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET,
        BACKSLASH = GLFW_KEY_BACKSLASH,
        RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET,
        GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT,
        WORLD_1 = GLFW_KEY_WORLD_1,
        WORLD_2 = GLFW_KEY_WORLD_2,
        ESCAPE = GLFW_KEY_ESCAPE,
        ENTER = GLFW_KEY_ENTER,
        TAB = GLFW_KEY_TAB,
        BACKSPACE = GLFW_KEY_BACKSPACE,
        INSERT = GLFW_KEY_INSERT,
        DELETE = GLFW_KEY_DELETE,
        RIGHT = GLFW_KEY_RIGHT,
        LEFT = GLFW_KEY_LEFT,
        DOWN = GLFW_KEY_DOWN,
        UP = GLFW_KEY_UP,
        PAGE_UP = GLFW_KEY_PAGE_UP,
        PAGE_DOWN = GLFW_KEY_PAGE_DOWN,
        HOME = GLFW_KEY_HOME,
        END = GLFW_KEY_END,
        CAPS_LOCK = GLFW_KEY_CAPS_LOCK,
        SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK,
        NUM_LOCK = GLFW_KEY_NUM_LOCK,
        PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN,
        PAUSE = GLFW_KEY_PAUSE,
        F1 = GLFW_KEY_F1,
        F2 = GLFW_KEY_F2,
        F3 = GLFW_KEY_F3,
        F4 = GLFW_KEY_F4,
        F5 = GLFW_KEY_F5,
        F6 = GLFW_KEY_F6,
        F7 = GLFW_KEY_F7,
        F8 = GLFW_KEY_F8,
        F9 = GLFW_KEY_F9,
        F10 = GLFW_KEY_F10,
        F11 = GLFW_KEY_F11,
        F12 = GLFW_KEY_F12,
        F13 = GLFW_KEY_F13,
        F14 = GLFW_KEY_F14,
        F15 = GLFW_KEY_F15,
        F16 = GLFW_KEY_F16,
        F17 = GLFW_KEY_F17,
        F18 = GLFW_KEY_F18,
        F19 = GLFW_KEY_F19,
        F20 = GLFW_KEY_F20,
        F21 = GLFW_KEY_F21,
        F22 = GLFW_KEY_F22,
        F23 = GLFW_KEY_F23,
        F24 = GLFW_KEY_F24,
        F25 = GLFW_KEY_F25,
        KP0 = GLFW_KEY_KP_0,
        KP1 = GLFW_KEY_KP_1,
        KP2 = GLFW_KEY_KP_2,
        KP3 = GLFW_KEY_KP_3,
        KP4 = GLFW_KEY_KP_4,
        KP5 = GLFW_KEY_KP_5,
        KP6 = GLFW_KEY_KP_6,
        KP7 = GLFW_KEY_KP_7,
        KP8 = GLFW_KEY_KP_8,
        KP9 = GLFW_KEY_KP_9,
        KP_DECIMAL = GLFW_KEY_KP_DECIMAL,
        KP_DIVIDE = GLFW_KEY_KP_DIVIDE,
        KP_MULTIPLY = GLFW_KEY_KP_MULTIPLY,
        KP_SUBTRACT = GLFW_KEY_KP_SUBTRACT,
        KP_ADD = GLFW_KEY_KP_ADD,
        KP_ENTER = GLFW_KEY_KP_ENTER,
        KP_EQUAL = GLFW_KEY_KP_EQUAL,
        LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
        LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL,
        LEFT_ALT = GLFW_KEY_LEFT_ALT,
        LEFT_SUPER = GLFW_KEY_LEFT_SUPER,
        RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
        RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL,
        RIGHT_ALT = GLFW_KEY_RIGHT_ALT,
        RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER,
        MENU = GLFW_KEY_MENU
    } Key;

    typedef enum GamepadButton
    {
        A_BUTTON = GLFW_GAMEPAD_BUTTON_A,
        B_BUTTON = GLFW_GAMEPAD_BUTTON_B,
        X_BUTTON = GLFW_GAMEPAD_BUTTON_X,
        Y_BUTTON = GLFW_GAMEPAD_BUTTON_Y,
        LEFT_BUMPER = GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,
        RIGHT_BUMPER = GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,
        BACK = GLFW_GAMEPAD_BUTTON_BACK,
        START = GLFW_GAMEPAD_BUTTON_START,
        GUIDE = GLFW_GAMEPAD_BUTTON_GUIDE,
        LEFT_THUMB = GLFW_GAMEPAD_BUTTON_LEFT_THUMB,
        RIGHT_THUMB = GLFW_GAMEPAD_BUTTON_RIGHT_THUMB,
        DPAD_UP = GLFW_GAMEPAD_BUTTON_DPAD_UP,
        DPAD_DOWN = GLFW_GAMEPAD_BUTTON_DPAD_DOWN,
        DPAD_LEFT = GLFW_GAMEPAD_BUTTON_DPAD_LEFT,
        DPAD_RIGHT = GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,
        CROSS = GLFW_GAMEPAD_BUTTON_CROSS,
        CIRCLE = GLFW_GAMEPAD_BUTTON_CIRCLE,
        SQUARE = GLFW_GAMEPAD_BUTTON_SQUARE,
        TRIANGLE = GLFW_GAMEPAD_BUTTON_TRIANGLE
    } GamepadButton;

    typedef enum MouseButton
    {
        MB1 = GLFW_MOUSE_BUTTON_1,
        MB2 = GLFW_MOUSE_BUTTON_2,
        MB3 = GLFW_MOUSE_BUTTON_3,
        MB4 = GLFW_MOUSE_BUTTON_4,
        MB5 = GLFW_MOUSE_BUTTON_5,
        MB6 = GLFW_MOUSE_BUTTON_6,
        MB7 = GLFW_MOUSE_BUTTON_7,
        MB8 = GLFW_MOUSE_BUTTON_8
    } MouseButton;

    typedef enum InputAction
    {
        PRESS = GLFW_PRESS,
        HOLD = GLFW_REPEAT,
        RELEASE = GLFW_RELEASE
    } InputAction;

    struct EventCallbackList
    {
        void *callback;
        struct EventCallbackList *next;
    };

    // +------------------------------------------------------------+
    // |  * event ids                                               |
    // +------------------------------------------------------------+

#define EVENT_WINDOW_PRE_START 0x00
#define EVENT_WINDOW_START 0x01
#define EVENT_WINDOW_LOOP 0x02
#define EVENT_WINDOW_STOP 0x03
#define EVENT_WINDOW_RESIZE 0x04
#define EVENT_WINDOW_SCENE_CHANGE 0x05
#define EVENT_WINDOW_FOCUS_CHANGE 0x06

#define EVENT_INPUT_KEY_PRESS 0x07
#define EVENT_INPUT_MOUSE_BUTTON_PRESS 0x08

// allows for user added events to be added
#ifndef EVENT_LAST
#define EVENT_LAST 0x08
#endif

    typedef void (*NullArgs)();

    typedef void (*EventWindowResize)(GLFWwindow *window, int width, int height);
    typedef void (*EventWindowFocusChange)(GLFWwindow *window, bool focused);

    typedef void (*EventInputKeyPress)(Key key, InputAction action);
    typedef void (*EventInputMouseButtonPress)(MouseButton button, InputAction action);

    // +------------------------------------------------------------+
    // |  * api methods                                             |
    // +------------------------------------------------------------+

    // window

    // launches engine window
    extern int window_launch(void);
    // set the window title
    extern void window_title(string window_title);
    // set the size of the window
    extern void window_size(int window_height, int window_width);
    // set window to fullscreen/windowed
    extern void window_fullscreen(bool window_fullscreen);
    // set use native screen resolution in fullscreen
    extern void window_fullscreen_native_resolution(bool window_fullscreen_native_res);
    // set window can be resized
    extern void window_resizable(bool window_resizable);

    // input

    // checks if key is pressed
    extern bool input_key_pressed(Key key);
    // checks if mouse button is pressed
    extern bool input_mouse_button_pressed(MouseButton button);
    // checks if gamepad button is pressed
    extern bool input_gamepad_button_pressed(GamepadButton button);

    // logging

    // standard log message
    extern void print(string message);
    extern void print_s(string source, string message);
    // debug log message
    extern void print_debug(string message);
    extern void print_debug_s(string source, string message);
    // error log message
    extern void print_error(string message);
    extern void print_error_s(string source, string message);

    // timeutil

    // gets a formatted timestamp for logging purposes (20 bytes min.)
    extern void timeutil_get_timestamp(string buffer);
    // gets the current time in microseconds
    extern uint64_t timeutil_current_time_micros();

    // callback

    // macro for calling events
    #define event_call(event_id, event_struct, args...)   \
        for (int i = 0; i < callback_size(event_id); i++) \
            ((event_struct)callback_get(event_id, i)->callback)(args);

    // register a callback
    extern void callback_register(int event_id, void *callback);
    // safely removes and frees events & memory
    // @return if removal was successful
    extern bool callback_remove(int event_id, void *callback);
    // safely removes and frees events & memory for all callback elements pointing to specified void ptr for that event
    // @return if removal was successful at least once
    extern bool callback_remove_all(int event_id, void *callback);
    // get a callback linkedlist element
    // @return linkedlist element of callback, the callback void ptr itself is accessible with struct EventCallbackList->callback
    extern struct EventCallbackList *callback_get(int event_id, int index);
    // gets the amount of callbacks registered to an event
    extern int callback_size(int event_id);

#ifdef __cplusplus
}
#endif

#endif