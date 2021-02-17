#ifndef CB_RENDERER_HPP__
#define CB_RENDERER_HPP__

namespace CylinderBank
{
    enum class RendererAPI
    {
        None,
        OpenGL
    };

    class Renderer
    {
        public:
            inline static RendererAPI GetAPI() { return api; }
            void temp();

        private:
            static RendererAPI api;
    };
}

#endif // CB_RENDERER_HPP__