#ifndef CB_GPU_BUFFER_HPP__
#define CB_GPU_BUFFER_HPP__

/**
 * @file GPUBuffer.hpp
 * @brief Contains the abstract and helper classes for shader buffers.
 *
 * The base classes (VertexBuffer and IndexBuffer) both make use of the other
 * structs and classes in this file to automate and abstract away the nitty
 * gritty of the rendering API.
 */

#include "../cb_util.hpp"

#include <cstddef>
#include <string>

namespace CylinderBank
{
    /**
     * @brief Useful in ranslating between Float3 and vec3, for example.
     */
    enum class ShaderDataType
    {
        None,
        Float, Float2, Float3, Float4,
    };

    /**
     * @brief Provide the size of the given ShaderDataType
     * @param t_type Type of shader data to query.
     * @return Size of shader data type, or zero on error.
     */
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

    /**
     * @brief Describes one element of a buffer.
     */
    struct BufferElement
    {
        ShaderDataType type;       ///< Type of data within the element
        std::string    name;       ///< Name of the element.
        std::size_t    size;       ///< Size of the element.
        std::size_t    offset;     ///< Distance from zero to the element
        bool           normalized; ///< Is the element normalized?

        BufferElement() = delete;
        /**
         * @param t_type The data type of the buffer element.
         * @param t_name The name corresponding with the shader source.
         * @param t_normalized
         *     Whether the data is normalized; defautls to false.
         */
        BufferElement(const ShaderDataType t_type,
                      const std::string   &t_name,
                      const bool           t_normalized = false):
            type(t_type),
            name(t_name),
            size(sizeof_ShaderDataType(t_type)),
            offset(0),
            normalized(t_normalized)
        { }

        /**
         * @return Number of components within the element.
         */
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

    /**
     * @class BufferLayout
     * @brief Describes the arrangement of the buffer in memory.
     */
    class BufferLayout
    {
        public:
            BufferLayout() = default;
            /**
             * @param t_elements The elements to hold in this buffer.
             */
            BufferLayout(
                const std::initializer_list<BufferElement> &t_elements):
                elements(t_elements),
                stride(0)
            {
                calculate_offsets_and_stride();
            }

            /**
             * @return The stride of the data.
             */
            std::size_t get_stride() const { return stride; }

            /**
             * @return The beginning of the elements vector.
             */
            std::vector<BufferElement>::const_iterator begin() const
            {
                return elements.begin();
            }
            /**
             * @return The end of the elements vector.
             */
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

    /**
     * @class VertexBuffer
     * @brief Abstract base class for vertex buffers
     */
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

    /**
     * @class IndexBuffer
     * @brief Abstract base class for indexBuffers buffers
     */class IndexBuffer
    {
        public:
            virtual ~IndexBuffer() { }

            virtual void bind()   const = 0;
            virtual void unbind() const = 0;

            static IndexBuffer* create(const float *,      // indicies
                                       const std::size_t); // count
    };
}

#endif // CB_GPU_BUFFER_HPP__