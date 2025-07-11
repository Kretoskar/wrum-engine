#include "AnimBoxWindow.h"

#include "AnimBoxCore/Core/Public/EventSystem.h"

bool AnimBox::AnimBoxWindow::Init()
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
    _width = videoMode->width / 2;
    _height = videoMode->height / 2;
    _name = "Anim Box";

    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    
    _glfwWindow = glfwCreateWindow(
        _width,
        _height,
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

    //if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    //{
    //	TURTLE_LOG_ERROR("Failed to initialize GLAD")
    //		return false;
    //}

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glViewport(0, 0, _width, _height);
    glClearColor(0.15f, 0.5f, 1.0f, 1.0f);

    // force VSYNC
    glfwSwapInterval(1);

    BindWindowEvents();
    
    return true;
}

void AnimBox::AnimBoxWindow::Update()
{
    glfwSwapBuffers(_glfwWindow);
    glfwPollEvents();
}

void AnimBox::AnimBoxWindow::Shutdown()
{
    glfwDestroyWindow(_glfwWindow);
    glfwTerminate();
}

void AnimBox::AnimBoxWindow::HandleWindowMoveEvents(int16_t xPos, int16_t yPos)
{
    LOG_MESSAGE("it's %d %d", xPos, yPos)
}
