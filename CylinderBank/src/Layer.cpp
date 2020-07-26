#include "CylinderBank/Layers/Layer.hpp"

#include "CylinderBank/util.hpp"

#include "CylinderBank_pch.hpp"

namespace CylinderBank
{
    Layer::Layer(const std::string &t_name):
    debug_name(t_name)
    { }

    Layer::~Layer()
    { }

    void Layer::on_push()
    { }

    void Layer::on_pop()
    { }

    void Layer::on_update()
    { }

    void Layer::on_event(Event &t_event)
    {
        CB_UNUSED(t_event);
    }
}