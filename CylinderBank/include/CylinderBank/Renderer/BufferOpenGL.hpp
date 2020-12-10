#ifndef CB_BUFFEROPENGL_HPP__
#define CB_BUFFEROPENGL_HPP__

#include "Buffer.hpp"

#include <cstdint>

namespace CylinderBank
{
    class VertexBufferOpenGL : public VertexBuffer
    {
        public:
            VertexBufferOpenGL(const float *t_vertices,
                               const std::size_t t_size);
            ~VertexBufferOpenGL();

            void bind() const override;
            void unbind() const override;

        private:
            std::uint32_t buffer_handle;
    };    

    class IndexBufferOpenGL : public IndexBuffer
    {
        public:
            IndexBufferOpenGL(const float *t_vertices,
                              const std::size_t t_count);
            ~IndexBufferOpenGL();

            void bind() const override;
            void unbind() const override;

        private:
            std::uint32_t buffer_handle;
            std::size_t   count;
    };
}

#endif // CB_BUFFEROPENGL_HPP__