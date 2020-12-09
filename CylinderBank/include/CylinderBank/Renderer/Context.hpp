#ifndef CB_CONTEXT_HPP__
#define CB_CONTEXT_HPP__

namespace CylinderBank
{
    class Context
    {
        public:
            virtual void init() = 0;
            virtual void swap_buffers() = 0;
    };
}

#endif //CB_CONTEXT_HPP__