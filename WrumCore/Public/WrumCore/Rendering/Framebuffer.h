#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Wrum
{
    class Framebuffer
    {
    public:
        bool Init(unsigned int width, unsigned int height);
        bool Resize(unsigned int newWidth, unsigned int newHeight);
        void Bind();
        void Unbind();
        void Draw();
        void Cleanup();

    private:
        unsigned _bufferWidth = 640;
        unsigned _bufferHeight = 480;
        unsigned _buffer = 0;
        unsigned _colorTex = 0;
        unsigned _depthBuffer = 0;

        bool CheckComplete();
    };
}