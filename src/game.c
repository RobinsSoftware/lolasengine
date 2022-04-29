#include <lolasengine/engine.h>

#include <stdio.h>
#include <stdlib.h>

void window_loop()
{
    char *ptr = malloc(1);
    memory_track_event(EVENT_WINDOW_START, ptr, NULL);
}

int main(void)
{
    callback_register(EVENT_WINDOW_START, &window_loop);
    window_launch();
}
