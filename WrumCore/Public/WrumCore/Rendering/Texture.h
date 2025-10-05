#pragma once



namespace Wrum
{
    struct Texture
    {
        uint32 _id;
        uint32 _type;
        uint32 _unit;
        int32 _width, _height, _numColCh;

    public:
        Texture(HString path, uint32 unit = GL_TEXTURE0, uint32 format = GL_RGB, uint32 pixelType = GL_UNSIGNED_BYTE, uint32 texType = GL_TEXTURE_2D);
        void Bind();
        void Delete();
    };
}