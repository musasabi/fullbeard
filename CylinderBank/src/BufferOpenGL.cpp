#include "CylinderBank_pch.hpp"
#include "glad/glad.h"
#include "util.hpp"

#include "Renderer/BufferOpenGL.hpp"

namespace CylinderBank
{
    VertexBufferOpenGL::VertexBufferOpenGL(const float *t_vertices,
                                           const std::size_t t_size)
    {
		glGenBuffers(1, &buffer_handle);
		glBindBuffer(GL_ARRAY_BUFFER, buffer_handle);
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr) t_size,
                     t_vertices, GL_STATIC_DRAW);
    }

    VertexBufferOpenGL::~VertexBufferOpenGL()
    {
        glDeleteBuffers(1, &buffer_handle);
    }

    void VertexBufferOpenGL::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, buffer_handle);
    }

    void VertexBufferOpenGL::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBufferOpenGL::set_layout(const BufferLayout& t_layout)
    {
        layout = t_layout;
    }

    const BufferLayout& VertexBufferOpenGL::get_layout() const
    {
        return layout;
    }

    IndexBufferOpenGL::IndexBufferOpenGL(const float *t_vertices,
                                         const std::size_t t_count)
    {
        CB_UNUSED(t_vertices);
        CB_UNUSED(t_count);
    }

    IndexBufferOpenGL::~IndexBufferOpenGL()
    {
        glDeleteBuffers(1, &buffer_handle);
    }

    void IndexBufferOpenGL::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, buffer_handle);
    }

    void IndexBufferOpenGL::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}