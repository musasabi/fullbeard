#include "cb_pch.hpp"
#include "glad/glad.h"
#include "cb_util.hpp"

#include "Renderer/GPUBufferOpenGL.hpp"

#include "Renderer/Renderer.hpp"

namespace CylinderBank
{
    VertexBuffer* VertexBuffer::create(const float *t_vertices,
                                       const std::size_t t_size)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::OpenGL:
                return new VertexBufferOpenGL(t_vertices, t_size);

            case RendererAPI::None:
            default:
                CB_ASSERT_CORE(false, "Unknown Renderer API (vertex buffer).");
                return nullptr;
        }
    }

    IndexBuffer* IndexBuffer::create(const float *t_vertices,
                                     const std::size_t t_count)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::OpenGL:
                return new IndexBufferOpenGL(t_vertices, t_count);

            case RendererAPI::None:
            default:
                CB_ASSERT_CORE(false, "Unknown Renderer API (index buffer).");
                return nullptr;
        }
    }
}