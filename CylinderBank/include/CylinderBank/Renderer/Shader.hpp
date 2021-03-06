#ifndef CB_SHADER_HPP__
#define CB_SHADER_HPP__

#include <string>

namespace CylinderBank
{
    class Shader
    {
        public:
            Shader(const std::string &t_vertex_source,
                   const std::string &t_fragment_source);
            ~Shader();

            Shader(const Shader&) = delete;
            Shader(Shader&&)      = default;

            Shader& operator=(const Shader&) = delete;
            Shader& operator=(Shader&&)      = default;

            void bind() const;
            void unbind() const;

        private:
            std::uint32_t shader_id;
    };
}

#endif //CB_SHADER_HPP__