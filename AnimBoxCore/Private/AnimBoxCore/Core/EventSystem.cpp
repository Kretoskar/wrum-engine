#include "PCH.h"
#include "AnimBoxCore/Core/EventSystem.h"

AnimBox::Dispatcher* AnimBox::Dispatcher::_instance = nullptr;

void AnimBox::Dispatcher::Init(ArenaAllocator& Arena)
{
    _instance = ArenaAllocator::New<Dispatcher>(Arena);
}

void AnimBox::Dispatcher::Subscribe(HString Type, std::function<void(void*)>&& Func)
{
    // TODO: std::move?
    _observers[Type].push_back(Func);
}

void AnimBox::Dispatcher::Post(HString Type, void* Payload) const
{
    if (!_observers.contains(Type))
    {
        return;
    }

    auto&& observers = _observers.at(Type);

    for (auto&& observer : observers)
    {
        observer(Payload);
    }
}