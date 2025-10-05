#include "PCH.h"

#include "stb_image/stb_image.h"
#include "WrumCore/Rendering/Texture.h"

namespace Wrum
{
    Texture::Texture(HString path, uint32_t unit, uint32_t format, uint32_t pixelType, uint32_t texType)
        : _type(texType), _unit(unit)
    {
        stbi_set_flip_vertically_on_load(false);
        unsigned char* _bytes = stbi_load(path.Get(), &_width, &_height, &_numColCh, 4);

        glGenTextures(1, &_id);

        glActiveTexture(GL_TEXTURE0 + _unit);
        glBindTexture(_type, _id);

        glTexParameteri(_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexParameteri(_type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(_type, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(_type, 0, GL_RGBA, _width, _height, 0, GL_RGBA, pixelType, _bytes);
        glGenerateMipmap(_type);

        stbi_image_free(_bytes);
        glBindTexture(_type, 0);
    }

    void Texture::Bind()
    {
        glActiveTexture(GL_TEXTURE0 + _unit);
        glBindTexture(_type, _id);
    }

    void Texture::Delete()
    {
        glDeleteTextures(1, &_id);
    }
}
