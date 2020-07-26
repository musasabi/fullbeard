#include "CylinderBank_pch.hpp"

#include "CylinderBank/Systems/Application.hpp"

#include "CylinderBank/util.hpp"
#include "CylinderBank/Input/Input.hpp"

#include <GLFW/glfw3.h>

namespace CylinderBank
{
    Application * Application::instance = nullptr;

    Application::Application()
    {
        CB_ASSERT_CORE(instance == nullptr,
                      "Only one application instance allowed.");
        instance = this;
        window = std::unique_ptr<Window>(Window::create());
        window->set_event_callback(CB_BIND_EVENT_FN(Application::on_event));

        layer_imgui = new LayerImGUI();
        push_overlay(layer_imgui);
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

            for(Layer *layer : layer_stack)
            {
                layer->on_update();
            }

            // why are we going through the whole layer stack twice?
            layer_imgui->begin_render();
            for(Layer *layer : layer_stack)
            {
                layer->imgui_draw();
            }
            layer_imgui->complete_render();

            window->on_update();
        }
    }

    void Application::on_event(Event &t_event)
    {
        EventDispatcher dispatcher(t_event);
        dispatcher.dispatch<EventWindowClose>(
            CB_BIND_EVENT_FN(Application::on_window_close));

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
        CB_UNUSED(t_event);
        running = false;
        return true;
    }
}