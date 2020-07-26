#ifndef CB_EVENT_HPP__
#define CB_EVENT_HPP__

// to overload << for the purposes of logging
#include <fmt/ostream.h>

#include <string>
#include <functional>

namespace CylinderBank
{
    enum class EventType
    {
        None = 0,
        AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved
    };

    enum EventCategory
    {
        None = 0,
        EventCategoryApplication = 1 << 0,
        EventCategoryInput       = 1 << 1,
        EventCategoryKeyboard    = 1 << 2,
        EventCategoryMouse       = 1 << 3,
        EventCategoryMouseButton = 1 << 4,
        EventCategoryMouseWheel  = 1 << 5
    };

    class Event
    {
        friend class EventDispatcher;

        public:
            virtual std::string to_string()    const = 0;
            virtual int get_category_flags()   const = 0;
            virtual EventType get_event_type() const = 0;

            inline bool is_in_category(const EventCategory t_category) const
            {
                return get_category_flags() & t_category;
            }

            bool handled = false;
    };

    inline std::ostream& operator<<(std::ostream& t_ostream,
                                    const Event& t_event)
    {
        return t_ostream << t_event.to_string();
    }

    class EventDispatcher
    {
        public:
            EventDispatcher(Event &t_event):
                event(t_event) { }

            template<typename T>
            bool dispatch(std::function<bool(T&)> t_func)
            {
                if(event.get_event_type() == T::get_static_type())
                {
                    event.handled = t_func(*(T*) &event);
                    return true;
                }

                return false;
            }

        private:
            Event& event;
    };
}
#endif // CB_EVENT_HPP__