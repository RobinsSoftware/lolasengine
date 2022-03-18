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

#include <stdlib.h>

#include <lolasengine/engine.h>

static DLList callbacks[EVENT_LAST + 1];

void callback_register(int event_id, void *callback)
{
    if (callbacks[event_id] == NULL)
        callbacks[event_id] = dllist_create();

    dllist_append(callbacks[event_id], callback);
}

void callback_remove(int event_id, void *callback)
{
    if(callbacks[event_id] == NULL)
        return;
    
    dllist_remove_value_all(callbacks[event_id], callback);
}

int callback_size(int event_id)
{
    if (callbacks[event_id] == NULL)
        return 0;
    return callbacks[event_id]->size;
}

DLList callback_get(int event_id)
{
    return callbacks[event_id];
}
