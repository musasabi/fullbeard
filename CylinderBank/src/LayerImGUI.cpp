#include "CylinderBank/Layers/LayerImGUI.hpp"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "CylinderBank/Systems/Application.hpp"
#include "CylinderBank/util.hpp"
#include "CylinderBank/Input/keycodes.hpp"

#include<GLFW/glfw3.h>
#include "CylinderBank_pch.hpp"

namespace CylinderBank
{
    LayerImGUI::LayerImGUI() :
    Layer("ImGUI Layer")
    {
    }
    
    LayerImGUI::~LayerImGUI() 
    {
    }
    
    void LayerImGUI::on_push() 
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO &io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		io.KeyMap[ImGuiKey_Tab]        = CB_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow]  = CB_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = CB_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow]    = CB_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow]  = CB_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp]     = CB_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown]   = CB_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home]       = CB_KEY_HOME;
		io.KeyMap[ImGuiKey_End]        = CB_KEY_END;
		io.KeyMap[ImGuiKey_Insert]     = CB_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete]     = CB_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace]  = CB_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space]      = CB_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter]      = CB_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape]     = CB_KEY_ESCAPE;

		io.KeyMap[ImGuiKey_A] = CB_KEY_A;
		io.KeyMap[ImGuiKey_C] = CB_KEY_C;
		io.KeyMap[ImGuiKey_V] = CB_KEY_V;
		io.KeyMap[ImGuiKey_X] = CB_KEY_X;
		io.KeyMap[ImGuiKey_Y] = CB_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = CB_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 460");
    }
    
    void LayerImGUI::on_pop() 
    {
    }
    
    void LayerImGUI::on_update() 
    {
		ImGuiIO     &io  = ImGui::GetIO();
		Application &app = Application::get_instance();
		io.DisplaySize   = ImVec2(app.get_window().get_width(),
                                  app.get_window().get_height());

		float current_time = (float)glfwGetTime();
		io.DeltaTime = time > 0.0f ? (current_time - time) : (1.0f / 60.0f);
		time = current_time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
    
    void LayerImGUI::on_event(Event &t_event) 
    {
		EventDispatcher dispatcher(t_event);

		dispatcher.dispatch<EventMouseButtonPressed>(
            CB_BIND_EVENT_FN(LayerImGUI::on_mouse_button_pressed));
		dispatcher.dispatch<EventMouseButtonReleased>(
            CB_BIND_EVENT_FN(LayerImGUI::on_mouse_button_released));
		dispatcher.dispatch<EventMouseMoved>(
            CB_BIND_EVENT_FN(LayerImGUI::on_mouse_moved));
		dispatcher.dispatch<EventMousewheelScrolled>(
            CB_BIND_EVENT_FN(LayerImGUI::on_mousewheel_scrolled));
		dispatcher.dispatch<EventKeyPressed>(
            CB_BIND_EVENT_FN(LayerImGUI::on_key_pressed));
		dispatcher.dispatch<EventKeyReleased>(
            CB_BIND_EVENT_FN(LayerImGUI::on_key_released));
		dispatcher.dispatch<EventKeyTyped>(
            CB_BIND_EVENT_FN(LayerImGUI::on_key_typed));
		dispatcher.dispatch<EventWindowResize>(
            CB_BIND_EVENT_FN(LayerImGUI::on_window_resized));
    }
    
    bool LayerImGUI::on_mouse_button_pressed(EventMouseButtonPressed &t_event) 
    {
        ImGuiIO &io = ImGui::GetIO();
		io.MouseDown[t_event.get_keycode()] = true;

		return false;
    }
    
    bool LayerImGUI::on_mouse_button_released(EventMouseButtonReleased &t_event) 
    {
        ImGuiIO &io = ImGui::GetIO();
		io.MouseDown[t_event.get_keycode()] = false;

		return false;
    }
    
    bool LayerImGUI::on_mousewheel_scrolled(EventMousewheelScrolled &t_event) 
    {
        ImGuiIO &io = ImGui::GetIO();
		io.MouseWheelH += t_event.get_x_offset();
        io.MouseWheel  += t_event.get_y_offset();

		return false;
    }
    
    bool LayerImGUI::on_mouse_moved(EventMouseMoved &t_event) 
    {
        ImGuiIO &io = ImGui::GetIO();
        io.MousePos = ImVec2(t_event.get_x(), t_event.get_y());

        return false;
    }
    
    bool LayerImGUI::on_key_pressed(EventKeyPressed &t_event) 
    {
        ImGuiIO &io = ImGui::GetIO();
		io.KeysDown[t_event.get_keycode()] = true;

        io.KeyCtrl  = io.KeysDown[CB_KEY_LEFT_CONTROL] ||
                      io.KeysDown[CB_KEY_RIGHT_CONTROL];
        io.KeyAlt   = io.KeysDown[CB_KEY_LEFT_ALT] ||
                      io.KeysDown[CB_KEY_RIGHT_ALT];
        io.KeyShift = io.KeysDown[CB_KEY_LEFT_SHIFT] ||
                      io.KeysDown[CB_KEY_RIGHT_SHIFT];
        io.KeySuper = io.KeysDown[CB_KEY_LEFT_SUPER] ||
                      io.KeysDown[CB_KEY_RIGHT_SUPER];

		return false;
    }
    
    bool LayerImGUI::on_key_released(EventKeyReleased &t_event) 
    {
        ImGuiIO &io = ImGui::GetIO();
		io.KeysDown[t_event.get_keycode()] = false;

		return false;
    }
    
    bool LayerImGUI::on_key_typed(EventKeyTyped &t_event) 
    {
		ImGuiIO& io = ImGui::GetIO();
		uint16_t keycode = t_event.get_keycode();
        io.AddInputCharacter(keycode);

		return false;
    }
    
    bool LayerImGUI::on_window_resized(EventWindowResize &t_event) 
    {
        ImGuiIO &io = ImGui::GetIO();
        io.DisplaySize = ImVec2(t_event.get_width(), t_event.get_height());
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
        glViewport(0, 0, t_event.get_width(), t_event.get_height());

        return false;
    }
}