#include "PCH.h"
#include "WrumCore/Core/EventSystem.h"
#include "WrumCore/Memory/ArenaAllocator.h"

#include "Sandbox/Application/Application.h"
#include "Sandbox/Window/SandboxWindow.h"
#include "WrumCore/Rendering/DebugRenderer.h"
#include "WrumCore/ResourceHandling/File.h"

void Sandbox::Application::Run()
{
    Wrum::ArenaAllocator Arena(1024 * 1024);
    
    Wrum::Dispatcher::Init(Arena);
    
    SandboxWindow window;
    window.Init();

    Wrum::CameraSettings camSettings; 
    
    Wrum::Camera cam =  Wrum::Camera(Wrum::Vec3(0.0f, 0.0f, 0.0f), Wrum::Vec3(0.0f, 0.0f, 0.0f), camSettings);
    
    Wrum::DebugRenderer Dr;
    Dr.Init();
    
    while (!window.GetShouldClose())
    {
        cam.Update();
        Dr.Render(cam);
        // Call all pending events 
        Wrum::Dispatcher::CallEvents();
        window.Update();
    }
}
