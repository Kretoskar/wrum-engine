﻿#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "WrumCore/Core/HString.h"
#include "WrumCore/Core/Types.h"

namespace Wrum
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

        uint16 GetWidth() const { return _width; }
        uint16 GetHeight() const { return _height; }
        
    protected:
        void BindWindowEvents();
        void UpdateWindowDimensions();

        virtual void OnWindowMoved(int16 xPos, int16 yPos){}
        
        virtual void OnWindowMinimized() {}
        virtual void OnWindowRestored() {}
        
        virtual void OnWindowMaximized() {}
        virtual void OnWindowUnmaximized() {}

        virtual void OnWindowResized(uint16 width, uint16 height) {}
        
        GLFWwindow* _glfwWindow = nullptr;
        bool _isValid = false;

        uint16 _width {}, _height{};
        HString _name;
    };
} 