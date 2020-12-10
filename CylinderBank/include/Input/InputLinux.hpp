#ifndef CB_INPUT_LINUX__
#define CB_INPUT_LINUX__

#include "Input.hpp"

namespace CylinderBank
{
    class InputLinux : public Input
    {
        public:
	        InputLinux()  = default;
	        
            virtual bool is_key_pressed_imp(uint16_t t_keycode) override;
            virtual bool is_mouse_button_pressed_imp(uint16_t t_button) override;
            virtual std::pair<float, float> get_mouse_position_imp() override;
    };
}

#endif // CB_INPUT_LINUX__
