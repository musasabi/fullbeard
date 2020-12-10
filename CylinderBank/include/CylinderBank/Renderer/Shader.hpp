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

            void bind() const;
            void unbind() const;

        private:
            uint32_t shader_id;
    };
}

#endif //CB_SHADER_HPP__