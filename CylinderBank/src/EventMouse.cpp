#include "CylinderBank/Events/EventMouse.hpp"

#include "CylinderBank_pch.hpp"

namespace CylinderBank
{
//##############################################################################
// class CylinderBank::EventMouseMoved

    EventMouseMoved::EventMouseMoved(const float t_x_position,
                                     const float t_y_position):
    x_position(t_x_position), y_position(t_y_position)
    { }

    std::string EventMouseMoved::to_string() const
    {
        std::stringstream ss;
        ss << "EventMouseMoved: " << x_position << "x" << y_position;
        return ss.str();
    }

    int EventMouseMoved::get_category_flags() const
    {
        return EventCategoryInput | EventCategoryMouse;
    }

    EventType EventMouseMoved::get_event_type() const
    {
        return get_static_type();
    }

    EventType EventMouseMoved::get_static_type()
    {
        return EventType::MouseMoved;
    }

//##############################################################################
// class CylinderBank::EventMousewheelScrolled

    EventMousewheelScrolled::EventMousewheelScrolled(const float t_x_offset,
                                                     const float t_y_offset):
    x_offset(t_x_offset), y_offset(t_y_offset)
    { }

    std::string EventMousewheelScrolled::to_string() const
    {
        std::stringstream ss;
        ss << "EventMousewheelScrolled: " << x_offset << "x" << y_offset;
        return ss.str();
    }

    int EventMousewheelScrolled::get_category_flags() const
    {
        return EventCategoryInput | EventCategoryMouse;
    }

    EventType EventMousewheelScrolled::get_event_type() const
    {
        return get_static_type();
    }

    EventType EventMousewheelScrolled::get_static_type()
    {
        return EventType::MouseScrolled;
    }

//##############################################################################
// class CylinderBank::EventMouseButton

    EventMouseButton::EventMouseButton(const uint16_t t_keycode):
    keycode(t_keycode)
    { }

    int EventMouseButton::get_category_flags() const
    {
        return EventCategoryInput | EventCategoryMouseButton;
    }

//##############################################################################
// class CylinderBank::EventMouseButtonPressed

    EventMouseButtonPressed::EventMouseButtonPressed(const uint16_t t_keycode,
                                                     const bool t_repeated):
    EventMouseButton(t_keycode),
    repeated(t_repeated)
    { }

    std::string EventMouseButtonPressed::to_string() const
    {
        std::stringstream ss;

        ss << "EventMouseButtonPressed: " << keycode
           << (repeated?" (repeat)":" ");

        return ss.str();
    }

    EventType EventMouseButtonPressed::get_event_type() const
    {
        return get_static_type();
    }

    EventType EventMouseButtonPressed::get_static_type()
    {
        return EventType::MouseButtonPressed;
    }

//##############################################################################
// class CylinderBank::EventMouseButtonReleased

    EventMouseButtonReleased::EventMouseButtonReleased(const uint16_t t_keycode):
    EventMouseButton(t_keycode)
    { }

    std::string EventMouseButtonReleased::to_string() const
    {
        std::stringstream ss;

        ss << "EventMouseButtonReleased: " << keycode;

        return ss.str();
    }

    EventType EventMouseButtonReleased::get_event_type() const
    {
        return get_static_type();
    }

    EventType EventMouseButtonReleased::get_static_type()
    {
        return EventType::MouseButtonReleased;
    }
}