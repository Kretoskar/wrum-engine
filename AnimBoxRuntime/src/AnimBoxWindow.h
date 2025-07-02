#pragma once

#include "AnimBoxCore/Window/Public/Window.h"

namespace AnimBox 
{
    class AnimBoxWindow : public Window
    {
    public:
        bool Init() override;
        void Update() override;
        void Shutdown() override;
    };
}