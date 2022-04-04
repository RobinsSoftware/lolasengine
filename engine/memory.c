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
#include <stdio.h>

#include <lolasengine/engine.h>

// optional use garbage collector
// minimalistic, will try to prevent memory leaks & clean up
// by doing sweeps upon events being fired within the engine

ArrayList events[EVENT_LAST + 1], groups[GC_LAST + 1];

MemoryNode memory_track(int group_id, void *memory, MemoryFinalizer finalizer)
{
    if (memory == NULL)
    {
        print_error_s("MEMORY", "Null memory pointer provided. (memory_track).");
        return NULL;
    }
    
    if (groups[group_id] == NULL)
        groups[group_id] = calloc(1, sizeof(struct ArrayList));

    MemoryNode node = calloc(1, sizeof(struct MemoryNode));

    if (groups[group_id] == NULL || node == NULL)
    {
        print_error_s("MEMORY", "Memory allocation failed. (memory_track).");
        return NULL;
    }
    
    node->memory = memory; 
    node->finalizer = finalizer;
    node->_event = false;
    node->_position = group_id;

    groups[group_id]->size++;
    groups[group_id]->array = realloc(groups[group_id]->array, groups[group_id]->size * sizeof(void*));
    groups[group_id]->array[groups[group_id]->size - 1] = node;

    return node;
}

MemoryNode memory_track_event(int event_id, void *memory, MemoryFinalizer finalizer)
{
    if (memory == NULL)
    {
        print_error_s("MEMORY", "Null memory pointer provided. (memory_track_event).");
        return NULL;
    }

    if (events[event_id] == NULL)
        events[event_id] = calloc(1, sizeof(struct ArrayList));

    MemoryNode node = calloc(1, sizeof(struct MemoryNode));

    if (events[event_id] == NULL || node == NULL)
    {
        print_error_s("MEMORY", "Memory allocation failed. (memory_track_event).");
        return NULL;
    }

    node->memory = memory; 
    node->finalizer = finalizer;
    node->_event = true;
    node->_position = event_id;

    events[event_id]->size++;
    events[event_id]->array = realloc(events[event_id]->array, events[event_id]->size * sizeof(void*));
    events[event_id]->array[events[event_id]->size - 1] = node;
    
    return node;
}

void memory_track_move(MemoryNode node, bool event, int id)
{
    arraylist_remove_first(node->_event ? events[node->_position] : groups[node->_position], node);
    arraylist_add(event ? events[id] : groups[id], node);

    node->_event = event;
    node->_position = id;
}

void memory_free(void *memory)
{
    MemoryNode node = memory_find(memory);

    if(node != NULL)
    {
        arraylist_remove_first(node->_event ? events[node->_position] : groups[node->_position], node);
        free(node);
    }

    free(memory);
}

void memory_free_all(int group_id)
{
    if (groups[group_id] == NULL)
        return;

    for (int i = 0; i < arraylist_size(groups[group_id]); i++)
    {
        MemoryNode node = (MemoryNode) arraylist_get(groups[group_id], i);
        
        arraylist_remove(groups[group_id], i);

        if (node->finalizer != NULL)
            ((MemoryFinalizer) node->finalizer)(node->memory);
        
        free(node->memory);
        free(node);
    }

    arraylist_clear(groups[group_id]);
    free(groups[group_id]);
    
    groups[group_id] = NULL;
}

void memory_free_all_event(int event_id)
{
    if (events[event_id] == NULL)
        return;
    
    for (int i = 0; i < arraylist_size(events[event_id]); i++)
    {
        MemoryNode node = (MemoryNode) arraylist_get(events[event_id], i);
        
        arraylist_remove(events[event_id], i);

        if (node->finalizer != NULL)
            ((MemoryFinalizer) node->finalizer)(node->memory);
        
        free(node->memory);
        free(node);
    }
    
    arraylist_clear(events[event_id]);
    free(events[event_id]);
    
    events[event_id] = NULL;
}

MemoryNode memory_find(void *value)
{
    for (int i = 0; i < GC_LAST+ 1; i++)
        for (int j = 0; groups[i] != NULL && j < groups[i]->size; i++)
            if (arraylist_get(groups[i], j) == value)
                return arraylist_get(groups[i], j);
                
    for (int i = 0; i < EVENT_LAST + 1; i++)
        for (int j = 0; events[i] != NULL && j < events[i]->size; i++)
            if (arraylist_get(events[i], j) == value)
                return arraylist_get(events[i], j);

    return NULL;
}
