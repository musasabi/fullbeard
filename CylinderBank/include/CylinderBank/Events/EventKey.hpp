#ifndef CB_EVENT_KEY_HPP__
#define CB_EVENT_KEY_HPP__

#include "Event.hpp"

#include <cstdint>

namespace CylinderBank
{
    class EventKey : public Event
    {
        public:
            inline  std::uint16_t get_keycode()   const { return keycode; }
            virtual int get_category_flags() const override;

        protected:
            explicit EventKey(const std::uint16_t t_keycode);
            std::uint16_t keycode;
    };

    class EventKeyPressed : public EventKey
    {
        public:
            EventKeyPressed(const std::uint16_t t_keycode, const bool t_repeated);
        	~EventKeyPressed() = default;

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
            explicit EventKeyReleased(const std::uint16_t t_keycode);
        	~EventKeyReleased() = default;

            virtual std::string to_string() const override;
            virtual EventType get_event_type()  const override;
            static  EventType get_static_type();
    };

    class EventKeyTyped : public EventKey
    {
        public:
            explicit EventKeyTyped(const std::uint16_t t_keycode);
        	~EventKeyTyped() = default;

            virtual std::string to_string() const override;
            virtual EventType get_event_type()  const override;
            static  EventType get_static_type();
    };
}

#endif // CB_EVENT_KEY_HPP__
