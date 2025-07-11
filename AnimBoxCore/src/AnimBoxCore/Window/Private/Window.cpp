#include "PCH.h"
#include "AnimBoxCore/Window/Public/Window.h"

using namespace AnimBox;

void Window::BindWindowEvents()
{
    /* Save the pointer to the instance as user pointer */
    glfwSetWindowUserPointer(_glfwWindow, this);

    /* Use a lambda to get the pointer and call the member function */
    glfwSetWindowPosCallback(GetGlfwWindow(), [](GLFWwindow* win, int xPos, int yPos)
    {
        Window* thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
        // TODO: custom narrowing cast
        thisWindow->HandleWindowMoveEvents(xPos, yPos);
    });
}