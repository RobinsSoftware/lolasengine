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

Color color_rgba(float red, float green, float blue, float alpha)
{
    Color color = memory_alloc(GC_END_OF_PROGRAM, sizeof(struct Color));
    color->r = red;
    color->g = green;
    color->b = blue;
    color->a = alpha;
    return color;
}

Color color_rgb(float red, float green, float blue)
{
    Color color = color_rgba(red, green, blue, 1);
    return color;
}

Color color_rgba_byte(byte red, byte green, byte blue, byte aloha)
{
    Color color = color_rgba(((float) red) / 0xFF, ((float) green) / 0xFF, ((float) blue) / 0xFF, ((float) blue) / 0xFF);
    return color;
}

Color color_rgb_byte(byte red, byte green, byte blue)
{
    Color color = color_rgba_byte(red, green, blue, 0xFF);
    return color;
}