#pragma once

#include "AnimBoxCore/Core/Types.h"
#include "AnimBoxCore/Window/Window.h"

namespace AnimBoxRuntime
{
    class AnimBoxWindow : public AnimBox::Window
    {
    public:
        bool Init() override;
        void Update() override;
        void Shutdown() override;

    protected:
        void OnWindowMoved(int16 xPos, int16 yPos) override;
        
        void OnWindowMinimized() override;
        void OnWindowRestored() override;

        void OnWindowMaximized() override;
        void OnWindowUnmaximized() override;

        void OnWindowResized(uint16 width, uint16 height) override;
    };
}