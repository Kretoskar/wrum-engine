#include "PCH.h"
#include "AnimBoxCore/Core/EventSystem.h"

AnimBox::Dispatcher* AnimBox::Dispatcher::_instance = nullptr;

void AnimBox::Dispatcher::Init(ArenaAllocator& Arena)
{
    _instance =  ArenaAllocator::New<Dispatcher>(Arena);
}

void AnimBox::Dispatcher::Subscribe(HString Type, std::function<void(void*)>&& Func)
{
    // TODO: std::move?
    _observers[Type].push_back(Func);
}

void AnimBox::Dispatcher::Post(HString Type, void* Payload)
{
    _eventsReadyToPost.emplace_back(Type,Payload);
}

void AnimBox::Dispatcher::CallEvents()
{
    Dispatcher* dispatcher = AnimBox::Dispatcher::GetInstance();

#if AB_DEBUG
    if (!dispatcher)
    {
        LOG_ERROR("Dispatcher is null, can't call events");
        return;
    }
#endif
    
    for (Event& e : dispatcher->_eventsReadyToPost)
    {
        if (!dispatcher->_observers.contains(e.Type))
        {
            return;
        }
    
        auto&& observers = dispatcher->_observers.at(e.Type);
    
        for (auto&& observer : observers)
        {
            observer(e.Payload);
        }
    }
    
    dispatcher->_eventsReadyToPost.clear();
}
