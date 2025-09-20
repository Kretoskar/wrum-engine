#include "PCH.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "WrumCore/Core/Logger.h"
#include "Sandbox/Window/SandboxUI.h"

namespace Sandbox
{
    void SandboxUI::CreateWidgets()
    {
        ImVec2 HorCenterVerBottomPos = ImGui::GetMainViewport()->GetCenter();
        HorCenterVerBottomPos.y = ImGui::GetMainViewport()->Size.y;

        ImVec2 ConsoleWindowSize = ImGui::GetMainViewport()->Size;
        ConsoleWindowSize.y /= 4;

        ImGuiWindowFlags flags = 0;
        ImGui::SetNextWindowBgAlpha(0.9f);
        ImGui::SetNextWindowPos(HorCenterVerBottomPos, ImGuiCond_Always, ImVec2(0.5f, 1.0f));
        ImGui::SetNextWindowSize(ConsoleWindowSize, ImGuiCond_Always);
        ImGui::Begin("CONSOLE", nullptr, flags);

        Wrum::Logger& logger = Wrum::Logger::GetInstance();
        
        for (unsigned int i = 0; i < logger.loggedLineBufferCurrCount; i++)
        {
            switch (logger.logLinesVerbosity[i])
            {
            case Wrum::Error:
                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));
                break;
            case Wrum::Warning:
                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 0, 255));
                break;
            case Wrum::Message:
                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
                break;
            }

            ImGui::Text(logger.logLines[i]);

            ImGui::PopStyleColor();
        }

        if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        {
            ImGui::SetScrollHereY(0.0f);
        }

        ImGui::End();
    }
}
