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
    // |  * data/                                                   |
    // +------------------------------------------------------------+

    // engine error codes

    typedef enum ErrorCode {
        NO_ERRORS,
        GLFW_INIT_ERROR,
        WINDOW_INIT_ERROR
    } ErrorCode;

    // custom types

    typedef char *string;
    typedef uint8_t byte;

    // lists

    typedef struct ArrayList
    {
        void **data;
        size_t size;
    }
    *ArrayList;

    // creates a new arraylist
    // @return new list ptr
    extern ArrayList arraylist_create();
    // gets the size of an arraylist
    extern int arraylist_size(ArrayList list);
    // gets the value stored at the index
    extern void *arraylist_get(ArrayList list, int index);
    // sets the value at a given index
    extern void arraylist_set(ArrayList list, int index, void *value);
    // adds a value to the arraylist
    extern void arraylist_add(ArrayList list, void *value);
    // adds the values of an array to the arraylist
    // @param elements amount of items in the array to copy
    extern void arraylist_add_array(ArrayList list, void *array, size_t elements);
    // adds the values of an arraylist to another arraylist
    extern void arraylist_add_arraylist(ArrayList list, ArrayList add);
    // remove an element at a specified index
    extern void arraylist_remove(ArrayList list, int index);
    // removes the first element that matches the provided value
    extern void arraylist_remove_first(ArrayList list, void *value);
    // removes all elements that match the provided value
    extern void arraylist_remove_all(ArrayList list, void *value);
    // clears all elements
    extern void arraylist_clear(ArrayList list);

    // +------------------------------------------------------------+
    // |  * util/                                                   |
    // +------------------------------------------------------------+

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

    // time

    // gets the time the window started at
    extern uint64_t time_start();
    // gets the current time in microseconds
    extern uint64_t time_current_micros();
    // gets a formatted timestamp for logging purposes (20 bytes min.)
    extern void time_current_string(string buffer);

    // file

    // get size of a file
    // @return size of file in bytes, will return -1 if file isn't found
    extern int file_sizeof(string file_name);
    // reads contents of file to buffer
    extern void file_read(string file_name, size_t buffer_size, uint8_t *buffer);

    // input

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
    }
    Key;

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
    }
    GamepadButton;

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
    }
    MouseButton;

    typedef enum InputAction
    {
        PRESS = GLFW_PRESS,
        HOLD = GLFW_REPEAT,
        RELEASE = GLFW_RELEASE
    }
    InputAction;

    // checks if key is pressed
    extern bool input_key_pressed(Key key);
    // checks if mouse button is pressed
    extern bool input_mouse_button_pressed(MouseButton button);
    // checks if gamepad button is pressed
    extern bool input_gamepad_button_pressed(GamepadButton button);

    // +------------------------------------------------------------+
    // |  * math/                                                   |
    // +------------------------------------------------------------+

    // vectors & matricies

    #define __vector_struct_template(type, size, components...)\
    typedef struct Vector_ ## type ## _ ## size\
    {\
        type components;\
    }\
    *Vector_ ## type ## _ ## size;\
    \
    typedef union Vector_ ## type ## _ ## size ## U\
    {\
        struct Vector_ ## type ## _ ## size vector;\
        type type ## _array[size];\
    }\
    Vector_ ## type ## _ ## size ## U;

    #define __matrix_struct_template(type, size_x, size_y, components...)\
    typedef struct Matrix_ ## type ## _ ## size_x ## x ## size_y\
    {\
        type components;\
    }\
    *Matrix_ ## type ## _ ## size_x ## x ## size_y;\
    \
    typedef union Matrix_ ## type ## _ ## size_x ## x ## size_y ## U\
    {\
        struct Matrix_ ## type ## _ ## size_x ## x ## size_y matrix;\
        type type ## _array[size_x * size_y];\
    }\
    Matrix_ ## type ## _ ## size_x ## x ## size_y ## U;

    __matrix_struct_template(double, 2, 2, m0, m1, m2, m3);
    __matrix_struct_template(double, 3, 2, m0, m1, m2, m3, m4, m5);
    __matrix_struct_template(double, 3, 3, m0, m1, m2, m3, m4, m5, m6, m7, m8);
    __matrix_struct_template(double, 4, 3, m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11);
    __matrix_struct_template(double, 4, 4, m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15);
    __matrix_struct_template(int, 2, 2, m0, m1, m2, m3);
    __matrix_struct_template(int, 3, 2, m0, m1, m2, m3, m4, m5);
    __matrix_struct_template(int, 3, 3, m0, m1, m2, m3, m4, m5, m6, m7, m8);
    __matrix_struct_template(int, 4, 3, m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11);
    __matrix_struct_template(int, 4, 4, m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15);
    __matrix_struct_template(float, 2, 2, m0, m1, m2, m3);
    __matrix_struct_template(float, 3, 2, m0, m1, m2, m3, m4, m5);
    __matrix_struct_template(float, 3, 3, m0, m1, m2, m3, m4, m5, m6, m7, m8);
    __matrix_struct_template(float, 4, 3, m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11);
    __matrix_struct_template(float, 4, 4, m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15);
    __vector_struct_template(double, 2, x, y);
    __vector_struct_template(double, 3, x, y, z);
    __vector_struct_template(double, 4, x, y, z, w);
    __vector_struct_template(int, 2, x, y);
    __vector_struct_template(int, 3, x, y, z);
    __vector_struct_template(int, 4, x, y, z, w);
    __vector_struct_template(float, 2, x, y);
    __vector_struct_template(float, 3, x, y, z);
    __vector_struct_template(float, 4, x, y, z, w);

    // +------------------------------------------------------------+
    // |  * /                                                       |
    // +------------------------------------------------------------+

    // garbage collector

    typedef void (*MemoryFinalizer)(void *memory);
        
    typedef struct MemoryNode
    {
        void *memory;
        MemoryFinalizer finalizer;
        bool _event;
        int _position;
    }
    *MemoryNode;

    // memory collection when the game shuts down safely
    #define GC_END_OF_PROGRAM 0x00
    // reserve collection groups
    #define GC_RESERVE_1 0x01
    #define GC_RESERVE_2 0x02
    #define GC_RESERVE_3 0x03
    #define GC_RESERVE_4 0x04
    // user preallocated groups
    #define GC_GROUP_1 0x05
    #define GC_GROUP_2 0x06
    #define GC_GROUP_3 0x07
    #define GC_GROUP_4 0x08

    #ifndef GC_LAST
    #define GC_LAST GC_GROUP_4
    #endif

    // track memory for removal with a specified group during runtime
    extern MemoryNode memory_track(int group_id, void *memory, MemoryFinalizer finalizer);
    // track memory for removal after an event is called during runtime
    // @param finalizer MemoryFinalizer callbacks run before the engine kills the memory
    extern MemoryNode memory_track_event(int event_id, void *memory, MemoryFinalizer finalizer);
    // frees the provided ptr and removes it from the garbage collector's memory
    extern void memory_free(void *memory);
    // free all memory of a group
    extern void memory_free_all(int group_id);
    // frees all memory assigned to an event after an event has finished execution
    extern void memory_free_all_event(int event_id);
    // finds the corresponding node for memory being tracked 
    extern MemoryNode memory_find(void *value);

    // callbacks

    #define EVENT_WINDOW_PRE_START 0x00
    #define EVENT_WINDOW_START 0x01
    #define EVENT_WINDOW_LOOP 0x02
    #define EVENT_WINDOW_STOP 0x03
    #define EVENT_WINDOW_RESIZE 0x04
    #define EVENT_WINDOW_SCENE_CHANGE 0x05
    #define EVENT_WINDOW_FOCUS_CHANGE 0x06

    #define EVENT_INPUT_KEY_PRESS 0x07
    #define EVENT_INPUT_MOUSE_BUTTON_PRESS 0x08

    #ifndef EVENT_LAST
    #define EVENT_LAST EVENT_INPUT_MOUSE_BUTTON_PRESS
    #endif

    typedef void (*NullArgs)();

    typedef void (*EventWindowResize)(GLFWwindow *window, int width, int height);
    typedef void (*EventWindowFocusChange)(GLFWwindow *window, bool focused);

    typedef void (*EventInputKeyPress)(Key key, InputAction action);
    typedef void (*EventInputMouseButtonPress)(MouseButton button, InputAction action);

    // macro for calling events
    #define event_call(event_id, event_void, args...)\
        for (int i = 0; i < callback_size(event_id); i++)\
            ((event_void) arraylist_get(callback_get(event_id), i))(args);\
        memory_free_all_event(event_id);
    
    // register a callback
    extern void callback_register(int event_id, void *callback);
    // safely removes and frees events & memory
    // @return if removal was successful
    extern void callback_remove(int event_id, void *callback);
    // get a list storing callbacks for a given event id
    // @return list of callbacks, they can be accessed by iterating through the elements
    extern ArrayList callback_get(int event_id);
    // gets the amount of callbacks registered to an event
    extern int callback_size(int event_id);

    // +------------------------------------------------------------+
    // |  * /render                                                 |
    // +------------------------------------------------------------+

    // window

    // launches engine window
    // @return window exit status code
    extern ErrorCode window_launch(void);
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

    // shader

    typedef enum ShaderType
    {
        FRAGMENT,
        VERTEX
    }
    ShaderType;

    typedef struct Shader
    {
        ShaderType type;
        string source, path;
        GLuint _glid;
    }
    *Shader;

    typedef struct ShaderProgram
    {
        ArrayList shaders;
        GLuint _glid;
        bool _inuse;
    }
    *ShaderProgram;

    // intiializes a shader program
    extern ShaderProgram shader_create_program();
    // compiles a shader program
    extern void shader_program_compile(ShaderProgram program);
    extern void shader_program_link(ShaderProgram program);
    extern void shader_program_attach(ShaderProgram program); 
    extern void shader_program_detach(ShaderProgram program);

    // janky but working c preprocessor vec & matrix uploading
    #define __shader_program_upload_template(args, args_alt, type_lower)\
    extern void shader_program_upload_ ## type_lower ## ( ## args ## );\
    extern void shader_program_upload_ ## type_lower ## u( ## args ## );
    
    __shader_program_upload_template(Matrix_double_2x2 matrix, Matrix_double_2x2U matrix, matrix_double_2x2);
    __shader_program_upload_template(Matrix_double_3x2 matrix, Matrix_double_3x2U matrix, matrix_double_3x2);
    __shader_program_upload_template(Matrix_double_3x3 matrix, Matrix_double_3x3U matrix, matrix_double_3x3);
    __shader_program_upload_template(Matrix_double_4x3 matrix, Matrix_double_4x3U matrix, matrix_double_4x3);
    __shader_program_upload_template(Matrix_double_4x4 matrix, Matrix_double_4x4U matrix, matrix_double_4x4);
    __shader_program_upload_template(Matrix_int_2x2 matrix, Matrix_int_2x2U matrix, matrix_int_2x2);
    __shader_program_upload_template(Matrix_int_3x2 matrix, Matrix_int_3x2U matrix, matrix_int_3x2);
    __shader_program_upload_template(Matrix_int_3x3 matrix, Matrix_int_3x3U matrix, matrix_int_3x3);
    __shader_program_upload_template(Matrix_int_4x3 matrix, Matrix_int_4x3U matrix, matrix_int_4x3);
    __shader_program_upload_template(Matrix_int_4x4 matrix, Matrix_int_4x4U matrix, matrix_int_4x4);
    __shader_program_upload_template(Matrix_float_2x2 matrix, Matrix_float_2x2U matrix, matrix_float_2x2);
    __shader_program_upload_template(Matrix_float_3x2 matrix, Matrix_float_3x2U matrix, matrix_float_3x2);
    __shader_program_upload_template(Matrix_float_3x3 matrix, Matrix_float_3x3U matrix, matrix_float_3x3);
    __shader_program_upload_template(Matrix_float_4x3 matrix, Matrix_float_4x3U matrix, matrix_float_4x3);
    __shader_program_upload_template(Matrix_float_4x4 matrix, Matrix_float_4x4U matrix, matrix_float_4x4);
    __shader_program_upload_template(Vector_double_2 vector, Vector_double_2U vector, vector_double_2);
    __shader_program_upload_template(Vector_double_3 vector, Vector_double_3U vector, vector_double_3);
    __shader_program_upload_template(Vector_double_4 vector, Vector_double_4U vector, vector_double_4);
    __shader_program_upload_template(Vector_int_2 vector, Vector_int_2U vector, vector_int_2);
    __shader_program_upload_template(Vector_int_3 vector, Vector_int_3U vector, vector_int_3);
    __shader_program_upload_template(Vector_int_4 vector, Vector_int_4U vector, vector_int_4);
    __shader_program_upload_template(Vector_float_2 vector, Vector_float_2U vector, vector_float_2);
    __shader_program_upload_template(Vector_float_3 vector, Vector_float_3U vector, vector_float_3);
    __shader_program_upload_template(Vector_float_4 vector, Vector_float_4U vector, vector_float_4);

#ifdef __cplusplus
}
#endif

#endif
