#pragma once

#include "WrumCore/Window/UI.h"

namespace Sandbox
{
    class SandboxUI : public Wrum::UI
    {
    protected:
        virtual void CreateWidgets() override;
    };
}