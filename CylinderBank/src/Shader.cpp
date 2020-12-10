#include "CylinderBank_pch.hpp"
#include "glad/glad.h"

#include "Renderer/Shader.hpp"

#include "CylinderBank.hpp"

namespace CylinderBank
{
    Shader::Shader(const std::string &t_vertex_source,
                   const std::string &t_fragment_source)
    {
        GLint compile_result = GL_FALSE;
        GLint link_result    = GL_FALSE;

        GLuint vertex_shader   = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

        const GLchar *vertex_source   = t_vertex_source.c_str();
        const GLchar *fragment_source = t_fragment_source.c_str();

        glShaderSource(vertex_shader, 1, &vertex_source, 0);
        glShaderSource(fragment_shader, 1, &fragment_source, 0);

        glCompileShader(vertex_shader);
        glCompileShader(fragment_shader);

        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compile_result);
        if(compile_result == GL_FALSE)
        {
            GLint log_length = 0;
            glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &log_length);

            std::vector<GLchar> log((uint32_t) log_length);
            glGetShaderInfoLog(vertex_shader, log_length,
                               &log_length, &log[0]);
            Log::core_error("Vertex shader compilation failed:\n{0}\n", log.data());

            glDeleteShader(vertex_shader);
            glDeleteShader(fragment_shader);

            return;
        }

        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compile_result);
        if (compile_result == GL_FALSE)
        {
            GLint log_length = 0;
            glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &log_length);

            std::vector<GLchar> log((uint32_t) log_length);
            glGetShaderInfoLog(fragment_shader, log_length,
                               &log_length, &log[0]);
            Log::core_error("Fragment shader compilation failed:\n{0}\n", log.data());

            glDeleteShader(vertex_shader);
            glDeleteShader(fragment_shader);

            return;
        }

        shader_id = glCreateProgram();

        glAttachShader(shader_id, vertex_shader);
        glAttachShader(shader_id, fragment_shader);

        glLinkProgram(shader_id);

        glGetProgramiv(shader_id, GL_LINK_STATUS, (int *)&link_result);
        if (link_result == GL_FALSE)
        {
            GLint log_length = 0;
            glGetProgramiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);

            std::vector<GLchar> log((uint32_t) log_length);
            glGetProgramInfoLog(shader_id, log_length, &log_length, &log[0]);
            Log::core_error("Shader linking failed:\n{0}\n", log.data());

            glDeleteProgram(shader_id);

            glDeleteShader(vertex_shader);
            glDeleteShader(fragment_shader);

            return;
        }

        glDetachShader(shader_id, vertex_shader);
        glDetachShader(shader_id, fragment_shader);
    }

    Shader::~Shader()
    {
        glDeleteProgram(shader_id);
    }

    void Shader::bind() const
    {
        glUseProgram(shader_id);
    }

    void Shader::unbind() const
    {
        glUseProgram(0);
    }
}