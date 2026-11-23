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
    ResourceManager::SetInstance(resourceManager);
    
    Framebuffer* framebuffer = ArenaAllocator::New<Framebuffer>(renderingArena);
    framebuffer->Init(window->GetWidth(), window->GetHeight());
    window->SetFramebuffer(framebuffer);

    SandboxUI* ui = ArenaAllocator::New<SandboxUI>(globalAppArena);
    ui->Init(window->GetGlfwWindow());
    
    Renderer* renderer = ArenaAllocator::New<Renderer>(renderingArena, cam);
    
    renderer->PointLights = 
    {
        {{1.5f, 2.0f, 1.5f}, {1.0f, 0.8f, 0.6f}, 15.0f},
        {{-1.0f, 1.0f, 0.0f}, {0.4f, 0.6f, 1.0f}, 8.0f}
    };
    
    ResourceID pbrShaderResource = resourceManager->MakeShaderResource("shaders/pbr.vert", "shaders/pbr.frag");
    resourceManager->LoadShader(pbrShaderResource);

    ResourceID simpleShaderResource = resourceManager->MakeShaderResource("shaders/pbr.vert", "shaders/vertexColor.frag");
    resourceManager->LoadShader(simpleShaderResource);

    //Plane* plane = ArenaAllocator::New<Plane>(renderingArena, Color::PASTEL_PEACH);
    // Cube* cube = ArenaAllocator::New<Cube>(renderingArena, Color::PASTEL_RED);
    
    ResourceID sphereResource = resourceManager->MakePrimitiveMeshResource(PrimitiveType::Sphere, Color::RED);
    resourceManager->LoadPrimitiveMesh(sphereResource);
    
    ResourceID arrowXResource = resourceManager->MakePrimitiveMeshResource(PrimitiveType::Arrow, Color::PASTEL_RED);
    resourceManager->LoadPrimitiveMesh(arrowXResource);
    
    // TODO: Store color in material
    Mat4 modelArrowX = Mat4::Identity;
    modelArrowX = Quat::FromRPY(MathCore::DegToRad(90.0f), 0.0f, 0.0f).ToMat4();
    
    Arrow* arrowY = ArenaAllocator::New<Arrow>(renderingArena, Color::PASTEL_GREEN);
    
    Arrow* arrowZ = ArenaAllocator::New<Arrow>(renderingArena, Color::PASTEL_BLUE);
    Mat4 modelArrowZ = Mat4::Identity;
    modelArrowZ = Quat::FromRPY(0.0f, 0.0f, MathCore::DegToRad(-90.0f)).ToMat4();
    
    // TODO: collect texture memory data
    ResourceID diffuseMapResource = resourceManager->MakeTextureResource("../res/textures/scuffed-plastic3-alb.png");
    ResourceID roughnessMapResource = resourceManager->MakeTextureResource("../res/textures/scuffed-plastic-rough.png");
    ResourceID metallicMapResource = resourceManager->MakeTextureResource("../res/textures/scuffed-plastic-metal.png");
    ResourceID normalMapResource = resourceManager->MakeTextureResource("../res/textures/scuffed-plastic-normal.png");
    resourceManager->LoadTexture(diffuseMapResource);
    resourceManager->LoadTexture(roughnessMapResource);
    resourceManager->LoadTexture(metallicMapResource);
    resourceManager->LoadTexture(normalMapResource);
    
    ResourceID pbrMaterialResource = resourceManager->MakeMaterialResource(pbrShaderResource);
    // TODO: encode shader resource as path and add laod material maybe?
    Material* pbrMaterial = resourceManager->GetMaterial(pbrMaterialResource);
    pbrMaterial->diffuseMapResource = diffuseMapResource;
    pbrMaterial->roughnessMapResource = roughnessMapResource;
    pbrMaterial->metallicMapResource = metallicMapResource;
    pbrMaterial->normalMapResource = normalMapResource;

    Material* material = ArenaAllocator::New<Material>(renderingArena, simpleShaderResource);
    
    ResourceID simpleMaterialResource = resourceManager->MakeMaterialResource(simpleShaderResource);

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
        
        for (i32 i = 0; i < 10; ++i)
        {
            //modelSphere.SetPosition(modelSphere.position.ToVec3() + Vec3(1.0f, 0.0f, 0.0f));
            for (i32 j = 0; j < 10; ++j)
            {
                for (i32 k = 0; k < 10; ++k)
                {
                    modelSphere.SetPosition(Vec3(i, j, k));
                    renderer->AddMeshToRender(sphereResource, pbrMaterialResource, modelSphere);
                }
            }
        }
        
        renderer->AddMeshToRender(arrowXResource, simpleMaterialResource, modelArrowX);
        
        renderer->DrawMesh(*arrowY, *resourceManager->GetMaterial(simpleMaterialResource), Mat4::Identity);
        renderer->DrawMesh(*arrowZ, *material, modelArrowZ);
        
        renderer->Render();
        
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
