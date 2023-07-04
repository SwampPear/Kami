#pragma once
#include "renderer.hpp"

namespace gfx{
    //view delegate
    class View : public MTK::ViewDelegate {
    public:
        explicit View(MTL::Device* device) : renderer{new gfx::Renderer(device)} {}
        ~View() override { delete renderer;};

        void drawInMTKView(MTK::View *pView) override {
            renderer->Draw(pView);
        };

    private:
        Renderer* renderer{nullptr};
    };

}