#ifndef CB_BUFFER_HPP__
#define CB_BUFFER_HPP__

#include "../cb_util.hpp"

#include <cstddef>
#include <string>

namespace CylinderBank
{
    enum class ShaderDataType
    {
        None,
        Float, Float2, Float3, Float4
    };

    static std::size_t sizeof_ShaderDataType(const ShaderDataType t_type)
    {
        switch(t_type)
        {
            case ShaderDataType::Float : return sizeof(float) * 1;
            case ShaderDataType::Float2: return sizeof(float) * 2;
            case ShaderDataType::Float3: return sizeof(float) * 3;
            case ShaderDataType::Float4: return sizeof(float) * 4;
            case ShaderDataType::None:
            default:
            {
                CB_ASSERT_CORE(false, "Unknown ShaderDataType while "
                                      "getting size of type.");
                return 0;
            }
        }
    }

    struct BufferElement
    {
        ShaderDataType type;
        std::string    name;
        std::size_t    size;
        std::size_t    offset;
        bool           normalized;

        BufferElement() = delete;
        BufferElement(ShaderDataType t_type,
                      std::string    t_name,
                      bool           t_normalized = false):
            type(t_type),
            name(t_name),
            size(sizeof_ShaderDataType(t_type)),
            offset(0),
            normalized(t_normalized)
        { }

        std::uint32_t get_component_count() const
        {
            switch(type)
            {
                case ShaderDataType::Float : return 1;
                case ShaderDataType::Float2: return 2;
                case ShaderDataType::Float3: return 3;
                case ShaderDataType::Float4: return 4;
                case ShaderDataType::None:
                default:
                {
                    CB_ASSERT_CORE(false, "Unknown ShaderDataType while "
                                          "getting component count.");
                    return 0;
                }
            }
        }

    };

    class BufferLayout
    {
        public:
            BufferLayout() = default;
            BufferLayout(const std::initializer_list<BufferElement>
                           &t_elements):
                elements(t_elements),
                stride(0)
            {
                calculate_offsets_and_stride();
            }

            std::size_t get_stride() const { return stride; }

            std::vector<BufferElement>::const_iterator begin() const
            {
                return elements.begin();
            }
            std::vector<BufferElement>::const_iterator end() const
            {
                return elements.end();
            }

        private:
            void calculate_offsets_and_stride()
            {
                std::size_t offset = 0;
                stride = 0;

                for(auto & element : elements)
                {
                    element.offset = offset;
                    offset += element.size;
                    stride += element.size;
                }
            }

            std::vector<BufferElement> elements;
            std::size_t stride;
    };

    class VertexBuffer
    {
        public:
            virtual ~VertexBuffer() { }

            virtual void bind()   const = 0;
            virtual void unbind() const = 0;

            virtual void set_layout(const BufferLayout&) = 0;
            virtual const BufferLayout& get_layout() const = 0;

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