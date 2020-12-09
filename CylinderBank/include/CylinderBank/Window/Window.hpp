#ifndef CB_WINDOW_HPP__
#define CB_WINDOW_HPP__

#include "../Events/Event.hpp"

#include <cstdint>

namespace CylinderBank
{
    struct WindowProperties
    {
        std::string title;
        uint16_t width;
        uint16_t height;

        WindowProperties(const std::string &t_title = "CylinderBank",
                         const uint16_t t_width  = 1920,
                         const uint16_t t_height = 1080):
        title(t_title), width(t_width), height(t_height)
        { }
    };

    class Window
    {
        public:
            virtual void on_update() = 0;

            virtual uint16_t get_width()  const = 0;
            virtual uint16_t get_height() const = 0;
            virtual bool     get_vsync()  const = 0;
            virtual void *   get_native_window() const = 0;

            virtual void set_vsync(const bool t_enabled) = 0;
            virtual void set_event_callback(
                const std::function<void(Event &)> t_callback) = 0;

            static Window* create(const WindowProperties &t_properties =
                                    WindowProperties());
                                    
        protected:
        	Window() = default;
    };
}

#endif // CB_WINDOW_HPP__
