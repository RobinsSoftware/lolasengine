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

DLList dllist_create()
{
    DLList list = calloc(1, sizeof(struct DLList));

    if  (list == NULL)
        print_error_s("ENGINE", "Failed to allocate memory for DLList.");

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

void dllist_set_index(DLList list, int index, void *value)
{
    dllist_get_index(list, index)->value = value;
}

DLListNode dllist_get_index(DLList list, int index)
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

void dllist_set_value_first(DLList list, void *value, void* new_value)
{
    dllist_get_value_first(list, value)->value = new_value;
}

DLListNode dllist_get_value_first(DLList list, void *value)
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
}

void dllist_remove_index(DLList list, int index)
{
    dllist_remove_node(list, dllist_get_index(list, index));
}

void dllist_remove_value_first(DLList list, void *value)
{
    dllist_remove_node(list, dllist_get_value_first(list, value));
}

void dllist_remove_value_all(DLList list, void *value)
{
    // time saving instead of constantly iterating over list?!
    int size = list->size;

    while (1)
    {
        // if size didnt change (no more were found): stop
        if (list->size == size)
            break;

        size = list->size;
        dllist_remove_node(list, dllist_get_value_first(list, value));
    }
}

void dllist_clear(DLList list)
{
    DLListNode cursor = list->first_node;

    for(int i = 0; i < list->size - 1; i++)
    {
        cursor = cursor->next;
        free(cursor->previous);
    }

    free(cursor);
    list->first_node = NULL;
    list->last_node = NULL;
    list->size = 0;
}

void dllist_free(DLList list)
{
    dllist_clear(list);
    free(list);
}