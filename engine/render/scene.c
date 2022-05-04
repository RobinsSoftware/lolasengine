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
#include <string.h>

Scene scene_create()
{
    Scene scene = memory_alloc(GC_END_OF_PROGRAM, sizeof(struct Scene));
    return scene;
}

void scene_color(Scene scene, Color color)
{
    scene->color.r = color->r;
    scene->color.g = color->g;
    scene->color.b = color->b;
    scene->color.a = color->a;
}

