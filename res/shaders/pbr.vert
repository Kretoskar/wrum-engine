#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTexUV;
layout (location = 4) in mat4 instanceModel;

out vec3 pos;
out vec3 normal;
out vec3 color;
out vec2 texUV;

uniform mat4 viewProj;

void main()
{
    pos = vec3(instanceModel * vec4(aPos, 1.0f));
    normal = transpose(inverse(mat3(instanceModel))) * aNormal;
    color = aColor;
    texUV = aTexUV;

    gl_Position = viewProj * vec4(pos, 1.0f);
}
