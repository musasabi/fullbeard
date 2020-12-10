#include "CylinderBank_pch.hpp"
#include "glad/glad.h"
#include "CylinderBank.hpp"

#include "Systems/Application.hpp"

#include "Input/Input.hpp"

namespace CylinderBank
{
    Application * Application::instance = nullptr;

    static GLenum shader_data_type_to_GL_type(ShaderDataType t_type)
    {
        switch(t_type)
        {
            case ShaderDataType::Float : return GL_FLOAT;
            case ShaderDataType::Float2: return GL_FLOAT;
            case ShaderDataType::Float3: return GL_FLOAT;
            case ShaderDataType::Float4: return GL_FLOAT;
            case ShaderDataType::None:
            default:
            {
                CB_ASSERT_CORE(false, "Unknown ShaderDataType while "
                                        "getting component count.");
                return GL_FALSE;
            }
        }
    }

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

        float vertices[3 * (3 + 4)] =
        {
            // x      y     z     r     g     b     a
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.3f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.8f, 0.3f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f
		};

        vertex_buffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));
        {
            BufferLayout layout = {
                { ShaderDataType::Float3, "a_position" },
                { ShaderDataType::Float4, "a_color" },
            };
            vertex_buffer->set_layout(layout);
        }

        std::uint32_t index = 0;
        for(const auto &element : vertex_buffer->get_layout())
        {
            glEnableVertexAttribArray(index);

            glVertexAttribPointer(
                index,
                (GLint) element.get_component_count(),
                shader_data_type_to_GL_type(element.type),
                element.normalized ? GL_TRUE : GL_FALSE,
                (GLint) vertex_buffer->get_layout().get_stride(),
                (const void *) element.offset
            );

            index++;
        }

		glGenBuffers(1, &index_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

		unsigned int indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     sizeof(indices),
                     indices,
                     GL_STATIC_DRAW);

        std::string vertex_source = R"(
			#version 330 core

			layout(location = 0) in vec3 a_position;
			layout(location = 1) in vec4 a_color;

			out vec4 v_color;

			void main()
			{
				gl_Position = vec4(a_position, 1.0);
				v_color = a_color;
			}
        )";

        std::string fragment_source = R"(
            #version 330 core

            layout(location = 0) out vec4 color;
            in vec4 v_color;

            void main()
            {
                color = v_color;
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