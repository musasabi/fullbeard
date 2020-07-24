#include "Fullbeard/Systems/LayerStack.hpp"

#include "fullbeard_pch.hpp"

namespace Fullbeard
{
    LayerStack::LayerStack()
    {
        layer_insert = layers.begin();
    }

    LayerStack::~LayerStack()
    {
        for(Layer *layer : layers)
        {
            delete layer;
        }
    }

    void LayerStack::push_layer(Layer *t_layer)
    {
        layer_insert = layers.emplace(layer_insert, t_layer);
    }

    void LayerStack::push_overlay(Layer *t_overlay)
    {
        layers.emplace_back(t_overlay);
    }

    void LayerStack::pop_layer(Layer *t_layer)
    {
        layer_iter layer = std::find(layers.begin(), layers.end(), t_layer);

        if(layer != layers.end())
        {
            layers.erase(layer);
            layer_insert--;
        }
    }

    void LayerStack::pop_overlay(Layer *t_overlay)
    {
        layer_iter overlay = std::find(layers.begin(), layers.end(), t_overlay);

        if(overlay != layers.end())
        {
            layers.erase(overlay);
        }
    }
}