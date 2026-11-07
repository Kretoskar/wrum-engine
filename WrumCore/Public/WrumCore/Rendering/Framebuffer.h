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
        u32 _bufferWidth = 640;
        u32 _bufferHeight = 480;
        u32 _buffer = 0;
        u32 _colorTex = 0;
        u32 _depthBuffer = 0;

        bool CheckComplete();
    };
}