#include <lolasengine/engine.h>

#include <stdio.h>

void loop() {
    if(input_key_pressed(SPACE))
        print("space");
}

int main(void) {
    callback_register(EVENT_WINDOW_LOOP, &loop);
    window_launch();
}