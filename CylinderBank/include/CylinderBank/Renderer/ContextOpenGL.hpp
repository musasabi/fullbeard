#ifndef CB_CONTEXT_OPENGL_HPP
#define CB_CONTEXT_OPENGL_HPP

#include "Context.hpp"


#include "GLFW/glfw3.h"

namespace CylinderBank
{
    class ContextOpenGL : public Context
    {
        public:
            ContextOpenGL(GLFWwindow *t_window_handle);

            void init() override;
            void swap_buffers() override;

        private:
            GLFWwindow *window_handle;
    };
}

#endif //CB_CONTEXT_OPENGL_HPP
