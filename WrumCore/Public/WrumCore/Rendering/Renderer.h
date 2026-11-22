#pragma once

#include <unordered_map>
#include <vector>

#include "Framebuffer.h"
#include "Material.h"
#include "Mesh/Mesh.h"
#include "WrumCore/Rendering/Vertex.h"
#include "WrumCore/World/BigusEntitus.h"

namespace Wrum
{
    class Camera;
}

namespace Wrum
{
    class Renderer
    {
    public:
        Renderer(Camera* camera) : _camera(camera)
        {
        }

        // TODO: remove
        void DrawMesh(Mesh& mesh, Material& material, const Mat4& transform);
        void AddMeshToRender(ResourceID mesh, ResourceID material, const Mat4& transform);
        void AddEntityToRender(const Entity& entity);
        void Render();

        std::vector<PointLight> PointLights;
        
    private:
        
        struct Batch
        {
            ResourceID MeshResource;
            ResourceID MaterialResource;
            std::vector<Mat4> Transforms;
        };
        struct BatchKey
        {
            ResourceID MeshResource;
            ResourceID MaterialResource;
            bool operator==(const BatchKey& other) const
            {
                return MeshResource == other.MeshResource && MaterialResource == other.MaterialResource;
            }
        };
        struct BatchKeyHash
        {
            size_t operator()(const BatchKey& key) const
            {
                const size_t mesh = std::hash<ResourceID>{}(key.MeshResource);
                const size_t material = std::hash<ResourceID>{}(key.MaterialResource);
                return mesh ^ (material + 0x9e3779b9 + (mesh << 6) + (mesh >> 2));
            }
        };

        std::vector<Batch> _batches;
        std::unordered_map<BatchKey, size_t, BatchKeyHash> _batchLookup;
        Camera* _camera;
    };
}
