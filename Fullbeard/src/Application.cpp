#include "Fullbeard/Systems/Application.hpp"

#include "Fullbeard/util.hpp"
#include "fullbeard_pch.hpp"

#include <GLFW/glfw3.h>

namespace Fullbeard
{
    Application::Application()
    {
        window = std::unique_ptr<Window>(Window::create());
        window->set_event_callback(std::bind(&Application::on_event, this, std::placeholders::_1));
    }

    Application::~Application()
    { }

    void Application::run()
    {
        running = true;

        while(running)
        {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            window->on_update();
        }
    }

    void Application::on_event(Event &t_event)
    {
        Log::core_trace("{0}", t_event);
        EventDispatcher dispatcher(t_event);
        dispatcher.dispatch<EventWindowClose>(std::bind(&Application::on_window_close, this, std::placeholders::_1));
    }

    bool Application::on_window_close(EventWindowClose &t_event)
    {
        UNUSED(t_event);
        running = false;
        return true;
    }
}