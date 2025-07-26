#pragma once

#include "PCH.h"

#include <functional>
#include <map>
#include <vector>

#include "AnimBoxCore/Core/HString.h"

#define BIND_EVENT(type, event) \
AnimBox::Dispatcher::GetInstance()->Subscribe(type, \
[this](auto&& PH1) \
{ \
event(std::forward<decltype(PH1)>(PH1)); \
});

#define POST_EVENT(type, payload) \
AnimBox::Dispatcher::GetInstance()->Post(type, payload);

namespace AnimBox
{
    class Dispatcher
    {
    public:
        Dispatcher() = default;
        
        static void Init(ArenaAllocator& Arena);

        Dispatcher(Dispatcher const&) = delete;
        void operator=(Dispatcher const&) = delete;

        [[nodiscard]]
        static Dispatcher* GetInstance()
        {
            return _instance;
        }

        void Subscribe(HString Type, std::function<void(void*)>&& Func);

        void Post(HString Type, void* Payload);
        
        static void CallEvents();
        
    private:
        static Dispatcher* _instance;
        std::map<HString, std::vector<std::function<void(void*)>>> _observers;

        struct Event
        {
            Event(HString Type, void* Payload) : Type(Type), Payload(Payload) {}
            
            HString Type;
            void* Payload;
        };
        
        std::vector<Event> _eventsReadyToPost;
    };

    namespace CustomEvent
    {
        static HString Type(HString name)
        {
            return name;
        }
    }
    
    namespace MouseButtonEvent
    {
        static HString Type(int button, int action, int mods)
        {
            static std::map<unsigned, HString> lookupMap;

            const unsigned lookupKey = button * 100 + action * 10 + mods;
            if (lookupMap.count(lookupKey) == 0)
            {
                char buffer[100];
                sprintf_s(buffer, "MouseButton%i%i%i", button, action, mods);
                lookupMap[lookupKey] = buffer;
            }


            return lookupMap[lookupKey];
        }
    };

    namespace KeyboardEvent
    {
        static HString Type(int key, int action, int mods)
        {
            static std::map<unsigned, HString> lookupMap;

            const unsigned lookupKey = key * 100 + action * 10 + mods;
            if (lookupMap.count(lookupKey) == 0)
            {
                char buffer[100];
                sprintf_s(buffer, "Key%i%i%i", key, action, mods);
                lookupMap[lookupKey] = buffer;
            }


            return lookupMap[lookupKey];
        }
    };

    namespace MousePositionEvent
    {
        struct MousePositionEventPayload
        {
            int32 posX, posY;
        };

        static HString Type()
        {
            static HString type = HString("MousePos");
            return type;
        }
    }
}