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

#include <sys/stat.h>
#include <stdio.h>

#include <lolasengine/engine.h>

int file_sizeof(string file_name)
{   
    #ifdef _WIN32
    struct _stat file_info;

    if (_stat(file_name, &file_info != 0))
    #else
    struct stat file_info;

    if (stat(file_name, &file_info) == -1)
    #endif
    {
        return -1;
    }

    return file_info.st_size;
}

void file_read(string file_name, size_t buffer_size, uint8_t *buffer)
{
    FILE *file = fopen(file_name, "r");
    fread(buffer, 1, buffer_size, file);
    fclose(file);
}