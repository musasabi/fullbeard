#ifndef CB_INPUT_HPP__
#define CB_INPUT_HPP__

#include <cstdint>
#include <utility>

namespace CylinderBank
{
    class Input
    {
        public:
	        
            inline static bool is_key_pressed(uint16_t t_keycode)
            {
                return instance->is_key_pressed_imp(t_keycode);
            }

            inline static bool is_mouse_button_pressed(uint16_t t_keycode)
            {
                return instance->is_mouse_button_pressed_imp(t_keycode);
            }

            inline static std::pair<float, float> get_mouse_position()
            {
                return instance->get_mouse_position_imp();
            }

        protected:
	        Input()  = default;

            virtual bool is_key_pressed_imp(uint16_t t_keycode) = 0;
            virtual bool is_mouse_button_pressed_imp(uint16_t t_button) = 0;
            virtual std::pair<float, float> get_mouse_position_imp() = 0;

        private:
            static Input* instance;
    };
}

#endif // CB_INPUT_HPP__
