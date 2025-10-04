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
#include "WrumCore/Rendering/Mesh/Primitives/Cube.h"
#include "WrumCore/Rendering/Mesh/Primitives/Plane.h"
#include "WrumCore/Rendering/Mesh/Primitives/Sphere.h"
#include "WrumCore/Window/UI.h"

void Sandbox::Application::Run()
{
    Wrum::ArenaAllocator Arena(1024 * 1024);
    
    Wrum::Dispatcher::Init(Arena);
    
    SandboxWindow window;
    window.Init();
    
    Wrum::CameraSettings camSettings; 
    camSettings._window = &window;
    Wrum::FlyCameraController flyCam;
    Wrum::Camera cam =  Wrum::Camera(Wrum::Vec3(1.0f, 1.0f, 1.0f), Wrum::Vec3(-0.5f, -0.5f, -0.5f), camSettings, &flyCam);
    flyCam.Init(&cam);
    
    Wrum::DebugRenderer DebugRenderer;
    DebugRenderer.Init();

    Wrum::Plane plane = Wrum::Plane({0.0f, 1.0f, 0.0f});
    //Wrum::Cube  cube = Wrum::Cube({1.0f, 0.0f, 0.0f});
    Wrum::Sphere sphere = Wrum::Sphere({1.0f, 0.0f, 0.0f}, 16, 16);
    
    Wrum::Shader shader = Wrum::Shader("shaders/pbr.vert", "shaders/vertexColor.frag");
    Wrum::Material material = Wrum::Material(&shader);

    Wrum::Renderer renderer = Wrum::Renderer(&cam);
    
    double dt = 0.0;

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

        Wrum::InputController::PollInput(window);
        
        cam.Update(window.GetWidth(), window.GetHeight());

        Wrum::Dispatcher::CallEvents();
        
        framebuffer.Bind();
        
        DebugRenderer.Update(dt);
        DebugRenderer.Render(cam);
        renderer.DrawMesh(sphere, material, model);
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
