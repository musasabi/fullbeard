#include "Fullbeard/Systems/Application.hpp"

#include "Fullbeard/util.hpp"

#include <GLFW/glfw3.h>

#include "fullbeard_pch.hpp"

namespace Fullbeard
{
    Application * Application::instance = nullptr;

    Application::Application()
    {
        ASSERT_CORE__(instance == nullptr,
                      "Only one application instance allowed.");
        instance = this;
        window = std::unique_ptr<Window>(Window::create());
        window->set_event_callback(BIND_EVENT_FN__(Application::on_event));
    }

    Application::~Application()
    { }

    void Application::run()
    {
        running = true;

        // GLfloat background_color[] = { 0.2f, 0.3f, 0.3f, 1.0f };

        while(running)
        {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            for(Layer *layer : layer_stack)
            {
                layer->on_update();
            }

            window->on_update();
        }
    }

    void Application::on_event(Event &t_event)
    {
        EventDispatcher dispatcher(t_event);
        dispatcher.dispatch<EventWindowClose>(
            BIND_EVENT_FN__(Application::on_window_close));

        for(rev_layer_iter layer = layer_stack.rbegin();
            layer != layer_stack.rend();
            layer++)
        {
            (*layer)->on_event(t_event);
            
            if(t_event.handled)
            {
                break;
            }
        }
    }

    void Application::push_layer(Layer *t_layer)
    {
        layer_stack.push_layer(t_layer);
        t_layer->on_push();
    }

    void Application::push_overlay(Layer *t_overlay)
    {
        layer_stack.push_overlay(t_overlay);
        t_overlay->on_push();
    }

    bool Application::on_window_close(EventWindowClose &t_event)
    {
        UNUSED__(t_event);
        running = false;
        return true;
    }
}