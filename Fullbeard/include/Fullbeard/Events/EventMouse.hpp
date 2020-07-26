#ifndef FULLBEARD_EVENT_MOUSE_HPP__
#define FULLBEARD_EVENT_MOUSE_HPP__

#include "Event.hpp"

#include <cstdint>

namespace Fullbeard
{
    class EventMouseMoved : public Event
    {
        public:
            EventMouseMoved(const float t_x_position, const float t_y_position);

            inline float get_x() const { return x_position; }
            inline float get_y() const { return y_position; }

            virtual std::string to_string() const override;
            virtual int get_category_flags() const override;
			virtual EventType get_event_type() const override;
            static  EventType get_static_type();

        private:
            float x_position;
            float y_position;
    };

    class EventMousewheelScrolled : public Event
    {
        public:
            EventMousewheelScrolled(const float t_x_offset,
                                    const float t_y_offset);

            inline float get_x_offset() const { return x_offset; }
            inline float get_y_offset() const { return y_offset; }

            virtual std::string to_string() const override;
            virtual int get_category_flags() const override;
			virtual EventType get_event_type() const override;
            static  EventType get_static_type();

        private:
            float x_offset;
            float y_offset;
    };

    class EventMouseButton : public Event
    {
        public:
            inline  uint16_t get_keycode()   const { return keycode; }
            virtual int get_category_flags() const override;

        protected:
            EventMouseButton(const uint16_t t_keycode);
            uint16_t keycode;
    };

    class EventMouseButtonPressed : public EventMouseButton
    {
        public:
            EventMouseButtonPressed(const uint16_t t_keycode,
                                    const bool t_repeated);

            inline bool is_repeated() const { return repeated; }

            virtual std::string to_string() const override;
            virtual EventType get_event_type()  const override;
            static  EventType get_static_type();

        private:
            bool repeated;
    };

    class EventMouseButtonReleased : public EventMouseButton
    {
        public:
            EventMouseButtonReleased(const uint16_t t_keycode);

            virtual std::string to_string() const override;
            virtual EventType get_event_type()  const override;
            static  EventType get_static_type();
    };
}
#endif // FULLBEARD_EVENT_MOUSE_HPP__