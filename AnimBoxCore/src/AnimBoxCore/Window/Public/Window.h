#pragma once

#include "glfw/include/GLFW/glfw3.h"
#include "AnimBoxCore/Core/Public/HString.h"

namespace AnimBox
{
    class Window
    {
    public:
        virtual bool Init() { return true; }
        virtual void Update() {}
        virtual void Shutdown() {}

        GLFWwindow* GetGlfwWindow() const { return _glfwWindow; }
        bool GetShouldClose() const { return _glfwWindow ? glfwWindowShouldClose(_glfwWindow) : false; }

    protected:
        GLFWwindow* _glfwWindow = nullptr;
        bool _isValid = false;

        uint32_t _width, _height;
        HString _name;
    };
}