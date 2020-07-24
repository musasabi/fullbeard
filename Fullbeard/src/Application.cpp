#include "Fullbeard/Systems/Application.hpp"

#include "Fullbeard/util.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#include "fullbeard_pch.hpp"

namespace Fullbeard
{
    Application::Application()
    {
        window = std::unique_ptr<Window>(Window::create());
        window->set_event_callback(std::bind(&Application::on_event,
                                   this,
                                   std::placeholders::_1));
    }

    Application::~Application()
    { }

    void Application::run()
    {
        running = true;

        GLfloat background_color[] = { 0.2f, 0.3f, 0.3f, 1.0f };

        while(running)
        {
            glClearColor(background_color[0], background_color[1],
                        background_color[2], background_color[3]);
            glClear(GL_COLOR_BUFFER_BIT);

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin("Properties!", nullptr, ImGuiWindowFlags_NoCollapse);

            ImGui::ColorEdit4("Background Color", background_color);

            ImGui::End();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            for(Layer *layer : layer_stack)
            {
                layer->on_update();
            }

            window->on_update();
        }
    }

    void Application::on_event(Event &t_event)
    {
        Log::core_trace("{0}", t_event);
        EventDispatcher dispatcher(t_event);
        dispatcher.dispatch<EventWindowClose>(
            std::bind(&Application::on_window_close,
                      this,
                      std::placeholders::_1));

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
    }

    void Application::push_overlay(Layer *t_overlay)
    {
        layer_stack.push_overlay(t_overlay);
    }

    bool Application::on_window_close(EventWindowClose &t_event)
    {
        UNUSED(t_event);
        running = false;
        return true;
    }
}