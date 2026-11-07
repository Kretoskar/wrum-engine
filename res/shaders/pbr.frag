#version 330 core
out vec4 FragColor;

in vec3 pos;
in vec3 normal;
in vec3 color;
in vec2 texUV;

uniform sampler2D diffuseMap;
uniform sampler2D roughnessMap;
uniform sampler2D metallicMap;
uniform sampler2D normalMap;

uniform bool hasRoughnessMap;
uniform bool hasMetallicMap;
uniform bool hasNormalMap;

uniform vec3 cameraPos;
uniform float metallic;
uniform float roughness;

// Must match Shader::MaxPointLights.
const int MAX_POINT_LIGHTS = 16;
const float PI = 3.14159265359;

struct PointLight
{
    vec3 position;
    vec3 color;
    float intensity;
};

uniform int pointLightCount;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

float DistributionGGX(vec3 N, vec3 H, float surfaceRoughness)
{
    float a = surfaceRoughness * surfaceRoughness;
    float a2 = a * a;
	
    float NdotH = max(dot(N, H), 0.0);
    float denominator = NdotH * NdotH * (a2 - 1.0) + 1.0;
	
    return a2 / (PI * denominator * denominator);
}

float GeometrySchlickGGX(float NdotV, float surfaceRoughness)
{
    float r = surfaceRoughness + 1.0;
    float k = r * r / 8.0;
	
    return NdotV / max(NdotV * (1.0 - k) + k, 0.000001);
}

vec3 FresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

vec3 GetSurfaceNormal()
{
    vec3 N = normalize(normal);
    if (!hasNormalMap)
    {
        return N;
    }

    vec3 tangentNormal = texture(normalMap, texUV).rgb * 2.0 - 1.0;
    // Images are loaded top-first, so OpenGL normal-map +Y opposes increasing V.
    tangentNormal.y = -tangentNormal.y;

    // Build a world-space tangent frame without requiring vertex tangents.
    vec3 dpdx = dFdx(pos);
    vec3 dpdy = dFdy(pos);
    vec2 duvdx = dFdx(texUV);
    vec2 duvdy = dFdy(texUV);
    float determinant = duvdx.x * duvdy.y - duvdx.y * duvdy.x;
    if (abs(determinant) < 0.0000000001)
    {
        return N;
    }

    vec3 T = (dpdx * duvdy.y - dpdy * duvdx.y) / determinant;
    T -= N * dot(N, T);
    if (dot(T, T) < 0.0000000001)
    {
        return N;
    }
    T = normalize(T);

    // Preserve the handedness of mirrored UVs.
    vec3 increasingV = (dpdy * duvdx.x - dpdx * duvdy.x) / determinant;
    vec3 B = cross(N, T);
    B *= dot(B, increasingV) < 0.0 ? -1.0 : 1.0;

    return normalize(mat3(T, B, N) * tangentNormal);
}

void main()
{
    vec4 diffuse = texture(diffuseMap, texUV);
    vec3 albedo = pow(diffuse.rgb, vec3(2.2));
	
    // Material maps contain linear data. Only albedo needs gamma decoding.
    float surfaceMetallic = clamp(hasMetallicMap ? texture(metallicMap, texUV).r : metallic, 0.0, 1.0);
    float surfaceRoughness = clamp(hasRoughnessMap ? texture(roughnessMap, texUV).r : roughness, 0.05, 1.0);
	
    vec3 N = GetSurfaceNormal();
    vec3 viewOffset = cameraPos - pos;
    vec3 V = viewOffset / max(length(viewOffset), 0.0001);
    float NdotV = max(dot(N, V), 0.0);
	
    vec3 F0 = mix(vec3(0.04), albedo, surfaceMetallic);
    vec3 lighting = vec3(0.0);

    int count = clamp(pointLightCount, 0, MAX_POINT_LIGHTS);
    for (int i = 0; i < count; i++)
    {
        vec3 lightOffset = pointLights[i].position - pos;
        float distanceSquared = max(dot(lightOffset, lightOffset), 0.0001);
        vec3 L = lightOffset / sqrt(distanceSquared);
        float NdotL = max(dot(N, L), 0.0);
        if (NdotL <= 0.0)
        {
            continue;
        }

        vec3 halfVector = V + L;
        vec3 H = halfVector / max(length(halfVector), 0.0001);
        vec3 radiance = max(pointLights[i].color, vec3(0.0)) * max(pointLights[i].intensity, 0.0) / distanceSquared;

        float distribution = DistributionGGX(N, H, surfaceRoughness);
        float geometry = GeometrySchlickGGX(NdotV, surfaceRoughness) * GeometrySchlickGGX(NdotL, surfaceRoughness);
		
        vec3 fresnel = FresnelSchlick(max(dot(H, V), 0.0), F0);
        vec3 specular = distribution * geometry * fresnel / max(4.0 * NdotV * NdotL, 0.0001);
        vec3 diffuseWeight = (vec3(1.0) - fresnel) * (1.0 - surfaceMetallic);
		
        lighting += (diffuseWeight * albedo / PI + specular) * radiance * NdotL;
    }

    vec3 result = 0.03 * albedo + lighting;
    result = result / (result + vec3(1.0));
    result = pow(result, vec3(1.0 / 2.2));
	
    FragColor = vec4(result, diffuse.a);
}
