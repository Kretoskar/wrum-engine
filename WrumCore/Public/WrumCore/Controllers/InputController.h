#pragma once
#include <map>

namespace Wrum
{
    class Window;
}

namespace Wrum
{
    enum class Input
    {
        W,
        A,
        S,
        D,
        RightMouseButton,
    };

    enum class InputState
    {
        None,
        Pressed,
        Held,
        Released,
    };
    
    class InputController
    {
    public:
        static void PollInput(const Window& window);
        static InputState GetInput(Input input);
        
    private:
        static void PollKey(Input input, int32 glKeyState);
        
        static inline std::map<Input, InputState> Inputs
        {
            {Input::W, InputState::None},
            {Input::A, InputState::None},
            {Input::S, InputState::None},
            {Input::D, InputState::None},
            {Input::RightMouseButton, InputState::None},
        };
    };
}
