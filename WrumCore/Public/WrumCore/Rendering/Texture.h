#pragma once



namespace Wrum
{
    struct Texture
    {
        u32 _id;
        u32 _type;
        u32 _unit;
        i32 _width, _height, _numColCh;

    public:
        Texture(HString path, u32 unit = 0, u32 format = GL_RGB, u32 pixelType = GL_UNSIGNED_BYTE, u32 texType = GL_TEXTURE_2D);
        void Bind();
        void Bind(u32 unit);
        void Delete();
    };
}
