#include <lolasengine/engine.h>

#include <stdio.h>

void key_callback(Key key, InputAction action) {
    print("1");
}

void key_callback2(Key key, InputAction action) {
    print("2");
}

void key_callback3(Key key, InputAction action) {
    print("3");
}
int main(void) {
    callback_register(EVENT_INPUT_KEY_PRESS, &key_callback);
    callback_register(EVENT_INPUT_KEY_PRESS, &key_callback2);
    callback_register(EVENT_INPUT_KEY_PRESS, &key_callback3);
    window_launch();
}