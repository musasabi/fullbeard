#ifndef FULLBEARD_APPLICATION_HPP__
#define FULLBEARD_APPLICATION_HPP__

#include "../Events/EventApplication.hpp"
#include "../Window/Window.hpp"
#include "../Systems/LayerStack.hpp"

namespace Fullbeard
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

            std::unique_ptr<Window> window;
            static Application *instance;
            LayerStack layer_stack;

            bool running = false;
    };
}

#endif // FULLBEARD_APPLICATION_HPP__