#pragma once

#include "WrumCore/Core/EventSystem.h"
#include "WrumCore/Core/Types.h"
#include "WrumCore/Window/Window.h"

namespace Wrum
{
    class Framebuffer;
}

namespace Sandbox
{
    class SandboxWindow : public Wrum::Window
    {
    public:
        bool Init() override;
        void Update() override;
        void Shutdown() override;
        void SetFramebuffer(Wrum::Framebuffer* framebuffer) { _framebuffer = framebuffer; }
        
    protected:
        void OnWindowMoved(int16 xPos, int16 yPos) override;
        
        void OnWindowMinimized() override;
        void OnWindowRestored() override;

        void OnWindowMaximized() override;
        void OnWindowUnmaximized() override;

        void OnWindowResized(uint16 width, uint16 height) override;
        void OnMouseMoved(double xPos, double yPos) override;

        Wrum::Framebuffer* _framebuffer = nullptr;
    };
}
