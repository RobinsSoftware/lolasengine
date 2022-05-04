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

ShaderProgram default_shader_program()
{
    ShaderProgram shader = shader_program_create();
    return shader;
}

Scene default_scene()
{
    Scene scene = scene_create();
    scene_color(scene, color_rgb_byte(255, 192, 203));
    return scene;
}