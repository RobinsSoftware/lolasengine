#include <lolasengine/engine.h>

#include <stdio.h>
#include <stdlib.h>

void window_loop()
{
    
}

int main(void)
{
    callback_register(EVENT_WINDOW_LOOP, &window_loop);
    window_launch();
}
