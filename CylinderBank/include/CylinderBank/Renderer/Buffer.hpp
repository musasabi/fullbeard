#ifndef CB_BUFFER_HPP__
#define CB_BUFFER_HPP__

#include <cstddef>

namespace CylinderBank
{
    class VertexBuffer
    {
        public:
            virtual ~VertexBuffer() { }

            virtual void bind()   const = 0;
            virtual void unbind() const = 0;

            static VertexBuffer* create(const float *,      // verticies
                                        const std::size_t); // size
    };

    class IndexBuffer
    {
        public:
            virtual ~IndexBuffer() { }

            virtual void bind()   const = 0;
            virtual void unbind() const = 0;

            static IndexBuffer* create(const float *,      // indicies
                                       const std::size_t); // count
    };
}

#endif // CB_BUFFER_HPP__