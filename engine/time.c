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

#include <stdio.h>
#include <time.h>
#include <sys/time.h>

#include <lolasengine/engine.h>

#include "../internal.h"

static uint64_t start_time_micros;

void __set_start_time()
{
    start_time_micros = time_current_micros();
}

uint64_t time_start()
{
    return start_time_micros;
}

uint64_t time_current_micros()
{
    struct timeval current;
    gettimeofday(&current, NULL);
    return current.tv_sec * (uint64_t) 1000000 + current.tv_usec;
}

void time_current_string(string buffer)
{
    time_t t = time(0);
    struct tm *pt = localtime(&t);
    sprintf(buffer, "%02d/%02d/%04d-%02d:%02d:%02d", pt->tm_mon, pt->tm_mday, pt->tm_year + 1900, pt->tm_hour, pt->tm_min, pt->tm_sec);
}