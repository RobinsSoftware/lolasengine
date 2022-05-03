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

ShaderProgram shader_program_create()
{
    ShaderProgram program = calloc(1, sizeof(struct ShaderProgram));
    memory_track(GC_END_OF_PROGRAM, program, (MemoryFinalizer) &shader_program_detach);
    program->shaders = arraylist_create();
    program->_glid = -1;
    program->_inuse = false;
    return program;
}

void shader_program_compile(ShaderProgram program)
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

void shader_program_link(ShaderProgram program)
{
    if(program->_glid != -1)
        glLinkProgram(program->_glid);
}

void shader_program_attach(ShaderProgram program)
{
    if(program->_inuse)
        return;
    
    glUseProgram(0);
    program->_inuse = true;
}

void shader_program_detach(ShaderProgram program)
{
    if (!program->_inuse)
        return;

    glUseProgram(0);
    program->_inuse = false;
}

void shader_program_upload_shader(ShaderProgram program, Shader shader)
{
    arraylist_add(program->shaders, shader);

    if (program->_glid == -1)
        return;

    shader_compile(shader);
    glAttachShader(program->_glid, shader->_glid);
}

void shader_program_remove_shader(ShaderProgram program, Shader shader)
{
    arraylist_remove_first(program->shaders, shader);

    if (program->_glid == -1)
        return;

    glDetachShader(program->_glid, shader->_glid);
}

void shader_program_upload_shaders(ShaderProgram program, ArrayList shaders)
{
    for (int i = 0; i < shaders->size; i++)
        shader_program_upload_shader(program, arraylist_get(shaders, i));
}

void shader_program_remove_shaders(ShaderProgram program, ArrayList shaders)
{
    for (int i = 0; i < shaders->size; i++)
        shader_program_remove_shader(program, arraylist_get(shaders, i));
}

Shader shader_create(ShaderType type, bool file, string src)
{
    Shader shader = calloc(1, sizeof(struct Shader));
    memory_track(GC_END_OF_PROGRAM, shader, (MemoryFinalizer) &shader_program_detach);
    shader->type = type;
    shader->_glid = -1;

    if (!file)
    {
        shader->source = src;
        shader->_len = strlen(shader->source);
    }
    else
    {
        shader->_len = file_sizeof(src);
        uint8_t *buffer = calloc(1, shader->_len);
        file_read(src, shader->_len, buffer);
        shader->source = (string) buffer;
    }

    return shader;
}

void shader_compile(Shader shader)
{
    if (shader->_glid != -1)
        return;

    shader->_glid = glCreateShader(shader->type);
    glShaderSource(shader->_glid, 1, (const GLchar *const *) shader->source, (const GLint *) &shader->_len);
    glCompileShader(shader->_glid);
}
