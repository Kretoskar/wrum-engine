#include "PCH.h"

#include "WrumCore/Window/UI.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace Wrum
{
    bool UI::Init(GLFWwindow* window)
    {
        IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
	
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		const char* glslVersion = "#version 440 core";
		ImGui_ImplOpenGL3_Init(glslVersion);

    	return true;
    }

    void UI::CreateFrame(double deltaTime)
    {
    	dt = deltaTime;

    	ImGui_ImplOpenGL3_NewFrame();
    	ImGui_ImplGlfw_NewFrame();
    	ImGui::NewFrame();

    	CreateWidgets();
    }

    void UI::Render()
    {
    	ImGui::Render();
    	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void UI::Cleanup()
    {
    	ImGui_ImplOpenGL3_Shutdown();
    	ImGui_ImplGlfw_Shutdown();
    	ImGui::DestroyContext();
    }
}
