#include "Fullbeard/Systems/LayerImGUI.hpp"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "Fullbeard/Systems/Application.hpp"
#include "Fullbeard/util.hpp"

#include<GLFW/glfw3.h>
#include "fullbeard_pch.hpp"

namespace Fullbeard
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

		io.KeyMap[ImGuiKey_Tab]        = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow]  = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow]    = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow]  = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp]     = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown]   = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home]       = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End]        = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert]     = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete]     = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace]  = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space]      = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter]      = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape]     = GLFW_KEY_ESCAPE;

		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

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
            BIND_EVENT_FN__(LayerImGUI::on_mouse_button_pressed));
		dispatcher.dispatch<EventMouseButtonReleased>(
            BIND_EVENT_FN__(LayerImGUI::on_mouse_button_released));
		dispatcher.dispatch<EventMouseMoved>(
            BIND_EVENT_FN__(LayerImGUI::on_mouse_moved));
		dispatcher.dispatch<EventMousewheelScrolled>(
            BIND_EVENT_FN__(LayerImGUI::on_mousewheel_scrolled));
		dispatcher.dispatch<EventKeyPressed>(
            BIND_EVENT_FN__(LayerImGUI::on_key_pressed));
		dispatcher.dispatch<EventKeyReleased>(
            BIND_EVENT_FN__(LayerImGUI::on_key_released));
		dispatcher.dispatch<EventWindowResize>(
            BIND_EVENT_FN__(LayerImGUI::on_window_resized));
    }
    
    bool LayerImGUI::on_mouse_button_pressed(EventMouseButtonPressed &t_event) 
    {
        ImGuiIO &io = ImGui::GetIO();
		io.MouseDown[t_event.get_keycode()] = true;

        Log::core_trace("imgui mouse press");

		return false;
    }
    
    bool LayerImGUI::on_mouse_button_released(EventMouseButtonReleased &t_event) 
    {
        ImGuiIO &io = ImGui::GetIO();
		io.MouseDown[t_event.get_keycode()] = false;

        Log::core_trace("imgui mouse release");

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

        io.KeyCtrl  = io.KeysDown[GLFW_KEY_LEFT_CONTROL] ||
                      io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyAlt   = io.KeysDown[GLFW_KEY_LEFT_ALT] ||
                      io.KeysDown[GLFW_KEY_RIGHT_ALT];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] ||
                      io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] ||
                      io.KeysDown[GLFW_KEY_RIGHT_SUPER];

		return false;
    }
    
    bool LayerImGUI::on_key_released(EventKeyReleased &t_event) 
    {
        ImGuiIO &io = ImGui::GetIO();
		io.KeysDown[t_event.get_keycode()] = false;

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