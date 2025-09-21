#include "PCH.h"

#include "WrumCore/Core/EventSystem.h"
#include "WrumCore/Memory/ArenaAllocator.h"

#include "Sandbox/Application/Application.h"

#include "Sandbox/Window/SandboxUI.h"
#include "Sandbox/Window/SandboxWindow.h"
#include "WrumCore/Controllers/CameraController.h"
#include "WrumCore/Controllers/InputController.h"
#include "WrumCore/Core/FrameDiagnostics.h"
#include "WrumCore/Rendering/DebugRenderer.h"
#include "WrumCore/ResourceHandling/File.h"
#include "WrumCore/Core/Time.h"
#include "WrumCore/Rendering/Material.h"
#include "WrumCore/Rendering/Renderer.h"
#include "WrumCore/Rendering/Mesh/Primitives/Plane.h"
#include "WrumCore/Window/UI.h"

void Sandbox::Application::Run()
{
    Wrum::ArenaAllocator Arena(1024 * 1024);
    
    Wrum::Dispatcher::Init(Arena);
    
    SandboxWindow window;
    window.Init();

    Wrum::CameraSettings camSettings; 

    Wrum::FlyCameraController flyCam;
    Wrum::Camera cam =  Wrum::Camera(Wrum::Vec3(1.0f, 1.0f, 1.0f), Wrum::Vec3(-0.5f, -0.5f, -0.5f), camSettings, &flyCam);
    
    Wrum::DebugRenderer DebugRenderer;
    DebugRenderer.Init();

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

    Wrum::Framebuffer framebuffer;
    framebuffer.Init(window.GetWidth(), window.GetHeight());
    window.SetFramebuffer(&framebuffer);

    SandboxUI ui;
    ui.Init(window.GetGlfwWindow());
    
    while (!window.GetShouldClose())
    {
        Wrum::Time::Update();
        Wrum::FrameDiagnostics::GatherFrameStart();
        dt = Wrum::FrameDiagnostics::last;
        
        //double timeSinceStart = Wrum::Time::TimeSinceProgramStart(Wrum::TimeUnit::Milliseconds);
        //dt = timeSinceStart - lastFrameTime; 
        //lastFrameTime = timeSinceStart;

        Wrum::InputController::PollInput(window);

        // Call all pending events 
        Wrum::Dispatcher::CallEvents();
        
        cam.Update(window.GetWidth(), window.GetHeight());
        
        framebuffer.Bind();
        
        DebugRenderer.Update(dt);
        DebugRenderer.Render(cam);
        renderer.DrawMesh(plane, material, model);
        
        framebuffer.Draw();

        ui.CreateFrame(dt);
        ui.Render();

        framebuffer.Bind();
        window.Update();
        
        Wrum::FrameDiagnostics::GatherFrameEnd();
    }

    ui.Cleanup();
    window.Shutdown();
}
