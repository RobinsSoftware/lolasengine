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

Scene scene_create()
{
    Scene scene = memory_alloc(GC_END_OF_PROGRAM, sizeof(struct Scene));
    return scene;
}

void scene_rgb(float r, float g, float b)
{

}

void scene_rgba(float r, float g, float b, float a)
{

}

void scene_rgb_hex(char hex[7])
{

}
