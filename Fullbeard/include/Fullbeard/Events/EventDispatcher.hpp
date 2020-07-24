#ifndef FULLBEARD_EVENT_DISPATCHER_HPP__
#define FULLBEARD_EVENT_DISPATCHER_HPP__

#include "Event.hpp"

#include <functional>

namespace Fullbeard
{
    class EventDispatcher
    {
        public:
            EventDispatcher(Event &t_event):
                event(t_event) { }

            template<typename T>
            bool dispatch(std::function<bool(T&)> func)
            {
                if(event.get_event_type() == T::get_static_type())
                {
                    event.handled = func(*(T*) &event);
                    return true;
                }

                return false;
            }

        private:
            Event& event;
    };
}

#endif // FULLBEARD_EVENT_DISPATCHER_HPP__