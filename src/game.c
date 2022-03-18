#include <lolasengine/engine.h>

#include <stdio.h>
#include <stdlib.h>

void window_loop()
{
    int* f = calloc(1, sizeof(int));
    memory_track_event(EVENT_WINDOW_LOOP, f, NULL);
}

int main(void)
{
    DLList list = dllist_create();
    dllist_append(list, &window_loop);
    callback_register(EVENT_WINDOW_LOOP, &window_loop);
    memory_free_all(GC_END_OF_PROGRAM);
    window_launch();
}
