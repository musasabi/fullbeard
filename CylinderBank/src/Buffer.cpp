#include "CylinderBank_pch.hpp"
#include "glad/glad.h"
#include "CylinderBank/util.hpp"

#include "CylinderBank/Renderer/BufferOpenGL.hpp"

#include "CylinderBank/Renderer/Renderer.hpp"

namespace CylinderBank
{
    VertexBuffer* VertexBuffer::create(const float *t_vertices,
                                       const std::size_t t_size)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::None:
                CB_ASSERT_CORE(false,
                    "No Renderer API selected (vertex buffer).");
                return nullptr;

            case RendererAPI::OpenGL:
                return new VertexBufferOpenGL(t_vertices, t_size);

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
            case RendererAPI::None:
                CB_ASSERT_CORE(false,
                    "No Renderer API selected (index buffer).");
                return nullptr;

            case RendererAPI::OpenGL:
                return new IndexBufferOpenGL(t_vertices, t_count);

            default:
                CB_ASSERT_CORE(false, "Unknown Renderer API (index buffer).");
                return nullptr;
        }
    }
}