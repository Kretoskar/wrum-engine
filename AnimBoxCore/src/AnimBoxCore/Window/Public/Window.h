#pragma once

#include "glfw/include/GLFW/glfw3.h"
#include "AnimBoxCore/Core/Public/HString.h"

namespace AnimBox
{
    class Window
    {
    public:
        virtual ~Window() = default;
        
        virtual bool Init() = 0;
        virtual void Update() = 0;
        virtual void Shutdown() = 0;

        GLFWwindow* GetGlfwWindow() const { return _glfwWindow; }
        bool GetShouldClose() const { return _glfwWindow ? glfwWindowShouldClose(_glfwWindow) : false; }

    protected:
        void BindWindowEvents();

        virtual void HandleWindowMoveEvents(int16_t xPos, int16_t yPos){}
        
        GLFWwindow* _glfwWindow = nullptr;
        bool _isValid = false;

        uint32_t _width {}, _height{};
        HString _name;
    };
} 