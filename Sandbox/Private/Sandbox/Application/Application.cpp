#include "PCH.h"

#include "WrumCore/Core/EventSystem.h"
#include "WrumCore/Memory/ArenaAllocator.h"

#include "Sandbox/Application/Application.h"

#include "Sandbox/Window/SandboxUI.h"
#include "Sandbox/Window/SandboxWindow.h"
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

    Wrum::Framebuffer framebuffer;
    framebuffer.Init(window.GetWidth(), window.GetHeight());
    window.SetFramebuffer(&framebuffer);

    SandboxUI ui;
    ui.Init(window.GetGlfwWindow());
    
    while (!window.GetShouldClose())
    {
        Wrum::FrameDiagnostics::GatherFrameStart();
        Wrum::Time::Update();
        
        double timeSinceStart = Wrum::Time::TimeSinceProgramStart(Wrum::TimeUnit::Milliseconds);
        dt = timeSinceStart - lastFrameTime; 
        lastFrameTime = timeSinceStart;

        Wrum::InputController::PollInput(window);

        if (Wrum::InputController::GetInput(Wrum::Input::W) == Wrum::InputState::Pressed)
        {
            LOG_MESSAGE("w")
        }
        
        cam.Update(window.GetWidth(), window.GetHeight());
        
        framebuffer.Bind();
        
        Dr.Update(dt);
        Dr.Render(cam);
        renderer.DrawMesh(plane, material, model);

        framebuffer.Unbind();
        framebuffer.Draw();

        ui.CreateFrame(dt);
        ui.Render();
        
        // Call all pending events 
        Wrum::Dispatcher::CallEvents();
        window.Update();

        if (Wrum::Time::GetFrame() > 2)
        {
            Wrum::FrameDiagnostics::GatherFrameEnd();
        }
    }

    ui.Cleanup();
    window.Shutdown();
}
