#include "PCH.h"
#include "AnimBoxCore/Core/EventSystem.h"
#include "AnimBoxCore/Memory/ArenaAllocator.h"

#include "AnimBoxRuntime/Application/Application.h"
#include "AnimBoxRuntime/Window/AnimBoxWindow.h"

void AnimBoxRuntime::Application::Run()
{
    AnimBox::ArenaAllocator Arena(1024 * 1024);
    
    AnimBox::Dispatcher::Init(Arena);
    
    AnimBoxWindow window;
    window.Init();
    while (!window.GetShouldClose())
    {
        // Call all pending events 
        AnimBox::Dispatcher::CallEvents();
        window.Update();
    }
}
