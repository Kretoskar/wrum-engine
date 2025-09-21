#include "PCH.h"
#include "WrumCore/Controllers/InputController.h"

#include "WrumCore/Core/EventSystem.h"
#include "WrumCore/Window/Window.h"

namespace Wrum
{
    void InputController::PollKey(Input input, int32_t glKeyState)
    {
        if (glKeyState == GLFW_PRESS || glKeyState == GLFW_REPEAT)
        {
            if (Inputs[input] == InputState::Pressed || Inputs[input] == InputState::Held)
            {
                Inputs[input] = InputState::Held;    
            }
            else
            {
                Inputs[input] = InputState::Pressed;    
            }
            
        }
        else if (glKeyState == GLFW_RELEASE)
        {
            if (Inputs[input] == InputState::Pressed || Inputs[input] == InputState::Held)
            {
                Inputs[input] = InputState::Released;    
            }
            else
            {
                Inputs[input] = InputState::None;    
            }
        }
    }

    void InputController::PollInput(const Window& window)
    {
        GLFWwindow* glfwWindow = window.GetGlfwWindow();

       PollKey(Input::W, glfwGetKey(glfwWindow, GLFW_KEY_W));
       PollKey(Input::A, glfwGetKey(glfwWindow, GLFW_KEY_A));
       PollKey(Input::S, glfwGetKey(glfwWindow, GLFW_KEY_S));
       PollKey(Input::D, glfwGetKey(glfwWindow, GLFW_KEY_D));
       PollKey(Input::RightMouseButton, glfwGetMouseButton(glfwWindow, GLFW_MOUSE_BUTTON_RIGHT));
       PollKey(Input::LeftShift, glfwGetKey(glfwWindow, GLFW_KEY_LEFT_SHIFT));
    }

    InputState InputController::GetInput(Input input)
    {
        return Inputs[input];
    }

    bool InputController::InputPressedOrHeld(Input input)
    {
        return GetInput(input) == InputState::Pressed ||  GetInput(input) == InputState::Held;
    }
}
