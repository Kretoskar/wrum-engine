#include "PCH.h"
#include "WrumCore/Core/EventSystem.h"

Wrum::Dispatcher* Wrum::Dispatcher::_instance = nullptr;

void Wrum::Dispatcher::Init(ArenaAllocator& Arena)
{
    _instance =  ArenaAllocator::New<Dispatcher>(Arena);
}

void Wrum::Dispatcher::Subscribe(HString Type, std::function<void(void*)>&& Func)
{
    // TODO: std::move?
    _observers[Type].push_back(Func);
}

void Wrum::Dispatcher::Post(HString Type, void* Payload)
{
    _eventsReadyToPost.emplace_back(Type,Payload);
}

void Wrum::Dispatcher::CallEvents()
{
    Dispatcher* dispatcher = Wrum::Dispatcher::GetInstance();

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
