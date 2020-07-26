#include "CylinderBank_pch.hpp"

#include "CylinderBank/Events/EventKey.hpp"

namespace CylinderBank
{
//##############################################################################
// class CylinderBank::EventKey

    EventKey::EventKey(const uint16_t t_keycode):
    keycode(t_keycode)
    { }

    int EventKey::get_category_flags() const
    {
        return EventCategoryInput | EventCategoryKeyboard;
    }

//##############################################################################
// class CylinderBank::EventKeyPressed

    EventKeyPressed::EventKeyPressed(const uint16_t t_keycode,
                                     const bool t_repeated):
    EventKey(t_keycode),
    repeated(t_repeated)
    { }

    std::string EventKeyPressed::to_string() const
    {
        std::stringstream ss;

        ss << "EventKeyPressed: " << keycode
           << (repeated?" (repeat)":" ");

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
// class CylinderBank::EventKeyReleased

    EventKeyReleased::EventKeyReleased(uint16_t t_keycode):
    EventKey(t_keycode)
    { }

    std::string EventKeyReleased::to_string() const
    {
        std::stringstream ss;

        ss << "EventKeyReleased: " << keycode;

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

//##############################################################################
// class CylinderBank::EventKeyTyped

    EventKeyTyped::EventKeyTyped(uint16_t t_keycode):
    EventKey(t_keycode)
    { }

    std::string EventKeyTyped::to_string() const
    {
        std::stringstream ss;

        ss << "EventKeyTyped: " << keycode;

        return ss.str();
    }

    EventType EventKeyTyped::get_event_type() const
    {
        return get_static_type();
    }

    EventType EventKeyTyped::get_static_type()
    {
        return EventType::KeyTyped;
    }
}