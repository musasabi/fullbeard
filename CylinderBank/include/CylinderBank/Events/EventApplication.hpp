#ifndef CB_EVENT_APP_HPP__
#define CB_EVENT_APP_HPP__

#include "Event.hpp"

#include <cstdint>

namespace CylinderBank
{
    class EventWindowResize : public Event
    {
        public:
            EventWindowResize(const std::uint16_t t_width,
                              const std::uint16_t t_height);
        	~EventWindowResize() = default;
        	
        	EventWindowResize(const EventWindowResize &) = default;
        	EventWindowResize(EventWindowResize &&)      = default;
        	
        	EventWindowResize& operator=(const EventWindowResize &) = default;
        	EventWindowResize& operator=(EventWindowResize &&)      = default;

            inline std::uint16_t get_width()  const { return width;  }
            inline std::uint16_t get_height() const { return height; }

            virtual std::string to_string() const override;
            virtual int get_category_flags() const override;
			virtual EventType get_event_type() const override;
            static  EventType get_static_type();

        private:
            std::uint16_t width;
            std::uint16_t height;
    };

	class EventWindowClose : public Event
	{
        public:
            EventWindowClose()  = default;

            virtual std::string to_string() const override;
            virtual int get_category_flags() const override;
			virtual EventType get_event_type() const override;
            static  EventType get_static_type();
	};

	class EventApplicationTick : public Event
	{
        public:
            EventApplicationTick()  = default;

            virtual int get_category_flags() const override;
			virtual EventType get_event_type() const override;
            static  EventType get_static_type();
	};

	class EventApplicationUpdate : public Event
	{
        public:
            EventApplicationUpdate()  = default;

            virtual int get_category_flags() const override;
			virtual EventType get_event_type() const override;
            static  EventType get_static_type();
	};

	class EventApplicationRender : public Event
	{
        public:
            EventApplicationRender()  = default;

            virtual int get_category_flags() const override;
			virtual EventType get_event_type() const override;
            static  EventType get_static_type();
	};
}

#endif // CB_EVENT_WINDOW_RESIZE_HPP__
