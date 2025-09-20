#pragma once

#include <GLFW/glfw3.h>

namespace Wrum
{
    class UI
    {
    public:
        virtual ~UI() = default;
        
        bool Init(GLFWwindow* window);
        void CreateFrame(double deltaTime);
        void Render();
        void Cleanup();

    protected:
        virtual void CreateWidgets() = 0;

        double dt = 0.0;
    };
}