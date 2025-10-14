#include "PCH.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "WrumCore/Core/Logger.h"
#include "Sandbox/Window/SandboxUI.h"

#include "imgui/imgui_internal.h"
#include "WrumCore/Core/FrameDiagnostics.h"

namespace Sandbox
{
    void SandboxUI::CreateWidgets()
    {
        CreateLoggerWidget();
        CreateStatsWidget();
    }
    
    void SandboxUI::CreateLoggerWidget()
    {
        ImVec2 HorCenterVerBottomPos = ImGui::GetMainViewport()->GetCenter();
        HorCenterVerBottomPos.y = ImGui::GetMainViewport()->Size.y;

        ImVec2 ConsoleWindowSize = ImGui::GetMainViewport()->Size;
        ConsoleWindowSize.y /= 4;

        ImGuiWindowFlags flags = 0;
        ImGui::SetNextWindowBgAlpha(0.8f);
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

    void SandboxUI::CreateStatsWidget()
    {
        ImVec2 DetailsWindowSize = ImGui::GetMainViewport()->Size;
        DetailsWindowSize.x /= 6;
        DetailsWindowSize.y = (DetailsWindowSize.y / 4);

        ImGuiWindowFlags flags = 0;

        ImGui::SetNextWindowBgAlpha(0.8f);
        ImGui::SetNextWindowPos(ImVec2(ImGui::GetMainViewport()->Size.x, 0.0f), ImGuiCond_Always, ImVec2(1.0f, 0.0f));
        ImGui::SetNextWindowSize(DetailsWindowSize, ImGuiCond_Always);
        ImGui::Begin("Stats:", nullptr, flags);
        ImGui::Columns(4);
        ImGui::Text("Last");
        ImGui::Text("%0.3lf", Wrum::FrameDiagnostics::last);
        ImGui::NextColumn();
        ImGui::Text("Avg");
        ImGui::Text("%0.3lf", Wrum::FrameDiagnostics::avg);
        ImGui::NextColumn();
        ImGui::Text("Min");
        ImGui::Text("%0.3lf", Wrum::FrameDiagnostics::min);
        ImGui::NextColumn();
        ImGui::Text("Max");
        ImGui::Text("%0.3lf", Wrum::FrameDiagnostics::max);
        ImGui::EndColumns();

        ImGui::Spacing();
        
        for (auto arena : Wrum::ArenaAllocator::GetMapOfObjects())
        {
            ImGui::Text(arena.second->GetTag().Get());
            float offsetKB = (float)arena.second->GetOffset() / 1024.0f;
            float capacityKB = (float)arena.second->GetCapacity() / 1024.0f;

            char name[100];
            std::sprintf(name, "%.0f/%.0fKiB", offsetKB, capacityKB);
            
            ImGui::ProgressBar(offsetKB / capacityKB, {0,0}, name);
        }
        
        
        ImGui::End();
    }
}
