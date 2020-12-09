#ifndef CB_APPLICATION_HPP__
#define CB_APPLICATION_HPP__

#include "../Events/EventApplication.hpp"
#include "../Window/Window.hpp"
#include "../Systems/LayerStack.hpp"
#include "../Layers/LayerImGUI.hpp"

#include "GLFW/glfw3.h"

namespace CylinderBank
{
    class Application
    {
        public:
            Application();
            virtual ~Application();

            void run();

            void on_event(Event &t_event);

            void push_layer(Layer *t_layer);
            void push_overlay(Layer *t_overlay);

            inline Window & get_window() const { return *window; }
            inline static Application & get_instance() { return *instance; }

        private:
            bool on_window_close(EventWindowClose &t_event);

            static Application *instance;
            std::unique_ptr<Window> window;
            LayerStack layer_stack;
            LayerImGUI *layer_imgui;

            bool running = false;

            GLuint vertex_array;
            GLuint vertex_buffer;
            GLuint index_buffer;
    };
}

#endif // CB_APPLICATION_HPP__