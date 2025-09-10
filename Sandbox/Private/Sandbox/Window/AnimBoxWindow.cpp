#include "Sandbox/Window/SandboxWindow.h"
#include "WrumCore/Core/EventSystem.h"
#include "WrumCore/Rendering/Framebuffer.h"

bool Sandbox::SandboxWindow::Init()
{
    if (!glfwInit())
    {
        LOG_ERROR("Failed to initialize window")
        return false;
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // Get the primary monitor
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    if (!primaryMonitor)
    {
        LOG_ERROR("no monitor found")
        return false;
    }

    // Get the current video mode of the monitor
    const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);
    if (!videoMode) {
        LOG_ERROR("no video mode found")
        return false;
    }

    // Use monitor's resolution
    _width = SafeCast_uint16(videoMode->width / 2);
    _height = SafeCast_uint16(videoMode->height / 2);
    _name = "Wrum Engine: Sandbox";

    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    
    _glfwWindow = glfwCreateWindow(
        SafeCast_int(_width),
        SafeCast_int(_height),
        _name.Get(),
        nullptr,
        nullptr);

    if (!_glfwWindow)
    {
        LOG_ERROR("Failed to initialize window")
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(_glfwWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
    	LOG_ERROR("Failed to initialize GLAD")
        return false;
    }

   //glEnable(GL_DEPTH_TEST);
   //glEnable(GL_BLEND);

   //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glViewport(0, 0, SafeCast_int(_width),  SafeCast_int(_height));
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // force VSYNC
    glfwSwapInterval(1);

    UpdateWindowDimensions();
    BindWindowEvents();
    
    return true;
}

void Sandbox::SandboxWindow::Update()
{
    glfwSwapBuffers(_glfwWindow);
    glfwPollEvents();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Sandbox::SandboxWindow::Shutdown()
{
    glfwDestroyWindow(_glfwWindow);
    glfwTerminate();
}

void Sandbox::SandboxWindow::OnWindowMoved(int16 xPos, int16 yPos)
{
}

void Sandbox::SandboxWindow::OnWindowMinimized()
{
    UpdateWindowDimensions();
    if (_framebuffer)
    {
        _framebuffer->Resize(GetWidth(), GetHeight());
    }
}

void Sandbox::SandboxWindow::OnWindowRestored()
{
    UpdateWindowDimensions();
    if (_framebuffer)
    {
        _framebuffer->Resize(GetWidth(), GetHeight());
    }
}

void Sandbox::SandboxWindow::OnWindowMaximized()
{
    UpdateWindowDimensions();
    if (_framebuffer)
    {
        _framebuffer->Resize(GetWidth(), GetHeight());
    }
}

void Sandbox::SandboxWindow::OnWindowUnmaximized()
{
    UpdateWindowDimensions();
    if (_framebuffer)
    {
        _framebuffer->Resize(GetWidth(), GetHeight());
    }
}

void Sandbox::SandboxWindow::OnWindowResized(uint16 width, uint16 height)
{
    if (_framebuffer)
    {
        _framebuffer->Resize(width, height);
    }
    UpdateWindowDimensions();
}
