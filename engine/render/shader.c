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
#include <string.h>

#include <lolasengine/engine.h>

ShaderProgram shader_create_program()
{
    ShaderProgram program = calloc(1, sizeof(struct ShaderProgram));
    memory_track(GC_END_OF_PROGRAM, program, (MemoryFinalizer) &shader_free_program);
    program->shaders = arraylist_create();
    program->_glid = -1;
    program->_inuse = false;
    return program;
}

void shader_compile_program(ShaderProgram program)
{
    if (program->_glid != -1)
        glDeleteProgram(program->_glid);

    program->_glid = glCreateProgram();

    // compile all shaders
    for (int i = 0; i < program->shaders->size; i++)
    {
        Shader shader = (Shader) arraylist_get(program->shaders, i);
        shader->_glid = glCreateShader(shader->type);

        GLchar const* src[] = {shader->source};
        GLint len[] = {strlen(shader->source)};
        glShaderSource(shader->_glid, 1, src, len);

        glCompileShader(shader->_glid);
    }
}

void shader_link_program(ShaderProgram program)
{
    if(program->_glid != -1)
        glLinkProgram(program->_glid);
}

void shader_attach_program(ShaderProgram program)
{
    if(program->_inuse)
        return;
    
    glUseProgram(0);
    program->_inuse = true;
}

void shader_detach_program(ShaderProgram program)
{
    if (!program->_inuse)
        return;

    glUseProgram(0);
    program->_inuse = false;
}

void shader_free_program(ShaderProgram program)
{   
    shader_detach_program(program);
}
