#pragma once

#include "AnimBoxCore/Core/Public/Types.h"
#include "AnimBoxCore/Window/Public/Window.h"

namespace AnimBox 
{
    class AnimBoxWindow : public Window
    {
    public:
        bool Init() override;
        void Update() override;
        void Shutdown() override;

    protected:
        void HandleWindowMoveEvents(int16 xPos, int16 yPos) override;
    };
}