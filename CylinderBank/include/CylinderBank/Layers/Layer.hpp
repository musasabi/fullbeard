#ifndef CB_LAYER_HPP__
#define CB_LAYER_HPP__

#include "../Events/Event.hpp"
#include "../util.hpp"

#include <string>

namespace CylinderBank
{
    class Layer
    {
        public:
            Layer(const std::string &t_name = "Layer"):
            debug_name(t_name)
            { }
            virtual ~Layer() { }

            virtual void on_push() { };
            virtual void on_pop() { };
            virtual void on_update() { };

            virtual void on_event(Event &t_event)
            {
                CB_UNUSED(t_event);
            };

            virtual void imgui_draw() { };

            inline const std::string& get_name() const
            {
                return debug_name;
            }

        protected:
            std::string debug_name;
    };
}

#endif // CB_LAYER_HPP__