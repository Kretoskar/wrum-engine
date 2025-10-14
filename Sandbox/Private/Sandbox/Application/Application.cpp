#include "PCH.h"

#include "WrumCore/Core/EventSystem.h"
#include "WrumCore/Memory/ArenaAllocator.h"

#include "Sandbox/Application/Application.h"

#include "Sandbox/Window/SandboxUI.h"
#include "Sandbox/Window/SandboxWindow.h"
#include "WrumCore/Controllers/CameraController.h"
#include "WrumCore/Controllers/InputController.h"
#include "WrumCore/Core/Color.h"
#include "WrumCore/Core/FrameDiagnostics.h"
#include "WrumCore/Rendering/DebugRenderer.h"
#include "WrumCore/ResourceHandling/File.h"
#include "WrumCore/Core/Time.h"
#include "WrumCore/Rendering/Material.h"
#include "WrumCore/Rendering/Renderer.h"
#include "WrumCore/Rendering/Texture.h"
#include "WrumCore/Rendering/Mesh/Primitives/Cube.h"
#include "WrumCore/Rendering/Mesh/Primitives/Plane.h"
#include "WrumCore/Rendering/Mesh/Primitives/Sphere.h"
#include "WrumCore/Window/UI.h"

using namespace Wrum;

void Sandbox::Application::Run()
{
    ArenaAllocator globalAppArena(1024 * 1024, "Global");
    ArenaAllocator renderingArena(1024 * 1024, "Rendering");
    
    Dispatcher::Init(globalAppArena);
    
    SandboxWindow* window = ArenaAllocator::New<SandboxWindow>(globalAppArena);
    window->Init();
    
    CameraSettings* camSettings = ArenaAllocator::New<CameraSettings>(globalAppArena);
    camSettings->_window = window;
    
    FlyCameraController* flyCam = ArenaAllocator::New<FlyCameraController>(globalAppArena);
    Camera* cam =  ArenaAllocator::New<Camera>(globalAppArena, Vec3(1.0f, 1.0f, 1.0f), Vec3(-0.5f, -0.5f, -0.5f), *camSettings, flyCam);
    flyCam->Init(cam);
    
    DebugRenderer* debugRenderer = ArenaAllocator::New<DebugRenderer>(renderingArena);
    debugRenderer->Init(renderingArena);

    Plane* plane = ArenaAllocator::New<Plane>(renderingArena, Color::PASTEL_PEACH);
   // Wrum::Cube  cube = Wrum::Cube({1.0f, 0.0f, 0.0f});
    Sphere* sphere = ArenaAllocator::New<Sphere>(renderingArena, Color::PASTEL_RED, 16, 16);

    // TODO: collect texture memory data
    Texture* texture = ArenaAllocator::New<Texture>(renderingArena, "../res/cat.png");
    
    Shader* pbrShader = ArenaAllocator::New<Shader>(renderingArena, "shaders/pbr.vert", "shaders/pbr.frag");
    Shader* simpleShader = ArenaAllocator::New<Shader>(renderingArena, "shaders/pbr.vert", "shaders/vertexColor.frag");
    
    PbrMaterial* pbrMaterial = ArenaAllocator::New<PbrMaterial>(renderingArena, pbrShader);
    pbrMaterial->diffuseMap = texture;

    Material* material = ArenaAllocator::New<Material>(renderingArena, simpleShader);
    Renderer* renderer = ArenaAllocator::New<Renderer>(renderingArena, cam);

    Framebuffer* framebuffer = ArenaAllocator::New<Framebuffer>(renderingArena);
    framebuffer->Init(window->GetWidth(), window->GetHeight());
    window->SetFramebuffer(framebuffer);

    SandboxUI* ui = ArenaAllocator::New<SandboxUI>(globalAppArena);
    ui->Init(window->GetGlfwWindow());

    Mat4 model = Mat4::Identity;
    //model.SetScale({0.1f, 0.1f, 0.1f});
    model.SetPosition({0.5f, 0.0f, 0.5f});

    Mat4 modelSphere = Mat4::Identity;
    // modelSphere.SetScale({0.1f, 0.1f, 0.1f});
    modelSphere.SetPosition({0.5f, 0.5, 0.5});
    
    double dt = 0.0;
    
    while (!window->GetShouldClose())
    {
        Time::Update();
        FrameDiagnostics::GatherFrameStart();
        dt = FrameDiagnostics::last;

        InputController::PollInput(*window);
        
        cam->Update(window->GetWidth(), window->GetHeight());

        Dispatcher::CallEvents();
        
        framebuffer->Bind();
        
        debugRenderer->Update(dt);
        debugRenderer->Render(*cam);
        
        renderer->DrawMesh(*sphere, *pbrMaterial, modelSphere);
      //  renderer.DrawMesh(cube, material, modelSphere);
        renderer->DrawMesh(*plane, *material, model);
        
        framebuffer->Draw();

        ui->CreateFrame(dt);
        ui->Render();

        framebuffer->Bind();
        window->Update();
        
        FrameDiagnostics::GatherFrameEnd();
    }

    ui->Cleanup();
    window->Shutdown();
}
