#ifndef CB_LAYERIMGUI_HPP__
#define CB_LAYERIMGUI_HPP__

#include "Layer.hpp"
#include "../Events/EventMouse.hpp"
#include "../Events/EventKey.hpp"
#include "../Events/EventApplication.hpp"

namespace CylinderBank
{
    class LayerImGUI : public Layer
    {
        public:
            LayerImGUI();
            ~LayerImGUI();

            virtual void on_push() override;
            virtual void on_pop() override;

            void begin_render();
            void complete_render();

            virtual void imgui_draw() override;

        private:
            static LayerImGUI *instance;
            float time = 0.0f;
    };
}
#endif // CB_LAYERIMGUI_HPP__