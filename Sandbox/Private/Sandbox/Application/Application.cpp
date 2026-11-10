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
#include "WrumCore/Math/Quat.h"
#include "WrumCore/Rendering/Material.h"
#include "WrumCore/Rendering/Renderer.h"
#include "WrumCore/Rendering/Texture.h"
#include "WrumCore/Rendering/Mesh/Primitives/Arrow.h"
#include "WrumCore/Rendering/Mesh/Primitives/Cube.h"
#include "WrumCore/Rendering/Mesh/Primitives/Plane.h"
#include "WrumCore/Rendering/Mesh/Primitives/Sphere.h"
#include "WrumCore/ResourceHandling/ResourceManager.h"
#include "WrumCore/Window/UI.h"

using namespace Wrum;

void Sandbox::Application::Run()
{
    ArenaAllocator globalAppArena(BIT_MEGA_BYTE(1), "Global");
    ArenaAllocator renderingArena(BIT_MEGA_BYTE(1), "Rendering");
    
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
    
    ResourceManager* resourceManager = ArenaAllocator::New<ResourceManager>(globalAppArena);
    
    ResourceID pbrShaderResource = resourceManager->MakeShaderResource("shaders/pbr.vert", "shaders/pbr.frag");
    resourceManager->LoadShader(pbrShaderResource);

    ResourceID simpleShaderResource = resourceManager->MakeShaderResource("shaders/pbr.vert", "shaders/vertexColor.frag");
    resourceManager->LoadShader(simpleShaderResource);

    //Plane* plane = ArenaAllocator::New<Plane>(renderingArena, Color::PASTEL_PEACH);
    // Cube* cube = ArenaAllocator::New<Cube>(renderingArena, Color::PASTEL_RED);
    Sphere* sphere = ArenaAllocator::New<Sphere>(renderingArena, Color::PASTEL_RED, 16, 16);
    
    Arrow* arrowX = ArenaAllocator::New<Arrow>(renderingArena, Color::PASTEL_RED);
    Mat4 modelArrowX = Mat4::Identity;
    modelArrowX = Quat::FromRPY(MathCore::DegToRad(90.0f), 0.0f, 0.0f).ToMat4();
    
    Arrow* arrowY = ArenaAllocator::New<Arrow>(renderingArena, Color::PASTEL_GREEN);
    
    Arrow* arrowZ = ArenaAllocator::New<Arrow>(renderingArena, Color::PASTEL_BLUE);
    Mat4 modelArrowZ = Mat4::Identity;
    modelArrowZ = Quat::FromRPY(0.0f, 0.0f, MathCore::DegToRad(-90.0f)).ToMat4();
    
    // TODO: collect texture memory data
    Texture* diffuseMap = ArenaAllocator::New<Texture>(renderingArena, "../res/textures/scuffed-plastic3-alb.png");
    Texture* roughnessMap = ArenaAllocator::New<Texture>(renderingArena, "../res/textures/scuffed-plastic-rough.png");
    Texture* metallicMap = ArenaAllocator::New<Texture>(renderingArena, "../res/textures/scuffed-plastic-metal.png");
    Texture* normalMap = ArenaAllocator::New<Texture>(renderingArena, "../res/textures/scuffed-plastic-normal.png");
    
    
    Material* pbrMaterial = ArenaAllocator::New<Material>(renderingArena, pbrShaderResource, resourceManager);
    pbrMaterial->diffuseMap = diffuseMap;
    pbrMaterial->roughnessMap = roughnessMap;
    pbrMaterial->metallicMap = metallicMap;
    pbrMaterial->normalMap = normalMap;

    Material* material = ArenaAllocator::New<Material>(renderingArena, simpleShaderResource, resourceManager);
    Renderer* renderer = ArenaAllocator::New<Renderer>(renderingArena, cam);
    
    renderer->PointLights = 
    {
        {{1.5f, 2.0f, 1.5f}, {1.0f, 0.8f, 0.6f}, 15.0f},
        {{-1.0f, 1.0f, 0.0f}, {0.4f, 0.6f, 1.0f}, 8.0f}
    };

    Framebuffer* framebuffer = ArenaAllocator::New<Framebuffer>(renderingArena);
    framebuffer->Init(window->GetWidth(), window->GetHeight());
    window->SetFramebuffer(framebuffer);

    SandboxUI* ui = ArenaAllocator::New<SandboxUI>(globalAppArena);
    ui->Init(window->GetGlfwWindow());

    Mat4 model = Mat4::Identity;
    //model.SetScale({0.1f, 0.1f, 0.1f});
    model.SetPosition({0.5f, 0.0f, 0.5f});

    Mat4 modelSphere = Mat4::Identity;
    //modelSphere.SetScale({0.2f, 0.2f, 0.2f});
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
        for (const PointLight& light : renderer->PointLights)
        {
            debugRenderer->DrawLightBulb(light.Position, light.Color);
        }
        debugRenderer->Render(*cam);
        
        renderer->DrawMesh(*sphere, *pbrMaterial, modelSphere);
        renderer->DrawMesh(*arrowX, *material, modelArrowX);
        renderer->DrawMesh(*arrowY, *material, Mat4::Identity);
        renderer->DrawMesh(*arrowZ, *material, modelArrowZ);
      //  renderer.DrawMesh(cube, material, modelSphere);
       // renderer->DrawMesh(*plane, *material, model);
        
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
