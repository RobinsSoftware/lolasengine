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
#include <string.h>

#include <lolasengine/engine.h>

ArrayList arraylist_create()
{
    ArrayList list = calloc(1, sizeof(struct ArrayList));
    memory_track(GC_END_OF_PROGRAM, list, (MemoryFinalizer) &arraylist_clear);
    return list;
}

int arraylist_size(ArrayList list)
{
    return list->size;
}

void *arraylist_get(ArrayList list, int index)
{
    return list->array[index];
}

bool arraylist_contains(ArrayList list, void *value)
{
    for (int i = 0; i < list->size; i++)
        if (list->array[i] == value)
            return true;
    return false;
}

void arraylist_set(ArrayList list, int index, void *value)
{
    list->array[index] = value;
}

void arraylist_add(ArrayList list, void *value)
{
    list->size++;
    list->array = realloc(list->array, list->size * sizeof(void*));
    list->array[list->size - 1] = value;
}

void arraylist_add_array(ArrayList list, void* array, size_t elements)
{
    list->size += elements;
    list->array = realloc(list->array, list->size * sizeof(void*));
    memcpy((*list->array + (list->size - elements) * sizeof(void*)), array, (list->size - elements) * sizeof(void*));
}

void arraylist_add_arraylist(ArrayList list, ArrayList add)
{
    list->size += add->size;
    list->array = realloc(list->array, list->size * sizeof(void*));
    memcpy((*list->array + ((list->size - add->size) * sizeof(void*))), add->array, (list->size - add->size) * sizeof(void*));
}

void arraylist_remove(ArrayList list, int index)
{
    list->size--;
    memcpy((*list->array + (index * sizeof(void))), (*list->array + ((index + 1) * sizeof(void))), (list->size - index) * sizeof(void*));
    list->array = realloc(list->array, list->size * sizeof(void*));
}

void arraylist_remove_first(ArrayList list, void *value)
{
    for (int i = 0; i < list->size; i++)
        if (list->array[i] == value)
            arraylist_remove(list, i);
}

void arraylist_remove_all(ArrayList list, void *value)
{
    while (arraylist_contains(list, value))
        arraylist_remove_first(list, value);
}

void arraylist_clear(ArrayList list)
{   
    if (list->array == NULL)
        return;

    free(list->array);
    list->array = NULL;
    list->size = 0;
}
