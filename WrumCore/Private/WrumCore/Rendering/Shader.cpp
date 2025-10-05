#include "PCH.h"
#include <glad/glad.h>
#include "WrumCore/Rendering/Shader.h"

namespace Wrum
{
    Shader::Shader(const File& vertexShaderFile, const File& fragmentShaderFile)
    {
        Create(vertexShaderFile, fragmentShaderFile);
    }

    Shader::~Shader()
    {
        Delete();
    }

    void Shader::Create(const File& vertexShaderFile, const File& fragmentShaderFile)
    {
        _id = CreateShader(vertexShaderFile, fragmentShaderFile);
    }

    void Shader::Bind() const
    {
        glUseProgram(_id);
    }

    void Shader::Delete()
    {
        glDeleteProgram(_id);
    }

    void Shader::SetUniform4f(HString name, float v0, float v1, float v2, float v3)
    {
        Bind();
        glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
    }

    void Shader::SetUniform1f(HString name, float v0)
    {
        Bind();
        glUniform1f(GetUniformLocation(name), v0);
    }

    void Shader::SetUniform2f(HString name, float v0, float v1)
    {
        Bind();
        glUniform2f(GetUniformLocation(name), v0, v1);
    }

    void Shader::SetUniform3f(HString name, float v0, float v1, float v2)
    {
        Bind();
        glUniform3f(GetUniformLocation(name), v0, v1, v2);
    }

    void Shader::SetUniform1i(HString name, int v0)
    {
        Bind();
        glUniform1i(GetUniformLocation(name), v0);
    }

    void Shader::SetUniformMat4f(HString name, const Mat4& mat)
    {
        Bind();
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat.v[0]);
    }

    void Shader::SetModelMatrix(Mat4 m)
    {
        Bind();
        SetUniformMat4f("model", m);
    }

    void Shader::SetVPMatrix(Mat4 m)
    {
        Bind();
        SetUniformMat4f("viewProj", m);
    }

    void Shader::SetCameraPosition(Vec3 pos)
    {
        Bind();
        SetUniform3f("cameraPos", pos.x, pos.y, pos.z);
    }

    void Shader::AssignDiffuseMap(Texture& texture)
    {
        Bind();
        texture.Bind();
        SetUniform1i("diffuseMap", 0);
    }

    int Shader::GetUniformLocation(HString name)
    {
        Bind();

        const char* nameChar = name.Get();

        if (_uniformLocationCache.contains(nameChar))
        {
            return _uniformLocationCache[nameChar];
        }

        const int location = glGetUniformLocation(_id, nameChar);
        _uniformLocationCache[nameChar] = location;

        if (location < 0)
        {
            LOG_WARNING("Trying to retrieve invalid uniform location of name %s", nameChar)
        }

        return 1;
    }

    uint32_t Shader::CreateShader(const File& vertexShaderFile, const File& fragmentShaderFile)
    {
        if (!vertexShaderFile.IsValid() || !fragmentShaderFile.IsValid())
        {
            LOG_ERROR("Failed to create shader from provided files")
            return 0;
        }

        unsigned int program = glCreateProgram();
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, *vertexShaderFile.GetFileContents());
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, *fragmentShaderFile.GetFileContents());

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }


    uint32_t Shader::CompileShader(unsigned int type, const std::string& source)
    {
        unsigned int id = glCreateShader(type);
        const char* scr = source.c_str();
        glShaderSource(id, 1, &scr, nullptr);
        glCompileShader(id);

        int32 result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            int32 length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = static_cast<char*>(alloca(length * sizeof(char)));
            glGetShaderInfoLog(id, length, &length, message);

            LOG_ERROR(message)
            glDeleteShader(id);

            return 0;
        }

        return id;
    }
}
