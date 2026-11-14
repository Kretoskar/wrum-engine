#pragma once

#include <span>

#include "Texture.h"
#include "WrumCore/Core/HString.h"
#include "WrumCore/Math/Mat4.h"
#include "WrumCore/Math/Vec3.h"
#include "WrumCore/Rendering/Light/PointLight.h"
#include "WrumCore/ResourceHandling/File.h"

namespace Wrum
{
    class Shader
    {
        std::unordered_map<HString, i32, HString::HStringHasher> _uniformLocationCache;

        u32 _id;

    public:
        // Must match MAX_POINT_LIGHTS in pbr.frag
        static constexpr u32 MaxPointLights = 16;

        Shader() = default;
        Shader(const File& vertexShaderFile, const File& fragmentShaderFile);
        ~Shader();

        void Create(const File& vertexShaderFile, const File& fragmentShaderFile);
        void Bind() const;
        void Delete();

        void SetUniform4f(HString name, f32 v0, f32 v1, f32 v2, f32 v3);
        void SetUniform1f(HString name, f32 v0);
        void SetUniform2f(HString name, f32 v0, f32 v1);
        void SetUniform3f(HString name, f32 v0, f32 v1, f32 v2);
        void SetUniform1i(HString name, i32 v0);

        void SetUniformMat4f(HString name, const Mat4& mat);

        void SetModelMatrix(const Mat4& m);
        void SetVPMatrix(const Mat4& m);
        void SetCameraPosition(const Vec3& pos);
        void SetPointLights(std::span<const PointLight> pointLights);

        void AssignDiffuseMap(Texture& texture);

    private:
        i32 GetUniformLocation(HString name);
        static u32 CreateShader(const File& vertexShaderFile, const File& fragmentShaderFile);
        static u32 CompileShader(u32 type, const std::string& source);
    };
}
