#include "Fullbeard/Systems/Layer.hpp"

#include "Fullbeard/util.hpp"

#include "fullbeard_pch.hpp"

namespace Fullbeard
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
        UNUSED(t_event);
    }
}