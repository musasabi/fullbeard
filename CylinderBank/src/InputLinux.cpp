#include "CylinderBank/Input/InputLinux.hpp"

#include "CylinderBank/Systems/Application.hpp"
#include "CylinderBank/util.hpp"

#include <GLFW/glfw3.h>

#include "CylinderBank_pch.hpp"

namespace CylinderBank
{
    Input * Input::instance = new InputLinux();

    GLFWwindow * get_window()
    {
        return static_cast<GLFWwindow *>(Application::get_instance().
                                                      get_window ().
                                                      get_native_window());
    }

    bool InputLinux::is_key_pressed_imp(uint16_t t_keycode) 
    {
        GLFWwindow *window = get_window();
 
        int state = glfwGetKey(window, (int) t_keycode);

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }



    bool InputLinux::is_mouse_button_pressed_imp(uint16_t t_keycode) 
    {
        GLFWwindow *window = get_window();

        int state = glfwGetMouseButton(window, (int) t_keycode);

        return state == GLFW_PRESS;
    }

    std::pair<float, float> InputLinux::get_mouse_position_imp() 
    {
        GLFWwindow *window = get_window();

        double x, y;
        glfwGetCursorPos(window, &x, &y);

        return { (float) x, (float) y };
    }

}