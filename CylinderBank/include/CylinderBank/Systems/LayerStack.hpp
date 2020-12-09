#ifndef CB_LAYERSTACK_HPP__
#define CB_LAYERSTACK_HPP__

#include "../Layers/Layer.hpp"

#include <vector>

namespace CylinderBank
{

    using layer_iter     = std::vector<Layer *>::iterator;
    using rev_layer_iter = std::vector<Layer *>::reverse_iterator;

    class LayerStack
    {
        public:
            LayerStack();
            ~LayerStack();

            LayerStack(const LayerStack &) = default;
            LayerStack(LayerStack &&)      = default;

            LayerStack& operator=(const LayerStack &) = default;
            LayerStack& operator=(LayerStack &&)      = default;

            void push_layer(Layer *layer);
            void pop_layer(Layer  *layer);

            void push_overlay(Layer *overlay);
            void pop_overlay(Layer  *overlay);

            inline layer_iter begin() { return layers.begin(); }
            inline layer_iter end()   { return layers.end();   }

            inline rev_layer_iter rbegin() { return layers.rbegin(); }
            inline rev_layer_iter rend()   { return layers.rend();   }

        private:
            std::vector<Layer *> layers;
            uint32_t layer_insert_pos;
    };
}

#endif // CB_LAYERSTACK_HPP__
