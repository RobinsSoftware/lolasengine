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

DLList dllist_create()
{
    DLList list = calloc(1, sizeof(struct DLList));
    memory_track(GC_END_OF_PROGRAM, list, (MemoryFinalizer) &dllist_clear);
    return list;
}

int dllist_size(DLList list)
{
    return list->size;
}

void* dllist_value(DLListNode node)
{
    return node->value;
}

void* dllist_get(DLList list, int index)
{
    return dllist_get_node(list, index)->value;
}

DLListNode dllist_get_node(DLList list, int index)
{
    // starts from side closest to
    bool direction = !(index > (list->size / 2));
    DLListNode cursor = direction ? list->first_node : list->last_node;

    for (
        int i = direction ? 0 : list->size - 1;
        direction ? i < index : i > index;
    ){
        cursor = direction ? cursor->next : cursor->previous;

        if (cursor == NULL)
            return NULL;

        if (direction)
            i++;
        else
            i--;
    }
    
    return cursor;
}

DLListNode dllist_get_node_with_value(DLList list, void *value)
{
    DLListNode cursor = list->first_node;
    
    for (int i = 0; i < list->size; i++)
    {
        if (cursor->value == value)
            return cursor;
        
        cursor = cursor->next;
    }

    return NULL;
}

void dllist_set(DLList list, int index, void *value)
{
    dllist_get_node(list, index)->value = value;
}

void dllist_set_value_first(DLList list, void *value, void* new_value)
{
    dllist_get_node_with_value(list, value)->value = new_value;
}


void dllist_append(DLList list, void *value)
{
    DLListNode node = calloc(1, sizeof(struct DLListNode));

    if  (node == NULL)
    {   
        print_error_s("ENGINE", "Failed to allocate memory for DLListNode.");
        return;
    }

    node->value = value;
    node->previous = list->last_node;
    list->size++;

    if (list->first_node == NULL)
        list->first_node = node;
    else
        list->last_node->next = node;

    list->last_node = node;
}

void dllist_remove_node(DLList list, DLListNode node)
{
    if (list->first_node == node)
    {   
        // tie elements at start
        list->first_node = node->next;
        list->first_node->previous = NULL;
    }
    else if (list->last_node == node)
    {
        // tie elements at end
        list->last_node = node->previous;
        list->last_node->next = NULL;
    }
    else
    {
        // free element in middle
        node->previous->next = node->next;
        node->next->previous = node->previous;
    }

    list->size--;
    free(node);
    node = NULL;
}

void dllist_remove(DLList list, int index)
{
    dllist_remove_node(list, dllist_get_node(list, index));
}

void dllist_remove__first(DLList list, void *value)
{
    dllist_remove_node(list, dllist_get_node_with_value(list, value));
}

void dllist_remove_all(DLList list, void *value)
{
    // time saving instead of constantly iterating over list?!
    int size = list->size;

    while (1)
    {
        // if size didnt change (no more were found): stop
        if (list->size == size)
            break;

        size = list->size;
        dllist_remove_node(list, dllist_get_node_with_value(list, value));
    }
}

void dllist_clear(DLList list)
{
    if(!list->size)
        return;

    DLListNode cursor = list->first_node;

    for(int i = 0; i < list->size - 1; i++)
    {
        cursor = cursor->next;
        free(cursor->previous);
        cursor->previous = NULL;
    }

    free(cursor);
    cursor = NULL;
    list->first_node = NULL;
    list->last_node = NULL;
    list->size = 0;
}
