#include "Fullbeard/Window/WindowLinux.hpp"

#include "Fullbeard/Events/EventApplication.hpp"

#include "fullbeard_pch.hpp"

namespace Fullbeard
{
    static bool glfw_initialized = false;

    static void glfwErrorCallback(int t_error, const char* t_message)
    {
        Log::core_error("GLFW Error {0}: {1}", t_error, t_message);
    }

    WindowLinux::WindowLinux(const WindowProperties &t_properties)
    {
        init(t_properties);
    }

    WindowLinux::~WindowLinux()
    {
        shutdown();
    }

    Window * Window::create(const WindowProperties &t_properties)
    {
        return new WindowLinux(t_properties);
    }

    void WindowLinux::init(const WindowProperties &t_properties)
    {
        data.title  = t_properties.title;
        data.width  = t_properties.width;
        data.height = t_properties.height;

        Log::core_info("Creating Linux window {0}, {1}x{2}",
                       data.title, data.width, data.height);

        if(!glfw_initialized)
        {
            int result = glfwInit();
            assert(((void) "Could not initialize GLFW", result));
            glfw_initialized = true;

            glfwSetErrorCallback(glfwErrorCallback);
        }

        window = glfwCreateWindow((int) data.width, (int) data.height,
                                  data.title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(window);
        glfwSetWindowUserPointer(window, &data);
        set_vsync(true);

        glfwSetWindowSizeCallback(window, [](GLFWwindow *t_window,
                                             int t_height, int t_width)
        {
            WindowData &data = 
                *(WindowData *) glfwGetWindowUserPointer(t_window);
            data.width  = (uint16_t) t_width;
            data.height = (uint16_t) t_height;

            EventWindowResize event(data.width, data.height);
            data.event_callback(event);
        });

        glfwSetWindowCloseCallback(window, [](GLFWwindow *t_window)
        {
            WindowData &data =
                *(WindowData *) glfwGetWindowUserPointer(t_window);

            EventWindowClose event;
            data.event_callback(event);
        });
    }

	void WindowLinux::set_vsync(const bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		data.vsync = enabled;
	}

	void WindowLinux::on_update()
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void WindowLinux::shutdown()
	{
		glfwDestroyWindow(window);
	}
}