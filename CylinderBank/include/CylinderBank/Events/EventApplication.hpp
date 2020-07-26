#ifndef CB_EVENT_APP_HPP__
#define CB_EVENT_APP_HPP__

#include "Event.hpp"

#include <cstdint>

namespace CylinderBank
{
    class EventWindowResize : public Event
    {
        public:
            EventWindowResize(const uint16_t t_width, const uint16_t t_height);

            inline uint16_t get_width()  const { return width;  }
            inline uint16_t get_height() const { return height; }

            virtual std::string to_string() const override;
            virtual int get_category_flags() const override;
			virtual EventType get_event_type() const override;
            static  EventType get_static_type();

        private:
            uint16_t width;
            uint16_t height;
    };

	class EventWindowClose : public Event
	{
        public:
            EventWindowClose();

            virtual std::string to_string() const override;
            virtual int get_category_flags() const override;
			virtual EventType get_event_type() const override;
            static  EventType get_static_type();
	};

	class EventApplicationTick : public Event
	{
        public:
            EventApplicationTick();

            virtual int get_category_flags() const override;
			virtual EventType get_event_type() const override;
            static  EventType get_static_type();
	};

	class EventApplicationUpdate : public Event
	{
        public:
            EventApplicationUpdate();

            virtual int get_category_flags() const override;
			virtual EventType get_event_type() const override;
            static  EventType get_static_type();
	};

	class EventApplicationRender : public Event
	{
        public:
            EventApplicationRender();

            virtual int get_category_flags() const override;
			virtual EventType get_event_type() const override;
            static  EventType get_static_type();
	};
}

#endif // CB_EVENT_WINDOW_RESIZE_HPP__