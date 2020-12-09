#include <glad/glad.h>

#include "CylinderBank/Renderer/ContextOpenGL.hpp"

#include "CylinderBank/util.hpp"

namespace CylinderBank
{
    static bool glad_initialized = false;

    ContextOpenGL::ContextOpenGL(GLFWwindow *t_window_handle):
        window_handle(t_window_handle)
    {
        CB_ASSERT_CORE(window_handle, "OpenGL window handle is null!");
    }

    void ContextOpenGL::init()
    {
        glfwMakeContextCurrent(window_handle);

        if(!glad_initialized)
        {
            int result = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
            CB_ASSERT_CORE(result, "Could not initialize glad");
            glad_initialized = true;
        }

        Log::core_info("OpenGL v{0}.{1}", GLVersion.major, GLVersion.minor);
        Log::core_info("Renderer: {0}", glGetString(GL_RENDERER));
        Log::core_info("Windowing: GLFW v{0}", glfwGetVersionString());
    }

    void ContextOpenGL::swap_buffers()
    {

    }
}