#include "cb_pch.hpp"
#include "cb_util.hpp"

#include "Window/WindowLinux.hpp"

#include "Events/EventApplication.hpp"
#include "Events/EventMouse.hpp"
#include "Events/EventKey.hpp"
#include "Renderer/ContextOpenGL.hpp"

namespace CylinderBank
{
    static bool glfw_initialized = false;

    static void glfwErrorCallback(int t_error, const char* t_message)
    {
        Log::core_error("GLFW Error {0}: {1}", t_error, t_message);
    }

    WindowLinux::WindowLinux(const WindowProperties &t_properties)
    {
        data.title  = t_properties.title;
        data.width  = t_properties.width;
        data.height = t_properties.height;

        Log::core_info("Creating Linux window {0}, {1}x{2}",
                       data.title, data.width, data.height);

        if(!glfw_initialized)
        {
            int result = glfwInit();
            CB_ASSERT_CORE(result, "Could not initialize GLFW");
            glfw_initialized = true;

            glfwSetErrorCallback(glfwErrorCallback);
        }

        window = glfwCreateWindow((int) data.width, (int) data.height,
                                  data.title.c_str(), nullptr, nullptr);

        rendering_context = new ContextOpenGL(window);
        rendering_context->init();

        glfwSetWindowUserPointer(window, &data);
        set_vsync(true);

        glfwSetWindowSizeCallback(window, [](GLFWwindow *t_window,
                                             int t_height, int t_width)
        {
            WindowData *data =
                (WindowData *) glfwGetWindowUserPointer(t_window);
            data->width  = (uint16_t) t_width;
            data->height = (uint16_t) t_height;

            EventWindowResize event(data->width, data->height);
            data->event_callback(event);
        });

        glfwSetWindowCloseCallback(window, [](GLFWwindow *t_window)
        {
            WindowData *data =
                (WindowData *) glfwGetWindowUserPointer(t_window);

            EventWindowClose event;
            data->event_callback(event);
        });

        glfwSetKeyCallback(window, [](GLFWwindow *t_window,
                                      int key, int scancode,
                                      int action, int mods)
        {
            CB_UNUSED(scancode);
            CB_UNUSED(mods);

            WindowData *data =
                (WindowData *) glfwGetWindowUserPointer(t_window);

            switch(action)
            {
                case GLFW_PRESS:
                {
                    EventKeyPressed event((uint16_t) key, false);
                    data->event_callback(event);
                    break;
                }

                case GLFW_RELEASE:
                {
                    EventKeyReleased event((uint16_t) key);
                    data->event_callback(event);
                    break;
                }

                case GLFW_REPEAT:
                {
                    EventKeyPressed event((uint16_t) key, true);
                    data->event_callback(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(window, [](GLFWwindow *t_window, unsigned int t_keycode)
        {
            WindowData *data =
                (WindowData *) glfwGetWindowUserPointer(t_window);

            EventKeyTyped event((uint16_t) t_keycode);
            data->event_callback(event);
        });

        glfwSetMouseButtonCallback(window, [](GLFWwindow *t_window,
                                              int key, int action, int mods)
        {
            CB_UNUSED(mods);

            WindowData *data =
                (WindowData *) glfwGetWindowUserPointer(t_window);

            switch(action)
            {
                case GLFW_PRESS:
                {
                    EventMouseButtonPressed event((uint16_t) key, false);
                    data->event_callback(event);
                    break;
                }

                case GLFW_RELEASE:
                {
                    EventMouseButtonReleased event((uint16_t) key);
                    data->event_callback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(window, [](GLFWwindow *t_window,
                                         double t_x_offset,
                                         double t_y_offset)
        {
            WindowData *data =
                (WindowData *) glfwGetWindowUserPointer(t_window);

            EventMousewheelScrolled event((float) t_x_offset,
                                          (float) t_y_offset);
            data->event_callback(event);
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow *t_window,
                                            double t_x_pos, double t_y_pos)
        {
            WindowData *data =
                (WindowData *) glfwGetWindowUserPointer(t_window);

            EventMouseMoved event((float) t_x_pos, (float) t_y_pos);
            data->event_callback(event);
        });
    }

    WindowLinux::~WindowLinux()
    {
		glfwDestroyWindow(window);
    }

    Window * Window::create(const WindowProperties &t_properties)
    {
        return new WindowLinux(t_properties);
    }


	void WindowLinux::set_vsync(const bool t_enabled)
	{
		if (t_enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		data.vsync = t_enabled;
	}

	void WindowLinux::on_update()
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void WindowLinux::shutdown()
	{
	}
}
