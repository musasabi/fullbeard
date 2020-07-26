#ifndef CB_WINDOW_LINUX_HPP__
#define CB_WINDOW_LINUX_HPP__

#include "Window.hpp"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace CylinderBank
{
    struct WindowData
    {
        std::string title;
        uint16_t width;
        uint16_t height;
        bool vsync;

        std::function<void(Event &)> event_callback;
    };

    class WindowLinux : public Window
    {
        public:
            WindowLinux(const WindowProperties &t_properties);
            virtual ~WindowLinux();

            inline virtual uint16_t get_width() const override
            {
                return data.width;
            };
            inline virtual uint16_t get_height() const override
            {
                return data.height;
            };
            inline virtual bool get_vsync() const override
            {
                return data.vsync;
            };

            void virtual set_vsync(const bool t_enabled) override;

            inline virtual void set_event_callback(
                const std::function<void(Event &)> t_callback) override
                {
                    data.event_callback = t_callback;
                }

            void virtual on_update() override;

        private:
            GLFWwindow *window;
            WindowData data;

            virtual void init(const WindowProperties &t_properties);
            virtual void shutdown();
    };
}

#endif // CB_WINDOW_LINUX_HPP__