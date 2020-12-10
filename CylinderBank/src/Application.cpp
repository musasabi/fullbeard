#include "CylinderBank_pch.hpp"

#include "glad/glad.h"

#include "CylinderBank/Systems/Application.hpp"

#include "CylinderBank/Input/Input.hpp"
#include "CylinderBank/CylinderBank.hpp"

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

		glGenVertexArrays(1, &vertex_array);
		glBindVertexArray(vertex_array);

		glGenBuffers(1, &vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &index_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

		unsigned int indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        std::string vertex_source = R"(
            #version 330 core

            layout(location = 0) in vec3 a_position;
            out vec4 v_position;

            void main()
            {
                gl_Position = vec4(a_position, 1.0);
                v_position  = vec4(a_position, 1.0);
            }
        )";

        std::string fragment_source = R"(
            #version 330 core

            layout(location = 0) out vec4 color;
            in vec4 v_position;

            void main()
            {
                color = v_position;
            }
        )";

        shader.reset(new Shader(vertex_source, fragment_source));
    }

    void Application::run()
    {
        running = true;

        while(running)
        {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            shader->bind();

            glBindVertexArray(vertex_array);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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