#include "PCH.h"
#include "WrumCore/Core/EventSystem.h"
#include "WrumCore/Memory/ArenaAllocator.h"

#include "Sandbox/Application/Application.h"
#include "Sandbox/Window/SandboxWindow.h"
#include "WrumCore/Rendering/DebugRenderer.h"
#include "WrumCore/ResourceHandling/File.h"
#include "WrumCore/Core/Time.h"

void Sandbox::Application::Run()
{
    Wrum::ArenaAllocator Arena(1024 * 1024);
    
    Wrum::Dispatcher::Init(Arena);
    
    SandboxWindow window;
    window.Init();

    Wrum::CameraSettings camSettings; 
    
    Wrum::Camera cam =  Wrum::Camera(Wrum::Vec3(1.0f, 1.0f, 1.0f), Wrum::Vec3(-0.5f, -0.5f, -0.5f), camSettings);
    
    Wrum::DebugRenderer Dr;
    Dr.Init();


    double lastFrameTime = 0.0;
    double dt = 0.0;
    // TODO: delta time for debug renderer
    while (!window.GetShouldClose())
    {
        Wrum::Time::Update();
        
        double timeSinceStart = Wrum::Time::TimeSinceProgramStart(Wrum::TimeUnit::Milliseconds);
        dt = timeSinceStart - lastFrameTime; 
        lastFrameTime = timeSinceStart;
        
        cam.Update(window.GetWidth(), window.GetHeight());
        Dr.Update(dt);
        Dr.Render(cam);
        // Call all pending events 
        Wrum::Dispatcher::CallEvents();
        window.Update();
    }
}
