#include "Fullbeard/Events/EventKey.hpp"

#include "fullbeard_pch.hpp"

namespace Fullbeard
{
//##############################################################################
// class Fullbeard::EventKey

    EventKey::EventKey(const uint16_t t_keycode):
    keycode(t_keycode)
    { }

    int EventKey::get_category_flags() const
    {
        return EventCategoryInput | EventCategoryKeyboard;
    }

//##############################################################################
// class Fullbeard::EventKeyPressed

    EventKeyPressed::EventKeyPressed(const uint16_t t_keycode,
                                     const bool t_repeated):
    EventKey(t_keycode),
    repeated(t_repeated)
    { }

    std::string EventKeyPressed::to_string() const
    {
        std::stringstream ss;

        ss << "EventKeyPressed: " << keycode
           << (repeated?" (repeat)":" ") << std::endl;

        return ss.str();
    }

    EventType EventKeyPressed::get_event_type() const
    {
        return get_static_type();
    }

    EventType EventKeyPressed::get_static_type()
    {
        return EventType::KeyPressed;
    }

//##############################################################################
// class Fullbeard::EventKeyReleased

    EventKeyReleased::EventKeyReleased(uint16_t t_keycode):
    EventKey(t_keycode)
    { }

    std::string EventKeyReleased::to_string() const
    {
        std::stringstream ss;

        ss << "EventKeyReleased: " << keycode << std::endl;

        return ss.str();
    }

    EventType EventKeyReleased::get_event_type() const
    {
        return get_static_type();
    }

    EventType EventKeyReleased::get_static_type()
    {
        return EventType::KeyReleased;
    }
}