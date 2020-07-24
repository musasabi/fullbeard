#ifndef FULLBEARD_LAYERSTACK_HPP__
#define FULLBEARD_LAYERSTACK_HPP__

#include "Layer.hpp"

#include <vector>

namespace Fullbeard
{

    using layer_iter     = std::vector<Layer *>::iterator;
    using rev_layer_iter = std::vector<Layer *>::reverse_iterator;

    class LayerStack
    {
        public:
            LayerStack();
            ~LayerStack();

            void push_layer(Layer *layer);
            void pop_layer(Layer  *layer);

            void push_overlay(Layer *overlay);
            void pop_overlay(Layer  *overlay);

            layer_iter begin() { return layers.begin(); }
            layer_iter end()   { return layers.end();   }

            rev_layer_iter rbegin() { return layers.rbegin(); }
            rev_layer_iter rend()   { return layers.rend();   }

        private:
            std::vector<Layer *> layers;
            std::vector<Layer *>::iterator layer_insert;
    };
}

#endif // FULLBEARD_LAYERSTACK_HPP__