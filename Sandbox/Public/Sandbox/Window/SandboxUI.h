#pragma once

#include "WrumCore/Window/UI.h"

namespace Sandbox
{
    class SandboxUI : public Wrum::UI
    {
    protected:
        void CreateLoggerWidget();
        void CreateStatsWidget();
        virtual void CreateWidgets() override;
    };
}