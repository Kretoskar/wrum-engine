#include "PCH.h"
#include "WrumCore/Core/EventSystem.h"
#include "WrumCore/Memory/ArenaAllocator.h"

#include "Sandbox/Application/Application.h"
#include "Sandbox/Window/SandboxWindow.h"
#include "WrumCore/ResourceHandling/File.h"

void Sandbox::Application::Run()
{
    Wrum::ArenaAllocator Arena(1024 * 1024);
    
    Wrum::Dispatcher::Init(Arena);
    
    SandboxWindow window;
    window.Init();

    Wrum::File file = Wrum::File("test.txt", true, &Arena);


    for (const std::string& line : file.GetLines())
    {
        LOG_MESSAGE("%s", line.c_str());
    }
    
    while (!window.GetShouldClose())
    {
        // Call all pending events 
        Wrum::Dispatcher::CallEvents();
        window.Update();
    }
}
