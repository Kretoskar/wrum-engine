#include "PCH.h"
#include "WrumCore/Rendering/Framebuffer.h"

using namespace Wrum;

bool Wrum::Framebuffer::Init(unsigned int width, unsigned int height)
{
    _bufferWidth = width;
    _bufferHeight = height;

    glGenFramebuffers(1, &_buffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _buffer);

    /* color texture */
    glGenTextures(1, &_colorTex);
    glBindTexture(GL_TEXTURE_2D, _colorTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height,  0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, _colorTex, 0);

    /* render buffer as depth buffer */
    glGenRenderbuffers(1, &_depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return CheckComplete();
}

bool Wrum::Framebuffer::Resize(unsigned int newWidth, unsigned int newHeight)
{
    _bufferWidth = newWidth;
    _bufferHeight = newHeight;

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glDeleteTextures(1, &_colorTex);
    glDeleteRenderbuffers(1, &_depthBuffer);
    glDeleteFramebuffers(1, &_buffer);

    return Init(newWidth, newHeight);
}

void Wrum::Framebuffer::Bind()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _buffer);
}

void Wrum::Framebuffer::Unbind()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void Wrum::Framebuffer::Draw()
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, _buffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(0, 0, _bufferWidth, _bufferHeight, 0, 0, _bufferWidth, _bufferHeight,
                    GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}

void Wrum::Framebuffer::Cleanup()
{
    Unbind();

    glDeleteTextures(1, &_colorTex);
    glDeleteRenderbuffers(1, &_depthBuffer);
    glDeleteFramebuffers(1, &_buffer);
}

bool Wrum::Framebuffer::CheckComplete()
{
    glBindFramebuffer(GL_FRAMEBUFFER, _buffer);

    GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (result != GL_FRAMEBUFFER_COMPLETE)
    {
        LOG_ERROR("framebuffer is NOT complete")
        return false;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return true;
}
