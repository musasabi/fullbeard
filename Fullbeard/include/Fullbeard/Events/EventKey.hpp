#ifndef FULLBEARD_EVENT_KEY_HPP__
#define FULLBEARD_EVENT_KEY_HPP__

#include "Event.hpp"

#include <cstdint>

namespace Fullbeard
{
    class EventKey : public Event
    {
        public:
            inline  uint16_t get_keycode()   const { return keycode; }
            virtual int get_category_flags() const override;

        protected:
            EventKey(const uint16_t t_keycode);
            uint16_t keycode;
    };

    class EventKeyPressed : public EventKey
    {
        public:
            EventKeyPressed(const uint16_t t_keycode, const bool t_repeated);

            inline bool is_repeated() const { return repeated; }

            virtual std::string to_string() const override;
            virtual EventType get_event_type()  const override;
            static  EventType get_static_type();

        private:
            bool repeated;
    };

    class EventKeyReleased : public EventKey
    {
        public:
            EventKeyReleased(const uint16_t t_keycode);

            virtual std::string to_string() const override;
            virtual EventType get_event_type()  const override;
            static  EventType get_static_type();
    };

    class EventKeyTyped : public EventKey
    {
        public:
            EventKeyTyped(const uint16_t t_keycode);

            virtual std::string to_string() const override;
            virtual EventType get_event_type()  const override;
            static  EventType get_static_type();
    };
}

#endif // FULLBEARD_EVENT_KEY_HPP__