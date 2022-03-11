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

#include <lolasengine/engine.h>

#include <stdio.h>
#include <stdlib.h>

struct EventCallbackList *callbacks[EVENT_LAST + 1];

// gets last element of the linked list
static struct EventCallbackList *last(struct EventCallbackList *next)
{
    if (next != NULL || next->next != NULL)
        return last(next);
    else
        return next;
}

void callback_register(int event_id, void *callback)
{
    struct EventCallbackList *list = malloc(sizeof(struct EventCallbackList));

    list->callback = callback;
    list->next = NULL;

    if (callbacks[event_id] == NULL)
        callbacks[event_id] = list;
    else
        last(callbacks[event_id])->next = list;
}

struct EventCallbackList *callback_get(int event_id, int index)
{
    struct EventCallbackList *list = callbacks[event_id];

    for (int i = 0; (i < index) && (list == NULL || list->next == NULL); i++)
        list = list->next;

    return list;
}

int callback_size(int event_id)
{
    struct EventCallbackList *list = callbacks[event_id];
    int count = 0;

    while (list != NULL)
    {
        list = list->next;
        count++;
    }

    return count;
}

void __free_callback_memory()
{
    for (int i = 0; i < EVENT_LAST; i++)
    {
        struct EventCallbackList *current = callbacks[i];

        while (1)
        {
            if (current == NULL)
                break;

            struct EventCallbackList *next = current->next;
            free(current);
            current = next;
        }
    }
}