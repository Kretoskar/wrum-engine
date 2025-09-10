#include "PCH.h"
#include "WrumCore/Window/Window.h"

#include "WrumCore/Core/Types.h"

using namespace Wrum;

void Window::BindWindowEvents()
{
    /* Save the pointer to the instance as user pointer */
    glfwSetWindowUserPointer(_glfwWindow, this);

    /* Use a lambda to get the pointer and call the member function */
    glfwSetWindowPosCallback(GetGlfwWindow(), [](GLFWwindow* win, int xPos, int yPos)
    {
        Window* thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
        thisWindow->OnWindowMoved(SafeCast_int16(xPos), SafeCast_int16(yPos));
    });

    glfwSetWindowIconifyCallback(GetGlfwWindow(), [](GLFWwindow* win, int minimized)
    {
        Window* thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));

        if (minimized)
        {
            thisWindow->OnWindowMinimized();
        }
        else
        {
            thisWindow->OnWindowRestored();
        }
    });

    glfwSetWindowMaximizeCallback(GetGlfwWindow(), [](GLFWwindow* win, int maximized)
    {
        Window* thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
        if (maximized)
        {
            thisWindow->OnWindowMaximized();
        }
        else
        {
            thisWindow->OnWindowUnmaximized();
        }
    });

    glfwSetFramebufferSizeCallback(_glfwWindow, [](GLFWwindow* win, int width, int height)
    {
        Window* thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
        thisWindow->OnWindowResized(SafeCast_uint16(width), SafeCast_uint16(height));
    });
}

void Window::UpdateWindowDimensions()
{
    int width;
    int height;
    glfwGetWindowSize(GetGlfwWindow(), &width, &height);
    _width = width;
    _height = height;
    glViewport(0,0,width,height);
}
