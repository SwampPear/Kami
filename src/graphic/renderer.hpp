#pragma once
#include "PCH.hpp"

namespace gfx{

    class Renderer {
    public:
        explicit Renderer(MTL::Device* device);
        ~Renderer();

        void Draw(MTK::View* view);

    private:
        MTL::Device* device{nullptr};
        MTL::CommandQueue* commandQueue{nullptr};
    };

}