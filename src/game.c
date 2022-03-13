#include <lolasengine/engine.h>

#include <stdio.h>

void start_callback() {
    print("test");
}

int main(void) {
    callback_register(EVENT_WINDOW_START, &start_callback);
    callback_register(EVENT_WINDOW_START, &start_callback);
    callback_remove_all(EVENT_WINDOW_START, &start_callback);
    window_launch();
}