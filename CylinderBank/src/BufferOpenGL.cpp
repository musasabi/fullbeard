#include "cb_pch.hpp"
#include "glad/glad.h"
#include "cb_util.hpp"

#include "Renderer/BufferOpenGL.hpp"

namespace CylinderBank
{
//##############################################################################
// class CylinderBank::VertexBufferOpenGL

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

//##############################################################################
// class IndexBufferOpenGL::VertexBufferOpenGL

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