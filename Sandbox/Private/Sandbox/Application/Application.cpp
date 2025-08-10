#include "PCH.h"
#include "WrumCore/Core/EventSystem.h"
#include "WrumCore/Memory/ArenaAllocator.h"

#include "Sandbox/Application/Application.h"
#include "Sandbox/Window/SandboxWindow.h"
#include "WrumCore/Rendering/DebugRenderer.h"
#include "WrumCore/ResourceHandling/File.h"
#include "WrumCore/Core/Time.h"
#include "WrumCore/Rendering/Material.h"
#include "WrumCore/Rendering/Renderer.h"
#include "WrumCore/Rendering/Mesh/Primitives/Plane.h"

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

    Wrum::Plane plane = Wrum::Plane({0.0f, 1.0f, 0.0f});

    Wrum::Shader shader = Wrum::Shader("shaders/pbr.vert", "shaders/vertexColor.frag");
    Wrum::Material material = Wrum::Material(&shader);

    Wrum::Renderer renderer = Wrum::Renderer(&cam);
    
    double lastFrameTime = 0.0;
    double dt = 0.0;
    // TODO: delta time for debug renderer

    Wrum::Mat4 model = Wrum::Mat4::Identity;
    model.SetScale({0.1, 0.1, 0.1});
    model.SetPosition({0.1f, 0.0f, 0.1f});
    
    while (!window.GetShouldClose())
    {
        Wrum::Time::Update();
        
        double timeSinceStart = Wrum::Time::TimeSinceProgramStart(Wrum::TimeUnit::Milliseconds);
        dt = timeSinceStart - lastFrameTime; 
        lastFrameTime = timeSinceStart;
        
        
        cam.Update(window.GetWidth(), window.GetHeight());
        Dr.Update(dt);
        Dr.Render(cam);
        renderer.DrawMesh(plane, material, model);
        // Call all pending events 
        Wrum::Dispatcher::CallEvents();
        window.Update();
    }
}
