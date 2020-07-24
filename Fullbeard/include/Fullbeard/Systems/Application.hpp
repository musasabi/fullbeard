#ifndef FULLBEARD_APPLICATION_HPP__
#define FULLBEARD_APPLICATION_HPP__

#include "../Events/EventApplication.hpp"
#include "../Window/Window.hpp"

namespace Fullbeard
{
    class Application
    {
        public:
            Application();
            virtual ~Application();

            void run();

            void on_event(Event &t_event);

        private:
            bool on_window_close(EventWindowClose &t_event);

            std::unique_ptr<Window> window;
            bool running = false;
    };
}

#endif // FULLBEARD_APPLICATION_HPP__