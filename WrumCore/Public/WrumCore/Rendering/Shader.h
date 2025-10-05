#pragma once

#include "Texture.h"
#include "WrumCore/Core/HString.h"
#include "WrumCore/Math/Mat4.h"
#include "WrumCore/Math/Vec3.h"
#include "WrumCore/ResourceHandling/File.h"

namespace Wrum
{
    class Shader
    {
        std::unordered_map<HString, int32, HString::HStringHasher> _uniformLocationCache;

        uint32 _id;

    public:
        Shader(const File& vertexShaderFile, const File& fragmentShaderFile);
        ~Shader();

        void Create(const File& vertexShaderFile, const File& fragmentShaderFile);
        void Bind() const;
        void Delete();

        void SetUniform4f(HString name, float v0, float v1, float v2, float v3);
        void SetUniform1f(HString name, float v0);
        void SetUniform2f(HString name, float v0, float v1);
        void SetUniform3f(HString name, float v0, float v1, float v2);
        void SetUniform1i(HString name, int v0);

        void SetUniformMat4f(HString name, const Mat4& mat);

        void SetModelMatrix(Mat4 m);
        void SetVPMatrix(Mat4 m);
        void SetCameraPosition(Vec3 pos);

        void AssignDiffuseMap(Texture& texture);

    private:
        int GetUniformLocation(HString name);
        static uint32 CreateShader(const File& vertexShaderFile, const File& fragmentShaderFile);
        static uint32 CompileShader(unsigned int type, const std::string& source);
    };
}
